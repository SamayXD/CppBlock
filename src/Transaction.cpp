#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

Transaction::Transaction(const std::string &from, const std::string &to, double amt) : sender(from), receiver(to), amount(amt){
    timestamp = time(nullptr);
}

std::string Transaction::toString() const {
    return sender + receiver + to_string(amount) + to_string(timestamp);
}

void Transaction::display() const {
    cout << "  ┌─ Transaction ─────────────────────────┐\n";
    cout << "  │ From:   " << setw(30) << left << sender << " │\n";
    cout << "  │ To:     " << setw(30) << left << receiver << " │\n";
    cout << "  │ Amount: " << setw(30) << left << fixed << setprecision(2) << amount << " │\n";
    cout << "  │ Time:   " << setw(30) << left << ctime(&timestamp);
    cout << "  └───────────────────────────────────────┘\n";
}

bool Transaction::isValid() const {
    return amount > 0 && !sender.empty() && !receiver.empty();
}


