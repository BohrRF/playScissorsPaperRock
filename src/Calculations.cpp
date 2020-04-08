#include "Calculations.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>

using std::cerr;
using std::clog;
using std::endl;
using std::fstream;
using std::ios;
using std::exception;
using std::sort;


const unsigned int MINWINDOWLEN = 1;
const unsigned int MAXWINDOWLEN = 5;

int cLog::readLog(const string& fileName)
{
    cResult temp;
    vector<cResult> logtemp;
    char num[2] = {0};

    int i = 0;
    sprintf(num, "%d", i);
    fstream fp(fileName + num + ".txt", ios::in);

    while(fp.good())
    {
        clog << "Reading File " << i << endl;
        while(fp >> temp.choices.first >> temp.choices.second >> temp.result)
        {
            //clog << temp.choices.first << ", " << temp.choices.second << ", " << temp.result << endl;
            logtemp.push_back(temp);
        }
        log.push_back(logtemp);
        logtemp.clear();
        fp.close();
        clog << "Finished." << endl;
        sprintf(num, "%d", ++i);
        fp.open(fileName + num + ".txt", ios::in);
    }
    return i;
}

unsigned int cLog::saveLog(const string& fileName, const vector<cResult> &slog)
{
    char num[2] = {0};
    unsigned int i = 0, line = 0;
    sprintf(num, "%d", i);
    fstream fp(fileName + num + ".txt", ios::in);
    while(fp.good())
    {
        fp.close();
        sprintf(num, "%d", ++i);
        fp.open(fileName + num + ".txt", ios::in);
    }
    fp.open(fileName + num + ".txt", ios::out);
    for(const auto &it: slog)
    {
        fp << it.choices.first << '\t' << it.choices.second << '\t' << it.result << endl;
        ++line;
    }
    fp.close();
    return line;
}

double Calculations::m_map(const double& currentVal, const double& range1, const double& range2, const double& range3, const double& range4) const
{
    if(range2 == range1)
    {
        cerr << "Could Not Map While Length of Original Range is Zero.";
        return 0;
    }
    return (range3 + (currentVal - range1) * (range4 - range3) / (range2 - range1));
}

int Calculations::compare(const vector<cResult> &Vec1, const vector<cResult> &Vec2) const
{
    if(Vec1.size() != Vec2.size())
    {
        cerr << "Failed to Compare Two Vector With Different Length.";
        return 0;
    }
    int temp = 0;
    vector<cResult>::size_type Length = Vec1.size();
    for(decltype(Length) i = 0; i < Length; i++)
    {
        if(Vec1[i].choices.first == Vec2[i].choices.first)
            ++temp;
    }
    //clog << "temp: " << temp << endl;
    return temp;
}


cTendency Calculations::tendencyCal(const int& windowLen, const vector<cResult> &logsec) const
{
    cTendency tendency;
    int Length = logsec.size();
    if(windowLen < 1 || Length < windowLen)
    {
        cerr << "Window Length is Too Long.";
        return tendency;
    }
    vector<cResult> Vec1, Vec2;
    Vec1.assign(logsec.end() - windowLen, logsec.end()); // len = 1    o, [o, end)
    for(int i = 0; i < Length - windowLen; i++)
    {
        Vec2.assign(logsec.begin() + i, logsec.begin() + i + windowLen);  //i = 0, len = 1                beg, [o , o)
                                                                    //i = Length - windowLen - 1    [o, o), end
        if(compare(Vec1, Vec2) == windowLen)
        {
            //clog << "switch: " << (log.begin() + i + windowLen)->first << endl;
            switch((logsec.begin() + i + windowLen)->choices.first)
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
    weight.assign(5, 1);
}

int Calculations::random() const
{
    return rand()%3 + 1;
}

cResult Calculations::judge(const int &player, const int &computer)
{
    cResult res;
    res.choices = make_pair(player, computer);
    res.result = computer - player;
    if(res.result == 2 || res.result == -2)
    {
        res.result /= -2;
    }
    log.push_back(res);
    return res;
}

int Calculations::judgeWithoutSave(const int &player, const int &computer) const
{
    int res = computer - player;
    if(res == 2 || res == -2)
    {
        res /= -2;
    }
    return res;
}

// const member function can only call const function
// in this case random() has to be const
int Calculations::predict(const unsigned int& minWindowLen, const unsigned int& maxWindowLen, const vector<cResult>& logsec) const
{
    cTendency tendency;
    for(auto i = minWindowLen; i <= maxWindowLen; i++)
    {
        try
        {
            tendency += (tendencyCal(i, logsec) *= weight.at(i - minWindowLen));
        }
        catch(const exception &exc)
        {
            cerr << exc.what() << endl;
        }
        catch(...)
        {
            cerr << "ERROR" << endl;
        }
    }
    if(tendency.useable())
    {
        //find biggest
        double sum = 0;
        vector<pair<int, double>> temp;
        temp.push_back(make_pair(1, tendency.mTenStone));
        temp.push_back(make_pair(2, tendency.mTenScissors));
        temp.push_back(make_pair(3, tendency.mTenCloth));
        for(const auto &it : temp)
            sum += it.second;
        for(auto &it : temp)
            it.second /= sum;
        sort(temp.begin(), temp.end(), [](pair<int, double>lval, pair<int, double> rval)
                                         {
                                             return lval.second > rval.second;
                                         });
        if(abs(temp[0].second - temp[1].second) < 0.1)
        {
            return temp[(judgeWithoutSave(temp[0].first, temp[1].first) + 1) / 2].first;
        }
        else
            return temp[0].first;
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
