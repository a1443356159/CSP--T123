#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int N = 10005;
char cwd[N], path[N];
void append_parts(const char s[], vector<string> &parts) {
    char item[N];
    int i = 0;
    while (s[i] != '\0') {
        while (s[i] == '/') i++;
        int len = 0;
        while (s[i] != '\0' && s[i] != '/') item[len++] = s[i++];
        item[len] = '\0';
        if (len == 0 || strcmp(item, ".") == 0) continue;
        if (strcmp(item, "..") == 0) {
            if (!parts.empty()) parts.pop_back();
        } else parts.push_back(item);
    }
}
int main() {
    int q;
    scanf("%10004s%d", cwd, &q);
    vector<string> base;
    append_parts(cwd, base);
    while (q--) {
        scanf("%10004s", path);
        vector<string> result;
        if (path[0] != '/') result = base;
        append_parts(path, result);
        if (result.empty()) printf("/");
        for (int i = 0; i < (int)result.size(); i++)
            printf("/%s", result[i].c_str());
        printf("\n");
    }
    return 0;
}
