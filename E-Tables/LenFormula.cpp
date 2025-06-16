#include "LenFormula.h"
#include "Engine.h"

double LenFormula::calculate(MyString& errorMessage) const
{
	if (lengthOfArgs > 1) {
		errorMessage = "Argument of LEN function should only be a single range!";
		return -1;
	}
	double length = 0;
	if (args[0][0] >= 'A' && args[0][0] <= Engine::getTable().getConfig().getMaxRows() + 'A') {
		int xCoordinate = args[0][1] - '1';
		int yCoordinate = args[0][0] - 'A';
		MyString currentArg = args[0];
		if (!currentArg.contains(':')) {
			const char* cellToString = Engine::getTable().getByIndex(xCoordinate, yCoordinate).toString();
			//this specification comes from the fact that toString() method on a BooleanCell return either f or t, for ease of reading and writing to files.
			if (strcmp(cellToString, "t")) return 4;
			else if (strcmp(cellToString, "f")) return 5;
			return  Utils::getStringLength(cellToString) - 1;	
		}
		else {
			
			errorMessage = "Argument of LEN function should be a Cell!";
			return -1;
		}
	}
	else {
		errorMessage = "Argument of LEN function should only be a Cell!";
		return -1;
	}
}

void LenFormula::evaluate(MyString& errorMessage, MyString& result) const
{
    result = "";
}

LenFormula::LenFormula(char** args, int length)
{
    this->args = args;
    this->lengthOfArgs = length;
}

LenFormula::~LenFormula()
{
    for (int i = 0; i < this->lengthOfArgs; i++) {
        delete[] args[i];
    }
    delete[] args;
}
