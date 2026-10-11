#include <cstdio>
#include <algorithm>
long long s[605][605];
int main() {
    int n, L, r, t; scanf("%d%d%d%d", &n, &L, &r, &t);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; scanf("%d", &x);
            s[i][j] = s[i-1][j]+s[i][j-1]-s[i-1][j-1]+x;
        }
    }
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x1 = std::max(1, i-r), x2 = std::min(n, i+r);
            int y1 = std::max(1, j-r), y2 = std::min(n, j+r);
            long long sum = s[x2][y2]-s[x1-1][y2]
                            -s[x2][y1-1]+s[x1-1][y1-1];
            long long area = 1LL*(x2-x1+1)*(y2-y1+1);
            if (sum <= area*t) answer++;
        }
    }
    printf("%d\n", answer);
    return 0;
}
