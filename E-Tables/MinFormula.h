#pragma once
#include "Formula.h"
class MinFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const;
public:
	double calculate() const override;
	const char* evaluate() const override;
	MinFormula(char** args, int length);
	~MinFormula();
};

