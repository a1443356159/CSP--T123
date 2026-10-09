#include <cstdio>
int n, path[10], used[10];
void dfs(int depth) {
    if (depth == n) {
        for (int i = 0; i < n; i++)
            printf("%d%c", path[i], i + 1 == n ? '\n' : ' ');
        return;
    }
    for (int x = 1; x <= n; x++) {
        if (used[x]) continue;
        used[x] = 1; path[depth] = x;
        dfs(depth + 1);
        used[x] = 0;
    }
}
int main() {
    scanf("%d", &n);
    dfs(0);
    return 0;
}
