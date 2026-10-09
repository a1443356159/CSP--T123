#include <bits/stdc++.h>
using namespace std;
int main() {
    int q; cin >> q;
    map<string, set<string>> rights;
    while (q--) {
        string op, user, resource; cin >> op >> user >> resource;
        if (op == "GRANT") rights[user].insert(resource);
        else if (op == "REVOKE") {
            auto it = rights.find(user);
            if (it != rights.end()) it->second.erase(resource);
        } else {
            auto it = rights.find(user);
            bool allowed = it != rights.end() && it->second.count(resource);
            cout << (allowed ? "YES" : "NO") << '\n';
        }
    }
}
