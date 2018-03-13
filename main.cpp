#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

// Matrix Mi has sizes (N[i]xN[i+1]).
int N[1001];
int M;
int D[1001][1001];
int scopes[1001][1001];
int matrix_index = 1;

int chain_multiply(int st, int end) {
    if (st == end)
        return 0;
    // If I already have the answer!
    if (D[st][end] != 0) {
        return D[st][end];
    }
    int min_value = 100000000;
    for (int k = st; k <= end - 1; ++k) {
        int candidate = chain_multiply(st, k) +
                        chain_multiply(k + 1, end) +
                        N[st] * N[k] * N[end];
        if (min_value > candidate)
            min_value = candidate;
    }
    D[st][end] = min_value;
    return min_value;
}

void chain_multiply_iterative()
{
    for(int size = 2; size <= M; size++) {
        for(int i = 1; i <= M + 1 - size; i++) {
            int j = i + size - 1;
            int min_value = 100000000;
            for(int k = i; k <= j - 1; k++) {
                if(D[i][k] + D[k+1][j] + N[i - 1] * N[k] * N[j] < min_value) {
                    min_value = D[i][k] + D[k+1][j] + N[i - 1] * N[k] * N[j];
                    scopes[i][j] = k;
                }
            }
            D[i][j] = min_value;
        }
    }
}

void print(int start, int end) {
    if(start == end) {
        cout << matrix_index++;
        return;
    }

    cout << "(";
    print(start, scopes[start][end]);
    print(scopes[start][end] + 1, end);
    cout << ")";
}

int main() {
    cin >> M;
    for (int i = 0; i <= M; ++i) {
        cin >> N[i];
    }
    chain_multiply_iterative();
    cout << D[1][M] << endl;
    print(1, M);
    cout << endl;
    return 0;
}

/*
5 17
2 4 6 8 10
*/
