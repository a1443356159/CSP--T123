#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    const long long NEG = -(1LL<<60);
    vector<long long> f(n+1, NEG); f[1] = 0;
    for (int i = 1; i <= n; ++i) {
        vector<long long> row(i+1);
        for (int j = 1; j <= i; ++j) cin >> row[j];
        for (int j = i; j >= 1; --j) f[j] = max(f[j], f[j-1]) + row[j];
    }
    cout << *max_element(f.begin()+1, f.end()) << '\n';
}
