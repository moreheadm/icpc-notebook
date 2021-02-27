
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")

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
#define readv(A, n) A.reserve(n); for (int i = 0; i < n; i++) \
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

template <typename T, typename V>
istream & operator>>(istream & is, pair<T, V> p) {
    is >> p.first >> p.second;
    return is;
}

const int base = 1000000000;
const int base_digits = 9;
 
struct Int {
   
    vector<int> a;
    int sign;
   
    /*<arpa>*/
   
    int size(){
        if(a.empty()) return 0;
        int ans=(a.size()-1)*base_digits;
        int ca=a.back();
        while(ca)
            ans++,ca/=10;
        return ans;
    }
   
    Int operator ^(const Int &v){
        Int ans=1,a=*this,b=v;
        while(!b.isZero()){
            if(b%2)
            ans*=a;
            a*=a,b/=2;
        }
        return ans;
    }
   
    string to_string(){
        stringstream ss;
        ss << *this;
        string s;
        ss >> s;
        return s;
    }
   
    int sumof(){
        string s = to_string();
        int ans = 0;
        for(auto c : s)  ans += c - '0';
        return ans;
    }
   
    /*</arpa>*/
   
    Int() :
    sign(1) {
    }
 
    Int(long long v) {
        *this = v;
    }
 
    Int(const string &s) {
        read(s);
    }
 
    /*
    void operator=(const Int &v) {
        sign = v.sign;
        a = v.a;
    }*/
 
    void operator=(long long v) {
        sign = 1;
        a.clear();
        if (v < 0)
            sign = -1, v = -v;
        for (; v > 0; v = v / base)
            a.push_back(v % base);
    }
 
    Int operator+(const Int &v) const {
        if (sign == v.sign) {
            Int res = v;
            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int) res.a.size())
                    res.a.push_back(0);
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry)
                    res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }
 
    Int operator-(const Int &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                Int res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                    res.a[i] += base;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
 
    void operator*=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / base);
            a[i] = (int) (cur % base);
            //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
        }
        trim();
    }
 
    Int operator*(int v) const {
        Int res = *this;
        res *= v;
        return res;
    }
 
    void operator*=(long long v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / base);
            a[i] = (int) (cur % base);
            //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
        }
        trim();
    }
 
    Int operator*(long long v) const {
        Int res = *this;
        res *= v;
        return res;
    }
 
    friend pair<Int, Int> divmod(const Int &a1, const Int &b1) {
        int norm = base / (b1.a.back() + 1);
        Int a = a1.abs() * norm;
        Int b = b1.abs() * norm;
        Int q, r;
        q.a.resize(a.a.size());
 
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.a[i] = d;
        }
 
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
 
    Int operator/(const Int &v) const {
        return divmod(*this, v).first;
    }
 
    Int operator%(const Int &v) const {
        return divmod(*this, v).second;
    }
 
    void operator/=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long) base;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }
 
    Int operator/(int v) const {
        Int res = *this;
        res /= v;
        return res;
    }
 
    int operator%(int v) const {
        if (v < 0)
            v = -v;
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i)
            m = (a[i] + m * (long long) base) % v;
        return m * sign;
    }
 
    void operator+=(const Int &v) {
        *this = *this + v;
    }
   
    void operator-=(const Int &v) {
        *this = *this - v;
    }
   
    void operator*=(const Int &v) {
        *this = *this * v;
    }
   
    void operator/=(const Int &v) {
        *this = *this / v;
    }
   
    Int operator ++(){
        *this += 1;
        return *this;
    }
   
    Int operator ++(int){
        Int temp = *this;
        *this += 1;
        return temp;
    }
   
    Int operator --(){
        *this -= 1;
        return *this;
    }
   
    Int operator --(int){
        Int temp = *this;
        *this -= 1;
        return temp;
    }
 
    bool operator<(const Int &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
           return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }
 
    bool operator>(const Int &v) const {
        return v < *this;
    }
   
    bool operator<=(const Int &v) const {
        return !(v < *this);
    }
   
    bool operator>=(const Int &v) const {
        return !(*this < v);
    }
   
    bool operator==(const Int &v) const {
        return !(*this < v) && !(v < *this);
    }
   
    bool operator!=(const Int &v) const {
        return *this < v || v < *this;
    }
 
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }
 
    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }
 
    Int operator-() const {
        Int res = *this;
        res.sign = -sign;
        return res;
    }
 
    Int abs() const {
        Int res = *this;
        res.sign *= res.sign;
        return res;
    }
 
    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--)
            res = res * base + a[i];
        return res * sign;
    }
 
    friend Int gcd(const Int &a, const Int &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
   
    friend Int lcm(const Int &a, const Int &b) {
        return a / gcd(a, b) * b;
    }
 
    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
       
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
 
    friend istream& operator>>(istream &stream, Int &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
 
    friend ostream& operator<<(ostream &stream, const Int &v) {
        if (v.sign == -1)
           stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }
 
    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++)
            p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int) cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }
 
    typedef vector<long long> vll;
 
    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }
 
        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());
 
        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);
 
        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];
 
        vll r = karatsubaMultiply(a2, b2);
       
        for (int i = 0; i < (int) a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            r[i] -= a2b2[i];
 
        for (int i = 0; i < (int) r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    }
 
    Int operator*(const Int &v) const {
        vector<int> a6 = convert_base(this->a, base_digits, 6);
        vector<int> b6 = convert_base(v.a, base_digits, 6);
       
        vll a(a6.begin(), a6.end());
        vll b(b6.begin(), b6.end());
       
        while (a.size() < b.size())
            a.push_back(0);
        while (b.size() < a.size())
            b.push_back(0);
        while (a.size() & (a.size() - 1))
            a.push_back(0), b.push_back(0);
           
        vll c = karatsubaMultiply(a, b);
        Int res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int) c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int) (cur % 1000000));
            carry = (int) (cur / 1000000);
        }
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
   
    //Added part.
   
    friend Int max(const Int &a,const Int &b){
        if(a<b){
            return a;
        }
        return b;
    }
   
    friend Int max(const Int &a,const int32_t &B){
        Int b = B;
        return max(a,b);
    }
   
    friend Int max(const Int &a,const int64_t &B){
        Int b = B;
        return max(a,b);
    }
   
    friend Int min(const Int &a,const Int &b){
        if(a>b){
            return b;
        }
        return a;
    }
   
    friend Int min(const Int &a,const int32_t &B){
        Int b = B;
        return min(a,b);
    }
   
    friend Int min(const Int &a,const int64_t &B){
        Int b = B;
        return min(a,b);
    }
   
    friend Int pow(const Int &a,const Int &b){
        Int _c = 1;
        Int _b = b;
        Int _a = a;
        while(_b != 0){
        	if(_b%2){
        		_c *= _a;
			}
			_a *= _a;
			_b /= 2;
		}
        return _c;
    }
   
    friend Int pow(const Int &a,const int32_t &B){
        Int b = B;
        return pow(a,b);
    }
   
    friend Int pow(const Int &a,const int64_t &B){
        Int b = B;
        return pow(a,b);
    }
   
    friend Int sqrt(Int a) {
        Int x0 = a, x1 = (a+1)/2;
        while (x1 < x0) {
            x0 = x1;
            x1 = (x1+a/x1)/2;
        }
        return x0;
    }
};

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) if(a.d[i][j] < ll(1e16)) a.d[i][j] += d[i][k]*m.d[k][j];
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N) if (ret[i] < ll(1e16)) ret[i] += d[i][j] * vec[j];
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};

typedef vector<Int> vb;

Int sum(vb & v) {
    return std::accumulate(all(v), Int(0), [](Int x, Int y) { return x + y; });
}

struct Res {
    bool success;
    Int size;
    char c;
};


const int L = 27;
Matrix<Int, L> M[52];
vector<string> T(L);
string s;

vb one_hot(char c) {
    vb v(L);
    v[c - 'a'] = 1;
    return v;
}

Int cache[52][L];

Res query(char c, Int q, ll k) {
    //deb(c, q, k);

    if (k == 0) {
        if (q == 1) return { true, 0, c };
        else return { false, 1, '\0' };
    }

    //vb cnts = M[k] * one_hot(c);

    //Int size = sum(cnts);
    Int size = cache[k][c - 'a'];

    if (q > size) {
        return { false, size, '\0' };
    }

    trav(d, T[c - 'a']) {
        Res res = query(d, q, k - 1);
        if (res.success) return res;
        q -= res.size;
    }

    exit(1);
}

char my_advance(char c, int x)  {
    vi dist(L, -1);

    int d = 0;
    while (dist[c - 'a'] < 0 && x > 0) {
        dist[c - 'a'] = d;
        c = T[c - 'a'][0];
        d++;
        x--;
    }

    int p = d - dist[c - 'a'];
    rep(i, 0, x % p) {
        c = T[c - 'a'][0];
    }
    return c;
}

void solve() {
    cin >> s;

    rep(i, 0, L - 1) {
        cin >> T[i];
    }
    T[L - 1] = s;

    rep(i, 0, L) {
        trav(c, T[i]) {
            M[1].d[c - 'a'][i]++;
        }
    }

    rep(i, 2, 52) {
        M[i] = M[i - 1] * M[1];
    }

    rep(i, 1, 52) {
        rep(c, 'a', 'z' + 2) {
            vb v = M[i] * one_hot(c);
            cache[i][c - 'a'] = sum(v);
        }
    }

    /*
    if (_MY_DEBUG_) {
        rep(i, 0, L) {
            rep(j, 0, L) {
                cdeb << M.d[i][j] << ' ';
            }
            cdeb << endl;
        }
        cdeb << endl;
    }
    */

    ll k;
    cin >> k;
    char first_char = 'z' + 1;

    if (k > 50) {
        first_char = my_advance(first_char, k - 50);
        k = 50;
    }
    //deb("finished advance");

    int m; cin >> m;

    rep(i, 0, m) {
        ll q; cin >> q;
        Res res = query(first_char, q, k + 1);
        cout << res.c << '\n';
    }

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cerr.tie(0);

    int t = 1;
    for (int i = 0; i < t; i++) solve();
}
