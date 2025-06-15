#pragma once
#include "Command.h"

class DeleteCommand :
    public Command
{
public:
    void execute() override;
};

