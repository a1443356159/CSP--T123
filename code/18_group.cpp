#include <cstdio>
#include <algorithm>
using namespace std;
long long f[2005], next_f[2005], value[25];
int cost[25];
int main() {
    int groups, capacity;
    scanf("%d%d", &groups, &capacity);
    for (int g = 0; g < groups; g++) {
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) scanf("%d%lld", &cost[i], &value[i]);
        for (int v = 0; v <= capacity; v++) {
            next_f[v] = f[v];
            for (int i = 0; i < k; i++)
                if (v >= cost[i])
                    next_f[v] = max(next_f[v], f[v - cost[i]] + value[i]);
        }
        for (int v = 0; v <= capacity; v++) f[v] = next_f[v];
    }
    printf("%lld\n", f[capacity]);
    return 0;
}
