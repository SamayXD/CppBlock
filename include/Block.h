#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include "Transaction.h"

class Block {
private:
    int index;
    long timestamp;
    std::vector<Transaction> transactions;
    std::string previousHash;
    std::string hash;
    int nonce;

    std::string calculateHash() const;
    std::string transactionsToString() const;

public:
    Block(int idx, const std::vector<Transaction>& trans, const std::string& prevHash);

    // mining
    void mineBlock(int difficulty);

    // getters
    int getIndex() const {return index;}
    std::string getHash() const {return hash;}
    std::string getPreviousHash() const {return previousHash;}
    int getNonce() const {return nonce;}
    const std::vector<Transaction>& getTransactions() const {return transactions;}

    //display
    void display() const;
};

#endif