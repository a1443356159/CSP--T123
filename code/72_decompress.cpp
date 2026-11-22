#include <cstdio>
#include <vector>
using namespace std;
vector<unsigned char> input, output;
int pos;
int hex_value(int c) { return c <= '9' ? c - '0' : c - 'a' + 10; }
unsigned int little_endian(int count) {
    unsigned int value = 0;
    for (int i = 0; i < count; i++)
        value |= (unsigned int)input[pos++] << (8 * i);
    return value;
}
int main() {
    int s; scanf("%d", &s);
    input.reserve(s);
    for (int i = 0; i < s; i++) {
        char a, b; scanf(" %c %c", &a, &b);
        input.push_back((unsigned char)(hex_value(a) * 16 + hex_value(b)));
    }
    unsigned int length = 0, shift = 0, byte;
    do {
        byte = input[pos++];
        length |= (byte & 127u) << shift; shift += 7;
    } while (byte & 128u);
    output.reserve(length);
    while (pos < s) {
        unsigned int tag = input[pos++], type = tag & 3u;
        unsigned int count, offset;
        if (type == 0) {
            unsigned int high = tag >> 2;
            count = high < 60 ? high + 1 : little_endian(high - 59) + 1;
            for (unsigned int i = 0; i < count; i++)
                output.push_back(input[pos++]);
        } else {
            if (type == 1) {
                count = ((tag >> 2) & 7u) + 4;
                offset = (tag >> 5) * 256 + input[pos++];
            } else {
                count = (tag >> 2) + 1; offset = little_endian(2);
            }
            // Recompute the source after every appended byte: overlap is valid.
            for (unsigned int i = 0; i < count; i++) {
                unsigned char value = output[output.size() - offset];
                output.push_back(value);
            }
        }
    }
    for (unsigned int i = 0; i < output.size(); i++) {
        printf("%02x", (unsigned int)output[i]);
        if (i % 8 == 7 || i + 1 == output.size()) printf("\n");
    }
    return 0;
}
