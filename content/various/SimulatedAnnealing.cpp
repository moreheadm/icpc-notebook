/**
 * Author: Max Morehead
 * Date: 2020-02-16
 * License: CC0
 * Source: some ideas from wikipedia, https://www.phy.ornl.gov/csep/mo/node32.html, 300IQ solution to Jan17 USACO 3
 * Description: Simple SA with exponential annealing
 */
#pragma once

typedef int numt;
numt solve() {
    // ADD: return the value of the current state
    return 0;
}

int main() {
    clock_t timer = clock();

    const double Tt = 1.9;
    double et = 0.0;
    double uphill = 1.;
    const double up_inc = 0.01;
    double f = 0.9999;
    double t0 = 100; // can initialize with delta / ln(0.8)
    double temp = t0;

    // ADD: initialize initial state
    numt curr = solve();
    numt res = curr;

    while (et < Tt) {
        // ADD: random move

        uphill *= (1. - up_inc);
        numt s = solve();
        // reverse if maximizing
        if (s < curr) {
            curr = s;
        } else {
            ll x = rand() + 1ll;
            ll y = rand() + 1ll;
            x %= y;
            // (s - curr) if maximizing
            if (x / (double) y <= exp((curr - s) / temp)) {
                // reverse if maximizing
                if (s > curr) uphill += up_inc;
                curr = s;
            } else {
                // ADD: move back
            }
        }

        // max if maximizing
        res = min(res, curr);

        if (uphill > 0.02) temp *= f;
        if (uphill < 0.001) temp /= f; 

        et = (clock() - timer) / double(CLOCKS_PER_SEC);
    }
}
