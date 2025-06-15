#include "ReferenceCell.h"
#include "NullCell.h"

ReferenceCell::ReferenceCell(int x, char y, int targetX, int targetY)
{
	this->xValue = x;
	this->yValue = y;
	setValue(targetX, targetY);
}

void ReferenceCell::setValue(int targetX, int targetY)
{
	if (this->xValue != targetX && this->yValue != targetY){
		this->targetX = targetX;
		this->targetY = targetY;
	}

}

double ReferenceCell::evaluate()
{
	return Engine::getTable().getByIndex(targetX, targetY).evaluate();
}

const char* ReferenceCell::toString() const
{
	return Engine::getTable().getByIndex(targetX, targetY).toString();
}

Cell* ReferenceCell::clone()
{
	return new ReferenceCell(this->xValue, this->yValue, this->targetX, this->targetY);
}

void ReferenceCell::clear()
{
	//because reference cell does not hold any value, the clear method replaced the cell with a null cell.
	Engine::getTable().setPointerCloneByIndex(this->xValue, this->yValue, new NullCell(this->xValue, this->yValue));
}
