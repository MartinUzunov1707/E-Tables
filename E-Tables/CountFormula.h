#pragma once
#include "Formula.h"
class CountFormula :
    public Formula
{
private:
	double evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const;
public:
	double calculate(MyString& errorMessage) const override;
	void evaluate(MyString& errorMessage, MyString& result) const override;
	CountFormula(char** args, int length);
	~CountFormula();
};

