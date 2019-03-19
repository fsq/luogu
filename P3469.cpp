#include "stdc++.h"

const int N = 100007;
int n, m, cnt=0;
int vis[N];
LL sz[N], ans[N];
VI e[N];

int dfs(int x, int fa) {
	vis[x] = ++cnt;
	int hi = vis[x];
	VLL a;
	FOREACH(y, e[x])
		if (!vis[y]) {
			if (int thi=dfs(y, x); thi >= vis[x])
				a.PB(sz[y]);
			else 
				hi = min(hi, thi);
			sz[x] += sz[y];
		} else if (y != fa)
			hi = min(hi, vis[y]);
	LL orphan = accumulate(ALL(a), 0ll);
	ans[x] = (LL)(n-1-orphan) * orphan + n - 1;
	FOREACH(o, a) {
		ans[x] += (orphan-o) * o;
		orphan -= o;
	}
	ans[x] <<= 1;
	++sz[x];
	return hi;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int x,y,i=0; i<m; ++i) {
		cin >> x >> y;
		e[x].PB(y);
		e[y].PB(x);
	}	
	MEMSET0(vis);
	MEMSET0(sz);
	MEMSET0(ans);

	dfs(1, -1);
	REP(i, 1, n) cout << ans[i] << '\n';
	return 0;
}