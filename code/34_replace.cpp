#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
char line[1005], pattern[1005], replacement[1005];
void read_line(char s[]) {
    if (fgets(s, 1005, stdin) == NULL) s[0] = '\0';
    s[strcspn(s, "\r\n")] = '\0';
}
int main() {
    read_line(line); read_line(pattern); read_line(replacement);
    string s = line, p = pattern, t = replacement, answer;
    string::size_type start = 0;
    while (true) {
        string::size_type pos = s.find(p, start);
        if (pos == string::npos) break;
        answer += s.substr(start, pos - start);
        answer += t;
        start = pos + p.size();
    }
    answer += s.substr(start);
    printf("%s\n", answer.c_str());
    return 0;
}
