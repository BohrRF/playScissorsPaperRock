#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <string>
#include <vector>
using std::vector;
using std::pair;
using std::make_pair;
using std::string;

extern const unsigned int MINWINDOWLEN, MAXWINDOWLEN;

class cResult
{
public:
    int result;
    pair<int, int> choices;
};

class cLog
{
public:
    vector<vector<cResult>> log;
    int readLog(const string &fileName);
    unsigned int saveLog(const string& fileName, const vector<cResult> &slog);
};

class cTendency
{
public:
    double mTenStone;
    double mTenScissors;
    double mTenCloth;
    cTendency()
    {
        mTenCloth = 0;
        mTenScissors = 0;
        mTenStone = 0;
    }
    bool useable() const
    {
        return (mTenCloth + mTenScissors + mTenStone) > 1e-2;
    }
    cTendency& operator+=(const cTendency &rVal)
    {
        this->mTenCloth += rVal.mTenCloth;
        this->mTenScissors += rVal.mTenScissors;
        this->mTenStone += rVal.mTenStone;
        return *this;
    }
    cTendency& operator*=(const double &rVal)
    {
        this->mTenCloth *= rVal;
        this->mTenScissors *= rVal;
        this->mTenStone *= rVal;
        return *this;
    }
};


class Calculations
{
    double m_map(const double &currentVal, const double &range1, const double &range2, const double &range3, const double &range4) const;
    int compare(const vector<cResult> &Vec1, const vector<cResult> &Vec2) const;
    cTendency tendencyCal(const int &windowLen, const vector<cResult> &log) const;

protected:
    int judgeWithoutSave(const int &player, const int &computer) const;

public:
    vector<double> weight;
    vector<cResult> log;
    Calculations();
    int random() const;
    cResult judge(const int &player, const int &computer);
    int predict(const unsigned int &minWindowLen, const unsigned int &maxWindowLen, const vector<cResult> &log) const;
    int counterCal(const int &Val) const;
};



#endif // CALCULATIONS_H





