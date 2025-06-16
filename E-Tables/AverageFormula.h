#pragma once
#include "Formula.h"
class AverageFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters, int& cellCounter) const;
public:
	double calculate() const override;
	const char* evaluate() const override;
	AverageFormula(char** args, int length);
	~AverageFormula();
};

