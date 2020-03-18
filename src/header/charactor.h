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

    //change Player's position data
    void changePosition(const transform &_pos);
    
    // save player moved data
    void saveUndo(const transform &_dir, const bool &_isMoved);
    std::vector<undo_data_form> & getUndo();
    void setUndo(const std::vector<undo_data_form> & _undo);
    // undo player's move
    void undo(map &m);

    // move @ return true when $ is moved by @
    bool move(const char &_input, map &m); 

    ~charactor();
};