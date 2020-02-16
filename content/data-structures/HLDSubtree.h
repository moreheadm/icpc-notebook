/**
 * Author: Nalin Bhardwaj
 * Date: 2020-01-25
 * License: CC0
 * Source: Folklore/self - https://codeforces.com/contest/696/submission/69540194
 * Description: HLD implementation that also supports subtree updates/queries.
 * Time: Path query is $O(\log^2 n)$
 */
typedef long long int lli;

const lli maxn = lli(1e5)+5, maxlog = 17, inf = lli(1e17)+5;

lli n, totchain = 0, curst = 0, inchain[maxn], head[maxn], inst[maxn], H[maxn], T[maxn][maxlog+1], lz[4*maxn], start[maxn], en[maxn], sz[maxn], lookup[maxn], ptr[maxn];
vector<lli> graph[maxn];
vector<lli> girls[maxn];
pair<lli, lli> st[4*maxn];

inline lli left(lli node) { return (node<<1); }
inline lli right(lli node) { return (node<<1)+1; }

void build(lli node, lli L, lli R) {
	if(L == R) {
		lli realnode = lookup[L];
		if(girls[realnode].empty()) st[node] = {inf, realnode};
		else st[node] = {*girls[realnode].begin(), realnode};
	}
	else {
		build(left(node), L, (L+R)/2);
		build(right(node), (L+R)/2+1, R);
		st[node] = min(st[left(node)], st[right(node)]);
	}
}

void shift(lli node, lli L, lli R) {
	if(lz[node] && L != R) {
		lz[left(node)] += lz[node];
		lz[right(node)] += lz[node];
		st[left(node)].first += lz[node];
		st[right(node)].first += lz[node];
	}
	lz[node] = 0;
}

void upd(lli node, lli L, lli R, lli a, lli b, lli v) {
	if(a > R || b < L) return;
	else if(a <= L && R <= b) {
		st[node].first += v;
		lz[node] += v;
	}
	else {
		shift(node, L, R);
		upd(left(node), L, (L+R)/2, a, b, v);
		upd(right(node), (L+R)/2+1, R, a, b, v);
		st[node] = min(st[left(node)], st[right(node)]);
	}
}

pair<lli, lli> qry(lli node, lli L, lli R, lli a, lli b) {
	if(a > R || b < L) return {inf, -1};
	else if(a <= L && R <= b) return st[node];
	else {
		shift(node, L, R);
		return min(qry(left(node), L, (L+R)/2, a, b), qry(right(node), (L+R)/2+1, R, a, b));
	}
}

void init() {
	for(lli j = 1;j <= maxlog;j++) {
		for(lli i = 0;i < n;i++) {
			if(T[i][j-1] != -1) T[i][j] = T[T[i][j-1]][j-1];
		}
	}
}

lli LCA(lli x, lli y) {
	if(H[x] > H[y]) swap(x, y);
	for(lli i = maxlog;i >= 0;i--) {
		if(H[y]-(1<<i) >= H[x]) y = T[y][i];
	}
	if(x == y) return x;
	for(lli i = maxlog;i >= 0;i--) {
		if(T[x][i] != T[y][i]) x = T[x][i], y = T[y][i];
	}
	return T[x][0];
}

// v MUST be an ancestor of u
pair<lli, lli> pathqry(lli node, lli anc)
{
	lli cur = node;
	pair<lli, lli> res = {inf, -1};
	while(inchain[cur] != inchain[anc])
	{
		res = min(res, qry(1, 0, curst-1, inst[head[inchain[cur]]], inst[cur]));
		cur = T[head[inchain[cur]]][0];
	}
	res = min(res, qry(1, 0, curst-1, inst[anc], inst[cur]));
	return res;
}

void dfs0(lli node, lli par, lli ht) {
	sz[node] = 1; H[node] = ht; T[node][0] = par;
	for(auto it: graph[node]) {
		if(it != par) {
			dfs0(it, node, ht+1);
			sz[node] += sz[it];
		}
	}
}

void dfs1(lli node, lli par, lli chain) {
	inchain[node] = chain;
	if(head[chain] == -1) head[chain] = node;
	inst[node] = curst++;
	lookup[curst-1] = node;
	start[node] = curst-1;

	pair<lli, lli> largest = {-1, -1};
	for(auto it: graph[node]) {
		if(it != par) largest = max(largest, {sz[it], it});
	}
	if(largest.second != -1) dfs1(largest.second, node, chain);
	for(auto it: graph[node]) {
		if(it != par && it != largest.second) {
			dfs1(it, node, totchain++);
		}
	}
	en[node] = curst-1;
}

// Add k to subtree(node)
upd(1, 0, n-1, start[node], en[node], k);

// initialisation before input
for(lli i = 0;i < maxn;i++) head[i] = -1;
for(lli i = 0;i < maxn;i++) {
	for(lli j = 0;j <= maxlog;j++) T[i][j] = -1;
}

// initialisation after input
dfs0(0, -1, 0);
init();
totchain = 1;
dfs1(0, -1, 0);
build(1, 0, curst-1);
