#include "stdc++.h"

int main() {
    ios::sync_with_stdio(false);
    VI a;
    for (int x; cin>>x; a.PB(x));

    VI f, g; // inc/dec
    FOREACH(x, a) {
        int i = lower_bound(ALL(f), x) - f.begin();
        if (i==f.size())
            f.PB(x);
        else
            f[i] = x;
        i = upper_bound(ALL(g), x, greater<int>()) - g.begin();
        if (i==g.size())
            g.PB(x);
        else
            g[i] = x;
    }
    cout << g.size() << '\n' << f.size() << endl;
    return 0;
}