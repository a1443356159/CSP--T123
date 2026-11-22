#include <bitset>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
const int MAX_ROLE = 505;
typedef bitset<MAX_ROLE> Mask;
typedef unordered_map<string, Mask> Index;
Index users, groups, operations, kinds, names;
Mask any_operation, any_kind, any_name;
unordered_map<string, int> role_id;
// A missing key produces an empty mask without inserting a record.
Mask lookup(const Index &index, const string &key) {
    Index::const_iterator it = index.find(key);
    return it == index.end() ? Mask() : it->second;
}
void read_rules(int r, Index &index, Mask &any, bool wildcard) {
    int count; cin >> count;
    if (!wildcard && count == 0) any.set(r);
    while (count--) {
        string value; cin >> value;
        if (wildcard && value == "*") any.set(r);
        else index[value].set(r);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, m, q; cin >> n >> m >> q;
    for (int r = 0; r < n; r++) {
        string name; cin >> name; role_id.emplace(name, r);
        read_rules(r, operations, any_operation, true);
        read_rules(r, kinds, any_kind, true);
        read_rules(r, names, any_name, false);
    }
    while (m--) {
        string role; int count; cin >> role >> count;
        int r = role_id.find(role)->second;
        while (count--) {
            string type, name; cin >> type >> name;
            if (type == "u") users[name].set(r);
            else groups[name].set(r);
        }
    }
    while (q--) {
        string user, group, op, kind, name;
        int count; cin >> user >> count;
        Mask candidate = lookup(users, user);
        // Group membership belongs to this query only.
        while (count--) {
            cin >> group; candidate |= lookup(groups, group);
        }
        cin >> op >> kind >> name;
        candidate &= lookup(operations, op) | any_operation;
        candidate &= lookup(kinds, kind) | any_kind;
        candidate &= lookup(names, name) | any_name;
        cout << (candidate.any() ? 1 : 0) << '\n';
    }
    return 0;
}
