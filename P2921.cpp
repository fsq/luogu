#include "stdc++.h"

const int N = 10'0007;
int n, ans[N], fa[N], sz[N];
VI e[N], et[N];

void visit(int x, VI& vis) {
	vis[x] = true;
	if (fa[x]!=x || sz[x]>1) 
		ans[x] = sz[fa[x]];
	else {
		if (!vis[e[x][0]])
			visit(e[x][0], vis);
		ans[x] = ans[e[x][0]] + 1;
	}
}

void dfs(int x, VI e[], VI& vis, VI& a) {
	vis[x] = true;
	FOREACH_IF(y, e[x], !vis[y])
		dfs(y, e, vis, a);
	a.PB(x);
}

int main() {
	ios::sync_with_stdio(false);

	cin >> n;
	for (int x,i=1; i<=n; ++i) {
		cin >> x;
		e[i].PB(x);
		et[x].PB(i);
	}

	VI ord, vis(n+1);
	REP_IF(i, 1, n, !vis[i])
		dfs(i, e, vis, ord);

	reverse(ALL(ord));
	
	FILL0(vis);
	FOREACH_IF(x, ord, VI cc;!vis[x]) {
		dfs(x, et, vis, cc);
		FOREACH(y, cc) 
			++sz[fa[y] = x];
	}

	FILL0(vis);
	REP_IF(i, 1, n, !vis[i]) 
		visit(i, vis);

	REP(i, 1, n) cout << ans[i] << '\n';
	return 0;
}