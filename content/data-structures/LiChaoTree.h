/**
 * Author: Nalin Bhardwaj
 * Date: 2020-01-25
 * License: CC0
 * Source: Tutorial - https://cp-algorithms.com/geometry/convex_hull_trick.html
 * Description: Add line $y = mx + c$ using add\_line$(\{m, c\})$. Query for point x using query(x).
 * For max instead of min, change lines marked with \#\#\#. P $>$ largest point at which query occurs
 * Coordinate compress if too large point values.
 * Time: O(\log N)
 */
#pragma once

typedef long long ll;

const ll maxn = ll(1e5)+5, inf = ll(1e18)+5;

struct point {
	ll m, c; // y = mx + c
	point() : m(0), c(inf) {} // ### (inf -> -inf)
	point(ll _m, ll _c) : m(_m), c(_c) {}
};

point line[8 * maxn];

struct li_chao_tree {
    inline int left(int node) { return (node<<1); }
    inline int right(int node) { return (node<<1)+1; }

	void add_line(point add, int node = 1, ll l = -maxn, ll r = maxn) {
		ll m = (l + r) / 2;
		bool lef = (eval(add, l) < eval(line[node], l)); // ###
		bool mid = (eval(add, m) < eval(line[node], m)); // ###
		if (mid) {
			swap(add, line[node]);
		}
		if (l == r - 1) { // Leaf Node
			return;
		} else if (lef != mid) { // Intersection point in [l, m)
			add_line(add, left(node), l, m);
		} else { // Intersection point in [m, r)
			add_line(add, right(node), m, r);
		}
	}
	ll query(ll x, int node = 1, ll l = -maxn, ll r = maxn) {
		ll ans = eval(line[node], x), m = (l + r) / 2;
		if (l == r - 1) {
			return ans;
		} else if (x < m) {
			return min(ans, query(x, left(node), l, m)); // ###
		} else {
			return min(ans, query(x, right(node), m, r)); // ###
		}
	}
	ll eval(point p, ll x) {
		return p.m * x + p.c;
	}
	void clear(int node = 1, ll l = -maxn, ll r = maxn) {
		ll m = (l + r) / 2;
		if (line[node].c == inf) {
			return;
		}
		line[node] = point();
		if (l == r - 1) {
			return;
		}
		clear(left(node), l, m);
		clear(right(node), m, r);
	}
};
