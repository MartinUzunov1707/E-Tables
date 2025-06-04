#pragma once
#include "Cell.h"
class NumCell :
    public Cell
{
private:
    double value;
public:
    NumCell(int x, char y, double value);
    void setValue(double value);
    double evaluate() override;
};

