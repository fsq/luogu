#include "stdc++.h"

int n, tot;
int a[100], vis[100];

bool dfs(int nb, const int full, int cur, int beg) {
    if (nb==0)
        return true;
    else {
    	if (cur==full) return dfs(nb-1, full, 0, 0);
    	if (cur + a[n-1] > full) return false;
        for (int j,i=beg; i<n; i=j) 
            if (!vis[i] && cur+a[i]<=full) {
            	vis[i] = true;
            	if (dfs(nb, full, cur+a[i], i+1)) return true;
            	vis[i] = false;
            	if (cur+a[i]==full || cur==0) return false;
                for (j=i; j<n && a[j]==a[i]; ++j);	
            } else 
                j = i + 1;
        return false;
    }
}


int main() {
    int mn = 100, mx = 0, _n;
    cin >> _n;

    for (int x,i=0; i<_n; ++i) {
        cin >> x;
        if (x <= 50) {
            a[n++] = x;
            tot += x;
            mx = max(mx, x);
            mn = min(mn, x);
        }
    }

    sort(a, a+n, greater<int>());
    for (int nb=tot/mn; nb>=2; --nb)
        if (tot%nb==0 && dfs(nb, tot/nb, 0, 0)) {
            cout << tot / nb << endl;
            return 0;
        }
    cout << tot << endl;
    return 0;
}