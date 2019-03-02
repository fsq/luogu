#include "stdc++.h"

map<char, multiset<char>> e;

void dfs(string& path, char now) {
    auto& en = e[now];
    while (!en.empty()) {
        char nxt = *en.begin();
        en.erase(en.begin());
        e[nxt].erase(now);
        dfs(path, nxt);
    }
    path += now;
}

int main() {
    int n;
    cin >> n;    
    FOR(i, n) {
        string s;
        cin >> s;
        e[s[0]].insert(s[1]);
        e[s[1]].insert(s[0]);
    }

    int odd = 0, cand = e.begin()->first;
    for (auto it=begin(e); it!=end(e); ++it) 
        if ((it->second.size()&1) && (++odd==1))
            cand = it->first;

    if (!(odd==0 || odd==2)) {
        cout << "No Solution\n";
        return 0;
    }

    string ans;
    dfs(ans, cand);
    reverse(ALL(ans));
    cout << ans << endl;

    return 0;
}