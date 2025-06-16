#pragma once
#include "Formula.h"

class LenFormula :public Formula
{
public:
	double calculate() const override;
	const char* evaluate() const override;
	LenFormula(char** args, int length);
	~LenFormula();
};

