#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int N = 100005;
char s[N], word[N];
int main() {
    if (fgets(s, N, stdin) == NULL) s[0] = '\0';
    s[strcspn(s, "\r\n")] = '\0';
    vector<string> words;
    int len = 0, quoted = 0, active = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '"') { quoted = !quoted; active = 1; }
        else if (c == ' ' && !quoted) {
            if (active) {
                word[len] = '\0'; words.push_back(word);
                len = 0; active = 0;
            }
        } else { word[len++] = c; active = 1; }
    }
    if (quoted) { puts("ERROR"); return 0; }
    if (active) { word[len] = '\0'; words.push_back(word); }
    printf("%d\n", (int)words.size());
    for (int i = 0; i < (int)words.size(); i++)
        printf("[%s]\n", words[i].c_str());
    return 0;
}
