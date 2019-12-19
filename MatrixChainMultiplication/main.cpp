#include <iostream>
#include <climits>


using namespace std;

// Matrix A[i] has dimension (dims[i-1] x dims[i]) for i = 1..n
int MatrixChainOrder(int dims[], int**splits, int n) {

    /* For simplicity of the program, one extra row and one
     extra column are allocated in min_cost[][].  0th row and 0th
     column of min_cost[][] are not used */
    int min_cost[n][n];

    /*
     * min_cost[i,j] = Minimum number of scalar multiplications needed
     * to compute the product matrix A[i] x A[i+1] x ... x A[j] where
     * dimension of A[i] is (dims[i-1] x dims[i])
     *
     * splits[i,j] = k (an index between i and j-1)
     * Index to split to attain the min_cost[i,j]. In other words,
     * the product A[i] x A[i+1] x ... x A[j] should be grouped as
     * (A[i] x A[i+1] x ... x A[k]) x (A[k+1] x ... x A[j-1] x A[j])
     * to minimize the number of scalar multiplications needed
     *
     * */

    // min_cost is zero when multiplying one matrix.
    for (int i = 1; i < n; i++)
        min_cost[i][i] = 0;

    // Call A[i] x ... x A[j] a matrix chain of length j-i+1.
    // L is chain length.
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            min_cost[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                // cost = Minimum number of scalar multiplications needed to compute
                // the product matrix (A[i] x ... x A[k]) x (A[k+1] x ... x A[j])
                int cost = min_cost[i][k] + min_cost[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < min_cost[i][j]) {
                    min_cost[i][j] = cost;
                    splits[i][j] = k;
                }
            }
        }
    }

    return min_cost[1][n - 1];
}

void printOptimalParens(int**splits, int i, int j) {
    if (i == j)
        cout << "A" << i;
    else {
        cout << "(";
        printOptimalParens(splits, i, splits[i][j]);
        printOptimalParens(splits, splits[i][j] + 1, j);
        cout << ")";
    }

}

int main() {

    // Dimensions of the matrices
    int dims[] = { 10,100,5,50,80,2 };

    int size = sizeof(dims) / sizeof(dims[0]);

    int **splits;
    splits = new int *[size];
    for (int i = 0; i < size; i++)
        splits[i] = new int[size];

    cout << "Minimum number of multiplications is "
         << MatrixChainOrder(dims, splits, size) << endl;

    cout << "Optimal parenthesization:" << endl;
    printOptimalParens(splits, 1, size - 1);

    return 0;
}
