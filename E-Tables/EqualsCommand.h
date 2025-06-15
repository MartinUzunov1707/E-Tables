#pragma once
#include "Command.h"
#include "Utils.h"
#include "ErrorCell.h"
#include "StringCell.h"
#include "BooleanCell.h"
#include "NumCell.h"

class EqualsCommand :
    public Command
{
public:
    EqualsCommand(Cell* target, char* arg);
    void execute() override;
};

