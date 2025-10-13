#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils{
public:
    // SHA256 hash fn
    static std::string sha256(const std::string& str);

    // helper fn for SHA256
    static unsigned int rightRotate(unsigned int value, unsigned int count);

    // display helpers
    static void clearScreen();
    static void printHeader(const std::string& title);
    static void printSeparator();
    static void waitForEnter();
};

#endif