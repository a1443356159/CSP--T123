#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int main() {
    int q;
    scanf("%d", &q);
    vector<int> a;
    while (q--) {
        char op[10]; scanf("%9s", op);
        if (strcmp(op, "ADD") == 0) {
            int x; scanf("%d", &x); a.push_back(x);
        } else if (strcmp(op, "UNDO") == 0) {
            if (!a.empty()) a.pop_back();
        } else {
            if (a.empty()) puts("EMPTY");
            else {
                for (int i = 0; i < (int)a.size(); i++)
                    printf("%d%c", a[i], i + 1 == (int)a.size() ? '\n' : ' ');
            }
        }
    }
    return 0;
}
