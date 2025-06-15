#include "DeleteCommand.h"
#include "Engine.h"
DeleteCommand::DeleteCommand(Cell* target)
{
	this->target = target;
}
void DeleteCommand::execute()
{
	if (Utils::validateCellCoordinates(this->target->getXValue(), this->target->getYValue() - 'A', 
		Engine::getTable().getConfig().getMaxCols(), Engine::getTable().getConfig().getMaxRows()))
	{
		if (target->getXValue() > Engine::getTable().getCurrentCol()) {
			Engine::getTable().setCurrentCol(target->getXValue());
		}
		if (target->getYValue() - 'A' > Engine::getTable().getCurrentRow()) {
			Engine::getTable().setCurrentRow(target->getYValue() - 'A');
		}
		this->target->clear();
	}
	else {
		throw std::out_of_range("Target cell is out of range!");
	}
}
