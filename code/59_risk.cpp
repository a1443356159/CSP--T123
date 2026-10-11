#include <cstdio>
int main() {
    int n, k, t, xl, yd, xr, yu;
    scanf("%d%d%d%d%d%d%d", &n, &k, &t, &xl, &yd, &xr, &yu);
    int pass = 0, stay = 0;
    for (int person = 0; person < n; person++) {
        bool touched = false, stayed = false; int run = 0;
        for (int j = 0; j < t; j++) {
            int x, y; scanf("%d%d", &x, &y);
            bool inside = xl <= x && x <= xr && yd <= y && y <= yu;
            if (inside) { touched = true; run++; }
            else run = 0;
            if (run >= k) stayed = true;
        }
        pass += touched; stay += stayed;
    }
    printf("%d\n%d\n", pass, stay);
    return 0;
}
