#include <iostream>
using namespace std;

const int MAX = 100;

void multiplyMatricesRec(
    int mat1[][MAX], int r1, int c1,
    int mat2[][MAX], int r2, int c2,
    int result[][MAX], int rRes, int cRes,
    int n) 
{
    if (n == 1) {
        result[rRes][cRes] += mat1[r1][c1] * mat2[r2][c2];
        return;
    }

    int half = n / 2;

    multiplyMatricesRec(mat1, r1, c1,        mat2, r2, c2,        result, rRes, cRes,        half);
    multiplyMatricesRec(mat1, r1, c1 + half, mat2, r2 + half, c2, result, rRes, cRes,        half);

    multiplyMatricesRec(mat1, r1, c1,        mat2, r2, c2 + half, result, rRes, cRes + half, half);
    multiplyMatricesRec(mat1, r1, c1 + half, mat2, r2 + half, c2 + half, result, rRes, cRes + half, half);

    multiplyMatricesRec(mat1, r1 + half, c1, mat2, r2, c2,        result, rRes + half, cRes, half);
    multiplyMatricesRec(mat1, r1 + half, c1 + half, mat2, r2 + half, c2, result, rRes + half, cRes, half);

    multiplyMatricesRec(mat1, r1 + half, c1, mat2, r2, c2 + half, result, rRes + half, cRes + half, half);
    multiplyMatricesRec(mat1, r1 + half, c1 + half, mat2, r2 + half, c2 + half, result, rRes + half, cRes + half, half);
}

int main() {
    int mat1[MAX][MAX] = {
        {1, 2},
        {3, 4}
    };

    int mat2[MAX][MAX] = {
        {5, 6},
        {7, 8}
    };

    int N = 2; 

    
    int result[MAX][MAX] = {0};

    
    multiplyMatricesRec(
        mat1, 0, 0,
        mat2, 0, 0,
        result, 0, 0,
        N
    );

    cout << "Resultant Matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}