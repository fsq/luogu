#include "stdc++.h"

int n;
VI e[103], et[103], vis(103), fa(103), ind(103), oud(103);
int a[103][103];

void init() {
	scanf("%d", &n);
	for (int x,i=1; i<=n; ++i) 
		for (scanf("%d", &x); x; scanf("%d", &x)) {
			e[i].PB(x);
			et[x].PB(i);
		}
}

void dfs(int x, VI e[], VI& vis, VI& a) {
	vis[x] = true;
	FOREACH(y, e[x])
		if (!vis[y])
			dfs(y, e, vis, a);
	a.PB(x);
}

int main() { 
	init();	

	VI ord;
	REP_IF(i, 1, n, !vis[i])
		dfs(i, e, vis, ord);
	FILL0(vis);

	ROFI(i, ord)
		if (!vis[ord[i]]) {
			VI cc;
			dfs(ord[i], et, vis, cc);
			FORI(i, cc)
				fa[cc[i]] = cc[0];
		}

	MEMSET0(a);
	int ans1 = 0, ans2 = 0, cc = 0;
	REP(i, 1, n)
		FOREACH(y, e[i])
			if (fa[i]!=fa[y] && !a[fa[i]][fa[y]]) {
				a[fa[i]][fa[y]] = 1;
				++oud[fa[i]];
				++ind[fa[y]];
			}

	REP_IF(i, 1, n, fa[i]==i) {
		++cc;
		ans1 += ind[i]==0;
		ans2 += oud[i]==0;
	}
	cout << ans1 << '\n' << (cc==1 ? 0 : max(ans1, ans2)) << endl;
	return 0;
}