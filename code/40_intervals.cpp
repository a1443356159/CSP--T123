#include <cstdio>
struct Interval { int l, r; } a[2005], b[2005];
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &a[i].l, &a[i].r);
    for (int i = 0; i < n; i++) scanf("%d%d", &b[i].l, &b[i].r);
    int i = 0, j = 0, answer = 0;
    while (i < n && j < n) {
        int l = a[i].l > b[j].l ? a[i].l : b[j].l;
        int r = a[i].r < b[j].r ? a[i].r : b[j].r;
        if (l < r) answer += r - l;
        if (a[i].r < b[j].r) i++;
        else if (a[i].r > b[j].r) j++;
        else { i++; j++; }
    }
    printf("%d\n", answer);
    return 0;
}
