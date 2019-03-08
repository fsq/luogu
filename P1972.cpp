#include "stdc++.h"

int n, m;
int fst[1000007], s[1000007];
VI q[500007];

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
	cin >> n;
	VI a(n+1);
	REP(i, 1, n) cin >> a[i];
	cin >> m;
	
	FOR(i, m) {
		q[i].resize(3);
		cin >> q[i][0] >> q[i][1];
		q[i][2] = i;
	}

	VI ans(m);
	sort(q, q+m, greater<VI>());

	for (int j=n,i=0; i<m; ) {
		for (; j >= q[i][0]; --j) {
			if (fst[a[j]]) add(fst[a[j]], -1);
			add(fst[a[j]]=j, 1);
		}
		
		for (int l=q[i][0]; i<m && q[i][0]==l; ++i) 
			ans[q[i][2]] = sum(q[i][1]);
	}

	FOREACH(x, ans) cout << x << endl;
	return 0;
}