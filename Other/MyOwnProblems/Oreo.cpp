#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;
#define ll long long
#define f(i, to) for (int i = 0; i < (to); ++i)

struct Oreo {
    ll a, b, c;
};

void solve(istream &cin, ostream &cout) {
    int n;
    cin >> n;
    vector<Oreo> oreos(n);
    for (int i = 0; i < n; i++){
        cin >> oreos[i].a >> oreos[i].b >> oreos[i].c;
    }

    // Sort in descending order by a (the algorithm expects this)
    sort(oreos.begin(), oreos.end(), [](const Oreo &x, const Oreo &y){
        return x.a > y.a;
    });

    ll res = 0, pre = 0;
    f(i, n){
        pre += oreos[i].b;
        res = max(res, pre + oreos[i].b);
    }
    cout << res << "\n";
}

int main(){
    srand(time(nullptr));

    ofstream inputFile("input.txt");
    int t = 100;
    inputFile << t << "\n";
    for (int tc = 0; tc < t; tc++){
        int n = 1000; // or choose a random n if desired
        inputFile << n << "\n";

        // Generate unique 'a' values using a set.
        set<ll> uniqueA;
        while ((int)uniqueA.size() < n) {
            uniqueA.insert(rand() % 10001); // range [0, 10000]
        }
        // Copy into a vector in ascending order.
        vector<ll> aAsc(uniqueA.begin(), uniqueA.end());

        // Create a vector of (a, c) pairs, where c is the 1-based rank (ascending order)
        vector<pair<ll,ll>> oreoData;
        for (int i = 0; i < n; i++){
            oreoData.push_back({aAsc[i], i + 1});
        }

        // Shuffle the order randomly for output.
        random_shuffle(oreoData.begin(), oreoData.end());

        // Output each Oreo with its a, a random b, and c as assigned.
        for (int i = 0; i < n; i++){
            ll a = oreoData[i].first;
            ll b = rand() % 10001;
            ll c = oreoData[i].second;
            inputFile << a << " " << b << " " << c << "\n";
        }
    }
    inputFile.close();

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    inFile >> t;
    while(t--){
        solve(inFile, outFile);
    }

    inFile.close();
    outFile.close();
    return 0;
}
