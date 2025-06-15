#include "EqualsCommand.h"
#include "Engine.h"
#include "Formula.h"
#include "SumFormula.h"

EqualsCommand::EqualsCommand(Cell* target, char* arg)
{
	target = target;
	arg = arg;
}

Formula* formulaFactory(char* formulaType, char* formulaArgs, int argsLength) {
	if (strcmp(formulaType, "SUM")) {
		return new SumFormula(Utils::splitValuesByDelimiter(formulaArgs, ','),argsLength);
	}
	else if (strcmp(formulaType, "AVERAGE")) {

	}
	else if (strcmp(formulaType, "MIN")) {

	}
	else if (strcmp(formulaType, "MAX")) {

	}
	else if (strcmp(formulaType, "LEN")) {

	}
	else if (strcmp(formulaType, "CONCAT")) {

	}
	else if (strcmp(formulaType, "SUBSTR")) {

	}
}

void EqualsCommand::execute()
{
	//An argument of the type A1 has a length of 3 characters, because we are counting '\0'
	char formulaType[Utils::BUFFER_SIZE];
	char formulaArgs[Utils::BUFFER_SIZE];
	MyString str = formulaArgs;
	bool hasDelimiter = str.contains('(');
	Utils::splitValuesByDelimiter(arg, formulaType, formulaArgs, '(');
	//we have to delete the last closing bracket
	int formulaArgsLength = Utils::getStringLength(formulaArgs) - 1;
	formulaArgs[formulaArgsLength] = '\0';
	if (!hasDelimiter) {
		delete[] target;
		target = &Engine::getTable().getByIndex(arg[0] - 'A', arg[1] - '0');
	}
	else {
		Formula* formula = formulaFactory(formulaType, formulaArgs, formulaArgsLength);
		if (strcmp(formula->evaluate(), "") == 0) {
			double calcResult = formula->calculate();
			if (calcResult == -1) {
				int xCoord = target->getXValue();
				int yCoord = target->getYValue() - 'A';
				delete[] target;
				target = new ErrorCell(xCoord, yCoord);
			}
			else {
				int xCoord = target->getXValue();
				int yCoord = target->getYValue() - 'A';
				delete[] target;
				target = new NumCell(xCoord, yCoord, calcResult);
			}
		}
	}
}
