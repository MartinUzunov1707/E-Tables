#pragma once
#include "Cell.h"
class NumCell :
    public Cell
{
private:
    double value;
public:
    NumCell(char x, int y, double value);
    void setValue(double value);
    double evaluate() override;
};

