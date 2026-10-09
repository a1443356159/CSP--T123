#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m)), b(n, vector<int>(m));
    for (auto &row : a) for (int &x : row) cin >> x;
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        int c = 0;
        for (int k = 0; k < 4; ++k) {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 0 && x < n && y >= 0 && y < m) c += a[x][y];
        }
        b[i][j] = (c >= 2);
    }
    for (auto &row : b) {
        for (int j = 0; j < m; ++j) cout << row[j] << (j+1 == m ? '\n' : ' ');
    }
}
