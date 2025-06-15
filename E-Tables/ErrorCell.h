#pragma once
#include "Cell.h"

class ErrorCell :
    public Cell
{
public:
    ErrorCell(int x, char y);
    double evaluate() override;
    const char* toString() const override;
    virtual Cell* clone() override;
    virtual void clear() override;
};

