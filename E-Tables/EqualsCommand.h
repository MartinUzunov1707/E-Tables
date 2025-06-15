#pragma once
#include "Command.h"
#include "Utils.h"

class EqualsCommand :
    public Command
{
public:
    void execute() override;
};

