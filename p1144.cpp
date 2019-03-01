#include "stdc++.h"

int n, m;
const int M = 100003;

int main() {
	cin >> n >> m;

	VI vis(n+1), dp(n+1), f(n+1);
	VVI e(n+1);

	for (int x,y,i=0; i<m; ++i) {
		cin >> x >> y;
		e[x].PB(y), e[y].PB(x);
	}

	f[1] = 1; 
	vis[1] = true;
	dp[1] = 1;
	queue<int> q;
	q.push(1);

	while (!q.empty()) {
		int x=q.front(); q.pop();
		for (auto y : e[x]) 
			if (!vis[y]) {
				vis[y] = true;
				q.push(y);
				f[y] = f[x];
				dp[y] = dp[x] + 1;
			} else if (dp[y] == dp[x]+1) 
				f[y] = (f[x] + f[y]) % M;
	}
	REP(i, 1, n) 
		cout << f[i] << endl;

	return 0;
}