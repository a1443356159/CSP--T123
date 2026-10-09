#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 505;
char g[N][N];
int d[N][N], qx[N * N], qy[N * N];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%504s", g[i]);
        fill(d[i], d[i] + m, -1);
    }
    int head = 0, tail = 0;
    if (g[0][0] == '.') {
        d[0][0] = 0; qx[tail] = 0; qy[tail++] = 0;
    }
    while (head < tail) {
        int x = qx[head], y = qy[head]; head++;
        for (int k = 0; k < 4; k++) {
            int a = x + dx[k], b = y + dy[k];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            if (g[a][b] == '#' || d[a][b] != -1) continue;
            d[a][b] = d[x][y] + 1;
            qx[tail] = a; qy[tail++] = b;
        }
    }
    printf("%d\n", d[n - 1][m - 1]);
    return 0;
}
