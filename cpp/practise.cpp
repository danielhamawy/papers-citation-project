#include <iostream>
#include <cassert>
using namespace std;

struct node{
    int info;
    node *link;
};
class linkedstack{
    private:
        node *stacktop;
        void copystack(const linkedstack& otherstack){
            if(otherstack.stacktop == NULL){
                stacktop = NULL;
                return;
            }
            node *newnode = new node;
            newnode->info = otherstack.stacktop->info;
            newnode->link = NULL;
            stacktop = newnode;

            node *current = otherstack.stacktop->link;
            node *last = stacktop;
            while(current != NULL){
                node *temp = new node;
                temp->info = current->info;
                temp->link = NULL;
                last->link = temp;
                last = temp;
                current = current->link;
            }
        }
    public:
        linkedstack(){
            stacktop = NULL;
        }
        void initializestack(){
            node *temp;
            while(stacktop!=NULL){
                temp = stacktop;
                stacktop = stacktop->link;
                delete temp;
            }
        }
        bool isempty()const{
            return stacktop == NULL;
        }
        ~linkedstack(){
            initializestack();
        }
        linkedstack(const linkedtstack& otherstack){
            stacktop = NULL;
            copystack(otherstack);
        }
        linkedstack& operator=(const linkedstack& otherstack){
            if(this != &otherstack){
                initializestack();
                copystack(otherstack);
            }
            return *this;
        }
        void pop(){
            node *temp;
            if(stacktop != NULL){
                temp = stacktop;
                stacktop = stacktop->link;
                delete temp;
            }else{
                cout<<"list is empty"<<endl;
            }
        }
        void push(int val){
            node *newnode = new node;
            newnode->info = val;
            newnode->link = stacktop;
            stacktop = newnode;
        }
        int top()const{
            assert(stacktop!=NULL);
            return stacktop->info;
        }
};