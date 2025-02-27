#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Oreo {
    long long a, b, c;
};

void solve(istream &in, ostream &out) {
    int n;
    in >> n;
    vector<Oreo> oreos(n);
    for (int i = 0; i < n; i++){
        in >> oreos[i].a >> oreos[i].b >> oreos[i].c;
    }

    // Sort Oreos by top cookie width in descending order.
    sort(oreos.begin(), oreos.end(), [](const Oreo &x, const Oreo &y){
        return x.a > y.a;
    });

    long long ans = 0, prefix = 0;
    // For each prefix, base oreo's cream counts twice.
    for (int i = 0; i < n; i++){
        prefix += oreos[i].b;
        ans = max(ans, prefix + oreos[i].b);
    }
    out << ans << "\n";
}

int main(){
    srand(time(nullptr));

    // Generate input file
    ofstream inputFile("input.txt");
    int t = 100;
    int n = 1000;
    inputFile << t << "\n";
    inputFile << n << "\n";
    for (int i = 0; i < n; i++){
        long long a = rand() % 1000000001; // [0, 1e9]
        long long b = rand() % 1000000001;
        long long c = rand() % 1000000001;
        inputFile << a << " " << b << " " << c << "\n";
    }
    inputFile.close();

    // Process input and produce output file
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
