#pragma once

#include "transform.h"
#include "header/map.h"

class charactor
{
private:
    transform position;
    map m;
    
public:
    charactor(const transform &_pos);

    void move(const char &_input);
    bool isCanMove(const transform &index, const transform &_direction, bool isPlayer);

    ~charactor();
};