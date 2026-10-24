#include<iostream>
using namespace std;

void merge(int* arr, int*aux,int left,int mid,int right){
    int i = left;
    int j = mid+1;
    int k = left;
    while(i<=mid && j<=right){
        if(arr[i]<= arr[j]){
            aux[k++] = arr[i++];
        }else aux[k++] = arr[j++];
    }while (i<=mid){  //right half ran out first so copy whats left of the left half
    aux[k++] = arr[i++];
    }
    while(j<=right){
    aux[k++] = arr[j++];
    }
    for(int i = left;i<=right;i++){
        arr[i] = aux[i];
    }
}
void twinsort(int* arr,int n){
    if(n<=1) return;
    int* aux = new int[n];
    int* runend = new int[n];
    while(true){
        int runcount = 0;
        int i = 0;
        while(i<n){
            while(i+1<n && arr[i]<=arr[i+1]){
                i++;
            }
            runend[runcount++] = i;
            i++;
        }
        if (runcount <= 1) break;
        int left = 0;
        for(int r = 0;r+1<runcount;r+=2){
            int mid = runend[r];
            int right = runend[r + 1];
            merge(arr, aux, left, mid, right);
            left = right + 1;
        }
    }
    delete[] aux;
    delete[] runend;
}