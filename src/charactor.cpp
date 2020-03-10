#include "header/charactor.h"
#include "header/map.h"

charactor::charactor(){
    position = transform(0,0);
}
charactor::charactor(const transform &_pos){
    position = _pos;
}

void charactor::changePosition(const transform &_pos){
    position = _pos;
}

void charactor::move(const char &_input, map &m){
    switch (_input)
    {
    case 'a':
        if(m.isCanSwap(position, transform(0, -1)))
            changePosition(position + transform(0, -1));
        break;
    case 'w':
        if(m.isCanSwap(position, transform(-1, 0)))
            changePosition(position + transform(-1, 0));
        break;
    case 'd':
        if(m.isCanSwap(position, transform(0, 1)))
            changePosition(position + transform(0, 1));
        break;
    case 's':
        if(m.isCanSwap(position, transform(1, 0)))
            changePosition(position + transform(1, 0));
        break;
    
    default:
        break;
    }
}

charactor::~charactor(){}
