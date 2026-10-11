#include <cstdio>
int a[35]; bool reachable[300005];
int main() {
    int n, x, total = 0; scanf("%d%d", &n, &x);
    for (int i = 0; i < n; i++) { scanf("%d", &a[i]); total += a[i]; }
    reachable[0] = true;
    for (int i = 0; i < n; i++)
        for (int s = total; s >= a[i]; s--)
            if (reachable[s-a[i]]) reachable[s] = true;
    for (int s = x; s <= total; s++)
        if (reachable[s]) { printf("%d\n", s); break; }
    return 0;
}
