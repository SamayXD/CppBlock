#ifndef WALLET_H
#define WALLET_H

#include <string>

class Wallet {
private:
    std::string address;

public:
    Wallet(const std::string& addr);

    //getter
    std::string getAddress() const {return address;}

    // display
    void display() const;

    // generate address (random)
    static std::string generateAddress();
};

#endif