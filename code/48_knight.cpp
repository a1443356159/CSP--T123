#include <cstdio>
#include <cstring>
struct Point { int x, y; } q[10005];
int dist[105][105];
int dx[8] = {1,1,-1,-1,2,2,-2,-2};
int dy[8] = {2,-2,2,-2,1,-1,1,-1};
int main() {
    int n, k, sx, sy; scanf("%d%d%d%d", &n, &k, &sx, &sy);
    memset(dist, -1, sizeof(dist));
    int head = 0, tail = 0, answer = 1;
    q[tail++] = {sx, sy}; dist[sx][sy] = 0;
    while (head < tail) {
        Point p = q[head++];
        if (dist[p.x][p.y] == k) continue;
        for (int d = 0; d < 8; d++) {
            int x = p.x+dx[d], y = p.y+dy[d];
            if (x < 1 || x > n || y < 1 || y > n || dist[x][y] != -1)
                continue;
            dist[x][y] = dist[p.x][p.y]+1;
            q[tail++] = {x,y}; answer++;
        }
    }
    printf("%d\n", answer);
    return 0;
}
