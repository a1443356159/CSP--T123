#include <cstdio>
int main() {
    int q; scanf("%d", &q);
    while (q--) {
        long long n, answer = 1; int k;
        scanf("%lld%d", &n, &k);
        for (long long p = 2; p <= n/p; p++) {
            if (n % p != 0) continue;
            int count = 0; long long power = 1;
            do { n /= p; power *= p; count++; } while (n % p == 0);
            if (count >= k) answer *= power;
        }
        // Remaining prime has exponent 1; k is at least 2.
        printf("%lld\n", answer);
    }
    return 0;
}
