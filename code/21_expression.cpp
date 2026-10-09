#include <bits/stdc++.h>
using namespace std;
struct Parser {
    string s; size_t p = 0;
    void space() { while (p<s.size() && s[p]==' ') ++p; }
    bool take(char c) {
        space(); if (p<s.size() && s[p]==c) { ++p; return true; }
        return false;
    }
    long long expression() {
        long long x = term();
        while (true) {
            if (take('+')) x += term();
            else if (take('-')) x -= term();
            else return x;
        }
    }
    long long term() {
        long long x = factor();
        while (take('*')) x *= factor();
        return x;
    }
    long long factor() {
        if (take('+')) return factor();
        if (take('-')) return -factor();
        if (take('(')) {
            long long x = expression();
            if (!take(')')) throw runtime_error("missing )");
            return x;
        }
        space();
        if (p==s.size() || !isdigit((unsigned char)s[p])) throw runtime_error("number expected");
        long long x = 0;
        while (p<s.size() && isdigit((unsigned char)s[p])) x = x*10+s[p++]-'0';
        return x;
    }
};
int main() {
    Parser a; getline(cin, a.s);
    try {
        long long answer = a.expression(); a.space();
        if (a.p != a.s.size()) throw runtime_error("trailing input");
        cout << answer << '\n';
    } catch (const exception &) { cout << "ERROR\n"; }
}
