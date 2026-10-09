#include <bits/stdc++.h>
using namespace std;
void append_parts(const string &s, vector<string> &parts) {
    string item; stringstream input(s);
    while (getline(input, item, '/')) {
        if (item.empty() || item == ".") continue;
        if (item == "..") { if (!parts.empty()) parts.pop_back(); }
        else parts.push_back(item);
    }
}
int main() {
    string cwd; cin >> cwd; int q; cin >> q;
    vector<string> base; append_parts(cwd, base);
    while (q--) {
        string path; cin >> path;
        vector<string> result = (path[0]=='/' ? vector<string>{} : base);
        append_parts(path, result);
        if (result.empty()) cout << '/';
        for (const string &x : result) cout << '/' << x;
        cout << '\n';
    }
}
