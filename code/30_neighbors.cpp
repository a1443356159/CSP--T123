#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
int main() {
    int q;
    scanf("%d", &q);
    multiset<int> s;
    while (q--) {
        char op[10]; int x;
        scanf("%9s%d", op, &x);
        if (strcmp(op, "ADD") == 0) s.insert(x);
        else if (strcmp(op, "DEL") == 0) {
            multiset<int>::iterator it = s.find(x);
            if (it != s.end()) s.erase(it);
        } else {
            multiset<int>::iterator it = s.lower_bound(x);
            if (it == s.end()) puts("NONE");
            else printf("%d\n", *it);
        }
    }
    return 0;
}
