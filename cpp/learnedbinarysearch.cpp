#include<iostream>
using namespace std;
struct linearmodel{
    double slope;
    double intercept;
    int maxerror;
};
linearmodel trainmodel(const int* a, int n){
    linearmodel m;
    m.slope = 0;
    m.intercept = 0;
    m.maxerror = 0;
    if(n<=0)return m;
    double meanX = 0;
    double meanY = (n - 1) / 2.0;
    for (int i = 0; i < n; i++)
        meanX += a[i];
    meanX /= n;
    double num = 0, den = 0;
    for (int i = 0; i < n; i++) {
        double dx = a[i] - meanX;
        double dy = i - meanY;
        num += dx * dy;
        den += dx * dx;
    }
    if (den == 0) {
        m.slope = 0;
        m.intercept = meanY;
        return m;
    }
    m.slope = num / den;
    m.intercept = meanY - m.slope * meanX;
    return m;
}
int predictPosition(const linearmodel& m, int key, int n) {
    double p = m.slope * key + m.intercept;
    if (p < 0) return 0;
    if (p > n - 1) return n - 1;
    return (int)(p + 0.5);
}

void computeMaxError(const int* a, int n, linearmodel& m) {
    int maxErr = 0;
    for (int i = 0; i < n; i++) {
        int pred = predictPosition(m, a[i], n);
        int err = pred - i;
        if (err < 0) err = -err;
        if (err > maxErr) maxErr = err;
    }
    m.maxerror = maxErr;
}
int learnedBinarySearch(const int* a, int n, const linearmodel& m, int target) {
    if (n <= 0) return -1;

    int pred = predictPosition(m, target, n);

    int low = pred - m.maxerror;
    int high = pred + m.maxerror;
    if (low < 0) low = 0;
    if (high > n - 1) high = n - 1;

    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target) {
            result = mid;
            high = mid - 1;
        }   
        else if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return result;
}