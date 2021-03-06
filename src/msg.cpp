#include "msg.h"
#include "Calculations.h"
#include <conio.h>

msg::msg()
{
    //ctor
}

string msg::getName()
{
    string temp;
    cout << "Name:";
    cin >> temp;
    return temp;
}


void msg::showHello()
{
    cout << "1.stone 2.scissors 3.cloth" << endl;
    cout << "First ten round to take sample" << endl;
    srand((unsigned)time(NULL));
}

void msg::showBegin()
{
    system("cls");
    cout << "1.stone 2.scissors 3.cloth" << endl;
    cout << "";
}


int msg::getPlayerChoice()
{
    int temp;
    cout << endl;
    cout << "Your Turn:";
    temp = getch() - 48;
    while(temp > 3 || temp <= 0)
    {
        cout << "Out of Range, Please Enter Again." << endl;
        cout << "Your Turn:";
        temp = getch() - 48;
    }
    cout << trans(temp) << endl;
    return temp;
}
const string msg::trans(int choice)
{
    switch(choice)
    {
        case 1: return "1.Stone";
        case 2: return "2.scissors";
        case 3: return "3.cloth";
        default: return "TRASLATE ERROR";
    }
}

void msg::showResult(cResult result)
{
    cout << "Computer: " << trans(result.choices.second) << endl;
    cout << "Result Of Turn " << n << ": ";
    switch(result.result)
    {
        case -1: cout << "Computer Win" << endl;
            ++lose; ++n;
            break;
        case 0 : cout << "Tie" << endl;
            ++n;
            break;
        case 1 : cout << "You Win" << endl;
            ++win; ++n;
            break;
        default: cerr << "Error" << endl;
    }
}
void msg::showRate()
{
    cout << "Win: " << 100.0 * win / n << "%, Tie: " << 100.0 * (n - win - lose) / n << "%, Lose: " << 100.0 * lose / n << "%" << endl;
}


