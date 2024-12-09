#include <iostream>
#include <string>

using namespace std;

bool ask(const string& t) {
    cout << "? " << t << endl;
    int res;
    cin >> res;
    return res;
}

void result(string s) {
    cout << "! " << s << endl;
}

void solve() {
    int n;
    cin >> n;
    string cur;
    while (cur.size() < n) {
        if (ask(cur + "0")) {
            cur += "0";
        } else if (ask(cur + "1")) {
            cur += "1";
        } else {
            break;
        }
    }
    while ((int) cur.size() < n) {
        if (ask("0" + cur)) {
            cur = "0" + cur;
        } else{
            cur = "1" + cur;
        }
    }
    result(cur);
}

int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}