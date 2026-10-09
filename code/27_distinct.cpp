#include <cstdio>
#include <algorithm>
using namespace std;
int a[200005];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a, a + n);
    int m = unique(a, a + n) - a;
    printf("%d\n", m);
    for (int i = 0; i < m; i++)
        printf("%d%c", a[i], i + 1 == m ? '\n' : ' ');
    return 0;
}
