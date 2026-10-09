#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, capacity; cin >> n >> capacity;
    vector<long long> f(capacity+1);
    for (int i = 0; i < n; ++i) {
        int cost; long long value; cin >> cost >> value;
        for (int v = capacity; v >= cost; --v) f[v] = max(f[v], f[v-cost]+value);
    }
    cout << f[capacity] << '\n';
}
