#pragma once

#include "Mapper.h"
#include <vector>

class Mapper_001 : public Mapper
{
public:
        Mapper_001(uint8_t prgBanks, uint8_t chrBanks);
        ~Mapper_001();
};