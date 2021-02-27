
#include <bits/stdc++.h>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize ("unroll-loops")

using namespace std;
typedef long long ll;
typedef long double dbl;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<dbl, dbl> pdd;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<dbl> vd;

#ifndef _MY_DEBUG_
#define _MY_DEBUG_ 0
#endif

#define cdeb if (_MY_DEBUG_) cerr
inline void deb() { cdeb << endl; }
template <typename H, typename... T> 
inline void deb(H h, T... t) { cdeb << h << ' '; deb(t...); }

#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
#define readv(A, n) A.reserve(n); for (ll i = 0; i < n; i++) \
    { remove_reference<decltype(A[0])>::type x; cin >> x; A.push_back(x); }

template <typename T>
ostream & operator<<(ostream & os, vector<T> v) {
    bool space = false;
    for (auto x : v) {
        if (space) os << ' ';
        os << x; 
        space = true;
    }
    return os;
}


const int maxn = int(1e5) + 5;
int st[2 * maxn];
int lazy[2 * maxn];

int n;
int h;

void app(int x, int p) {
    st[p] += x;
    if (p < n) lazy[p] += x;
}

void prop(int p) {
    if (lazy[p]) {
        app(lazy[p], p << 1);
        app(lazy[p], p << 1 | 1);
        lazy[p] = 0;
    }
}

void prop_to_root(int p) {
    for (int s = 31 ^ __builtin_clz(p); (p >> s) < min(n, p); s--) {
        int k = p >> s;
        prop(k);
    }
}

void rebuild(int p) {
    while (p > 1) p >>= 1, st[p] = max(st[p << 1], st[p << 1 | 1]) + lazy[p];
}

void prop_all() {
    rep(i, 1, n) {
        prop(i);
        st[i] = max(st[i << 1], st[i << 1 | 1]);
    }
}

void upd(int x, int l, int r) {
    if (l > r) return;
    int l0 = l + n; int r0 = r + n;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) app(x, l++);
        if (~r & 1) app(x, r--);
    }

    rebuild(l0); rebuild(r0);
}

int query(int l, int r) {
    if (l > r) return 0;
    prop_to_root(l + n); prop_to_root(r + n);
    int res = 0;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, st[l++]);
        if (~r & 1) res = max(st[r--], res);
    }
    return res;
}


int lb(int x, int l, int r) {
    int r0 = r;
    //deb("lb", x, l, r);
    int ql[64];
    int qr[32];
    int ri = 32, li = 0;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) ql[li++] = l++;
        if (~r & 1) qr[--ri] = r--;
    }

    copy(qr + ri, qr + 32, ql + li);
    //rep(i, 0, li + 32 - ri) deb("test", ql[i]);

    rep(i, 0, li + 32 - ri) {
        int p = ql[i];
        //deb("lbi", p, st[p]);
        if (st[p] >= x) {

            while (p < n) {
                prop(p);
                //deb("test", p, st[p], st[p << 1]);
                p = p << 1 | (st[p << 1] < x);
            }
            return p - n;
        }
    }
    return r0 + 1;
}

void my_swap(int i1, ll i2, vi & index_of, vi & queue_of) {
    int q1 = queue_of[i1];
    int q2 = queue_of[i2];

    index_of[q1] = i2;
    index_of[q2] = i1;
    queue_of[i1] = q2;
    queue_of[i2] = q1;
}


void solve() {
    int q;
    cin >> n >> q;
    //readv(A, n);

    //h = n <= 1 ? 0 : 32 - __builtin_clz(n - 1);

    vector<pair<int, int>> Q(n);
    rep(i, 0, n) {
        cin >> Q[i].first;
        Q[i].second = i;
    }
    sort(all(Q));

    vi index_of(n);
    vi queue_of(n);

    rep (i, 0, n) {
        index_of[Q[i].second] = i;
        queue_of[i] = Q[i].second;
        st[i + n] = Q[i].first;
    }

    for (int i = n - 1; i > 0; i--) st[i] = max(st[i << 1], st[i << 1 | 1]);

    rep(i, 0, q) {
        int t = 0; cin >> t;
        if (t == 1) {
            int x; cin >> x; x--;
            int a = index_of[x];
            int q = query(a, a);
            int b = lb(q + 1, 0, n - 1) - 1;

            upd(1, b, b);
            my_swap(a, b, index_of, queue_of);

        } else if (t == 2) {
            int x; cin >> x;
            int l = lb(x, 0, n - 1);
            cout << (n - l) << '\n';
        } else {
            int x; cin >> x;
            int l = lb(x, 0, n - 1);
            upd(-1, l, n - 1);
        }

    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    for (int i = 0; i < t; i++) solve();
}
