#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n; long long x; cin >> x;
    long long ending = x, answer = x;
    for (int i = 1; i < n; ++i) {
        cin >> x; ending = max(x, ending+x); answer = max(answer, ending);
    }
    cout << answer << '\n';
}
