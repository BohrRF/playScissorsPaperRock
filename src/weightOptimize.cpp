#include "weightOptimize.h"

#include <iostream>

using std::clog;
using std::endl;


weightOptimize::weightOptimize(const string &name)
{
    windowRange =  MAXWINDOWLEN - MINWINDOWLEN + 1;
    fileName = name;
}

unsigned int weightOptimize::lossCal() const
{
    unsigned int loss = 0;
    vector<cResult> temp;
    vector<cResult>::size_type Length = log.size();
    for(unsigned int i = 10; i < Length; i++)
    {
        temp.assign(log.begin(), log.begin() + i);
        if(judgeWithoutSave((log.begin() + i)->choices.first, predict(1, windowRange, temp)) == -1)
        {
            ++loss;
        }
    }
    return loss;
}

vector<int> weightOptimize::gradCal(const double &diff)
{
    vector<int> temp;
    for(unsigned int i = 0; i < windowRange; i++)
    {
        weight[i] -= diff;
        temp.push_back(lossCal());

        //clog << i << ':' << temp.back();

        weight[i] += diff;
        temp.back() -= lossCal();

        //clog << "-" << lossCal() << "=" << temp.back() << endl;
    }
    return temp;
}


void weightOptimize::Optimize()
{
    bool flag = true;
    double diff = 0.1, weightSum = 0;
    vector<int> temp;
    int losscheck = 0, losstemp = 0, j = 0;
    int num = historylog.readLog(fileName);
    weight[0] = 5;//8
    weight[1] = 5;//12
    weight[2] = 5;//5
    weight[3] = 5;//1
    weight[4] = 5;//1
    for(int i = 0; i < num; i++)
    {
        log.assign(historylog.log[i].begin(), historylog.log[i].end());
        diff = 0.1;
        while(1)
        {
            flag = false;
            weightSum = 0;
            temp = gradCal(diff);
            //clog << '(' << temp[0] << ", " << temp[1] << ", " << temp[2] << ", " << temp[3] << ", " << temp[4] << ')' << endl;
            for(const auto &it: temp)
            {
                flag += (it != 0);
            }
            if(flag)
            {
                for(decltype(temp.size()) i = 0; i < temp.size(); i++)
                {
                    weight[i] += 0.4 * diff * temp[i];
                }
                diff = 0.1;
            }
            else if(diff < 2)
            {
                diff += 0.2;
            }
            else
                break;
            for(const auto &it : weight)
                weightSum += it;

            if(j++ % 300 == 0)
            {
                if(losscheck != (losstemp = lossCal()))
                    losscheck = losstemp;
                else
                    break;
            }
            //clog << '(' << weight[0] << ", " << weight[1] << ", " << weight[2] << ", " << weight[3] << ", " << weight[4] << ')' << endl;
            //clog << "loss:" << lossCal() << "diff:" << diff << endl;

        }
        //system("cls");
        clog << "end of file " << i << endl;
        clog << '(' << weight[0] << ", " << weight[1] << ", " << weight[2] << ", " << weight[3] << ", " << weight[4] << ')' << endl;
        clog << "loss:" << lossCal() << "diff:" << diff << endl;
        getchar();
    }

}



