#include <bits/stdc++.h>
using namespace std;

#define F_GET(_1, _2, _3, NAME, ...) NAME
#define f(...) F_GET(__VA_ARGS__, f3, f2)(__VA_ARGS__)
#define f2(i, to) for (int i = 0; i < (to); ++i)
#define f3(i, from, to) for (int i = (from); i < (to); ++i)

int k, n, m;
struct point {
  double x, y;
};
using vpt = vector<point>;
double cross(point o, point a, point b) {
  return (b.y - o.y) * (a.x - o.x) - (a.y - o.y) * (b.x - o.x);
}

// Good standardizatoin of my understanding / impl of cross for geometry
// direction Counterclockwise is the default, so think about going left -> right
// on the lower hull as the reference
void pivotSort(vpt& a, point pivot) {
  auto [x, y] = pivot;
  sort(a.begin(), a.end(), [&](point p, point q) {
    return atan2(p.y - y, p.x - x) < atan2(q.y - y, q.x - x);
  });
};

// void solve() {
//   cin >> n >> m;
//   vpt a(n); f(i, n) cin >> a[i].x >> a[i].y;
//   vpt b(m); f(i, m) cin >> b[i].x >> b[i].y;
//   // Remember we need to sort around pivot, and that default order gives
//   COUNTERCLOCKWISE order sort(all(b), [&](point p, point q) {
//     return tie(p.x, p.y) < tie(q.x, q.y);
//   });
//   v<point> top, bot;
//   auto add = [&](v<point>& res, auto&& points) {
//     for(point p : points) {
//       while(res.size() >= 2 && cross(res[res.size()-2], res[res.size()-1], p)
//       < 0) {
//         res.pop_back();
//       }
//       res.push_back(p);
//     }
//   };
//   add(bot, b);
//   add(top, b | views::reverse);
//   top.pop_back(); bot.pop_back();
//   // a.front() == a.back();
//   auto hull = bot;
//   hull.insert(hull.end(), all(top));
//
//   int res = 0;
//   int sz = hull.size();
//   f(i, sz) {
//     point o = hull[(i+sz-1) % sz];
//     point p = hull[i];
//     point q = hull[(i+1) % sz];
//     v<point> c;
//     for(point pp : a) {
//       if(cross(o, p, pp) >= 0 && cross(p, q, pp) >= 0) {
//         continue;
//       }
//       c.push_back(pp);
//     }
//     pivotSort(c, p);
//     // print(a);
//     deque<point> sweep;
//     for(point pp : c) {
//       while(!sweep.empty() && cross(sweep.front(), pp, p) <= 0) {
//         // cout << "crossed " << sweep.front()  << sp << pp << sp << p << en;
//         sweep.pop_front();
//       }
//       sweep.push_back(pp);
//       int curr = sweep.size();
//       if(curr > res) {
//         res = curr;
//         // cout << res << " " << o << " " << p << " " << q << " " << sweep <<
//         endl;
//       }
//     }
//   }
// }
//   cout << res << endl;


void solve() {
  cin >> n >> m;
  vpt a(n);
  f(i, n) cin >> a[i].x >> a[i].y;
  vpt b(m);
  f(i, m) cin >> b[i].x >> b[i].y;
  int res = 0;
  f(i, m) {
    point p = b[i];
    // angle, is_chip
    vector<pair<double, int>> ev;
    for (auto& c : a) {
      ev.push_back({atan2(c.y - p.y, c.x - p.x), 1});
    }
    f(j, m) if (j != i) { ev.push_back({atan2(b[j].y - p.y, b[j].x - p.x), 0}); }
    sort(ev.begin(), ev.end());
    int sz = ev.size();
    f(j, sz) ev.push_back({ev[j].first + 2 * M_PI, ev[j].second});
    int curr = 0, bad = 0, r = 0;
    f(l, sz) {
      while (r < 2 * sz && ev[r].first - ev[l].first < M_PI - 1e-9) {
        if (ev[r].second == 1)
          curr++;
        else
          bad++;
        r++;
      }
      if (bad == 0)
        res = max(res, curr);

      if (ev[l].second == 1)
        curr--;
      else
        bad--;
    }
  }
  cout << res << endl;
}

int32_t main() {
  solve();
}
