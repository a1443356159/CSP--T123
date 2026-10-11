#include <cstdio>
unsigned long long pre[1005][1005];
int main() {
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 0; i <= n; i++) pre[i][0] = 0;
        for (int j = 0; j <= m; j++) pre[0][j] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                unsigned long long x;
                scanf("%llu", &x);
                pre[i][j] = x + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
            }
        }
        unsigned long long answer = 0;
        for (int i = 0; i < q; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            unsigned long long sum = pre[x2][y2] - pre[x1-1][y2]
                                   - pre[x2][y1-1] + pre[x1-1][y1-1];
            answer ^= sum;
        }
        printf("%llu\n", answer);
    }
    return 0;
}
