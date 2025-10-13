#ifndef TUI_H
#define TUI_H

#include <string>
#include "Blockchain.h"
#include "Wallet.h"

class TUI {
private:
    Blockchain& blockchain;
    Wallet currentWallet;
    bool running;

    // menu fns
    void displayMainMenu();
    void handleCreateTransaction();
    void handleMineBlock();
    void handleViewBlockchain();
    void handleCheckBalance();
    void handleViewPending();
    void handleValidateChain();
    void handleChangeWallet();
    void handleViewStats();

    //helper fns
    std::string getInput(const std::string& prompt);
    double getDoubleInput(const std::string& prompt);
    int getIntInput(const std::string& prompt);

private:
    TUI(Blockchain& bc);

    void run();
};


#endif