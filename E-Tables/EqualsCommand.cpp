#include "EqualsCommand.h"
#include "Engine.h"
#include "Formula.h"
#include "SumFormula.h"

EqualsCommand::EqualsCommand(Cell* target, char* args)
{
	this->target = target;
	this->arg = new char[Utils::BUFFER_SIZE];
	int argsLength = Utils::getStringLength(args);
	for (int i = 0;i < argsLength; i++) {
		arg[i] = args[i];
	}
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
	int xCoord = target->getXValue();
	char yCoord = target->getYValue();
	//An argument of the type A1 has a length of 3 characters, because we are counting '\0'
	char formulaType[Utils::BUFFER_SIZE];
	char formulaArgs[Utils::BUFFER_SIZE];
	Utils::splitValuesByDelimiter(arg, formulaType, formulaArgs, '(');
	MyString str = arg;
	bool hasDelimiter = str.contains('(');
	
	if (!hasDelimiter) {
		delete[] target;
		//target = &Engine::getTable().getByIndex(arg[1] - 'A', arg[2] - '1');
		target = new ReferenceCell(xCoord, yCoord,arg[2] - '1', arg[1] - 'A');
	}
	else {
		//we have to delete the last closing bracket
		int formulaArgsLength = Utils::getStringLength(formulaArgs);
		formulaArgs[formulaArgsLength - 1] = '\0';
		Formula* formula = formulaFactory(formulaType, formulaArgs, formulaArgsLength);
		if (strcmp(formula->evaluate(), "") == 0) {
			double calcResult = formula->calculate();
			if (calcResult == -1) {
				delete[] target;
				target = new ErrorCell(xCoord, yCoord);
			}
			else {
				delete[] target;
				target = new NumCell(xCoord, yCoord, calcResult);
			}
		}
	}
	Engine::getTable().setPointerByIndex(xCoord, yCoord - 'A', target);
}
