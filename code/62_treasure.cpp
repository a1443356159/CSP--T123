#include <cstdio>
int x[1005], y[1005], pattern[55][55];
int main() {
    int n, L, S; scanf("%d%d%d", &n, &L, &S);
    for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
    int need = 0;
    for (int row = S; row >= 0; row--)
        for (int col = 0; col <= S; col++) {
            scanf("%d", &pattern[row][col]); need += pattern[row][col];
        }
    int answer = 0;
    for (int i = 0; i < n; i++) {
        if (x[i]+S > L || y[i]+S > L) continue;
        bool ok = true; int count = 0;
        for (int j = 0; j < n; j++) {
            int a = x[j]-x[i], b = y[j]-y[i];
            if (a < 0 || a > S || b < 0 || b > S) continue;
            if (!pattern[a][b]) { ok = false; break; }
            count++;
        }
        if (ok && count == need) answer++;
    }
    printf("%d\n", answer);
    return 0;
}
