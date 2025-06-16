#include "AverageFormula.h"
#include "Engine.h"

double AverageFormula::evaluateRange(char* leftCell, char* rightCell, bool& hasNumericParameters,int& cellCounter) const
{
	double sum = 0.0;
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
					sum += target->evaluate();
					cellCounter++;
				}
			}
		}
	}
	return sum;
}

double AverageFormula::calculate(MyString& errorMessage) const
{
	double sum = 0.0;
	int cellCounter = 0;
	bool hasNumericParameters = true;
	for (int i = 0; i < lengthOfArgs; i++)
	{
		if (args[i][0] >= 'A' && args[i][0] <= Engine::getTable().getConfig().getMaxRows() - 'A') {
			int xCoordinate = args[i][1] - '1';
			MyString currentArg = args[i];
			int argLength = currentArg.getLength();
			if (currentArg.contains(':')) {
				char leftCell[Utils::BUFFER_SIZE];
				char rightCell[Utils::BUFFER_SIZE];
				Utils::splitValuesByDelimiter(currentArg.getString(), leftCell, rightCell, ':');
				sum += evaluateRange(leftCell, rightCell, hasNumericParameters, cellCounter);
			}
			else {
				int yCoordinate = args[i][0] - 'A';
				if (yCoordinate >= 0 && yCoordinate <= Engine::getTable().getConfig().getMaxCols()) {
					Cell* target = &Engine::getTable().getByIndex(xCoordinate, yCoordinate);
					if (target->toString()[0] == '"' || target->toString()[0] == '#' || strcmp(target->toString(), "") == 0) {
						hasNumericParameters = false;
					}
					sum += target->evaluate();
					cellCounter++;
				}
			}
		}
		else if(args[i][0] >= '0' && args[i][0] <= '9') {
			double value = 0;
			Utils::tryConvertToDouble(args[i], value);
			sum += value;
			hasNumericParameters = true;
		}
		else {
			hasNumericParameters = false;
		}
	}
	if (!hasNumericParameters || lengthOfArgs == 0) {
		errorMessage = "Parameters of AVERAGE function should be cells with numerical values!";
		return -1;
	}
	return sum / cellCounter;
}

const char* AverageFormula::evaluate() const
{
    return "";
}

AverageFormula::AverageFormula(char** args, int length)
{
    this->args = args;
    this->lengthOfArgs = length;
}

AverageFormula::~AverageFormula()
{
	for (int i = 0; i < this->lengthOfArgs; i++) {
		delete[] args[i];
	}
	delete[] args;
}
