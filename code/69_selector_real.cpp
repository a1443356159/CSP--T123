#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct Node { string tag, id; int parent; };
vector<Node> nodes;
string lower_tag(string s) {
    for (int i = 0; i < (int)s.size(); i++)
        s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}
bool matches(int u, const string &token) {
    if (token[0] == '#') return nodes[u].id == token;
    return nodes[u].tag == token;
}
bool selected(int u, const vector<string> &tokens) {
    int k = (int)tokens.size() - 1;
    if (!matches(u, tokens[k])) return false;
    // Each remaining selector must match a strict ancestor.
    for (int v = nodes[u].parent; v != -1 && k > 0;
         v = nodes[v].parent)
        if (matches(v, tokens[k - 1])) k--;
    return k == 0;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    string line; getline(cin, line);
    vector<int> ancestors;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        int dots = 0;
        while (dots < (int)line.size() && line[dots] == '.') dots++;
        int depth = dots / 2;
        ancestors.resize(depth);
        Node node;
        istringstream in(line.substr(dots));
        in >> node.tag >> node.id;
        node.tag = lower_tag(node.tag);
        node.parent = depth == 0 ? -1 : ancestors.back();
        nodes.push_back(node); ancestors.push_back(i);
    }
    while (q--) {
        getline(cin, line);
        istringstream in(line);
        string word; vector<string> tokens;
        while (in >> word)
            tokens.push_back(word[0] == '#' ? word : lower_tag(word));
        vector<int> answer;
        for (int u = 0; u < n; u++)
            if (selected(u, tokens)) answer.push_back(u + 1);
        cout << answer.size();
        for (int id : answer) cout << ' ' << id;
        cout << '\n';
    }
    return 0;
}
