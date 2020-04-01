#include "msg.h"
#include "Calculations.h"

#include <string>
#include <vector>


using std::vector;

int main()
{
    msg mes;
    Calculations cal;
    mes.showHello();
    for(int i = 0; i < 10; i++)
    {
        mes.showResult( cal.judge(mes.getPlayerChoice(), cal.random()) );
    }
    mes.showBegin();
    while(1)
    {
        mes.showResult( cal.judge(mes.getPlayerChoice(), cal.counterCal(cal.predict(2, 4)) ) );
    }
    return 0;
}

