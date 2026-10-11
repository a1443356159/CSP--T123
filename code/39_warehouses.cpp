#include <cstdio>
int a[1005][15];
int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int k = 0; k < m; k++) scanf("%d", &a[i][k]);
    for (int i = 1; i <= n; i++) {
        int answer = 0;
        for (int j = 1; j <= n; j++) {
            bool upper = true;
            for (int k = 0; k < m; k++) {
                if (a[j][k] <= a[i][k]) { upper = false; break; }
            }
            if (upper) { answer = j; break; }
        }
        printf("%d\n", answer);
    }
    return 0;
}
