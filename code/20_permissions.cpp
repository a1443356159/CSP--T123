#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <string>
using namespace std;
map<string, set<string> > rights;
int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        char op[10], user[21], resource[21];
        scanf("%9s%20s%20s", op, user, resource);
        if (strcmp(op, "GRANT") == 0) rights[user].insert(resource);
        else {
            map<string, set<string> >::iterator it = rights.find(user);
            if (strcmp(op, "REVOKE") == 0) {
                if (it != rights.end()) it->second.erase(resource);
            } else {
                int allowed = it != rights.end() && it->second.count(resource);
                puts(allowed ? "YES" : "NO");
            }
        }
    }
    return 0;
}
