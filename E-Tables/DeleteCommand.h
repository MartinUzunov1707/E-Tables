#pragma once
#include "Command.h"

class DeleteCommand :
    public Command
{
public:
    DeleteCommand(Cell* target);
    void execute() override;
};

