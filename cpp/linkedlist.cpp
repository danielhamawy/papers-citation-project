#include<iostream>
using namespace std;

struct node{
    int data;
    node* next;
};
class linkedlist{
    private:
        node* head;
    public:
        linkedlist(){
            head = NULL;
        }
        ~linkedlist(){
            node* nodeptr;
            node* nextnode;
            nodeptr = head;
            while (nodeptr != NULL){
                nextnode = nodeptr->next;
                delete nodeptr;
                nodeptr = nextnode;
            }
            head = NULL;
        }
        void displaylist() const{
            if(!head){
                cout<<"list is empty"<<endl;
                return;
            }
            node* nodeptr = head;
            cout<<"list: ";
            while (nodeptr != NULL){
                cout<<nodeptr->data;
                if(nodeptr->next != NULL){
                    cout<<"->";
                }
                nodeptr = nodeptr->next;
            }
            cout<<"->NULL"<<endl;
        }
        void appendnode(double num){
            node* nodeptr;
            node* newnode;
            newnode = new node;
            newnode->data = num;
            newnode->next = NULL;
            if(!head){
                head = newnode;
            }else{
                nodeptr = head;
                while(nodeptr->next != NULL){
                    nodeptr = nodeptr->next;
                }
                nodeptr->next = newnode;
            }
            cout<<num<<" added to list"<<endl;
        }
        void insertnode(double num){
            node* nodeptr;
            node* newnode;
            node* previousnode = NULL;
            newnode = new node;
            newnode->next = NULL;
            newnode->data = num;
            if(!head){
                head = newnode;
                newnode->next = NULL;
            }else{
                nodeptr = head;
                previousnode = NULL;
                while(nodeptr != NULL && nodeptr->data<num){
                    previousnode = nodeptr;
                    nodeptr = nodeptr->next;
                }
                if(previousnode == NULL){
                    head = newnode;
                    newnode->next = nodeptr;
                }else{
                    newnode->next = nodeptr;
                    previousnode->next = newnode;
                }
            }
            cout<<num<<" inserted in sorted position"<<endl;
        }
        void insertNode(int pos, double val) {
            node* newnode = new node;
            newnode->data = val;
            newnode->next = NULL;
            // count list size
            int size = 0;
            node* nodeptr = head;
            while (nodeptr != NULL) {
                size++;
                nodeptr = nodeptr->next;
            }
            // pos doesn't exist
            if (pos > size - 1) {
                cout << "No effect as pos:" << pos << " doesn't exist" << endl;
                delete newnode;
                return;
            }
            // insert at head (pos == 0)
            if (pos == 0) {
                newnode->next = head;
                head = newnode;
                return;
            }
            // insert at position
            nodeptr = head;
            for (int i = 0; i < pos - 1; i++) {
                nodeptr = nodeptr->next;
            }
            newnode->next = nodeptr->next;
            nodeptr->next = newnode;
        }
        int findNodeByVal(double val) {
            node* nodeptr = head;
            int pos = 0;
            while (nodeptr != NULL) {
                if (nodeptr->data == val)
                    return pos;
                nodeptr = nodeptr->next;
                pos++;
            }
            return -1;
        }
        int findNodeByPos(int pos) {
            node* nodeptr = head;
            int current = 0;
            while (nodeptr != NULL) {
                if (current == pos)
                    return nodeptr->data;
                nodeptr = nodeptr->next;
                current++;
            }
            return -1;
        }
        void deletenode(double num){
            node* nodeptr;
            node* previousnode = NULL;
            if(!head){
                cout<<"list is empty"<<endl;
                return;
            }
            if(head->data == num){
                nodeptr = head->next;
                delete head;
                head = nodeptr;
                cout<<num<<" deleted"<<endl;
                return;
            }
            nodeptr = head;
            previousnode = NULL;
            while(nodeptr != NULL && nodeptr->data != num){
                previousnode = nodeptr;
                nodeptr = nodeptr->next;
            }
            if(nodeptr != NULL){
                previousnode->next = nodeptr->next;
                delete nodeptr;
                nodeptr = NULL;
                cout<<num<<" is deleted"<<endl;
            }else{
                cout<<"num is not found"<<endl;
            }
        }
        //copy constructor
        linkedlist(const linkedlist& other){
            head = NULL;
            node* nodeptr = other.head;
            while(nodeptr != NULL){
                appendnode(nodeptr->data);
                nodeptr = nodeptr->next;
            }
        }
        //assignment operator
        linkedlist& operator=(const linkedlist& other){
            if(this == &other){
                return *this;
            }
            node* nodeptr = head;
            while(nodeptr != NULL){
                node* nextnode = nodeptr->next;
                delete nodeptr;
                nodeptr = nextnode;
            }
            head = NULL;
            nodeptr = other.head;
            while(nodeptr != NULL){
                appendnode(nodeptr->data);
                nodeptr = nodeptr->next;
            }
            return *this;
        }

};
int main(){
    linkedlist list;

    // displaylist - empty
    list.displaylist();

    // appendnode
    list.appendnode(3);
    list.appendnode(4);
    list.appendnode(9);
    list.displaylist();          // 3->4->9->NULL

    // insertnode (sorted)
    list.insertnode(1);
    list.insertnode(6);
    list.displaylist();          // 1->3->4->6->9->NULL

    // insertNode by position
    list.insertNode(0, 6);       // insert at head
    list.displaylist();          // 6->1->3->4->6->9->NULL
    list.insertNode(3, 8);       // insert at pos 3
    list.displaylist();          // 6->1->3->8->4->6->9->NULL
    list.insertNode(99, 11);     // pos doesn't exist
    list.displaylist();          // no change

    // findNodeByVal
    cout << "find val 8:  pos = " << list.findNodeByVal(8)  << endl;  // found
    cout << "find val 99: pos = " << list.findNodeByVal(99) << endl;  // -1

    // findNodeByPos
    cout << "val at pos 0: " << list.findNodeByPos(0) << endl;   // 6
    cout << "val at pos 3: " << list.findNodeByPos(3) << endl;   // 8
    cout << "val at pos 99: " << list.findNodeByPos(99) << endl; // -1

    // deletenode
    list.deletenode(8);          // middle
    list.deletenode(6);          // head
    list.deletenode(9);          // tail
    list.deletenode(99);         // not found
    list.displaylist();

    return 0;
}