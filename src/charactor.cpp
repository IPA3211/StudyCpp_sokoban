#include "header/charactor.h"
#include "header/map.h"

charactor::charactor(const transform &_pos){
    position = _pos;
}

void charactor::move(const char &_input){
    switch (_input)
    {
    case 'w':
        
        break;
    case 'a':
        /* code */
        break;
    case 's':
        /* code */
        break;
    case 'd':
        /* code */
        break;
    
    default:
        break;
    }
}

bool charactor::isCanMove(const transform &index, const transform &_direction, bool isPlayer){
    transform temp = index;
    
    temp = temp + _direction;

    if(isPlayer){
        
    }
}