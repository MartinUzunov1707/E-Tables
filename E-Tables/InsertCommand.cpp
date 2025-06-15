#include "InsertCommand.h"
#include "Engine.h"
#include <stdexcept>

InsertCommand::InsertCommand(Cell* target,char* args)
{
	this->target = target;
	this->arg = new char[Utils::BUFFER_SIZE];
	int argsLength = Utils::getStringLength(args);
	for (int i = 0;i < argsLength; i++) {
		arg[i] = args[i];
	}
}

void InsertCommand::execute()
{
	if (Utils::validateCellCoordinates(this->target->getXValue(),this->target->getYValue()-'A',Engine::getTable().getConfig().getMaxCols(), Engine::getTable().getConfig().getMaxRows()))
	{
		// Update the current column and row if necessary
		if (target->getXValue() > Engine::getTable().getCurrentCol()) {
			Engine::getTable().setCurrentCol(target->getXValue());
		}
		if (target->getYValue() - 'A' > Engine::getTable().getCurrentRow()) {
			Engine::getTable().setCurrentRow(target->getYValue() - 'A');
		}
		int xCoord = target->getXValue();
		char yCoord = target->getYValue();

		if (arg[0] == '"') {
			delete[] target;
			target = new StringCell(xCoord, yCoord, arg);
		}
		else if (arg[0] == 'T' || arg[0] == 'F') {
			//bool
			delete[] target;
			bool value = (arg[0] == 'T');
			target = new BooleanCell(xCoord, yCoord, value);
		}
		else if (arg[0] >= '0' && arg[0] <= '9') {
			// double
			double value = 0;
			if (Utils::tryConvertToDouble(arg, value)) {

				delete[] target;
				target = new NumCell(xCoord, yCoord, value);
			}
			else {
				throw std::invalid_argument("Invalid argument type for insert command!");
			}

		}
		else {
			throw std::invalid_argument("Invalid argument type for insert command!");
		}
	}
	else {
		throw std::out_of_range("Target cell is out of range!");
	}
	Engine::getTable().setPointerCloneByIndex(target->getXValue(), target->getYValue()-'A', target);
}

