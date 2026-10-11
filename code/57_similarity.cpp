#include <cstdio>
#include <string>
#include <unordered_map>
int main() {
    int n, m; scanf("%d%d", &n, &m);
    std::unordered_map<std::string, int> mask;
    mask.max_load_factor(0.7f); mask.reserve(n+m);
    for (int article = 0; article < 2; article++) {
        int count = article == 0 ? n : m;
        for (int i = 0; i < count; i++) {
            char word[11]; scanf("%10s", word);
            for (int j = 0; word[j]; j++)
                if (word[j] >= 'A' && word[j] <= 'Z') word[j] += 'a'-'A';
            mask[std::string(word)] |= article == 0 ? 1 : 2;
        }
    }
    int intersection = 0;
    for (std::unordered_map<std::string, int>::const_iterator it = mask.begin();
         it != mask.end(); ++it) if (it->second == 3) intersection++;
    printf("%d\n%d\n", intersection, (int)mask.size());
    return 0;
}
