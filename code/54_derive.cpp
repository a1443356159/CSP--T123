#include <cstdio>
int main() {
    int n, previous = 0; scanf("%d", &n);
    long long largest = 0, smallest = 0;
    for (int i = 0; i < n; i++) {
        int b; scanf("%d", &b);
        largest += b;
        if (i == 0 || b > previous) smallest += b;
        previous = b;
    }
    printf("%lld\n%lld\n", largest, smallest);
    return 0;
}
