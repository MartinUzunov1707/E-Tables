#pragma once
#include "Formula.h"

class SumFormula :
    public Formula
{
public:
	SumFormula(char** args, int length);
	double calculate() const;
};

