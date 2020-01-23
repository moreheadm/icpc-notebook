#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

struct pnode {
	int res = 0;
	pnode *L, *R;

	pnode(int v = 0, pnode* l = NULL, pnode* r = NULL)
	{
		res = v;
		L = l;
		R = r;
	}
};

typedef pnode* node;

node dummy;

int A[int(1e5)+5], pm[int(1e5)+5];
node root[int(1e5)+5];

node upd(node root, int L, int R, int idx)
{
	if(L == R && L == idx)
	{
		return new pnode(root->res+1, dummy, dummy);
	}
	else
	{
		if(idx >= L && idx <= (L+R)/2) return new pnode(root->res+1, upd(root->L, L, (L+R)/2, idx), root->R);
		else return new pnode(root->res+1, root->L, upd(root->R, (L+R)/2+1, R, idx));
	}
}

int qry(node rootL, node rootR, int L, int R, int k)
{
	if(L == R) return L;
	else
	{
		int left = rootR->L->res-rootL->L->res;
		//cout << L << " " << R << " " << left << " " << k << "\n";
		if(left >= k)
		{
			return qry(rootL->L, rootR->L, L, (L+R)/2, k);
		}
		else return qry(rootL->R, rootR->R, (L+R)/2+1, R, k-left);
	}
}

int main(void)
{
	dummy = new pnode();
	dummy->L = dummy->R = dummy;
	int n, m, x, y, k;
	scanf("%d%d", &n, &m);

	set<int> compressor;
	unordered_map<int, int> mp;
	for(int i = 0;i < n;i++)
	{
		scanf("%d", &A[i]);
		compressor.insert(A[i]);
	}

	int v = 1;
	for(auto it: compressor) mp[it] = v++;

	for(int i = 0;i < n;i++)
	{
		pm[mp[A[i]]] = A[i];
		A[i] = mp[A[i]];
	}

	for(int i = 0;i < n;i++)
	{
		if(i) root[i] = upd(root[i-1], 0, v, A[i]);
		else root[i] = upd(dummy, 0, v, A[i]);
	}

	while(m--)
	{
		scanf("%d%d%d", &x, &y, &k)
		x--; y--;
		printf("%d\n", pm[min(v-1, qry((((x-1)<0)?dummy:root[x-1]), root[y], 0, v, k))]);
	}
}