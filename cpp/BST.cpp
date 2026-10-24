#include<iostream>
using namespace std;

enum ordertype{PRE_ORDER,IN_ORDER,POST_ORDER};
struct node{
    int info;
    node *left;
    node *right;
};
class treetype{
    private:
        node* root;
        Quetype preque;
        Quetype inque;
        Quetype postque;
    public:
        treetype(){
            root = NULL;
        }
        ~treetype(){
            destroy(root);
        }
        void destroy(node*& tree){
            if(tree != NULL){
                destroy(tree->left);
                destroy(tree->right);
                delete tree;
            }
        }
        treetype(const treetype& originaltree){
            copytree(root,originaltree.root);
        }
        void copytree(node*& copy,node* originaltree){
            if(originaltree == NULL){
                copy = NULL;
            }else{
                copy = new node;
                copy->info = originaltree->info;
                copytree(copy->left,originaltree->left);
                copytree(copy->right,originaltree->right);
            }
        }
        void operator=(const treetype& originaltree){
            if(this == &originaltree){
                return;
            }
            makeEmpty();
            copytree(root,originaltree.root);
        }
        void makeEmpty(){
            destroy(root);
            root = NULL;
        }
        bool isempty(){return root == NULL;}
        bool isfull(){
            node* temp = new node;
            if(temp == NULL){
                return true;
            }else{
                delete temp;
                return false;
            }
        }//tree is never full this is just for safety
        int countnodes(node* tree){
            if(tree == NULL){
                return 0;
            }else{
                return countnodes(tree->left)+countnodes(tree->right)+1;
            }
        }
        int numberofnodes(){
            return countnodes(root);
        }
        void retrieveitem(int& item,bool& found){
            retrieve(root,item,found);
        }
        void retrieve(node* tree,int& item,bool& found){
            if(tree == NULL){
                found = false;
            }else if(item<tree->info){
                retrieve(tree->left,item,found);
            }else if(item>tree->info){
                retrieve(tree->right,item,found);
            }else{
                item = tree->info;
                found = true;
            }
        }
        void insert(node*& tree, int item){
            if(tree == NULL){
                tree = new node;
                tree->left = NULL;
                tree->right = NULL;
                tree->info = item;
            }else if(item<tree->info){
                insert(tree->left,item);
            }else if(item>tree->info){
                insert(tree->right,item);
            }
        }
        void insertitem(int item){
            insert(root,item);
        }
        //delete's 3 cases
        void getpredecessor(node* tree,int& data){   //this gets the largest value
            while(tree->right != NULL){
                tree = tree->right;
            }
            data = tree->info;
        }
        void Delete(node*& tree,int item){
            if(item<tree->info)
                Delete(tree->left,item);
            else if(item>tree->info)
                Delete(tree->right,item);
            else
                deletenode(tree);
        }
        void deletenode(node*& tree){
            int data;
            node* tempptr;
            tempptr = tree;
            if(tree->left == NULL){
                tree = tree->right;
                delete tempptr;
            }else if(tree->right == NULL){
                tree = tree->left;
                delete tempptr;
            }else{
                getpredecessor(tree->left,data);
                tree->info = data;
                Delete(tree->left,data);
            }
        }
        void deleteitem(int item){
            Delete(root,item);
        }
        //reset tree
        void preorder(node* tree, Quetype& preQue){
            if(tree != NULL){
                preQue.enqueue(tree->info);
                preorder(tree->left,preque);
                preorder(tree->right,preque);
            }
        }
        void inorder(node* tree, Quetype& inque){
            if(tree != NULL){
                inorder(tree->left,inque);
                inque.enqueue(tree->info);
                inorder(tree->right,inque);
            }
        }
        void postorder(node* tree,Quetype& postque){
            if(tree != NULL){
                postorder(tree->left,postque);
                postorder(tree->right,postque);
                postque.enqueue(tree->info);
            }
        }
        void resettree(ordertype order){
            switch(order){
                case PRE_ORDER:
                    preque.makeEmpty();
                    preorder(root,preque);
                    break;
                case IN_ORDER:
                    inque.makeEmpty();
                    inorder(root,inque);
                    break;
                case POST_ORDER:
                    postque.makeEmpty();
                    postorder(root,postque);
                    break;
            }
        }
        void getnextitem(int& item,ordertype order,bool& finished){
            finished = false;
            switch(order){
                case PRE_ORDER:
                    preque.dequeue(item);
                    if(preque.isempty())
                        finished = true;
                    break;
                case IN_ORDER:
                    inque.dequeue(item);
                    if(inque.isempty())
                        finished = true;
                    break; 
                case POST_ORDER:
                    postque.dequeue(item);
                    if(postque.isempty())
                        finished = true;
                    break;               
            }
        }
        void print(node* tree){
            if(tree != NULL){
                print(tree->left);
                cout<<tree->info<<" ";
                print(tree->right);
            }
        }
        void printtree(){
            print(root);
            cout<<endl;
        }
};