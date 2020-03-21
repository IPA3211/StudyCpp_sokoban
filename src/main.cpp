#include <iostream>
#include <vector>
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"
#include "header/gameCore.h"

int main(void){
    
    gameCore *g = new gameCore();
    
    while(g->start()){
        delete g;
        g = new gameCore();
    }

    return 0;
}