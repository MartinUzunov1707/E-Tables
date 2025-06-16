#include "EqualsCommand.h"
#include "Engine.h"
#include "Formula.h"
#include "SumFormula.h"
#include "AverageFormula.h"
#include "MinFormula.h"
#include "MaxFormula.h"
#include "LenFormula.h"
#include "ConcatFormula.h"
#include "SubStringFormula.h"
#include "CountFormula.h"

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
		return new MinFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else if (strcmp(formulaType, "=MAX") == 0) {
		return new MaxFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else if (strcmp(formulaType, "=LEN") == 0) {
		return new LenFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else if (strcmp(formulaType, "=CONCAT") == 0) {
		return new ConcatFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else if (strcmp(formulaType, "=SUBSTR") == 0) {
		return new SubStringFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else if (strcmp(formulaType, "=COUNT") == 0) {
		return new CountFormula(Utils::splitValuesByDelimiter(formulaArgs, ','), argsLength);
	}
	else{
		throw std::invalid_argument("Command does not exist!");
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
	MyString errorMessage = "";
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
		MyString result = "";
		formula->evaluate(errorMessage,result);
		if (strcmp(result.getString(), "") == 0) {
			double calcResult = formula->calculate(errorMessage);
			if (calcResult == -1) {
				delete[] target;
				target = new ErrorCell(xCoord, yCoord);
			}
			else {
				delete[] target;
				target = new NumCell(xCoord, yCoord, calcResult);
			}
		}
		else {
			if (strcmp(result.getString(), "\n") == 0) {
				delete[] target;
				target = new ErrorCell(xCoord, yCoord);
			}
			else {
				delete[] target;
				target = new StringCell(xCoord, yCoord, result);
			}
		}
	}
	Engine::getTable().setPointerByIndex(xCoord, yCoord - 'A', target);
	if (strcmp(errorMessage.getString(), "") != 0) {
		throw std::invalid_argument(errorMessage.getString());
	}
}
