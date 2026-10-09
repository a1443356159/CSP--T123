#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 200005;
struct Student { char id[31]; int score; };
Student a[N];
bool cmp(Student x, Student y) {
    if (x.score != y.score) return x.score > y.score;
    return strcmp(x.id, y.id) < 0;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%30s%d", a[i].id, &a[i].score);
    sort(a, a + n, cmp);
    for (int i = 0; i < n; i++) printf("%s %d\n", a[i].id, a[i].score);
    return 0;
}
