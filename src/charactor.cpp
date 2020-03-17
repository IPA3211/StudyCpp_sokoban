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
    std::cout << position.getX() << " " << position.getY() << std::endl;
}

void charactor::move(const char &_input, map &m){
    switch (_input)
    {
    case 'a':
        if(m.isCanSwap(position, transform(0, -1))){
            changePosition(position + transform(0, -1));
            saveUndo(transform(0, -1));
        }
        break;
    case 'w':
        if(m.isCanSwap(position, transform(-1, 0))){
            changePosition(position + transform(-1, 0));
            saveUndo(transform(-1, 0));
        }
        break;
    case 'd':
        if(m.isCanSwap(position, transform(0, 1))){
            changePosition(position + transform(0, 1));
            saveUndo(transform(0, 1));
        }
        break;
    case 's':
        if(m.isCanSwap(position, transform(1, 0))){
            changePosition(position + transform(1, 0));
            saveUndo(transform(1, 0));
        }
        break;
    
    default:
        break;
    }
}

void charactor::saveUndo(const transform &_dir){
    if(undo_data.size() < 5){
        undo_data.push_back(_dir);
        std::cout << "s" << std::endl;
    }
    else{
        undo_data.erase(undo_data.begin());
        undo_data.push_back(_dir);
        std::cout << "ss" << std::endl;
    }

}

void charactor::undo(map &m){
    if(undo_data.size() > 0){

        if(m.isCanSwap(position, transform(0,0) - undo_data.back())){
            changePosition(position - undo_data.back());
        }

        if(m.getDataInfo(position + undo_data.back()) == '$' || m.getDataInfo(position + undo_data.back()) == '$'+1){
            m.isCanSwap(position - undo_data.back(), transform(0,0) - undo_data.back());
        }

        std::cout << undo_data.back().getX() << " " << undo_data.back().getY() <<std::endl;

        undo_data.pop_back();
    }
}

charactor::~charactor(){}
