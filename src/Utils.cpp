#include "Utils.h"
#include "iostream"
#include "sstream"
#include "iomanip"

using namespace std;

std::string Utils::sha256(const string &str) {

    // initial hash values (h0 - h7) defined by sha256 standard
    unsigned int h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // 64 constant 32-bit words, also defined by 256 standard
    // these are used in each round of processing
    static const unsigned int k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    vector<unsigned char> data(str.begin(), str.end());
    unsigned long long bitLen = data.size() * 8;

    data.push_back(0x80);
    while ((data.size() % 64) != 56) {
        data.push_back(0x00);
    }

    for (int i = 7; i >= 0; i--) {
        data.push_back((bitLen >> (i * 8)) & 0xff);
    }

    for (size_t chunk = 0; chunk < data.size() ; chunk += 64) {
        unsigned int w[64] = {0};

        for (int i = 0; i < 16; i++) {
            w[i] =  (data[chunk + i * 4] << 24) |
                        (data[chunk + i * 4 + 1] << 15) |
                            (data[chunk + i * 4 + 2 ] << 8) |
                                (data[chunk + i * 4 + 3]);
        }

        for (int i = 16; i < 64; i++) {
            unsigned int s0 = rightRotate(w[i-15], 7) ^ rightRotate(w[i-15], 18) ^ (w[i-15]>>3);
            unsigned int s1 = rightRotate(w[i-2], 17) ^ rightRotate(w[i-2], 19) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }
        unsigned int a = h[0], b = h[1], c = h[2], d = h[3];
        unsigned int e = h[4], f = h[5], g = h[6], hh = h[7];

        for (int i = 0; i < 64; i++) {
            unsigned int S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
            unsigned int ch = (e & f) ^ ((~e) & g);
            unsigned int temp1 = hh + S1 + ch + k[i] + w[i];
            unsigned int S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
            unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned int temp2 = S0 + maj;

            hh = g; g = f; f = e; e = d + temp1;
            d = c; c = b; b = a; a = temp1 + temp2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }
    stringstream ss;
    for (int i = 0; i < 8; i++) {
        ss << hex << setw(8) << setfill('0') << h[i];
    }
    return ss.str();
}

unsigned int Utils::rightRotate(unsigned int value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}


void Utils::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Utils::printHeader(const string& title) {
    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    cout << "║  " << setw(55) << left << title << "  ║\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
}

void Utils::printSeparator() {
    cout << "────────────────────────────────────────────────────────────\n";
}

void Utils::waitForEnter() {
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}


