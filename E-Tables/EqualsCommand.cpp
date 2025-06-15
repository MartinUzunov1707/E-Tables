#include "EqualsCommand.h"
#include "Engine.h"

void EqualsCommand::execute()
{
	//An argument of the type A1 has a length of 3 characters, because we are counting '\0'
	if (Utils::getStringLength(arg) == 3) {
		delete[] target;
		target = &Engine::getTable().getByIndex(arg[0] - 'A', arg[1] - '0');
	}
	else {
		//todo
	}
}
