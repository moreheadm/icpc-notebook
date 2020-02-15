/**
 * Author: Jingbo/SGTU
 * Date: 2020-02-15
 * Source: Jingbo's notebook
 * Description: Given n circles, for all k <= n, computes the area of regions part of atleast k circles.
 * Time: O(n^2)
 * Status:
 */
#pragma once

const int N = 22222;
const double EPS = 1e-8;
const double PI = acos(-1.0);
typedef complex<double> Point;
int n, m;
double r[N], result[N];
Point c[N];
pair<double, int> event[N];
int sgn (double x) {return x < -EPS? -1: x < EPS? 0: 1;}
double det (const Point &a, const Point &b) { return a.real() * b.imag() - a.imag()
  * b.real();}
  void addEvent (double a, int v) {
    event[m ++] = make_pair(a, v);
  }
void addPair (double a, double b) {
  if (sgn(a - b) <= 0) {
    addEvent(a, +1);
    addEvent(b, -1);
  } else {
    addPair(a, +PI);
    addPair(-PI, b);
  }
}
Point polar (double t) { return Point(cos(t), sin(t)); }
Point radius (int i, double t) {
  return c[i] + polar(t) * r[i];
}
void solve () {
  // result[k]: the total area covered no less than k times
  memset(result, 0, sizeof(result));
  for (int i = 0; i < n; ++ i) {
    m = 0;
    addEvent(-PI, 0);
    addEvent(+PI, 0);
    for (int j = 0; j < n; ++ j) {
      if (i != j) {
        if (sgn(abs(c[i] - c[j]) - abs(r[i] - r[j])) <= 0) {
          if (sgn(r[i] - r[j]) <= 0) {
            addPair(-PI, +PI);
          }
        } else {
          if (sgn(abs(c[i] - c[j]) - (r[i] + r[j])) >= 0) {
            continue;
          }
          double d = abs(c[j] - c[i]);
          Point b = (c[j] - c[i]) / d * r[i];
          double t = acos((r[i] * r[i] + d * d - r[j] * r[j]) / (2 *
                r[i] * d));
          Point a = b * polar(-t);
          Point c = b * polar(+t);
          addPair(arg(a), arg(c));
        }
      }
    }
    sort(event, event + m);
    int count = event[0].second;
    for (int j = 1; j < m; ++ j) {
      double delta = event[j].first - event[j - 1].first;
      result[count] += r[i] * r[i] * (delta - sin(delta));
      result[count] += det(radius(i, event[j - 1].first), radius(i,
            event[j].first));
      count += event[j].second;
    }
  }
}
