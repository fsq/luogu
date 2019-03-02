#include "stdc++.h"

class Player {
public:
    int id, s, w;
    Player() {} 
};

bool cmp(const Player& a, const Player& b) {
    return a.s > b.s || (a.s==b.s && a.id<b.id);
}

int main() {
    int n, r, q;
    cin >> n >> r >> q;

    n <<= 1;

    vector<Player> a(n);
    for (int i=0; i<n; ++i) {
        cin >> a[i].s;
        a[i].id = i+1;
    }

    for (int w,i=0; i<n; ++i) 
        cin >> a[i].w;

    sort(ALL(a), cmp);
    vector<Player> win, lose;

    while (r--) {
        win.clear(), lose.clear();
        for (int i=0; i<n; i+=2) {
            Player& winner = a[i];
            Player& loser  = a[i+1];
            if (a[i+1].w > a[i].w) swap(winner, loser);
            ++winner.s;
            win.PB(move(winner));
            lose.PB(move(loser));
        }
        a.clear();
        for (int i=0, j=0; i<SZ(win) || j<SZ(lose); ) 
            if (i<SZ(win) && (j==SZ(lose) || cmp(win[i], lose[j]))) 
                a.PB(move(win[i++]));
            else 
                a.PB(move(lose[j++]));
    }
    cout << a[q-1].id << endl;

    return 0;
}