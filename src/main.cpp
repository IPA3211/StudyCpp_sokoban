#include <iostream>
#include <vector>
#include "header/transform.h"
#include "header/fileio.h"

int main(void){
    
    fileio file("/tmp/guest-pjhd2b/studycpp_sokoban/bin/map.txt", mode::IN);
    
    std::vector<trimedStirng> a;

    a = file.filetrimByline("map");
    

    std::cout<< a.size() << std::endl;
    std::cout<< a.at(1).x << " " << a.at(1).y << std::endl;

    std::cout<<a.at(1).str << std::endl;


    return 0;
}