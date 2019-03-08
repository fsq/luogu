#include "stdc++.h"

int n, m;
int fst[1000007], s[500007];
pair<PII, int> q[500007];

inline int lowbit(int x) { return x & -x; }

void add(int x, int v) {
	for (; x<=n; x+=lowbit(x)) s[x] += v;
}

int sum(int x) {
	int ans = 0;
	for (; x; x-=lowbit(x)) ans += s[x];
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	VI a(n+1);
	REP(i, 1, n) cin >> a[i];
	cin >> m;
	
	FOR(i, m) {
		cin >> q[i].F.F >> q[i].F.S;
		q[i].S = i;
	}

	VI ans(m);
	sort(q, q+m, [](const pair<PII,int>& a, const pair<PII,int>& b) {
		return a.F.F > b.F.F;
	});

	for (int j=n,i=0; i<m; ) {
		for (; j >= q[i].F.F; --j) {
			if (fst[a[j]]) add(fst[a[j]], -1);
			add(fst[a[j]]=j, 1);
		}
		
		for (int l=q[i].F.F; i<m && q[i].F.F==l; ++i) 
			ans[q[i].S] = sum(q[i].F.S);
	}

	FOREACH(x, ans) cout << x << endl;
	return 0;
}