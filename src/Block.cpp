#include "Block.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

Block::Block(int idx, const std::vector<Transaction> &trans, const std::string &prevHash)
        : index(idx), transactions(trans), previousHash(prevHash), nonce(0){
        timestamp = time(nullptr);
        hash = calculateHash();
}

string Block::calculateHash() const {
        stringstream ss;
        ss << index << timestamp << transactionsToString() << previousHash << nonce;
        return Utils::sha256(ss.str());
}

std::string Block::transactionsToString() const {
        string result;
        for (const auto& tx : transactions) {
                result += tx.toString();
        }
        return result;
}

void Block::mineBlock(int difficulty) {
        string target(difficulty, '0');

        cout << "\n    Mining block #" << index << "...\n";
        cout << "Target: " << target << "...\n";

        int attempts = 0;
        while (hash.substr(0, difficulty) != target) {
                nonce++;
                hash = calculateHash();
                attempts++;

                if (attempts % 10000 == 0) {
                        cout << " Attempts" << attempts << " - Nonce: " << nonce << "\r" << flush;
                }
        }
}

void Block::display() const {
        cout << "\n╔══════════════════ BLOCK #" << index << " ══════════════════╗\n";
        cout << "║ Timestamp: " << ctime(&timestamp);
        cout << "║ Previous Hash: " << previousHash.substr(0, 16) << "...\n";
        cout << "║ Hash:          " << hash.substr(0, 16) << "...\n";
        cout << "║ Nonce:         " << nonce << "\n";
        cout << "║ Transactions:  " << transactions.size() << "\n";
        cout << "╚═══════════════════════════════════════════════════════════╝\n";

        for (const auto& tx : transactions) {
                tx.display();
        }
}


