#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5005;
int a[N], f[N];
int main() {
    int n, answer = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) {
        f[i] = 1;
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
        answer = max(answer, f[i]);
    }
    printf("%d\n", answer);
    return 0;
}
