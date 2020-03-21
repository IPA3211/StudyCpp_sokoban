#include "header/charactor.h"
#include "header/map.h"

#include <iostream>

charactor::charactor(){
    position = transform(0,0);
    undo_data.reserve(5);
}
charactor::charactor(const transform &_pos){
    position = _pos;
}

void charactor::changePosition(const transform &_pos){
    position = _pos;
    //std::cout << position.getX() << " " << position.getY() << std::endl;
}

bool charactor::move(const char &_input, map &m){
    bool is$Moved = false;
    switch (_input)
    {
    case 'a':
        if(m.isCanSwap(position, transform(0, -1), is$Moved)){
            changePosition(position + transform(0, -1));
            saveUndo(transform(0, -1), is$Moved);
        }
        break;
    case 'w':
        if(m.isCanSwap(position, transform(-1, 0), is$Moved)){
            changePosition(position + transform(-1, 0));
            saveUndo(transform(-1, 0), is$Moved);
        }
        break;
    case 'd':
        if(m.isCanSwap(position, transform(0, 1), is$Moved)){
            changePosition(position + transform(0, 1));
            saveUndo(transform(0, 1), is$Moved);
        }
        break;
    case 's':
        if(m.isCanSwap(position, transform(1, 0), is$Moved)){
            changePosition(position + transform(1, 0));
            saveUndo(transform(1, 0), is$Moved);
        }
        break;
    
    default:
        break;
    }

    return is$Moved;
}

void charactor::saveUndo(const transform &_dir, const bool &_isMoved){
    undo_data_form udf;
    udf.dir = _dir;
    udf.is$moved = _isMoved;
    if(undo_data.size() < 5){
        undo_data.push_back(udf);
        //std::cout << "s" << std::endl;
    }
    else{
        undo_data.erase(undo_data.begin());
        undo_data.push_back(udf);
        //std::cout << "ss" << std::endl;
    }

}

std::vector<undo_data_form> & charactor::getUndo(){
    return undo_data;
}

void charactor::setUndo(const std::vector<undo_data_form> & _undo){
    undo_data = _undo;
}

void charactor::undo(map &m){
    bool b;
    if(undo_data.size() > 0){
        transform temp = undo_data.back().dir;

        if(m.isCanSwap(position, transform(0,0) - temp, b)){

            if(undo_data.back().is$moved){
                m.isCanSwap(position + temp, transform(0,0) - temp, b);
                //std::cout << "is $ so swap" << std::endl;
            }

            changePosition(position - temp);
        }
       //std::cout << temp.getX() << " " << temp.getY() <<std::endl;

        undo_data.pop_back();
    }
}

charactor::~charactor(){}