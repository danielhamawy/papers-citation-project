#include<iostream>
using namespace std;

struct node{
    int data;
    node* next;
};
class Linkedqueue{
    private:
        node *queuefront;
        node *queuerear;
    public:
        Linkedqueue(){
            queuefront = NULL;
            queuerear = NULL;
        }
        void initializequeue(){
            node *temp;
            while(queuefront != NULL){
                temp = queuefront;
                queuefront = queuefront->next;
                delete temp;
            }
            queuerear = NULL;
        }
        bool isempty(){return queuefront == NULL;}
        bool ifull(){return false;}
        int front(){
            if(queuefront == NULL){
                cout<<"list is empty"<<endl;
                return -1;
            }
            return queuefront->data;
        }
        int back(){
            if(queuefront == NULL){
                cout<<"list is empty"<<endl;
                return -1;
            }
            return queuerear->data;
        }
        void enqueue(int num){
            node* newnode = new node;
            newnode->data = num;
            newnode->next = NULL;
            if(queuerear == NULL){
                queuefront = newnode;
                queuerear = newnode;
            }else{
                queuerear->next = newnode;
                queuerear = newnode;
            }
        }  
        void dequeue(){
            if(queuefront == NULL){
                cout<<"list is empty"<<endl;
                return;
            }
            node* temp = queuefront;
            queuefront = queuefront->next;
            delete temp;
            if(queuefront == NULL){
                queuerear = NULL;
            }
        }
        ~Linkedqueue(){
            node* temp;
            while(queuefront != NULL){
                temp = queuefront;
                queuefront = queuefront->next;
                delete temp;
            }
        }  
};
int main() {
    Linkedqueue q;

    // enqueue some values
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    // check front and back
    cout << "Front: " << q.front() << endl;  // 10
    cout << "Back: " << q.back() << endl;    // 40

    // dequeue and check again
    q.dequeue();
    cout << "Front after dequeue: " << q.front() << endl;  // 20

    // dequeue all
    q.dequeue();
    q.dequeue();
    q.dequeue();

    // try to dequeue from empty
    q.dequeue();  // should print "list is empty"

    return 0;
}