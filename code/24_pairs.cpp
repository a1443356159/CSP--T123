#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; long long c; cin >> n >> c;
    map<long long,long long> count;
    for (int i = 0; i < n; ++i) { long long x; cin >> x; ++count[x]; }
    long long answer = 0;
    for (auto [x, k] : count) {
        if (c == 0) answer += k*(k-1)/2;
        else { auto it = count.find(x+c); if (it != count.end()) answer += k*it->second; }
    }
    cout << answer << '\n';
}
