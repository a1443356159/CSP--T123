#include <bits/stdc++.h>
using namespace std;
int main() {
    int groups, capacity; cin >> groups >> capacity;
    vector<long long> f(capacity+1);
    for (int g = 0; g < groups; ++g) {
        int k; cin >> k; vector<pair<int,long long>> items(k);
        for (auto &[c,w] : items) cin >> c >> w;
        auto next = f;
        for (int v = 0; v <= capacity; ++v)
            for (auto [c,w] : items) if (v >= c) next[v] = max(next[v], f[v-c]+w);
        f.swap(next);
    }
    cout << f[capacity] << '\n';
}
