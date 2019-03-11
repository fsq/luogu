#include "stdc++.h"

const int N = 100007;
int a[N], n, M, m;

struct Node {
	int l, r;
	LL a, b, s; // a*x+b
} t[4*N+3];

inline int LS(int x) { return x << 1; }
inline int RS(int x) { return x << 1 | 1; }

inline void refresh(int x) {
	t[x].s = (t[LS(x)].s + t[RS(x)].s) % M;
}

inline void apply(int x, LL p, LL q) {
	t[x].s = (t[x].s * p + q * (t[x].r-t[x].l+1)) % M;
	t[x].a = t[x].a * p % M;
	t[x].b = (t[x].b * p + q) % M;
}

inline void push(int x) {
	apply(LS(x), t[x].a, t[x].b);
	apply(RS(x), t[x].a, t[x].b);
	t[x].a = 1, t[x].b = 0;
}

void build(int x, int l, int r) {
	t[x].l = l, t[x].r = r;
	t[x].a = 1, t[x].b = 0;
	if (l==r) 
		t[x].s = a[l];
	else {
		build(LS(x), l, (l+r)>>1);
		build(RS(x), ((l+r)>>1)+1, r);
		refresh(x);
	}
}

void update(int x, int l, int r, LL p, LL q) {
	if (r < t[x].l || l > t[x].r) 
		return;
	else if (l <= t[x].l && t[x].r <= r)
		apply(x, p, q);
	else {
		push(x);
		update(LS(x), l, r, p, q);
		update(RS(x), l, r, p, q);
		refresh(x);
	}
}

LL sum(int x, int l, int r) {
	if (l <= t[x].l && t[x].r <= r) 
		return t[x].s;
	else if (r < t[x].l || t[x].r < l)
		return 0;
	else {
		push(x);
		return (sum(LS(x), l, r) + sum(RS(x), l, r)) % M;
	}
}

int main() {
	scanf("%d %d", &n, &M);
	REP(i, 1, n) scanf("%d", &a[i]);
	scanf("%d", &m);

	build(1, 1, n);
	for (int cmd,l,r,c; m; m--) {
		scanf("%d %d %d", &cmd, &l, &r);
		if (cmd == 3) 
			printf("%lld\n", sum(1, l, r));
		else {
			scanf("%d", &c);
			if (cmd == 1) 
				update(1, l, r, c, 0);
			else 
				update(1, l, r, 1, c);
		}
	}
	return 0;
}