#include <bits/stdc++.h>
using namespace std;
struct Node { string tag, id; int parent; };
int main() {
    int n, q; cin >> n >> q;
    vector<Node> a(n); vector<int> ancestors;
    for (int i = 0; i < n; ++i) {
        int depth; cin >> depth >> a[i].tag >> a[i].id;
        while ((int)ancestors.size() > depth) ancestors.pop_back();
        a[i].parent = ancestors.empty() ? -1 : ancestors.back();
        ancestors.push_back(i);
    }
    string line; getline(cin, line);
    auto matches = [&](int u, const string &token) {
        if (token[0]=='#') return a[u].id != "-" && a[u].id == token.substr(1);
        return a[u].tag == token;
    };
    while (q--) {
        getline(cin, line); stringstream ss(line); vector<string> tokens;
        string token; while (ss >> token) tokens.push_back(token);
        vector<int> answer;
        for (int u = 0; u < n; ++u) {
            int k = (int)tokens.size()-1;
            if (!matches(u, tokens[k])) continue;
            --k; int v = a[u].parent;
            while (v != -1 && k >= 0) {
                if (matches(v, tokens[k])) --k;
                v = a[v].parent;
            }
            if (k < 0) answer.push_back(u+1);
        }
        cout << answer.size(); for (int x : answer) cout << ' ' << x; cout << '\n';
    }
}
