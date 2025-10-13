#ifndef CPPBLOCK_TRANSACTION_H
#define CPPBLOCK_TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string sender;
    std::string receiver;
    double amount;
    long timestamp;

public:
    // constructor
    Transaction(const std::string& from, const std::string& to, double amt);

    // getters
    std::string getSender() const {return sender;}
    std::string getReceiver() const {return receiver;}
    double getAmount() const {return amount;}
    long getTimestamp() const {return timestamp;}

    // convert to string for hashing
    std::string toString() const;

    // display
    void display() const;

    // validation
    bool isValid() const;
};

#endif