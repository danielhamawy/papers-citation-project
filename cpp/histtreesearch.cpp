#include<iostream>
using namespace std;
const int B = 32;
const int Leafsize = 64;

struct HistNode{
    int lo,hi,start,end;
    HistNode** children;
};
HistNode* buildNode(int* arr, int start, int end,int lo,int hi){
    HistNode* node = new HistNode;
    node->lo = lo;
    node->hi = hi;
    node->start = start;
    node->end = end;
    node->children = nullptr;
    if(end-start<=Leafsize||lo==hi)return node;
    long long range =(long long) hi-lo+1;
    int binkeys[B];
    for (int b = 0; b < B; b++) binkeys[b] = 0;
    for (int i = start; i < end; i++) {
        int b = (int)(((long long)arr[i] - lo) * B / range);
        binkeys[b]++;
    }
    node->children = new HistNode*[B];
    int pos = start;
    for (int b = 0; b < B; b++) {
        if (binkeys[b] == 0) {
            node->children[b] = nullptr;
            continue;
        }
        int binLo = lo + (int)((b * range + B - 1) / B);
        int binHi = lo +(int) (((b + 1) * range + B - 1) / B - 1);
        node->children[b] = buildNode(arr, pos, pos + binkeys[b], binLo,binHi);
        pos += binkeys[b];
    }
    return node;
}
int searchLeaf(int* arr, int start, int end, int key) {
    int l = start, r = end;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] < key) l = mid + 1;
        else r = mid;
    }
    if (l < end && arr[l] == key) return l;
    return -1;
}
int histTreeSearch(HistNode* root, int* arr, int key) {
    HistNode* node = root;
    while (node->children != nullptr) {
        if (key < node->lo || key > node->hi) return -1;
        long long range = (long long)node->hi - node->lo + 1;
        int b = (int)(((long long)key - node->lo) * B / range);
        node = node->children[b];
        if (node == nullptr) return -1;
    }
    if (key < node->lo || key > node->hi) return -1;
    return searchLeaf(arr, node->start, node->end, key);
}
void freeTree(HistNode* node) {
    if (node == nullptr) return;
    if (node->children != nullptr) {
        for (int b = 0; b < B; b++) freeTree(node->children[b]);
        delete[] node->children;
    }
    delete node;
}

