#include <cstdio>
#include <algorithm>
char grid[105][105];
int col[105];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%100s", grid[i]);
    int answer = n * m + 1;
    for (int top = 0; top < n; top++) {
        std::fill(col, col + m, 0);
        for (int bottom = top; bottom < n; bottom++) {
            for (int j = 0; j < m; j++) col[j] += grid[bottom][j] == '1';
            int left = 0, sum = 0;
            for (int right = 0; right < m; right++) {
                sum += col[right];
                while (sum >= k) {
                    int area = (bottom - top + 1) * (right - left + 1);
                    answer = std::min(answer, area);
                    sum -= col[left++];
                }
            }
        }
    }
    printf("%d\n", answer == n * m + 1 ? 0 : answer);
    return 0;
}
