#include "InsertCommand.h"
#include "Engine.h"
#include <stdexcept>

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

		if (arg[0] == '"') {
			delete[] target;
			target = new StringCell(this->target->getXValue(), this->target->getYValue(), arg);
		}
		else if (arg[0] == 'T' || arg[0] == 'F') {
			//bool
			delete[] target;
			bool value = (arg[0] == 'T');
			target = new StringCell(this->target->getXValue(), this->target->getYValue(), arg);
		}
		else if (arg[0] >= '0' && arg[0] >= '9') {
			// double
			delete[] target;
			double value = 0;
			if (Utils::tryConvertToDouble(arg, value)) {
				target = new StringCell(this->target->getXValue(), this->target->getYValue(), arg);
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
	
}

