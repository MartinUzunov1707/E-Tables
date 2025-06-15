#pragma once
#include "Cell.h"
class Command
{
protected :
	Cell* target;
	char* arg;
public:
	virtual void execute() = 0;
};

