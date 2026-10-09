#include <cstdio>
#include <cstring>
struct Node { char tag[21], id[21]; int parent; };
Node a[505];
int ancestors[505], answer[505];
char line[1005], tokens[10][22];
int matches(int u, const char token[]) {
    if (token[0] == '#')
        return strcmp(a[u].id, "-") != 0 && strcmp(a[u].id, token + 1) == 0;
    return strcmp(a[u].tag, token) == 0;
}
int main() {
    int n, q, top = 0;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        int depth;
        scanf("%d%20s%20s", &depth, a[i].tag, a[i].id);
        top = depth;
        a[i].parent = top == 0 ? -1 : ancestors[top - 1];
        ancestors[top++] = i;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
    while (q--) {
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        int count = 0;
        char *s = strtok(line, " \t\r\n");
        while (s != NULL) {
            strcpy(tokens[count++], s);
            s = strtok(NULL, " \t\r\n");
        }
        int total = 0;
        for (int u = 0; u < n; u++) {
            int k = count - 1;
            if (k < 0 || !matches(u, tokens[k])) continue;
            k--;
            int v = a[u].parent;
            while (v != -1 && k >= 0) {
                if (matches(v, tokens[k])) k--;
                v = a[v].parent;
            }
            if (k < 0) answer[total++] = u + 1;
        }
        printf("%d", total);
        for (int i = 0; i < total; i++) printf(" %d", answer[i]);
        printf("\n");
    }
    return 0;
}
