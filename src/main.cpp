#include <iostream>
#include <vector>
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"

int main(void){
    
    fileio file("/tmp/guest-jmmbxv/studycpp_sokoban/bin/map.txt", mode::IN);
    
    std::vector<trimedStirng> a;

    a = file.filetrimByline("map");
    
    map m(a.at(0).str, transform(a.at(0).x, a.at(0).y));

    m.showMap();

    std::cout<< a.at(0).x << " " << a.at(0).y << std::endl;

    std::cout<<a.at(0).str << std::endl;


    return 0;
}