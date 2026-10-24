#include <iostream>
using namespace std;
class Queuearray{
    private:
        int *list;
        int queuefront;
        int queuerear;
        int maxqueuesize;
        int count;
    public:
        Queuearray(int size){
            maxqueuesize = size;
            list = new int[maxqueuesize];
            queuefront = 0;
            queuerear = 0;          //if Linear array queuerear = -1
            count = 0;
        }
        bool isempty(){return count == 0;}
        bool isfull(){return count == maxqueuesize;}

        void initializequeue(){
            queuefront = 0;
            queuerear = 0;          //also -1 if LA
            count = 0;
        }
        int front(){
            if(count == 0){
                cout<<"queue is empty"<<endl;
                return -1;
            }
            return list[queuefront];
        }
        int back(){
            if(count == 0){
                cout<<"queue is empty"<<endl;
                return -1;
            }
            return list[(queuerear-1 + maxqueuesize) % maxqueuesize];
            //if LA: return list[queuerear]
        }
        void enqueue(int item){
            if(count == maxqueuesize){
                cout<<"queue is full"<<endl;
                return ;
            }
            list[queuerear] = item;
            queuerear = (queuerear +1) % maxqueuesize;
            count++;
            //for LA after the if it would be:
            //queuerear++;
            //list[queuerear] = item;
            //count++;
        }
        void dequeue(){
            if(count == 0){
                cout<<"queue is empty"<<endl;
                return ;
            }
            queuefront = (queuefront+1)%maxqueuesize;
            //if LA: queuefront++
            count--;
        }
        ~Queuearray(){
            delete[]list;
        }
};
int main() {
    Queuearray q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;
    q.dequeue();
    cout << "Front after dequeue: " << q.front() << endl;
    return 0;
}