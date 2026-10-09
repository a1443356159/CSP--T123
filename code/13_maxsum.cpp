#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int n; long long x;
    scanf("%d%lld", &n, &x);
    long long ending = x, answer = x;
    for (int i = 1; i < n; i++) {
        scanf("%lld", &x);
        ending = max(x, ending + x);
        answer = max(answer, ending);
    }
    printf("%lld\n", answer);
    return 0;
}
