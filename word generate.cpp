#include <iostream>
#include <x86intrin.h>   // for __rdtsc()
using namespace std;

int lcg(int &Xi, int a, int c, int m) {
    Xi = (a * Xi + c) % m;
    return Xi;
}

void word(int wsize) {
    char letters[26] = {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    int Xi = __rdtsc() % 26;  // initial seed
    int a = 7, c = 3, m = 26; // better LCG parameters

    string result = "";
    for (int i = 0; i < wsize; i++) {
        unsigned long long noise = __rdtsc();
        Xi ^= (noise & 0xFFFF);   // stir extra entropy
        int r = lcg(Xi, a, c, m);
        result += letters[r];
    }

    cout << "FINAL WORD: " << result << endl;
}

int main() {
    word(5);
}

