#ifndef WEIGHTOPTIMIZE_H
#define WEIGHTOPTIMIZE_H

#include "Calculations.h"

class weightOptimize : public Calculations
{
    unsigned int windowRange;

    vector<int> gradCal(const double &diff);
    unsigned int lossCal() const;

public:
    string fileName;
    cLog historylog;

    weightOptimize(const string &name);
    void Optimize();
};

#endif // WEIGHTOPTIMIZE_H
