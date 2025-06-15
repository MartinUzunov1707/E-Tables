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
	void execute() override;
};

