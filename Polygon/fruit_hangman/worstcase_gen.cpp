#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int len = opt<int>("len", 500);
    int k = opt<int>("k", 25);

    // generate k words sharing a long common prefix, differing at last 2 chars
    int wordLen = len / k;
    if(wordLen < 3) wordLen = 3;

    string prefix(wordLen - 2, 'a');

    vector<string> words;
    for(int i = 0; i < k; i++) {
        string suffix;
        suffix += (char)('a' + i / 26);
        suffix += (char)('a' + i % 26);
        words.push_back(prefix + suffix);
    }

    // build string by concatenating all k words (each used once)
    string s;
    vector<int> perm(k);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());
    for(int i = 0; i < k; i++) {
        s += words[perm[i]];
    }

    // string length is exactly k * wordLen = len (when len divisible by k)
    if(s.empty()) s = words[0];

    int pos = rnd.next(0, (int)s.size() - 1);
    s[pos] = '_';

    println(s);
    println(k);
    for(auto& w : words) println(w);

    return 0;
}
