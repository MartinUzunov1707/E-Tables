#pragma once
#include "Formula.h"

class MaxFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const;
public:
	double calculate() const override;
	const char* evaluate() const override;
	MaxFormula(char** args, int length);
	~MaxFormula();
};


