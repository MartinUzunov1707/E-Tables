#pragma once
#include "Formula.h"

class LenFormula :public Formula
{
public:
	double calculate(MyString& errorMessage) const override;
	const char* evaluate() const override;
	LenFormula(char** args, int length);
	~LenFormula();
};

