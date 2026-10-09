#include <bits/stdc++.h>
using namespace std;
struct Student { string id; int score; };
int main() {
    int n; cin >> n;
    vector<Student> a(n);
    for (auto &x : a) cin >> x.id >> x.score;
    sort(a.begin(), a.end(), [](const Student &x, const Student &y) {
        if (x.score != y.score) return x.score > y.score;
        return x.id < y.id;
    });
    for (auto x : a) cout << x.id << ' ' << x.score << '\n';
}
