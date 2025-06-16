#pragma once
#include "Formula.h"
class AverageFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters, int& cellCounter) const;
public:
	double calculate(MyString& errorMessage) const override;
	void evaluate(MyString& errorMessage, MyString& result) const override;
	AverageFormula(char** args, int length);
	~AverageFormula();
};

