#include <cstdio>
#include <map>
using namespace std;
int main() {
    int n; long long c;
    scanf("%d%lld", &n, &c);
    map<long long, long long> count;
    for (int i = 0; i < n; i++) {
        long long x; scanf("%lld", &x); count[x]++;
    }
    long long answer = 0;
    map<long long, long long>::iterator it;
    for (it = count.begin(); it != count.end(); ++it) {
        long long x = it->first, k = it->second;
        if (c == 0) answer += k * (k - 1) / 2;
        else {
            map<long long, long long>::iterator p = count.find(x + c);
            if (p != count.end()) answer += k * p->second;
        }
    }
    printf("%lld\n", answer);
    return 0;
}
