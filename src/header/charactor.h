#pragma once

#include "map.h"
#include "transform.h"

#include <vector>

class map;

class charactor
{
private:
    transform position;
    std::vector<transform> undo_data;
    
public:
    charactor();
    charactor(const transform &_pos);

    void changePosition(const transform &_pos);
    
    void saveUndo(const transform &_dir);
    void undo(map &m);

    void move(const char &_input, map &m);

    ~charactor();
};