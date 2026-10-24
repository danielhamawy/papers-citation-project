#pragma once
#include <iostream>
#include<cmath>

using namespace std;
void insertionsort(int arr[], int start, int end);
void heapsort(int arr[], int start, int end);
void scramble(int arr[], int start, int end);
int  median(const int arr[], int a, int b, int c);
void pdqloop(int arr[], int start, int end, int limit);
int  ninther(const int arr[], int start, int end);

void pdqsort(int arr[],int start,int end){
    if(start >= end){return;}   //base case
    int limit = (int)log2(end-start + 1)*2; //bad partitions allowed
    pdqloop(arr,start,end,limit);
}
void pdqloop(int arr[],int start,int end,int limit){
    int len = end-start+1;
    if(len<=24){
        insertionsort(arr,start,end);
        return;
    }
    if(limit == 0){
        heapsort(arr,start,end);
        return;
    }
    int mid = start+len/2;
    int pindex;
    if(len>128)pindex = ninther(arr,start,end);
    else pindex = median(arr,start,mid,end);
    swap(arr[pindex],arr[start]);
    int pivot = arr[start];
    int left = start+1,right = end;
    while(left<= right){
        while(arr[left]<pivot){
            left++;
        }while(arr[right]>pivot){
            right--;
        }
        if(left>=right){break;}
        swap(arr[left],arr[right]);
        left++;
        right--;
    }
    swap(arr[start],arr[right]);
    int Ppos = right;
    int leftsize = Ppos-start;
    int rightsize = end-Ppos;
    bool unbalanced = (leftsize<len/8)||(rightsize<len/8);
    int bad_allowed = limit;

    if(unbalanced){
        bad_allowed--;
        if(leftsize >= 8)  scramble(arr, start, Ppos-1);
        if(rightsize >= 8) scramble(arr, Ppos+1, end);
    }

    pdqloop(arr, start, Ppos - 1, bad_allowed);
    pdqloop(arr, Ppos + 1, end, bad_allowed);
}
void insertionsort(int arr[],int start,int end){
    for(int i = start+1;i<=end;i++){
        int key = arr[i];
        int j = i-1;
        while(j>=start && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;

    }
}
int median(const int arr[], int a, int b, int c) {
    if ((arr[a] <= arr[b] && arr[b] <= arr[c]) || (arr[c] <= arr[b] &&arr[b] <= arr[a])) {
        return b;
    }
    if ((arr[b] <= arr[a] && arr[a] <= arr[c]) || (arr[c] <= arr[a] && arr[a] <= arr[b])) {
        return a;
    }
    return c;
}
void siftDown(int a[], int start, int n, int i) {
    while (true) {
        int l = 2 * i + 1, r = l + 1, big = i;
        if (l < n && a[start + l] > a[start + big]) big = l;
        if (r < n && a[start + r] > a[start + big]) big = r;
        if (big == i) return;
        swap(a[start + i], a[start + big]);
        i = big;
    }
}

void heapsort(int arr[], int start, int end) {
    int n = end - start + 1;
    for (int i = n / 2 - 1; i >= 0; i--) siftDown(arr, start, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[start], arr[start + i]);
        siftDown(arr, start, i, 0);
    }
}
void scramble(int arr[], int start, int end) {  
    int len = end - start + 1;
    swap(arr[start], arr[start + len / 4]);
    swap(arr[end],   arr[end - len / 4]);
    swap(arr[start + len / 2 - 1], arr[start + len / 2 + 1]);
}
int ninther(const int arr[],int start,int end){
    int len = end-start+1;
    int mid = start+len/2;
    int step = len/8; //only called when len>128
    int m1 = median(arr, start,start + step, start + 2 * step);
    int m2 = median(arr, mid - step,mid,mid + step);
    int m3 = median(arr, end - 2*step, end - step,end);
    return median(arr,m1,m2,m3);
}