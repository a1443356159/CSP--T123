#include <cctype>
#include <iostream>
#include <map>
#include <string>
using namespace std;
typedef map<string, long long> Counts;
string text;
int pos;
bool digit() {
    return pos < (int)text.size() && isdigit((unsigned char)text[pos]);
}
long long number() {
    if (!digit()) return 1;
    long long value = 0;
    while (digit()) value = value * 10 + text[pos++] - '0';
    return value;
}
void merge_counts(Counts &to, const Counts &from, long long multiplier) {
    for (const pair<const string, long long> &item : from)
        to[item.first] += item.second * multiplier;
}
// Read a formula, leaving ')', '+' or '=' for the caller.
Counts formula() {
    Counts result;
    while (pos < (int)text.size() && text[pos] != ')' &&
           text[pos] != '+' && text[pos] != '=') {
        Counts term;
        if (text[pos] == '(') {
            pos++; term = formula(); pos++; // Consume ')'.
        } else {
            string element(1, text[pos++]);
            if (pos < (int)text.size() && islower((unsigned char)text[pos]))
                element += text[pos++];
            term[element] = 1;
        }
        long long multiplier = number();
        merge_counts(result, term, multiplier);
    }
    return result;
}

Counts side() {
    Counts result;
    while (true) {
        long long coefficient = number();
        Counts molecule = formula();
        merge_counts(result, molecule, coefficient);
        if (pos == (int)text.size() || text[pos] == '=') break;
        pos++; // Consume '+' and start the next molecule.
    }
    return result;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        cin >> text; pos = 0;
        Counts left = side(); pos++; // Consume '='.
        Counts right = side();
        cout << (left == right ? 'Y' : 'N') << '\n';
    }
    return 0;
}
