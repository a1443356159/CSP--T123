#include <cstdio>
int main() {
    int n; long long m; scanf("%d%lld", &n, &m);
    for (int i = 0; i < n; i++) {
        int base; scanf("%d", &base);
        printf("%lld%c", m%base, i+1 == n ? '\n' : ' ');
        m /= base;
    }
    return 0;
}
