#include <iostream>
#include <cassert>
using namespace std;
template<class Type>
struct nodetype{
    Type info;
    nodetype<Type> *link;
};
template<class Type>
class linkedstack{
    private:
    nodetype<Type> *stacktop;
    copystack(const linkedstack& otherstack){
        if(otherstack.stacktop == NULL){
            stacktop = NULL;
            return;
        }
        nodetype *newnode = new nodetype;
        newnode->info = otherstack.stacktop->info;
        newnode->link = NULL;
        stacktop = newnode;

        nodetype* curr = otherstack.stacktop->link;
        nodetype* last = stacktop;
        while(curr != NULL){
            nodetype* temp = new nodetype;
            temp->info = curr->info;
            temp->link = NULL;
            last->link = temp;
            last = temp;
            curr = curr->link;
        }
    }
    public:
    Type top ()const{
        assert(stacktop != NULL);
        return stacktop->info;
    }
    void push(const Type& newelement){
        nodetype<Type> *newnode = new nodetype<Type>;
        newnode -> info = newelement;
        newnode-> link = stacktop;
        stacktop = newnode;
    }
    void pop(){
        nodetype <Type> *temp;
        if(stacktop!=NULL){
            temp = stacktop;
            stacktop = stacktop->link;
            delete temp;
        }else
        cout<<"empty list"<<endl;
    }
    bool isfull()const{return false;}
    bool isempty()const{return (stacktop == NULL );}
    linkedstack(){
        stacktop = NULL;
    }
    ~linkedstack(){
        initializestack();
    }
    void initializestack(){
        nodetype<Type> *temp;
        while(stacktop!=NULL){
            temp = stacktop;
            stacktop = stacktop->link;
            delete temp;
        }
    }
    // copy constructor
    linkedstack(const linkedstack<Type>& otherstack) {
        stacktop = NULL;
        copystack(otherstack);
    }


    // assignment operator
    const linkedstack<Type>& operator=(const linkedstack<Type>& otherstack) {
        if (this != &otherstack) {
            initializestack();  // delete current nodes
            copystack(otherstack);
        }return *this;
    }
};
int main() {
    linkedstack<int> mystack;

    mystack.push(10);
    mystack.push(20);
    mystack.push(30);

    cout << "Top: " << mystack.top() << endl; 

    mystack.pop();
    cout << "Top after pop: " << mystack.top() << endl; 
    cout << "Is empty: " << mystack.isempty() << endl; 

    cout << "Is full: " << mystack.isfull() << endl; 
    mystack.pop();
    mystack.pop();

    cout << "Is empty now: " << mystack.isempty() << endl; 

    mystack.pop(); 
    return 0;
}