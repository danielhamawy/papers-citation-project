#include<iostream>
using namespace std;
void hanoi(int n,int from, int to, int spare){
    if(n == 0){
        return;
    }
    hanoi(n-1,from,spare,to);
    cout<<from<<" "<<to<<endl;
    hanoi(n-1,spare,to,from);
};

int main(){
    int n; cin>>n;
    long long k = (1LL<<n)-1;
    cout<<k<<endl;
    hanoi(n,1,3,2);
}