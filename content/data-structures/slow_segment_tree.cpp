
#include <bits/stdc++.h>

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
void deb() { cdeb << endl; }
template <typename H, typename... T> 
void deb(H h, T... t) { cdeb << h << ' '; deb(t...); }

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define readv(v, A, n) v A(n); for (int i = 0; i < n; i++) { cin >> A[i]; }

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

struct node {
    int distinct;
    vi prev;
};

const int maxn = 30005;
node st[4 * maxn];
vi prev_idx;

void init(int i, int j, int n, vi & A) {
    set<int> s;
    for (int x = i; x <= j; x++) s.insert(A[x]);

    vi prev(prev_idx.begin() + i, prev_idx.begin() + j + 1);
    sort(all(prev));
    st[n] = {int(s.size()), move(prev)};

    if (i == j) return;

    int mid = (i + j) / 2;
    init(i, mid, 2 * n, A);
    init(mid + 1, j, 2 * n + 1, A);
}

int query(int a, int b, int i, int j, int n) {
    deb("q", a, b, i, j, n);
    if (a <= i && b >= j) {
        auto t = lower_bound(all(st[n].prev), i);
        auto b = lower_bound(all(st[n].prev), a);
        deb("a", st[n].distinct, int(t - b));
        return st[n].distinct - int(t - b);
    }

    int mid = (i + j) / 2;
    int ans = 0;
    if (a <= mid) ans += query(a, b, i, mid, 2 * n);
    if (b >= mid + 1) ans += query(a, b, mid + 1, j, 2 * n + 1);

    return ans;
}

void solve() {
    int n; cin >> n;
    readv(vi, A, n);

    prev_idx.assign(n, -1);
    map<int, int> prev;

    rep(i, 0, n) {
        auto it = prev.find(A[i]);
        if (it != prev.end()) prev_idx[i] = it->second;

        prev[A[i]] = i;
        deb("prev_idx:", i, prev_idx[i]);
    }

    init(0, n-1, 1, A);

    int q; cin >> q;
    rep(i, 0, q) {
        int x, y;
        cin >> x >> y; x--; y--;
        cout << query(x, y, 0, n - 1, 1) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    for (int i = 0; i < t; i++) solve();
}
