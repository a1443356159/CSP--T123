#include <cstdio>
const int N = 505;
int a[N][N], b[N][N];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) scanf("%d", &a[i][j]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int count = 0;
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < n && y >= 0 && y < m)
                    count += a[x][y];
            }
            b[i][j] = (count >= 2);
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            printf("%d%c", b[i][j], j + 1 == m ? '\n' : ' ');
    return 0;
}
