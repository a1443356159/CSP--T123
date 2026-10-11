#include <cstdio>
int main() {
    int x, last = 0, answer = 0;
    while (scanf("%d", &x) == 1 && x != 0) {
        if (x == 1) last = 1;
        else if (last <= 1) last = 2;
        else last += 2;
        answer += last;
    }
    printf("%d\n", answer);
    return 0;
}
