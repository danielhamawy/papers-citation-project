#include<iostream>
#include<random>
#include<chrono>
#include"histtreesearch.cpp"
#include"learnedbinarysearch.cpp"
#include"radixspline.cpp"
#include"pdqsort.cpp"
#include"samplesort.cpp"
#include"twinarraysort.cpp"
#include"myswap.cpp"
using namespace std;

const int N = 1000000;
void makeNearlySorted(int* data, int n) {
    for (int i = 0; i < n; i++) {
        data[i] = i * 1000;
    }

    mt19937 gen(12346);
    uniform_int_distribution<int> pos(0, n - 1);

    for (int k = 0; k < n / 100; k++) {
        int a = pos(gen);
        int b = pos(gen);
        int tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    }
}

void makeReverseSorted(int* data, int n) {
    for (int i = 0; i < n; i++) {
        data[i] = (n - i) * 1000;
    }
}

void makeDuplicates(int* data, int n) {
    mt19937 gen(12347);
    uniform_int_distribution<int> dist(0, 999);

    for (int i = 0; i < n; i++) {
        data[i] = dist(gen);
    }
}  
void makeRandom(int* data, int n) {
    mt19937 gen(12345);
    uniform_int_distribution<int> dist(0, 1000000000);

    for (int i = 0; i < n; i++) {
        data[i] = dist(gen);
    }
}

bool isSorted(int* data, int n) {
    for (int i = 1; i < n; i++) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    return true;
}
typedef void (*SortFunc)(int*, int, int);

double timeSort(SortFunc sortFunc, int* original, int* work, int n) {
    for (int i = 0; i < n; i++) {
        work[i] = original[i];
    }

    auto t1 = chrono::steady_clock::now();
    sortFunc(work, 0, n - 1);
    auto t2 = chrono::steady_clock::now();

    if (!isSorted(work, n)) {
        cout << "ERROR: output is not sorted!" << endl;
    }

    return chrono::duration<double, milli>(t2 - t1).count();
}

const int Q = 100000;

void makeQueries(int* data, int n, int* queries, int q) {
    mt19937 gen(12348);
    uniform_int_distribution<int> pos(0, n - 1);

    for (int i = 0; i < q; i++) {
        queries[i] = data[pos(gen)];
    }
}
void twinsortWrapper(int* arr, int start, int end) {
    twinsort(arr + start, end - start + 1);
}
void learnedsortWrapper(int* arr, int start, int end) {
    learnedsort(arr + start, end - start + 1);
}

void testSorting() {
    int* original = new int[N];
    int* work = new int[N];

    makeRandom(original, N);
    cout << "function random: " << timeSort(learnedsortWrapper, original, work, N) << " ms" << endl;

    makeNearlySorted(original, N);
    cout << "function nearly sorted: " << timeSort(learnedsortWrapper, original, work, N) << " ms" << endl;

    makeReverseSorted(original, N);
    cout << "function reverse sorted: " << timeSort(learnedsortWrapper, original, work, N) << " ms" << endl;

    makeDuplicates(original, N);
    cout << "function duplicates: " << timeSort(learnedsortWrapper, original, work, N) << " ms" << endl;

    delete[] original;
    delete[] work;
}
void testRadixSpline() {
    int* data = new int[N];
    int* queries = new int[Q];

    makeRandom(data, N);
    pdqsort(data, 0, N - 1);
    makeQueries(data, N, queries, Q);

    RadixSpline rs;
    auto b1 = chrono::steady_clock::now();
    buildSpline(data, N, 32, rs);
    buildRadixTable(data, N, 16, rs);
    rsComputeMaxError(data, N, rs);
    auto b2 = chrono::steady_clock::now();

    int correct = 0;
    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < Q; i++) {
        int idx = radixSplineSearch(data, N, rs, queries[i]);
        if (idx != -1 && data[idx] == queries[i]) {
            correct++;
        }
    }
    auto t2 = chrono::steady_clock::now();

    double buildMs = chrono::duration<double, milli>(b2 - b1).count();
    double totalNs = chrono::duration<double, nano>(t2 - t1).count();
    cout << "radix spline build: " << buildMs << " ms" << endl;
    cout << "radix spline search: " << totalNs / Q << " ns per query" << endl;
    cout << "spline points: " << rs.numSpline << endl;
    cout << "max error: " << rs.maxError << endl;
    cout << "correct: " << correct << " of " << Q << endl;

    delete[] rs.splineKeys;
    delete[] rs.splinePos;
    delete[] rs.radixTable;
    delete[] data;
    delete[] queries;
}

void testLearnedSearch() {
    int* data = new int[N];
    int* queries = new int[Q];

    makeRandom(data, N);
    pdqsort(data, 0, N - 1);
    makeQueries(data, N, queries, Q);

    auto b1 = chrono::steady_clock::now();
linearmodel m = trainmodel(data, N);
computeMaxError(data, N, m);
auto b2 = chrono::steady_clock::now();

double buildMs = chrono::duration<double, milli>(b2 - b1).count();


    int correct = 0;
    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < Q; i++) {
        int idx =learnedBinarySearch(data, N, m, queries[i]);
        if (idx != -1 && data[idx] == queries[i]) {
            correct++;
        }
    }
    auto t2 = chrono::steady_clock::now();

    double totalNs = chrono::duration<double, nano>(t2 - t1).count();
    cout << "learned search build: " << buildMs << " ms" << endl;
    cout << "search is : " << totalNs / Q << " ns per query" << endl;
    cout << "max error: " << m.maxerror << endl;
    cout << "correct: " << correct << " of " << Q << endl;

    delete[] data;
    delete[] queries;
}
void testHistTree() {
    int* data = new int[N];
    int* queries = new int[Q];

    makeRandom(data, N);
    pdqsort(data, 0, N - 1);
    makeQueries(data, N, queries, Q);

    auto b1 = chrono::steady_clock::now();
    HistNode* root = buildNode(data, 0, N, data[0], data[N - 1]);
    auto b2 = chrono::steady_clock::now();

    int correct = 0;
    auto t1 = chrono::steady_clock::now();
    for (int i = 0; i < Q; i++) {
        int idx = histTreeSearch(root, data, queries[i]);
        if (idx != -1 && data[idx] == queries[i]) {
            correct++;
        }
    }
    auto t2 = chrono::steady_clock::now();

    double buildMs = chrono::duration<double, milli>(b2 - b1).count();
    double totalNs = chrono::duration<double, nano>(t2 - t1).count();
    cout << "hist-tree build: " << buildMs << " ms" << endl;
    cout << "hist-tree search: " << totalNs / Q << " ns per query" << endl;
    cout << "correct: " << correct << " of " << Q << endl;

    freeTree(root);
    delete[] data;
    delete[] queries;
}

int main() {
    //testSorting();
    testLearnedSearch();
    //testRadixSpline();
    //testHistTree();

    return 0;
}