#pragma once
#include "Formula.h"

class LenFormula :public Formula
{
public:
	double calculate(MyString& errorMessage) const override;
	void evaluate(MyString& errorMessage, MyString& result) const override;
	LenFormula(char** args, int length);
	~LenFormula();
};

