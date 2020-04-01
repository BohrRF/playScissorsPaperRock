#include "msg.h"
#include "Calculations.h"
#include <conio.h>

msg::msg()
{
    //ctor
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
    ++n;
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
            break;
        case 0 : cout << "Tie" << endl;
            break;
        case 1 : cout << "You Win" << endl;
            break;
        default: cerr << "Error" << endl;
    }

}


