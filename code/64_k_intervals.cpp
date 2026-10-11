#include <cstdio>
long long cnt[100005];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    cnt[0] = 1;
    int remainder = 0;
    long long answer = 0;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        remainder = (remainder + x) % k;
        answer += cnt[remainder];
        cnt[remainder]++;
    }
    printf("%lld\n", answer);
    return 0;
}
