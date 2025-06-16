#pragma once
#include "Formula.h"

class SubStringFormula :
    public Formula
{
public:
	double calculate(MyString& errorMessage) const override;
	void evaluate(MyString& errorMessage, MyString& result) const override;
	SubStringFormula(char** args, int length);
	~SubStringFormula();
};

