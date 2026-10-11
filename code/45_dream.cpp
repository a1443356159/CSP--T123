#include <cstdio>
long long a[100005], b[100005], need[100005];
long long pre[100005], suf[100007];
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    need[0] = a[0];
    for (int i = 1; i <= n; i++) need[i] = need[i-1]+a[i]-b[i];
    pre[0] = need[0];
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i-1] > need[i] ? pre[i-1] : need[i];
    suf[n] = need[n];
    for (int i = n-1; i >= 0; i--)
        suf[i] = suf[i+1] > need[i] ? suf[i+1] : need[i];
    for (int i = 1; i <= n; i++) {
        long long answer = pre[i-1] > suf[i]+b[i] ?
                           pre[i-1] : suf[i]+b[i];
        printf("%lld%c", answer, i == n ? '\n' : ' ');
    }
    return 0;
}
