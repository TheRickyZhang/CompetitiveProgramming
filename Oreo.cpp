#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
#define ll long long
#define f(i, to) for (int i = 0; i < (to); ++i)

struct Oreo {
    long long a, b, c;
};

void solve(istream &cin, ostream &cout) {
    int n;
    cin >> n;
    vector<Oreo> oreos(n);
    for (int i = 0; i < n; i++){
        cin >> oreos[i].a >> oreos[i].b >> oreos[i].c;
    }

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
    int t = 1000;
    inputFile << t << "\n";
    for (int tc = 0; tc < t; tc++){
        int n = 100; // or choose a random n if desired
        inputFile << n << "\n";
        for (int i = 0; i < n; i++){
            long long a = rand() % 10001;
            long long b = rand() % 10001;
            long long c = rand() % 10001;
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
