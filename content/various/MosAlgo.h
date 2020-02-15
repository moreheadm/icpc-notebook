/**
 * Author: Nalin Bhardwaj
 * License: CC0
 * Source: Codeforces
 * Description: Mo's on trees with path queries to print the smallest non-negative integer on simple path $a_i$ and $b_i$.
 * Status: https://codeforces.com/gym/100962/attachments Problem F AC
 * Time: O(N \sqrt{N} \log(N))
 */

const int maxn = int(2e5)+5, inf = int(1e9)+5, block = 500;

int A[maxn], BIT[maxn+5], ans[maxn], start[maxn], en[maxn], occ[maxn], cnt[maxn];
pair<pair<int, int>, int> Q[maxn];
vector<int> dis;
vector<pair<int, int>> graph[maxn];

inline int left(int node) { return (node<<1); }
inline int right(int node) { return (node<<1)+1; }

void upd(int idx, int v)
{
    while(idx < maxn)
    {
        BIT[idx] += v;
        idx += (idx&-idx);
    }
}

int qry()
{
    int idx = 0, b = 16, s = 0;
    while(b >= 0)
    {
        if(BIT[idx+(1<<b)]+s == idx+(1<<b))
        {
            idx += (1<<b);
            s += BIT[idx];
        }
        b--;
    }
    return idx;
}

void dfs0(int node, int par, int into)
{
    A[node] = into, start[node] = int(dis.size());
    dis.push_back(node);
    for(auto it: graph[node])
    {
        if(it.first != par) dfs0(it.first, node, it.second);
    }
    en[node] = int(dis.size());
    dis.push_back(node);
}

inline int cmp(pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b)
{
    if(a.first.first/block != b.first.first/block) return a.first.first < b.first.first;
    else if((a.first.first/block)%2) return a.first.second > b.first.second;
    else return a.first.second < b.first.second;
}

void rem(int v)
{
    v++;
    cnt[v]--;
    if(cnt[v] == 0) upd(v, -1);
}

void add(int v)
{
    v++;
    cnt[v]++;
    if(cnt[v] == 1) upd(v, 1);
}

void act(int node)
{
    if(A[node] >= maxn) return;
    occ[node]++;
    if(occ[node] == 2) rem(A[node]);
    else add(A[node]);
}

void deact(int node)
{
    if(A[node] >= maxn) return;
    occ[node]--;
    if(occ[node] == 1) add(A[node]);
    else rem(A[node]);
}

int main(void)
{
    int n, q, u, v, x;
    scanf("%d%d", &n, &q);
    for(int i = 1;i < n;i++)
    {
        scanf("%d%d%d", &u, &v, &x);
        u--, v--;
        graph[u].push_back({v, x}), graph[v].push_back({u, x});
    }

    dfs0(0, -1, inf);

    //for(auto it: dis) cout << it << " ";
    //cout << "\n";

    for(int i = 0;i < q;i++)
    {
        scanf("%d%d", &u, &v);
        u--, v--;
        if(start[u] > start[v]) swap(u, v);

        if(start[u] <= start[v] && start[v] <= en[u]) Q[i] = {{start[u]+1, start[v]}, i};
        else Q[i] = {{en[u], start[v]}, i};
        //cout << Q[i].first.first << ":" << Q[i].first.second << " " << Q[i].second << "\n";
    }

    sort(Q, Q+q, cmp);

    int L = 0, R = 0;
    act(dis[0]);

    for(int i = 0;i < q;i++)
    {
        int ql = Q[i].first.first, qr = Q[i].first.second;

        if(ql <= qr)
        {
            while(R < qr) act(dis[++R]);
            while(L < ql) deact(dis[L++]);
            while(L > ql) act(dis[--L]);
            while(R > qr) deact(dis[R--]);
            ans[Q[i].second] = qry();
        }
        else ans[Q[i].second] = 0;
    }

    for(int i = 0;i < q;i++) printf("%d\n", ans[i]);
}
