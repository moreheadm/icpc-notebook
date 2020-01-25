/**
 * Author: Nalin Bhardwaj
 * Date: 2020-01-25
 * License: CC0
 * Source: Folklore/self
 * Description: Convex hull trick for finding max f(x) given a number of lines f(x) = mx+c.
 * During inserting, m should be in increasing order.
 * Time: Query is $O(\log N)$. Insert is $O(1)$ amortized
 */
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