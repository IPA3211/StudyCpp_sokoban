#pragma once

#include "map.h"
#include "transform.h"

class map;

class charactor
{
private:
    transform position;
    
public:
    charactor();
    charactor(const transform &_pos);

    void changePosition(const transform &_pos);

    void move(const char &_input, map &m);

    ~charactor();
};