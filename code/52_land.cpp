#include <cstdio>
int main() {
    int n, a, b; scanf("%d%d%d", &n, &a, &b);
    long long answer = 0;
    while (n--) {
        int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int left = x1 > 0 ? x1 : 0, down = y1 > 0 ? y1 : 0;
        int right = x2 < a ? x2 : a, up = y2 < b ? y2 : b;
        if (left < right && down < up) answer += 1LL*(right-left)*(up-down);
    }
    printf("%lld\n", answer);
    return 0;
}
