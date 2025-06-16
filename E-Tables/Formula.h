#pragma once
#include "MyString.h"
class Formula
{
protected:
	char** args;
	int lengthOfArgs;
public:
	virtual double calculate(MyString& errorMessage) const = 0;
	virtual const char* evaluate() const = 0;
	virtual ~Formula() = default;
};

