#include "ConcatFormula.h"
#include "Engine.h"

double ConcatFormula::evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters) const
{
    return 0.0;
}

double ConcatFormula::calculate(MyString& errorMessage) const
{
	return 0.0;
}

void ConcatFormula::evaluate(MyString& errorMessage, MyString& result) const
{
	if (lengthOfArgs != 2) {
		errorMessage = "Argument of CONCAT function should only be a single range and a delimiter!";
		result = "\n";
	}
	MyString res = "";
	if (args[0][0] >= 'A' && args[0][0] <= Engine::getTable().getConfig().getMaxRows() + 'A') {
		int xCoordinate = args[0][1] - '1';
		MyString currentArg = args[0];
		const char* delimiter = args[1];
		int argLength = currentArg.getLength();
		if (currentArg.contains(':')) {
			char leftCell[Utils::BUFFER_SIZE];
			char rightCell[Utils::BUFFER_SIZE];
			Utils::splitValuesByDelimiter(currentArg.getString(), leftCell, rightCell, ':');
			if (leftCell[0] >= 'A' && leftCell[0] <= Engine::getTable().getConfig().getMaxRows() + 'A'
				&& rightCell[0] >= 'A' && rightCell[0] <= Engine::getTable().getConfig().getMaxRows() + 'A') {
				int leftYCoordinate = leftCell[0] - 'A', leftXCoordinate = leftCell[1] - '1';
				int rightYCoordinate = rightCell[0] - 'A', rightXCoordinate = rightCell[1] - '1';
				int colDiff = rightCell[1] - leftCell[1], rowDiff = rightYCoordinate - leftYCoordinate;
				//resolving range
				if (leftYCoordinate >= 0 && leftYCoordinate < Engine::getTable().getConfig().getMaxCols()
					&& rightYCoordinate >= 0 && rightYCoordinate < Engine::getTable().getConfig().getMaxCols()) {

					for (int i = 0; i <= rowDiff; i++) {
						for (int a = 0; a <= colDiff; a++) {
							Cell* target = &Engine::getTable().getByIndex(a + leftXCoordinate, i + leftYCoordinate);
							const char* targetString = target->toString();
							if (i == rowDiff && a == colDiff) {
								res.append(targetString);
							}
							else {
								res.append(targetString).append(delimiter[1]);
							}
						}
					}
				}
			}
			else {
				errorMessage = "Argument of CONCAT function should only be a single range IN BOUNDS and a delimiter!";
			}
		}
		else {
			errorMessage = "Argument of CONCAT function should only be a range and a delimiter!";
			result = "\n";
		}
	}
	else {
		errorMessage = "Argument of CONCAT function should only be a single range IN BOUNDS and a delimiter!";
		result = "\n";
	}

	if (strcmp(res.getString(),"")==0 || lengthOfArgs != 2) {
		errorMessage = "Argument of CONCAT function should only be a range";
		result = "\n";
	}
	result = res.getString();
}

ConcatFormula::ConcatFormula(char** args, int length)
{
	this->args = args;
	this->lengthOfArgs = length;
}

ConcatFormula::~ConcatFormula()
{
	for (int i = 0; i < this->lengthOfArgs; i++) {
		delete[] args[i];
	}
	delete[] args;
}
