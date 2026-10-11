#include <cstdio>
int delta[10005];
int main() {
    int n, previous = 0; scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        // Position i starts a surviving segment iff previous < p <= a.
        if (previous < a) { delta[previous+1]++; delta[a+1]--; }
        previous = a;
    }
    int segments = 0, answer = 0;
    for (int p = 1; p <= 10000; p++) {
        segments += delta[p]; if (segments > answer) answer = segments;
    }
    printf("%d\n", answer);
    return 0;
}
