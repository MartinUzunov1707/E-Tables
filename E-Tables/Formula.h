#pragma once
#include "MyString.h"
class Formula
{
protected:
	char** args;
	int lengthOfArgs;
public:
	virtual double calculate(MyString& errorMessage) const = 0;
	virtual void evaluate(MyString& errorMessage, MyString& result) const = 0;
	virtual ~Formula() = default;
};

