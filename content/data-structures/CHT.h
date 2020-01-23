#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
 
typedef long long int lli;
 
const lli maxn = lli(1e5)+5;
 
struct line {
	lli m, c;
	line(lli _m = 0, lli _c = 0)
	{
		m = _m, c = _c;
	}
};
 
struct cht {
	lli sz = 0;
	line st[maxn];
 
	double intersect(line a, line b)
	{
		return double(a.c-b.c)/(b.m-a.m);
	}
 
	void insert(line a)
	{
		while(sz > 1)
		{
			if(intersect(st[sz-2], a) < intersect(st[sz-2], st[sz-1])) sz--;
			else break;
		}
		st[sz++] = a;
	}
 
	lli qry(lli x)
	{
		lli L = 0, R = sz-1;
		while(L < R)
		{
			lli mid = (L+R)/2;
			if(x < intersect(st[mid], st[mid+1])) R = mid;
			else L = mid+1;
		}
		return st[L].m*x+st[L].c;
	}
};
 
lli a[maxn], b[maxn], dp[maxn];
 
int main(void)
{
	lli n;
	scanf("%lld", &n);
	for(lli i = 0;i < n;i++) scanf("%lld", &a[i]);
	for(lli i = 0;i < n;i++) scanf("%lld", &b[i]);
 
	cht C;
	dp[0] = 0;
	C.insert({b[0], dp[0]});
	for(lli i = 1;i < n;i++)
	{
		dp[i] = C.qry(a[i]);
		C.insert({b[i], dp[i]});
	}
	printf("%lld\n", dp[n-1]);
}