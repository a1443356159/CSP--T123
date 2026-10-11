#include <cstdio>
int a[1005];
int main() {
    int n, answer = 0; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 1; i + 1 < n; i++) {
        if ((a[i] > a[i-1] && a[i] > a[i+1]) ||
            (a[i] < a[i-1] && a[i] < a[i+1])) answer++;
    }
    printf("%d\n", answer);
    return 0;
}
