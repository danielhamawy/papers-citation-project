#include<iostream>
#include<cassert>
using namespace std;

template<class Type>
class stacktype{
    private:
        int maxstacksize;
        int stacktop;
        Type *list;

        void copystack(const stacktype <Type>& otherstack){
            delete[] list;
            maxstacksize = otherstack.maxstacksize;
            stacktop = otherstack.stacktop;
            list = new Type[maxstacksize];
            for(int i = 0;i<stacktop;i++){
                list[i] = otherstack.list[i];
            }
        }
        void initializestack(){stacktop = 0;}
    public:
        bool isempty(){return(stacktop== 0);}
        bool isfull(){return(stacktop == maxstacksize);}

        stacktype(const stacktype <Type>& otherstack){
            list = nullptr;
            copystack(otherstack);
        }

        const stacktype <Type>& operator=(const stacktype<Type>& otherstack){   //assignment overload operator (=)
            if(this != &otherstack) {copystack (otherstack);}
            return *this;
        }
        stacktype(int stacksize = 100){
            if(stacksize<=0){maxstacksize = 100;}
            else maxstacksize = stacksize;
            stacktop = 0;
            list = new Type[maxstacksize];
        }
        ~stacktype(){
            delete[] list;
        }
        void push(const Type& newitem){
            if(stacktop != maxstacksize){
                list[stacktop] = newitem;
                stacktop++;
            }
        }
        Type top() const {
            assert(stacktop != 0);
            return list[stacktop - 1];
        }
        void pop(){
            if(stacktop != 0){stacktop--;}
        }
    };
    int main(){
    // test default constructor
    stacktype<int> s1;

    // test push & top
    s1.push(10);
    s1.push(20);
    s1.push(30);
    cout << "Top of s1: " << s1.top() << endl;        // 30

    // test isempty & isfull
    cout << "s1 empty? " << s1.isempty() << endl;     // 0 (false)
    cout << "s1 full?  " << s1.isfull()  << endl;     // 0 (false)

    // test pop
    s1.pop();
    cout << "After pop, top of s1: " << s1.top() << endl;  // 20

    // test copy constructor
    stacktype<int> s2(s1);
    cout << "Top of s2 (copy of s1): " << s2.top() << endl;  // 20

    // test assignment operator
    stacktype<int> s3;
    s3.push(99);
    s3 = s1;
    cout << "Top of s3 (assigned from s1): " << s3.top() << endl;  // 20

    // test custom stacksize constructor
    stacktype<int> s4(3);
    s4.push(1);
    s4.push(2);
    s4.push(3);
    cout << "s4 full? " << s4.isfull() << endl;       // 1 (true)
    s4.push(4);                                        // silently does nothing
    cout << "Top of s4 after overpush: " << s4.top() << endl;  // 3

    // test isempty on fresh stack
    stacktype<int> s5;
    cout << "s5 empty? " << s5.isempty() << endl;     // 1 (true)

    // test pop until empty
    s1.pop();  // removes 20
    cout << "s1 empty after popping all? " << s1.isempty() << endl;  // 1 (true)

    return 0;
}