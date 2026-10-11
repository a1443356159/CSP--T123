#include <cstdio>
struct Point { int x, y; char type; } p[1005];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d%d %c", &p[i].x, &p[i].y, &p[i].type);
    while (m--) {
        int c, a, b; scanf("%d%d%d", &c, &a, &b);
        long long first = c + 1LL*a*p[0].x + 1LL*b*p[0].y;
        char positive = first > 0 ? p[0].type :
                        (p[0].type == 'A' ? 'B' : 'A');
        bool ok = true;
        for (int i = 0; i < n; i++) {
            long long v = c + 1LL*a*p[i].x + 1LL*b*p[i].y;
            if (v == 0 || ((v > 0) != (p[i].type == positive)))
                ok = false;
        }
        puts(ok ? "Yes" : "No");
    }
    return 0;
}
