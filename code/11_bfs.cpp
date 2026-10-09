#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    vector<string> g(n); for (auto &s : g) cin >> s;
    vector<vector<int>> d(n, vector<int>(m, -1));
    queue<pair<int,int>> q;
    if (g[0][0] == '.') { d[0][0] = 0; q.push({0,0}); }
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
    while (!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int a = x+dx[k], b = y+dy[k];
            if (a<0 || a>=n || b<0 || b>=m || g[a][b]=='#' || d[a][b]!=-1) continue;
            d[a][b] = d[x][y]+1; q.push({a,b});
        }
    }
    cout << d[n-1][m-1] << '\n';
}
