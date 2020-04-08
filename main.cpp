#include "msg.h"
#include "Calculations.h"
#include "weightOptimize.h"

#include <string>
#include <vector>

using std::vector;


int main()
{
    string name = "test";
    cLog log;
    msg mes;
    Calculations cal;
    weightOptimize opt(name);

    opt.Optimize();

    cal.weight = opt.weight;

    mes.showHello();
    for(int i = 0; i < 10; i++)
    {
        mes.showResult( cal.judge(mes.getPlayerChoice(), cal.random()) );
        mes.showRate();
    }
    mes.showBegin();
    for(int i = 0; i < 200; i++)
    {
        mes.showResult( cal.judge(mes.getPlayerChoice(), cal.counterCal(cal.predict(MINWINDOWLEN, MAXWINDOWLEN, cal.log)) ) );
        mes.showRate();
    }
    log.saveLog(name, cal.log);
    return 0;
}

