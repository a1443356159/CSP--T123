#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    queue<int> q;
    while (n--) {
        char op[10];
        scanf("%9s", op);
        if (strcmp(op, "PUSH") == 0) {
            int x; scanf("%d", &x); q.push(x);
        } else {
            if (q.empty()) puts("EMPTY");
            else { printf("%d\n", q.front()); q.pop(); }
        }
    }
    return 0;
}
