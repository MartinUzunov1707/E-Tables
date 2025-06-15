#pragma once
#include "Command.h"
#include "StringCell.h";
#include "NumCell.h";
#include "BooleanCell.h";
#include "BooleanCell.h";
#include "Utils.h"


class InsertCommand : public Command
{
public:
	InsertCommand(Cell* target, char* args);
	void execute() override;
};

