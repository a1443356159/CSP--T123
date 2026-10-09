#include <bits/stdc++.h>
using namespace std;
map<string, vector<string>> definitions, memo;
map<string, int> state;
const vector<string> &expand(const string &name) {
    if (!definitions.count(name)) throw runtime_error("unknown name");
    if (state[name] == 1) throw runtime_error("cycle");
    if (state[name] == 2) return memo.at(name);
    state[name] = 1;
    vector<string> output;
    for (const string &token : definitions.at(name)) {
        if (token[0] != '@') output.push_back(token);
        else {
            const auto &part = expand(token.substr(1));
            output.insert(output.end(), part.begin(), part.end());
        }
    }
    state[name] = 2; memo[name] = move(output); return memo.at(name);
}
int main() {
    int n; cin >> n;
    while (n--) {
        string name; int k; cin >> name >> k;
        auto &tokens = definitions[name]; tokens.resize(k);
        for (auto &s : tokens) cin >> s;
    }
    string start; cin >> start;
    try {
        const auto &out = expand(start);
        for (size_t i = 0; i < out.size(); ++i) cout << (i ? " " : "") << out[i];
        cout << '\n';
    } catch (const exception &) { cout << "ERROR\n"; }
}
