#pragma once

#include "map.h"
#include "transform.h"

#include <vector>

class map;

struct undo_data_form
{
    transform dir;
    bool is$moved;
};



class charactor
{
private:
    transform position;
    std::vector<undo_data_form> undo_data;
    
public:
    charactor();
    charactor(const transform &_pos);

    void changePosition(const transform &_pos);
    
    void saveUndo(const transform &_dir, const bool &_isMoved);
    void undo(map &m);

    void move(const char &_input, map &m);

    ~charactor();
};