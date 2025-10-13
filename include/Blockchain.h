#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include "Block.h"
#include "Transaction.h"

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    std::vector<Transaction> pendingTransactions;
    double miningReward;

   Block getLatestBlock() const;

public:
    // default vals
    Blockchain(int diff = 3, double reward = 50.0);

   // transaction operations
    void addTransaction(const Transaction& transaction);
    void minePendingTransactions(const std::string& minerAddress);

    // query ops
    double getBalance(const std::string& address) const;
    bool isChainValid() const;
    int getChainLength() const { return chain.size(); }
    int getPendingTransactionsCount() const { return pendingTransactions.size(); }

    // display
    void displayChain() const;
    void displayPendingTransactions() const;
    void displayBlock(int index) const;

    //getters
    int getDifficulty() const { return difficulty; }
    double getMiningReward() const { return miningReward;}
};

#endif