#include "SubStringFormula.h"
#include "Engine.h"

double SubStringFormula::calculate(MyString& errorMessage) const
{
    return 0.0;
}

void SubStringFormula::evaluate(MyString& errorMessage, MyString& result) const
{
	if (lengthOfArgs != 3) {
		errorMessage = "SubString formula should only have 3 arguments!";
		result = "\n";
	}
	double length = 0;
	if (args[0][0] >= 'A' && args[0][0] <= Engine::getTable().getConfig().getMaxRows() + 'A') {
		int xCoordinate = args[0][1] - '1';
		int yCoordinate = args[0][0] - 'A';
		MyString currentArg = args[0];
		if (!currentArg.contains(':')) {
			MyString cellToString = Engine::getTable().getByIndex(xCoordinate, yCoordinate).toString();
			//this specification comes from the fact that toString() method on a BooleanCell return either f or t, for ease of reading and writing to files.
			int startIndex = 0, length = 0;
			Utils::tryConvertToInt(args[1], startIndex);
			Utils::tryConvertToInt(args[2], length);
			//compensating for the opening quotation mark
			length++;
			if (startIndex < 0 || length < 0 || startIndex + length > cellToString.getLength()) {
				errorMessage = "Invalid parameters!";
				result = "\n";
			}
			result = cellToString.substr(startIndex, length);
		}
		else {

			errorMessage = "Argument of SubString function should be a Cell!";
			result = "\n";
		}
	}
	else {
		errorMessage = "Argument of SubString function should only be a Cell!";
		result = "\n";
	}
}

SubStringFormula::SubStringFormula(char** args, int length)
{
	this->args = args;
	this->lengthOfArgs = length;
}

SubStringFormula::~SubStringFormula()
{
	for (int i = 0; i < this->lengthOfArgs; i++) {
		delete[] args[i];
	}
	delete[] args;
}
