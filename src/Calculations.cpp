#include "Calculations.h"
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::clog;
using std::endl;

double Calculations::m_map(const double& currentVal, const double& range1, const double& range2, const double& range3, const double& range4) const
{
    if(range2 == range1)
    {
        cerr << "Could Not Map While Length of Original Range is Zero.";
        return 0;
    }
    return (range3 + (currentVal - range1) * (range4 - range3) / (range2 - range1));
}

int Calculations::compare(const vector<pair<int, int>> &Vec1, const vector<pair<int, int>> &Vec2) const
{
    if(Vec1.size() != Vec2.size())
    {
        cerr << "Failed to Compare Two Vector With Different Length.";
        return 0;
    }
    int temp = 0;
    vector<pair<int, int>>::size_type Length = Vec1.size();
    for(decltype(Length) i = 0; i < Length; i++)
    {
        if(Vec1[i].first == Vec2[i].first)
            ++temp;
    }
    //clog << "temp: " << temp << endl;
    return temp;
}

cTendency Calculations::tendencyCal(const int& windowLen) const
{
    cTendency tendency;
    int Length = log.size();
    if(windowLen < 1 || Length < windowLen)
    {
        cerr << "Window Length is Too Long.";
        return tendency;
    }
    vector<pair<int, int>> Vec1, Vec2;
    Vec1.assign(log.end() - windowLen, log.end());
    for(int i = 0; i < Length - windowLen; i++)
    {
        Vec2.assign(log.begin() + i, log.begin() + i + windowLen);
        if(compare(Vec1, Vec2) == windowLen)
        {
            //clog << "switch: " << (log.begin() + i + windowLen)->first << endl;
            switch((log.begin() + i + windowLen)->first)
            {
                case 1: tendency.mTenStone += 1; break;
                case 2: tendency.mTenScissors += 1; break;
                case 3: tendency.mTenCloth += 1; break;
                default: cerr << "Number in Log Out of Range.";
            }
            tendency *= m_map(i, 0, Length - windowLen, 0.2, 1);
            //clog << tendency.mTenStone <<", "<<tendency.mTenScissors<<", "<<tendency.mTenCloth<<endl;
        }
    }
    return tendency;
}
Calculations::Calculations()
{
    //ctor
}

int Calculations::random() const
{
    return rand()%3 + 1;
}

cResult Calculations::judge(const int &player, const int &computer)
{
    cResult res;
    log.push_back(res.choices = make_pair(player, computer));
    res.result = computer - player;
    if(res.result == 2 || res.result == -2)
    {
        res.result /= -2;
    }
    return res;
}


int Calculations::predict(const unsigned int &minWindowLen, const unsigned int &maxWindowLen) const // const member function can only call const function
{                                                                                                   // in this case random() has to be const
    pair<int, double> temp;
    cTendency tendency;
    for(auto i = minWindowLen; i < maxWindowLen; i++)
    {
        tendency += tendencyCal(i);
    }
    if(tendency.useable())
    {
        //find biggest
        temp = (tendency.mTenStone > tendency.mTenScissors) ? make_pair(1, tendency.mTenStone) : make_pair(2, tendency.mTenScissors);
        temp = (temp.second > tendency.mTenCloth) ? temp : make_pair(3, tendency.mTenCloth);
        return temp.first;
    }
    else
        return random();
}

int Calculations::counterCal(const int &Val) const
{
    switch(Val)
    {
        case 1: return 3;
        case 2: return 1;
        case 3: return 2;
        default:
            cerr << "Fail to Calculate Counter Choice.";
            return 0;
    }
}

