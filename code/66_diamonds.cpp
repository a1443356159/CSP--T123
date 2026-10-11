#include <cstdio>
#include <algorithm>
int a[50005], len[50005], best[50006];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    std::sort(a, a + n);
    int right = 0;
    for (int left = 0; left < n; left++) {
        while (right < n && a[right] - a[left] <= k) right++;
        len[left] = right - left;
    }
    for (int i = n - 1; i >= 0; i--)
        best[i] = std::max(len[i], best[i + 1]);
    int answer = 0;
    for (int i = 0; i < n; i++)
        answer = std::max(answer, len[i] + best[i + len[i]]);
    printf("%d\n", answer);
    return 0;
}
