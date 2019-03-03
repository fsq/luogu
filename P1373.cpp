#include "stdc++.h"

int f[803][803][2][17], a[803][803];
int n, m, k;
const int M = 1'000'000'007;

int main() {
    cin >> n >> m >> k;
    ++k;
    
    REP(i, 1, n) REP(j, 1, m) cin >> a[i][j];

    REP(i, 1, n) REP(j, 1, m) {
        FOR(x, k) {
            f[i][j][1][x] = (f[i-1][j][0][(x+a[i][j]) % k] + 
                            f[i][j-1][0][(x+a[i][j]) % k]) % M;
            f[i][j][0][x] = (f[i-1][j][1][(x-a[i][j]+k) % k] + 
                            f[i][j-1][1][(x-a[i][j]+k) % k]) % M;
        }
        f[i][j][0][a[i][j]] = (1 + f[i][j][0][a[i][j]]) % M;
    }
    
    int ans = 0;
    REP(i, 1, n) REP(j, 1, m) 
        ans = (ans + f[i][j][1][0]) % M;
    cout << ans << endl;
    return 0;
}