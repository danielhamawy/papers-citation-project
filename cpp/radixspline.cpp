#include<iostream>
using namespace std;
struct RadixSpline {
    int* splineKeys;
    int* splinePos;
    int numSpline;
    int* radixTable;
    int shift;
    int minKey;
    int maxError;
};

void buildSpline(const int* a, int n, int k, RadixSpline& rs) {
    rs.numSpline = (n - 1) / k + 1;
    if ((n - 1) % k != 0) rs.numSpline++;

    rs.splineKeys = new int[rs.numSpline];
    rs.splinePos = new int[rs.numSpline];

    int count = 0;
    for (int i = 0; i < n; i += k) {
        rs.splineKeys[count] = a[i];
        rs.splinePos[count] = i;
        count++;
    }
    if ((n - 1) % k != 0) {
        rs.splineKeys[count] = a[n - 1];
        rs.splinePos[count] = n - 1;
        count++;
    }
    rs.numSpline = count;
}
void buildRadixTable(const int* a, int n, int r, RadixSpline& rs) {
    rs.minKey = a[0];
    long long range = (long long)a[n - 1] - a[0];
    int buckets = 1 << r;

    rs.shift = 0;
    while ((range >> rs.shift) >= buckets) rs.shift++;

    rs.radixTable = new int[buckets + 1];

    int s = 0;
    for (int p = 0; p <= buckets; p++) {
        while (s < rs.numSpline &&
               (((long long)rs.splineKeys[s] - rs.minKey) >> rs.shift) < p)
            s++;
        rs.radixTable[p] = s;
    }
}
int rsPredict(const RadixSpline& rs, int key) {  //called rs because it takes the predict position function in learned sort
    int last = rs.numSpline - 1;
    if (key <= rs.splineKeys[0]) return rs.splinePos[0];
    if (key >= rs.splineKeys[last]) return rs.splinePos[last];

    long long p = ((long long)key - rs.minKey) >> rs.shift;
    int lo = rs.radixTable[p] - 1;
    int hi = rs.radixTable[p + 1] - 1;
    if (lo < 0) lo = 0;
    if (hi > last - 1) hi = last - 1;

    int i = lo;
    while (i < hi && rs.splineKeys[i + 1] <= key) i++;

    long long k1 = rs.splineKeys[i], k2 = rs.splineKeys[i + 1];
    long long p1 = rs.splinePos[i], p2 = rs.splinePos[i + 1];
    if (k2 == k1) return (int)p1;
    return (int)(p1 + (key - k1) * (p2 - p1) / (k2 - k1));
}
void rsComputeMaxError(const int* a, int n, RadixSpline& rs) {
    int maxErr = 0;
    for (int i = 0; i < n; i++) {
        int pred = rsPredict(rs, a[i]);
        int err = pred - i;
        if (err < 0) err = -err;
        if (err > maxErr) maxErr = err;
    }
    rs.maxError = maxErr;
}
int radixSplineSearch(const int* a, int n, const RadixSpline& rs, int target) {
    if (n <= 0) return -1;

    int pred = rsPredict(rs, target);

    int low = pred - rs.maxError;
    int high = pred + rs.maxError;
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
