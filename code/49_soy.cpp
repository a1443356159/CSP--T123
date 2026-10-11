#include <cstdio>
int main() {
    int money; scanf("%d", &money);
    int paid = money/10, answer = 0;
    for (int five = 0; five*5 <= paid; five++) {
        int rest = paid-five*5;
        int bottles = five*7+(rest/3)*4+rest%3;
        if (bottles > answer) answer = bottles;
    }
    printf("%d\n", answer);
    return 0;
}
