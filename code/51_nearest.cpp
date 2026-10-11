#include <cstdio>
long long dist[205];
bool used[205];
int main() {
    int n, X, Y; scanf("%d%d%d", &n, &X, &Y);
    for (int i = 1; i <= n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        long long dx = 1LL*x-X, dy = 1LL*y-Y;
        dist[i] = dx*dx+dy*dy;
    }
    for (int round = 0; round < 3; round++) {
        int best = 0;
        for (int i = 1; i <= n; i++)
            if (!used[i] && (best == 0 || dist[i] < dist[best])) best = i;
        printf("%d\n", best); used[best] = true;
    }
    return 0;
}
