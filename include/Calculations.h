#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>
using std::vector;
using std::pair;
using std::make_pair;

class cResult
{
public:
    int result;
    pair<int, int> choices;
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
    int compare(const vector<pair<int, int>> &Vec1, const vector<pair<int, int>> &Vec2) const;
    cTendency tendencyCal(const int &windowLen) const;
public:
    vector<pair<int, int>> log;
    Calculations();
    int random() const;
    cResult judge(const int &player, const int &computer);
    int predict(const unsigned int &minWindowLen, const unsigned int &maxWindowLen) const;
    int counterCal(const int &Val) const;
};

#endif // CALCULATIONS_H
