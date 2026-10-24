#include<iostream>
#include "pdqsort.cpp"
using namespace std;

void insertionSort(int* arr,int lo,int hi){
    for(int i = lo+1;i<=hi;i++){
        int key = arr[i];
        int j = i-1;
        while(j>=lo && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
void fallbacksort(int* arr,int lo, int hi);
int choosesplitters(int* arr,int n,int* splitters,int Ssize){
    if(Ssize<2 || Ssize>n) return 0;
    int* sample = new int[Ssize];
    int step = n/Ssize;
    for(int i = 0;i<Ssize;i++){
        sample[i] = arr[i*step];
    }
    fallbacksort(sample,0,Ssize-1);
    int m = 0;
    for(int i = 0;i<Ssize;i++){
        if(m==0||sample[i] !=splitters[m-1]){
            splitters[m++] = sample[i];
        }
    }
    delete []sample;
    return m;
}
int findbucket(int x, int* splitters, int m) {
    int lo = 0, hi =m;
    while (lo<hi) {
        int mid = lo + (hi-lo)/2;
        if (splitters[mid] < x) lo = mid + 1;
        else hi = mid;
    }
    if (lo < m && splitters[lo] == x) return 2 * lo + 1;
    return 2 * lo;
}
const int SMALL_BUCKET = 32;

void learnedsort(int* arr, int n) {
    int sampleSize = n / 100;
    if (n < 1000) {
        fallbacksort(arr, 0, n - 1);
        return;
    }
    int* splitters = new int[sampleSize];
    int m = choosesplitters(arr, n, splitters, sampleSize);
    int numBuckets = 2 * m + 1;
    int* ids   = new int[n];
    int* start = new int[numBuckets + 1]();
    int* pos   = new int[numBuckets];
    int* aux   = new int[n];
    for (int i = 0; i < n; i++) {
        ids[i] = findbucket(arr[i], splitters, m);
        start[ids[i] + 1]++;
    }
    for (int b = 0; b < numBuckets; b++){
        start[b + 1] += start[b];
    }
    for (int b = 0; b < numBuckets; b++){
        pos[b] = start[b];
    }
    for (int i = 0; i < n; i++){
        aux[pos[ids[i]]++] = arr[i];
    }
    for (int i = 0; i < n; i++){
        arr[i] = aux[i];
    }
    for (int b = 0; b < numBuckets; b += 2) {
        int lo = start[b];
        int hi = start[b + 1] - 1;
        int size = hi - lo + 1;
        if (size <= 1) continue;
        if (size <= SMALL_BUCKET) insertionSort(arr, lo, hi);
        else fallbacksort(arr, lo, hi);
    }

    delete[] splitters;
    delete[] ids;
    delete[] start;
    delete[] pos;
    delete[] aux;
}
void fallbacksort(int* arr, int lo, int hi) {
    pdqsort(arr, lo, hi);
}