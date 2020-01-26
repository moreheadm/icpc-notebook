/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * \textttt{crt(x, a)} computes $z$ such that
 * $z \pmod x_i = a_i \forall i$. Note that the solution is
 * unique modulo $M = \text{lcm}(x_i)$ . Return (z, M). Note that we do not require the a_i
 * to be relatively prime.
 *
 * Status: Works
 * Time: $N \log(N)$
 */
#pragma once

#include "euclid.h"

pair<ll, ll> crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return {x < 0 ? x + m*n/g : x, m*n/g};
}

pair<ll, ll> crt(vector<int>& x, vector<int>& a) {
    pair<ll, ll> ret = {a[0], x[0]};

    for(int i = 1;i < int(x.size());i++) {
        ret = crt(ret.second, ret.first, a[i], x[i]);
    }
    return ret;
}
