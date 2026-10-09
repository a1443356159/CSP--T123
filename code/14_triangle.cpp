#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1005;
const long long NEG = -(1LL << 60);
long long f[N], row[N];
int main() {
    int n;
    scanf("%d", &n);
    fill(f, f + n + 1, NEG); f[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) scanf("%lld", &row[j]);
        for (int j = i; j >= 1; j--)
            f[j] = max(f[j], f[j - 1]) + row[j];
    }
    printf("%lld\n", *max_element(f + 1, f + n + 1));
    return 0;
}
