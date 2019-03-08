#include "stdc++.h"

int n, m;
int ind[1007];
int e[1007][1007];

int main() {
	cin >> n >> m;

	MEMSET0(ind);
	MEMSET0(e);

	for (int x,j,i=0; i<m; ++i) {
		cin >> j;
		VI a, b;
		while (j--) {
			cin >> x;
			if (!a.empty() && x!=a.back()+1)
 				REP(k, a.back()+1, x-1) b.PB(k);
			a.PB(x);
		}
		FOREACH(x, a) FOREACH(y, b) 
			if (!e[x][y]) {
				++ind[y];
				e[x][y] = 1;
			}
	}

	VI f(n+1, -1);
	queue<int> q;
	REP_IF(i, 1, n, !ind[i]) {
		q.push(i);
		f[i] = 1;
	}

	while (!q.empty()) {
		int x=q.front(); q.pop();
		REP_IF(y, 1, n, e[x][y]) {
			f[y] = max(f[y], f[x]+1);
			if (--ind[y] == 0)
				q.push(y);
		}
	}

	cout << *max_element(ALL(f)) << endl;

	return 0;
}