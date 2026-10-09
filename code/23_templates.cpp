#include <cstdio>
#include <map>
#include <string>
#include <vector>
using namespace std;
map<string, int> number;
vector<string> definition[105], memo[105];
int state[105];
int expand(int u) {
    if (state[u] == 1) return 0;
    if (state[u] == 2) return 1;
    state[u] = 1;
    for (int i = 0; i < (int)definition[u].size(); i++) {
        string token = definition[u][i];
        if (token[0] != '@') memo[u].push_back(token);
        else {
            map<string, int>::iterator it = number.find(token.substr(1));
            if (it == number.end() || !expand(it->second)) return 0;
            int v = it->second;
            for (int j = 0; j < (int)memo[v].size(); j++)
                memo[u].push_back(memo[v][j]);
        }
    }
    state[u] = 2;
    return 1;
}
int main() {
    int n;
    scanf("%d", &n);
    char name[21], token[21];
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%20s%d", name, &k); number[name] = i;
        for (int j = 0; j < k; j++) {
            scanf("%20s", token); definition[i].push_back(token);
        }
    }
    scanf("%20s", name);
    map<string, int>::iterator it = number.find(name);
    if (it == number.end() || !expand(it->second)) puts("ERROR");
    else {
        int u = it->second;
        for (int i = 0; i < (int)memo[u].size(); i++)
            printf("%s%s", i == 0 ? "" : " ", memo[u][i].c_str());
        printf("\n");
    }
    return 0;
}
