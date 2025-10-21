#include "Wallet.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

Wallet::Wallet(const std::string &addr) : address(addr) {}

void Wallet::display() const {
    cout << "\n┌─ Current Wallet ──────────────────────┐\n";
    cout << "│ Address: " << address << "\n";
    cout << "└────────────────────────────────────────┘\n";
}

// string Wallet::generateAddress() {
//     srand(time(nullptr));
//     stringstream ss;
//     ss << "ADDR";
//     for (int i = 0; i < 8; i++) {
//         ss << hex << (rand() % 16);
//     }
//     return ss.str();
// }


std::string Wallet::generateAddress() {
    srand(time(nullptr));
    stringstream ss;
    ss << "ADDR";
    for (int i = 0; i < 8; i++) {
        ss << hex << (rand() % 16);
    }

    return ss.str();
}

