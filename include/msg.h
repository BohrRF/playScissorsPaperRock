#ifndef MSG_H
#define MSG_H
#include "Calculations.h"

#include <iostream>
#include <ctime>
#include <string>

using std::endl;
using std::cout;
using std::cerr;
using std::cin;
using std::string;

class msg
{
public:
    unsigned int n = 0;

    msg();
    void showHello();
    void showBegin();
    void showResult(cResult result);
    const string trans(int choice);
    int getPlayerChoice();
};

#endif // MSG_H
