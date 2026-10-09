#include <cstdio>
#include <algorithm>
using namespace std;
long long f[5005];
int main() {
    int n, capacity;
    scanf("%d%d", &n, &capacity);
    for (int i = 0; i < n; i++) {
        int cost; long long value;
        scanf("%d%lld", &cost, &value);
        for (int v = cost; v <= capacity; v++)
            f[v] = max(f[v], f[v - cost] + value);
    }
    printf("%lld\n", f[capacity]);
    return 0;
}
