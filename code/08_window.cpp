#include <cstdio>
const int N = 200005;
long long a[N];
int main() {
    int n; long long k;
    scanf("%d%lld", &n, &k);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    if (k <= 1) { puts("0"); return 0; }
    long long product = 1, answer = 0;
    int left = 0;
    for (int right = 0; right < n; right++) {
        product *= a[right];
        while (left <= right && product >= k) product /= a[left++];
        answer += right - left + 1;
    }
    printf("%lld\n", answer);
    return 0;
}
