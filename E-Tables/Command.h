#pragma once
#include "Cell.h"
class Command
{
private :
	Cell* target;
	Argument arg;
public:
	void execute();
};

