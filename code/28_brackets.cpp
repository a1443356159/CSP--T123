#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
char s[100005];
int match(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}
int main() {
    if (fgets(s, sizeof(s), stdin) == NULL) s[0] = '\0';
    s[strcspn(s, "\r\n")] = '\0';
    stack<char> st;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else {
            if (st.empty() || !match(st.top(), c)) {
                puts("NO"); return 0;
            }
            st.pop();
        }
    }
    puts(st.empty() ? "YES" : "NO");
    return 0;
}
