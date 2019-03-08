#include "stdc++.h"

int n, m, nq;
VVI g;
vector<vector<PII>> e, f; // node, dis
vector<PII> q;
VI fa, dp;
const int INF = 0x3f3f3f3f;

void init() {
	cin >> n >> m;

	g = VVI(m, VI(3));
	FOR(i, m) cin >> g[i][1] >> g[i][2] >> g[i][0];

	cin >> nq;
	q.resize(nq);
	FOR(i, nq) cin >> q[i].F >> q[i].S;

	f = vector<vector<PII>>(n+1, vector<PII>(15, {-1, INF}));
}

int find(int x) {
	return fa[x]==x ? x : fa[x]=find(fa[x]);
}

void mst() {
	e.resize(n+1);
	sort(ALL(g), greater<VI>());
	fa.resize(n+1);
	iota(ALL(fa), 0);
	for (auto& eg : g) 
		if (find(eg[1]) != find(eg[2])) {
			fa[fa[eg[1]]] = fa[eg[2]];
			e[eg[1]].PB({eg[2], eg[0]});
			e[eg[2]].PB({eg[1], eg[0]});
		}
}

void dfs(VI& vis, int x, int d) {
	vis[x] = true;
	dp[x] = d;
	FOREACH(&pr, e[x])
		if (!vis[pr.F]) {
			f[pr.F][0] = {x, pr.S};
			dfs(vis, pr.F, d+1);
		}
}

void dfs() {
	VI vis(n+1);
	dp.resize(n+1);
	REP_IF(i, 1, n, !vis[i])
		dfs(vis, i, 1);
}

void init_lca() {
	REP(k, 1, 14)
		REP_IF(i, 1, n, f[i][k-1].F!=-1 && f[f[i][k-1].F][k-1].F!=-1) 
			f[i][k] = {f[f[i][k-1].F][k-1].F,
						min(f[i][k-1].S, f[f[i][k-1].F][k-1].S)};   
}

int lca(int x, int y) {
	if (find(x) != find(y)) return -1;
	if (dp[x] < dp[y]) swap(x, y);

	int ans = INF;

	for (int k=14; k>=0 && dp[x]>dp[y]; --k) 
		if (dp[x]-(1<<k) >= dp[y]) {
			ans = min(ans, f[x][k].S);
			x = f[x][k].F;
		}

	if (x==y) return ans;

	for (int k=14; k>=0; --k)
		if (f[x][k].F != f[y][k].F) {
			ans = min(ans, min(f[x][k].S, f[y][k].S));
			x = f[x][k].F;
			y = f[y][k].F;
		}

	return min(ans, min(f[x][0].S, f[y][0].S));
}

int main(int argc, char const *argv[]) {
	init(); 
	mst();
	dfs();
	init_lca();

	for (auto qr : q) 
		cout << lca(qr.F, qr.S) << endl;

	return 0;
}