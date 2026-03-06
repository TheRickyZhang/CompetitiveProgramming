#include <algorithm>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using ll = long long;

using namespace std;

int main() {
  // This is just Yu-Gi-Oh.
  // Is my issues possibly time limit related? Is there an edge case I'm
  // missing?
  /*
   * Test I've made:
   * 3 4
   * ATK 2100
   * DEF 3000
   * DEF 2400
   * 2000
   * 2500
   * 2900
   * 4000
   * My code will result in 1900 damage dealt. This is not the maximal damage I
   * could deal. If I attack 2100 with 2900 (the next highest Ciel card) and
   * then destroy the defense cards, I can attack directly with 2000, dealing
   * 2800 damage. What is different in this case: Ciel has more cards than Jiro,
   * and unlike test case 2, attacking directly with 2000, the weakest of Ciel's
   * card that would be able to attack after every other card destroys Jiro's
   * cards, deals more damage than Ciel's strongest card of 4000 would to Jiro's
   * 2100 card if it were the only card to attack, as it is in my code. I'm not
   * sure if I can say with certainty wihen this alternate method would be
   * better than mine; there is a similar case in test case 2 where Ciel's'
   * cards are overall strong enough to destroy all of Jiro's cards and get a
   * direct attack, but this isn't the maximal damage. If I can't determine
   * which method I should use before selecting it for maximal damage, maybe I
   * do both and then use whichever result is the maximum value like I could try
   * to see before hand which method is better I guess but that would involve
   * doing like part of the work in solving for the damage anyways
   */
  ll n, m;
  ll damage = 0, sum = 0, damage2 = 0;
  cin >> n >> m;

  vector<string> position;
  vector<ll> atk;
  vector<ll> def;
  vector<ll> ciel;

  for (ll i = 0; i < n; i++) {
    string j_pos;
    int strength;
    cin >> j_pos >> strength;
    // cin >> jiro_atk[i]
    if (j_pos == "ATK") {
      atk.push_back(strength);
    } else {
      def.push_back(strength);
    }
  }
  ll offenses = accumulate(atk.begin(), atk.end(), 0LL);
  ll defenses = accumulate(def.begin(), def.end(), 0LL);

  for (ll i = 0; i < m; i++) {
    int strength;
    cin >> strength;
    ciel.push_back(strength);
    sum += strength;
  }

  int best = INT_MIN;
  // Case 1: Just do attacks (greatest n vs lowest m)
  {
    sort(ciel.begin(), ciel.end(), greater<>());
    sort(atk.begin(), atk.end());
    int x = 0;
    for(int i = 0; i < min(ciel.size(), atk.size()); i++) {
      if(ciel[i] < atk[i]) break;
      x += ciel[i] - atk[i];
    }
    best = max(best, x);
  }

  // Case 2: Try breaking defense
  {
    sort(ciel.begin(), ciel.end());
    sort(def.begin(), def.end());
    bool good = true;
    for(int d : def) {
      auto it = upper_bound(ciel.begin(), ciel.end(), d);
      if(it == ciel.end()) {
        good = false;
        break;
      }
      ciel.erase(it);
    }
    sort(ciel.begin(), ciel.end(), greater<>());
    sort(atk.begin(), atk.end(), greater<>());
    int x = 0;
    for(int i = 0; i < ciel.size(); i++) {
      if(i < atk.size()) {
        if(ciel[i] < atk[i]) {
          good = false;
          break;
        }
        x += ciel[i] - atk[i];
      } else {
        x += ciel[i];
      }
    }
    if(good) {
      best = max(best, x);
    }
  }

  cout << best << endl;
  return 0;
}
