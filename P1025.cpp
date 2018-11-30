#include "stdc++.h"

int main() {
    int n, k;
    cin >> n >> k;
    // O(n^2k)
    // vector<VVI> f(n+1, VVI(k+1, VI(n+1)));
    // f[1][1][1] = 1;
    // REP(i, 2, n)
    //     REP(j, 1, min(i, k))
    //         REP(k, 1, i)
    //             f[i][j][k] = f[i-1][j][k-1] + f[i-k][j-1][k];
    // int sum = 0;
    // REP(i, 1, n)
    //     sum += f[n][k][i];
    // cout << sum << endl;

    VVI f(n+1, VI(n+1));
    f[1][1] = 1;
    REP(i, 2, n)
        REP(j, 1, i)
            f[i][j] = f[i-1][j-1] + f[i-j][j];
    cout << f[n][k] << endl;
    return 0;
}