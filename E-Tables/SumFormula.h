#pragma once
#include "Formula.h"

class SumFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const;
public:
	double calculate(MyString& errorMessage) const override;
	void evaluate(MyString& errorMessage, MyString& result) const override;
	SumFormula(char** args, int length);
	~SumFormula();
};

