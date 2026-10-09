#include <cstdio>
#include <map>
#include <string>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    map<string, int> count;
    for (int i = 0; i < n; i++) {
        char word[31];
        scanf("%30s", word); count[word]++;
    }
    map<string, int>::iterator it;
    for (it = count.begin(); it != count.end(); ++it)
        printf("%s %d\n", it->first.c_str(), it->second);
    return 0;
}
