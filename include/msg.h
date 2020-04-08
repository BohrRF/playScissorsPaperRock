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
    unsigned int win = 0;
    unsigned int lose = 0;

    msg();
    string getName();
    void showHello();
    void showBegin();
    void showResult(cResult result);
    void showRate();
    const string trans(int choice);
    int getPlayerChoice();
};

#endif // MSG_H
