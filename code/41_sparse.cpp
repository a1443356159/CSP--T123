#include <cstdio>
struct Item { int index, value; } a[500005], b[500005];
int main() {
    int n, ca, cb; scanf("%d%d%d", &n, &ca, &cb);
    for (int i = 0; i < ca; i++) scanf("%d%d", &a[i].index, &a[i].value);
    for (int j = 0; j < cb; j++) scanf("%d%d", &b[j].index, &b[j].value);
    long long answer = 0;
    int i = 0, j = 0;
    while (i < ca && j < cb) {
        if (a[i].index < b[j].index) i++;
        else if (a[i].index > b[j].index) j++;
        else { answer += 1LL*a[i].value*b[j].value; i++; j++; }
    }
    printf("%lld\n", answer);
    return 0;
}
