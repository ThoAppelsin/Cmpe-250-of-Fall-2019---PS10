#include <iostream>
using namespace std;

int numOfCalls1 = 0;
int numOfCalls2 = 0;
int numOfCalls3 = 0;

long long fibonacci_recursive(int n ) {
    numOfCalls1++;
    //cout << "Called fibonacci_recursive(" << n << ")" << endl;
    if( n <= 1 )
        return n;
    else
        return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

const int MAX = 1000;

/* function for nth Fibonacci number */
long long fibonacci_memoizing(int n) {
    static long long lookup[MAX] = {0, 1};

    numOfCalls2++;
    //cout << "Called fibonacci_memoizing(" << n << ")" << endl;
    if (n <= 1)
        return n;
    else if (lookup[n] != 0)
        return lookup[n];
    else
        return lookup[n] = fibonacci_memoizing(n - 1) + fibonacci_memoizing(n - 2);
}

long long fibonacci_tabulating(int n) {
    static long long lookup[MAX] = {0, 1};
    static int max_n = 1;

    numOfCalls3++;
    if(n <= max_n)
        return lookup[n];

    for (int i = 2; i <= n; i++) {
        lookup[i] = lookup[i - 1] + lookup[i - 2];
    }
    max_n = n;
    return lookup[n];
}

int main() {
    int n = 30;
    long long result1 = fibonacci_recursive(n);
    cout << "fibonacci_recursive(" << n << "): " << result1 << " Number of calls: " << numOfCalls1 << endl;

    long long result2 = fibonacci_memoizing(n);
    cout << "fibonacci_memoizing(" << n << "): " << result2 << " Number of calls: " << numOfCalls2 << endl;

    result2 = fibonacci_memoizing(n);
    cout << "fibonacci_memoizing(" << n << "): " << result2 << " Number of calls: " << numOfCalls2 << endl;

    long long result3 = fibonacci_tabulating(n);
    cout << "fibonacci_tabulating(" << n << "): " << result3 << " Number of calls: " << numOfCalls3 << endl;

    return 0;
}