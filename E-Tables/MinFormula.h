#pragma once
#include "Formula.h"
class MinFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const;
public:
	double calculate(MyString& errorMessage) const override;
	void evaluate(MyString& errorMessage, MyString& result) const override;
	MinFormula(char** args, int length);
	~MinFormula();
};

