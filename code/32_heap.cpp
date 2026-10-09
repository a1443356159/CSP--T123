#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x); q.push(x);
        if ((int)q.size() > k) q.pop();
    }
    vector<int> a;
    while (!q.empty()) { a.push_back(q.top()); q.pop(); }
    reverse(a.begin(), a.end());
    for (int i = 0; i < (int)a.size(); i++)
        printf("%d%c", a[i], i + 1 == (int)a.size() ? '\n' : ' ');
    return 0;
}
