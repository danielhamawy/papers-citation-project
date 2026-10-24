#include <iostream>
using namespace std;

int interpolationBinarySearch(const int arr[], int n, int target) {
    if (n == 0 || target < arr[0] || target > arr[n - 1]) return -1;

    double ratio = static_cast<double>(target - arr[0]) / (arr[n - 1] - arr[0]);
    int pred = static_cast<int>(ratio * (n - 1));

    int window = 2;
    int low = (pred - window < 0) ? 0 : pred - window;
    int high = (pred + window >= n) ? n - 1 : pred + window;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}