#include <cstdio>
int main() {
    int n, answer = 0; scanf("%d", &n);
    do { answer += n % 10; n /= 10; } while (n != 0);
    printf("%d\n", answer);
    return 0;
}
