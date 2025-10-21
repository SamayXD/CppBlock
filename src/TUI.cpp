#include "TUI.h"
#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

TUI::TUI(Blockchain& bc)
    : blockchain(bc), currentWallet(Wallet::generateAddress()), running(true) {}

void TUI::run() {
    Utils::clearScreen();
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║              🔗 BLOCKCHAIN SIMULATOR 🔗                    ║\n";
    cout << "║                   Version 1.0                              ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";

    currentWallet.display();
    Utils::waitForEnter();

    while (running) {
        displayMainMenu();
    }
}

void TUI::displayMainMenu() {
    Utils::clearScreen();
    currentWallet.display();

    cout << "\n╔════════════════ MAIN MENU ═════════════════╗\n";
    cout << "║  1. 💸 Create Transaction                  ║\n";
    cout << "║  2. ⛏️  Mine Block                          ║\n";
    cout << "║  3. 📊 View Blockchain                     ║\n";
    cout << "║  4. 💰 Check Balance                       ║\n";
    cout << "║  5. 📝 View Pending Transactions           ║\n";
    cout << "║  6. ✅ Validate Blockchain                 ║\n";
    cout << "║  7. 👤 Change Wallet                       ║\n";
    cout << "║  8. 📈 View Statistics                     ║\n";
    cout << "║  9. 🚪 Exit                                ║\n";
    cout << "╚════════════════════════════════════════════╝\n";

    int choice = getIntInput("Enter choice");

    switch (choice) {
        case 1: handleCreateTransaction(); break;
        case 2: handleMineBlock(); break;
        case 3: handleViewBlockchain(); break;
        case 4: handleCheckBalance(); break;
        case 5: handleViewPending(); break;
        case 6: handleValidateChain(); break;
        case 7: handleChangeWallet(); break;
        case 8: handleViewStats(); break;
        case 9: running = false; cout << "\n👋 Goodbye!\n"; break;
        default: cout << "❌ Invalid choice\n"; Utils::waitForEnter();
    }
}

void TUI::handleCreateTransaction() {
    Utils::clearScreen();
    Utils::printHeader("CREATE TRANSACTION");

    string receiver = getInput("Enter receiver address");
    double amount = getDoubleInput("Enter amount");

    Transaction tx(currentWallet.getAddress(), receiver, amount);
    blockchain.addTransaction(tx);

    Utils::waitForEnter();
}

void TUI::handleMineBlock() {
    Utils::clearScreen();
    Utils::printHeader("MINE BLOCK");

    blockchain.minePendingTransactions(currentWallet.getAddress());

    Utils::waitForEnter();
}

void TUI::handleViewBlockchain() {
    Utils::clearScreen();
    blockchain.displayChain();
    Utils::waitForEnter();
}

void TUI::handleCheckBalance() {
    Utils::clearScreen();
    Utils::printHeader("CHECK BALANCE");

    string address = getInput("Enter address (or press ENTER for current wallet)");
    if (address.empty()) {
        address = currentWallet.getAddress();
    }

    double balance = blockchain.getBalance(address);

    cout << "\n┌─ Balance ──────────────────────────────┐\n";
    cout << "│ Address: " << address << "\n";
    cout << "│ Balance: " << fixed << setprecision(2) << balance << " coins\n";
    cout << "└────────────────────────────────────────┘\n";

    Utils::waitForEnter();
}

void TUI::handleViewPending() {
    Utils::clearScreen();
    blockchain.displayPendingTransactions();
    Utils::waitForEnter();
}

void TUI::handleValidateChain() {
    Utils::clearScreen();
    Utils::printHeader("VALIDATE BLOCKCHAIN");

    bool valid = blockchain.isChainValid();

    if (valid) {
        cout << "\n✅ Blockchain is VALID\n";
        cout << "All blocks are properly linked and mined.\n";
    } else {
        cout << "\n❌ Blockchain is INVALID\n";
        cout << "Tampering detected or mining requirements not met.\n";
    }

    Utils::waitForEnter();
}

void TUI::handleChangeWallet() {
    Utils::clearScreen();
    Utils::printHeader("CHANGE WALLET");

    cout << "1. Generate new wallet\n";
    cout << "2. Enter existing wallet address\n";

    int choice = getIntInput("Choice");

    if (choice == 1) {
        currentWallet = Wallet(Wallet::generateAddress());
        cout << "✅ New wallet generated\n";
    } else if (choice == 2) {
        string address = getInput("Enter wallet address");
        currentWallet = Wallet(address);
        cout << "✅ Wallet changed\n";
    }

    currentWallet.display();
    Utils::waitForEnter();
}

void TUI::handleViewStats() {
    Utils::clearScreen();
    Utils::printHeader("BLOCKCHAIN STATISTICS");

    cout << "┌─ Stats ────────────────────────────────┐\n";
    cout << "│ Total Blocks:        " << blockchain.getChainLength() << "\n";
    cout << "│ Pending Transactions: " << blockchain.getPendingTransactionsCount() << "\n";
    cout << "│ Mining Difficulty:    " << blockchain.getDifficulty() << "\n";
    cout << "│ Mining Reward:        " << blockchain.getMiningReward() << " coins\n";
    cout << "│ Your Balance:         " << blockchain.getBalance(currentWallet.getAddress()) << " coins\n";
    cout << "└────────────────────────────────────────┘\n";

    Utils::waitForEnter();
}

string TUI::getInput(const string& prompt) {
    cout << "\n" << prompt << ": ";
    string input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    return input;
}

double TUI::getDoubleInput(const string& prompt) {
    cout << "\n" << prompt << ": ";
    double value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt << ": ";
    }
    return value;
}

int TUI::getIntInput(const string& prompt) {
    cout << "\n" << prompt << ": ";
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt << ": ";
    }
    return value;
}