#include "InsertCommand.h"
#include "Engine.h"
#include <stdexcept>

void InsertCommand::execute()
{
	if (target->getXValue() > 0 && target->getXValue() < Engine::getTable().getConfig().getMaxCols()
		&& target->getYValue() > 'A' && target->getXValue() < Engine::getTable().getConfig().getMaxRows() + 'A') {
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

