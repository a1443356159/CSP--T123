#include <cstdio>
#include <cstring>
char s[105], line[110];
int next_char[128], jump[31][128];
void read_line(char text[], int cap) {
    fgets(text, cap, stdin);
    text[strcspn(text, "\r\n")] = 0;
}
void finish_line() { int c; while ((c=getchar()) != '\n' && c != EOF) {} }
int main() {
    read_line(s, sizeof(s));
    for (int c = 0; c < 128; c++) next_char[c] = c;
    int n; scanf("%d", &n); finish_line();
    for (int i = 0; i < n; i++) {
        read_line(line, sizeof(line));
        next_char[(unsigned char)line[1]] = (unsigned char)line[2];
    }
    for (int c = 0; c < 128; c++) jump[0][c] = next_char[c];
    for (int b = 1; b < 31; b++)
        for (int c = 0; c < 128; c++) jump[b][c] = jump[b-1][jump[b-1][c]];
    int m; scanf("%d", &m);
    while (m--) {
        int k; scanf("%d", &k); putchar('#');
        for (int i = 1; s[i] && s[i] != '#'; i++) {
            int c = (unsigned char)s[i];
            for (int b = 0; b < 31; b++) if ((k >> b) & 1) c = jump[b][c];
            putchar(c);
        }
        puts("#");
    }
    return 0;
}
