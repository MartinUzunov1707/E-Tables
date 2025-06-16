#include "MaxFormula.h"
#include "Engine.h"

double MaxFormula::evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const
{
	double max = INT_MIN;
	if (leftCell[0] >= 'A' && leftCell[0] <= Engine::getTable().getConfig().getMaxRows() - 'A'
		&& rightCell[0] >= 'A' && rightCell[0] <= Engine::getTable().getConfig().getMaxRows() - 'A') {
		int leftYCoordinate = leftCell[0] - 'A', leftXCoordinate = leftCell[1] - '1';
		int rightYCoordinate = rightCell[0] - 'A', rightXCoordinate = rightCell[1] - '1';
		int colDiff = rightCell[1] - leftCell[1], rowDiff = rightYCoordinate - leftYCoordinate;

		if (leftYCoordinate >= 0 && leftYCoordinate < Engine::getTable().getConfig().getMaxCols()
			&& rightYCoordinate >= 0 && rightYCoordinate < Engine::getTable().getConfig().getMaxCols()) {

			for (int i = 0; i <= rowDiff; i++) {
				for (int a = 0; a <= colDiff; a++) {
					Cell* target = &Engine::getTable().getByIndex(a + leftXCoordinate, i + leftYCoordinate);
					if (target->toString()[0] == '"' || target->toString()[0] == '#' || strcmp(target->toString(), "") == 0) {
						hasNumericParameters = false;
					}
					else if (target->evaluate() > max) {
						max = target->evaluate();
					}
				}
			}
		}
	}
	return max;
}

double MaxFormula::calculate(MyString& errorMessage) const
{
	if (lengthOfArgs > 1) {
		errorMessage = "Argument of MAX function should only be a single range!";
		return -1;
	}
	double max = INT_MIN;
	bool hasNumericParameters = true;
	if (args[0][0] >= 'A' && args[0][0] <= Engine::getTable().getConfig().getMaxRows() - 'A') {
		int xCoordinate = args[0][1] - '1';
		MyString currentArg = args[0];
		int argLength = currentArg.getLength();
		if (currentArg.contains(':')) {
			char leftCell[Utils::BUFFER_SIZE];
			char rightCell[Utils::BUFFER_SIZE];
			Utils::splitValuesByDelimiter(currentArg.getString(), leftCell, rightCell, ':');
			max = evaluateRange(leftCell, rightCell, hasNumericParameters);
		}
		else {
			errorMessage = "Argument of MAX function should only be a range!";
			return -1;
		}
	}
	else {
		errorMessage = "Argument of MAX function should only be a range!";
		return -1;
	}

	if (!hasNumericParameters || lengthOfArgs == 0) {
		return -1;
	}
	return max;
}

const char* MaxFormula::evaluate() const
{
    return "";
}

MaxFormula::MaxFormula(char** args, int length)
{
	this->args = args;
	this->lengthOfArgs = length;
}

MaxFormula::~MaxFormula()
{
	for (int i = 0; i < this->lengthOfArgs; i++) {
		delete[] args[i];
	}
	delete[] args;
}
