#include "EqualsCommand.h"
#include "Engine.h"
#include "Formula.h"
#include "SumFormula.h"
#include "AverageFormula.h"

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
	if (strcmp(formulaType, "=SUM") == 0) {
		return new SumFormula(Utils::splitValuesByDelimiter(formulaArgs, ','),argsLength);
	}
	else if (strcmp(formulaType, "=AVERAGE") == 0) {
		return new AverageFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else if (strcmp(formulaType, "=MIN") == 0) {

	}
	else if (strcmp(formulaType, "=MAX") == 0) {

	}
	else if (strcmp(formulaType, "=LEN") == 0) {

	}
	else if (strcmp(formulaType, "=CONCAT") == 0) {

	}
	else if (strcmp(formulaType, "=SUBSTR") == 0) {

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
		int formulaArgsLength = Utils::getStringLength(formulaArgs) - 1;
		formulaArgs[formulaArgsLength - 1] = '\0';
		formulaArgsLength = Utils::countDelimiter(formulaArgs,',') + 1;
		Formula* formula = formulaFactory(formulaType, formulaArgs, formulaArgsLength);
		const char* result = formula->evaluate();
		if (strcmp(result, "") == 0) {
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
