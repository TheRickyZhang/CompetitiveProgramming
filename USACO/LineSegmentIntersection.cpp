#include <bits/stdc++.h>
using namespace std;
#define int long long

struct point { int x, y; };

int side(point a, point b, point c) {
    // +1 if c is left of a→b, –1 if right, 0 if colinear
    int64_t v = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
    return (v>0) - (v<0);
}

bool onSegment(point a, point b, point c) {
    // precondition: c is colinear with a–b
    return min(a.x,b.x) <= c.x && c.x <= max(a.x,b.x)
        && min(a.y,b.y) <= c.y && c.y <= max(a.y,b.y);
}

bool segI(point a, point b, point c, point d) {
    int o1 = side(a,b,c), o2 = side(a,b,d);
    int o3 = side(c,d,a), o4 = side(c,d,b);
    if (o1*o2 < 0 && o3*o4 < 0) return true;
    if (o1 == 0 && onSegment(a,b,c)) return true;
    if (o2 == 0 && onSegment(a,b,d)) return true;
    if (o3 == 0 && onSegment(c,d,a)) return true;
    if (o4 == 0 && onSegment(c,d,b)) return true;
    return false;
}

bool rectI(point a, point b, point c, point d) {
    // fixed: use min/max so endpoints can be unordered
    return max(min(a.x,b.x), min(c.x,d.x)) <= min(max(a.x,b.x), max(c.x,d.x))
        && max(min(a.y,b.y), min(c.y,d.y)) <= min(max(a.y,b.y), max(c.y,d.y));
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    while(n--){
        point a,b,c,d;
        cin>>a.x>>a.y>>b.x>>b.y
            >>c.x>>c.y>>d.x>>d.y;
        // first check bounding‐boxes, then the full intersection test
        if(rectI(a,b,c,d) && segI(a,b,c,d))
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
}
