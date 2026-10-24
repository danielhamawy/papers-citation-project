#include<iostream>
#include <string>
using namespace std;
class BankAccount{
    private:
        string name;
        double sBalance;
    public:
        BankAccount(string name,double sBalance){
            this-> name = name;
            this-> sBalance = sBalance;
        }
        double withdraw(double change){
            if(change>sBalance){
                cout<<"insufficient funds!\n";
            }else{
            sBalance -= change;
            }
            return sBalance;
        }
        double deposit(double change){
            sBalance += change;
            return sBalance;
        }
        void display(){
            cout<<"Account name: "<<name<<endl;
            cout<<"Remaining balance: "<<sBalance<<endl;
        }
};

int main(){
    system("cls");
    string name;
    double balance,amount;
    int x;
    cout<<"enter the name of the bank account\n";
    cin>>name;
    cout<<"enter balance\n";
    cin>>balance;
    
    BankAccount num1(name,balance);
    num1.display();
    
    cout<<"Click 1 to withdraw, Click 2 to deposit, Click 3 to check account only\n";
    cin>>x;
    if (x == 1){
        cout<<"Enter amount to withdraw\n";
        cin>>amount;
        num1.withdraw(amount);
    }else if(x == 2){
        cout<<"Enter amount to deposit\n";
        cin>>amount;
        num1.deposit(amount);
    }else{
        cout<<"Have a nice day!\n";
    }
    num1.display();
}