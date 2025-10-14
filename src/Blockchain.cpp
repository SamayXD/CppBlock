#include "Blockchain.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

Blockchain::Blockchain(int diff, double reward)
    : difficulty(diff), miningReward(reward){
    vector<Transaction> genesisTransactions;
    chain.push_back(Block(0, genesisTransactions, "0"));
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

void Blockchain::addTransaction(const Transaction &transaction) {
    if (transaction.isValid()) {
        pendingTransactions.push_back(transaction);
        cout << "Transaction Added to the pool\n";
    } else {
        cout << "Failed to add transaction\n";
    }
}

void Blockchain::minePendingTransactions(const std::string &minerAddress) {
    if (pendingTransactions.empty()) {
        cout << "No pending transactions\n";
        return;
    }

    Block newBlock(chain.size(), pendingTransactions, getLatestBlock().getHash());
    newBlock.mineBlock(difficulty);

    chain.push_back(newBlock);

    pendingTransactions.clear();
    pendingTransactions.push_back(Transaction("SYSTEM", minerAddress, miningReward));

    cout << "Mining Reward of " << miningReward << " added to the next block\n";
}

double Blockchain::getBalance(const string& address) const {
    double balance = 0;

    for (const auto& block : chain) {
        for (const auto& tx : block.getTransactions()) {
            if (tx.getSender() == address) {
                balance -= tx.getAmount();
            }
            if (tx.getReceiver() == address) {
                balance += tx.getAmount();
            }
        }
    }
    return balance;
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size() ; i++) {
        const Block& current = chain[i];
        const Block& previous = chain[i - 1];

       if (current.getHash() != current.calculateHash()) {
           return false;
       }

        if (previous.getHash() != current.getPreviousHash()) {
            return false;
        }

        string target(difficulty, '0');
        if (current.getHash().substr(0, difficulty) != target) {
            return false;
        }
    }

    return true;
}

void Blockchain::displayChain() const {
   Utils::printHeader("BLOCKCHAIN");
    cout << "Total Blocks: " << chain.size() << "\n";
    cout << "Difficulty: " << difficulty << "\n";
    Utils::printSeparator();

    for (const auto& block : chain) {
        block.display();
    }
}

void Blockchain::displayPendingTransactions() const {
    Utils::printHeader("PENDING TRANSACTIONS");
    cout << "Count: " << pendingTransactions.size() << "\n";
    Utils::printSeparator();

    if (pendingTransactions.empty()) {
        cout << "No pending Transactions\n";
    }else {
        for (const auto& tx : pendingTransactions) {
            tx.display();
        }
    }
}

void Blockchain::displayBlock(int index) const {
    if (index >= 0 && index < (int)chain.size()) {
        chain[index].display();
    }else {
        cout << "Blocks not  found\n";
    }
}
