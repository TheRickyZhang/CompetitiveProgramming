#include <bits/stdc++.h>
using namespace std;

struct node {
  int x, y;
  string s;
};

int main() {
  node s{0, 1, "hello"};
  cout<<s.x<<" "<<s.y<<" "<<s.s<<endl;
  node t = std::move(s);
  cout<<s.x<<" "<<s.y<<" "<<s.s<<endl;
}
