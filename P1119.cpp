#include "stdc++.h"

const int N = 205;
const int INF = 0x3f3f3f3f;

int n, m;
int f[N][N];
int up[N];

int main() {
    ios::sync_with_stdio(false);

    MEMSET(f, 0x3f);
    MEMSET(up, false);
    cin >> n >> m;
    
    VI fix(n);
    FOR(i, n) {
        f[i][i] = 0;
        cin >> fix[i];
    }
    for (int x,y,d,i=0; i<m; ++i) {
        cin >> x >> y >> d;
        f[x][y] = f[y][x] = d;
    }

    cin >> m;
    queue<VI> q;
    for (int x,y,t,i=0; i<m; ++i) {
        cin >> x >> y >> t;
        q.push({x, y, t});
    }

    for (int j,i=0; q.size() && i<=n; i=j) {
        while (q.size() && (i==n || q.front()[2]<fix[i])) {
            int dis = f[q.front()[0]][q.front()[1]];
            cout << (up[q.front()[0]] && up[q.front()[1]] && dis!=INF ?
                     dis : -1) << endl;
            q.pop();
        }
        for (j=i; j<n && fix[j]==fix[i]; ++j) {
            up[j] = true;
            FOR(x, n) FOR(y, n) 
                f[x][y] = min(f[x][y], f[x][j]+f[j][y]);
        }
    }

    return 0;
}