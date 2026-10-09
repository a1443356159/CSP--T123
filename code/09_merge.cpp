#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    priority_queue<long long, vector<long long>, greater<long long> > q;
    for (int i = 0; i < n; i++) {
        long long x;
        scanf("%lld", &x); q.push(x);
    }
    long long answer = 0;
    while (q.size() > 1) {
        long long x = q.top(); q.pop();
        long long y = q.top(); q.pop();
        answer += x + y; q.push(x + y);
    }
    printf("%lld\n", answer);
    return 0;
}
