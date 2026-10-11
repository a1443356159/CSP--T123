#include <cstdio>
int a[1000005], cnt[2005];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int left = 1, kinds = 0, bestLeft = 1, bestRight = n;
    for (int right = 1; right <= n; right++) {
        if (cnt[a[right]]++ == 0) kinds++;
        while (kinds == m) {
            if (right - left < bestRight - bestLeft) {
                bestLeft = left;
                bestRight = right;
            }
            if (--cnt[a[left]] == 0) kinds--;
            left++;
        }
    }
    printf("%d %d\n", bestLeft, bestRight);
    return 0;
}
