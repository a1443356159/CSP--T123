#include <cstdio>
#include <set>
#include <utility>
std::set<std::pair<int,int> > points;
int x[1005], y[1005], answer[5];
bool exists(int x, int y) {
    return points.find(std::make_pair(x,y)) != points.end();
}
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i], &y[i]); points.insert(std::make_pair(x[i],y[i]));
    }
    for (int i = 0; i < n; i++) {
        int a = x[i], b = y[i];
        if (!exists(a+1,b) || !exists(a-1,b) ||
            !exists(a,b+1) || !exists(a,b-1)) continue;
        int score = exists(a-1,b-1)+exists(a-1,b+1)
                   +exists(a+1,b-1)+exists(a+1,b+1);
        answer[score]++;
    }
    for (int i = 0; i < 5; i++) printf("%d\n", answer[i]);
    return 0;
}
