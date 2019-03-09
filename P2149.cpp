#include "stdc++.h"

const int N = 1507;
const int INF = 0x3f3f3f3f;
int n, m, s1, t1, s2, t2;
int a[N][N], ind[N];

VI shortest_path(int s) {
    VI d(n+1, INF), vis(n+1);
    d[s] = 0;
    FOR(_t, n) {
        int u, mind=INF;
        REP(i, 1, n)
            if (!vis[i] && d[i]<mind) 
                tie(mind, u) = {d[i], i};

        if (mind == INF) break;
        vis[u] = true;
        REP(j, 1, n)
            if (!vis[j] && d[u]+a[u][j]<d[j])
                d[j] = d[u] + a[u][j];
    }
    return d;
}

int solve(int s1, int t1, int s2, int t2,
          CVI& ds1, CVI& dt1, CVI& ds2, CVI& dt2) {
    VVI e(n+1);
    REP(u, 1, n) REP(v, 1, n)
        if (ds1[u]+a[u][v]+dt1[v]==ds1[t1] && ds2[u]+a[u][v]+dt2[v]==ds2[t2]) {
            e[u].PB(v);
            ++ind[v];
        }

    VI d(n+1);
    queue<int> q;
    REP_IF(i, 1, n, !ind[i]) q.push(i);
    while (!q.empty()) {
        POP(x, q);
        FOREACH(y, e[x]) {
            d[y] = max(d[y], d[x]+a[x][y]);
            if (--ind[y] == 0)
                q.push(y);
        }
    }
    return *max_element(ALL(d));
}

int main() {
    MEMSET0(ind);
    MEMSET(a, 0x3f);
    cin >> n >> m >> s1 >> t1 >> s2 >> t2;
    for (int u,v,l,i=0; i<m; ++i) {
        cin >> u >> v >> l;
        a[u][v] = a[v][u] = l;
    }

    VI ds1 = shortest_path(s1), ds2 = shortest_path(s2),
       dt1 = shortest_path(t1), dt2 = shortest_path(t2);

    cout << max(solve(s1, t1, s2, t2, ds1, dt1, ds2, dt2), 
                solve(s1, t1, t2, s2, ds1, dt1, dt2, ds2));

    return 0;
}