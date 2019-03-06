#include "stdc++.h"

const int M = 9901;

int main() {
	int n, k;
	cin >> n >> k;
	VVI f(n+1, VI(k+1));
	REP(j, 1, k) f[1][j] = 1;
	REP(i, 2, n) 
		REP(j, 2, k) 
			REP(x, 1, i-2)
				f[i][j] = (f[i][j] + f[x][j-1]*f[i-x-1][j-1]) % M;
		
	
	cout << (f[n][k]-f[n][k-1]+M)%M << endl;
	return 0;
}