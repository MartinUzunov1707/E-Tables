#pragma once
#include "Formula.h"

class SumFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const;
public:
	double calculate() const override;
	char* evaluate() const override;
	SumFormula(char** args, int length);
	double calculate() const;
};

