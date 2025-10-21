#include <iostream>
#include "Blockchain.h"
#include "TUI.h"

using namespace std;

int main() {
    try {
        // Create blockchain with difficulty 3 and reward 50
        Blockchain myBlockchain(3, 50.0);

        // Create and run TUI
        TUI interface(myBlockchain);
        interface.run();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}