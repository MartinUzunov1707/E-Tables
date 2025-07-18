#pragma once
#include "Cell.h"

class NullCell :
    public Cell
{
public:
    NullCell(int x, char y);
    double evaluate() override;
    const char* toString() const override;
    virtual Cell* clone() override;
	virtual void clear() override;
};

