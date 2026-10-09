#include <cstdio>
#include <cstring>
char s[1005];
int p = 0, valid = 1;
void skip_space() { while (s[p] == ' ') p++; }
int take(char c) {
    skip_space();
    if (s[p] == c) { p++; return 1; }
    return 0;
}
long long expression();
long long factor() {
    if (take('+')) return factor();
    if (take('-')) return -factor();
    if (take('(')) {
        long long x = expression();
        if (!take(')')) valid = 0;
        return x;
    }
    skip_space();
    if (s[p] < '0' || s[p] > '9') { valid = 0; return 0; }
    long long x = 0;
    while (s[p] >= '0' && s[p] <= '9') x = x * 10 + s[p++] - '0';
    return x;
}
long long term() {
    long long x = factor();
    while (valid && take('*')) x *= factor();
    return x;
}
long long expression() {
    long long x = term();
    while (valid) {
        if (take('+')) x += term();
        else if (take('-')) x -= term();
        else break;
    }
    return x;
}
int main() {
    if (fgets(s, sizeof(s), stdin) == NULL) s[0] = '\0';
    s[strcspn(s, "\r\n")] = '\0';
    long long answer = expression();
    skip_space();
    if (!valid || s[p] != '\0') puts("ERROR");
    else printf("%lld\n", answer);
    return 0;
}
