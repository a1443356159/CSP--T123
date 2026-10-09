#include <bits/stdc++.h>
using namespace std;
int main() {
    string s; getline(cin, s);
    vector<string> words; string cur;
    bool quoted = false, active = false;
    for (char c : s) {
        if (c == '"') { quoted = !quoted; active = true; }
        else if (c == ' ' && !quoted) {
            if (active) { words.push_back(cur); cur.clear(); active = false; }
        } else { cur += c; active = true; }
    }
    if (quoted) { cout << "ERROR\n"; return 0; }
    if (active) words.push_back(cur);
    cout << words.size() << '\n';
    for (const auto &w : words) cout << '[' << w << "]\n";
}
