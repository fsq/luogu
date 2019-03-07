#include "stdc++.h"

int n, m, nq;
VVI g, e;
vector<vector<PII>> f; // node, dis
vector<PII> q;
VI fa, dp;
const int INF = 0x3f3f3f3f;

void init() {
	cin >> n >> m;

	g = VVI(m, VI(3));

	FOR(i, m) 
		cin >> g[i][1] >> g[i][2] >> g[i][0];

	cin >> nq;
	q.resize(nq);

	FOR(i, nq)
		cin >> q[i].first >> q[i].second;

	f = vector(n+1, vector<PII>(15, {-1, INF}));
}

int find(int x) {
	return fa[x]==x ? x : fa[x]=find(fa[x]);
}

void mst() {
	e.resize(n+1);
	sort(ALL(g), greater<VII>());
	fa.resize(n+1);
	iota(ALL(fa), 0);
	for (auto& eg : g) 
		if (find(eg[1]) != find(eg[2])) {
			fa[eg[1]] = fa[eg[2]];
			e[eg[1]].PB({eg[2], eg[0]});
			e[eg[2]].PB({eg[1], eg[0]});
		}
}

void dfs(VI& vis, int x, int d) {
	vis[x] = true;
	dp[x] = d;
	for (auto& pr : e[x])
		if (!vis[pr.first]) {
			f[pr.first][0] = {x, pr.second};
			dfs(vis, y, d+1);
		}
}

void dfs() {
	VI vis(n+1);
	dp.resize(n+1);
	REP(i, 1, n) 
		if (!vis[i])
			dfs(vis, i, 1);
}

void init_lca() {
	REP(k, 1, 14)
		REP(i, 1, n)
			if (f[i][k-1].first!=-1 && f[f[i][k-1].first].first!=-1) 
				f[i][k] = {f[f[i][k-1].first].first, 
							f[i][k-1].second + f[f[i][k-1].first].second};
}

int lca(int x, int y) {
	if (find(x) != find(y)) return -1;
	if (dp[x] < dp[y]) swap(x, y);

	int ans = 0;

	for (int k=14; k>=0 && dp[x]>dp[y]; --k) 
		if (dp[x]-(1<<k) >= dp[y]) {
			ans += f[x][k].second;
			x = f[x][k].first;
		}

	if (x==y) return ans;

	for (int k=14; k>=0; --k)
		if (f[x][k].first != f[y][k].first) {
			ans += f[x][k].second + f[y][k].second;
			x = f[x][k].first;
			y = f[y][k].first;
		}

	return ans + f[x][0] + f[y][0];
}

int main(int argc, char const *argv[]) {

	init(); 

	mst();

	dfs();

	init_lca();

	for (auto qr : q) 
		cout << lca(qr.first, qr.second) << endl;


	return 0;
}