#include "header/map.h"
#include "header/transform.h"
#include <sstream>

map::map(){
    map_data = nullptr;
    map_size = transform(0, 0);
}

map::map(const transform &_ms){
    resizeMap(_ms);
}

void map::resizeMap(const transform &_ms){
    map_size = _ms;

    map_data = new int *[_ms.getX()];
    for(int i = 0; i < _ms.getX(); i++){
        map_data[i] = new int [_ms.getY()];
    }
}
void map::buildMap(const std::string &str, const transform &_ms){
    resizeMap(_ms);
    std::stringstream ss;
    
    ss.str(str);

    for(int i = 0; i < _ms.getX(); i++){
        ss.get
    }
    
}

void map::freeMapData(){
    for(int i = 0; i < map_size.getX(); i++){
        delete [] map_data[i];
        map_data[i] = nullptr;
    }    

    delete [] map_data;
    map_data = nullptr;

    map_size = transform(0, 0);
}

map::~map(){
    freeMapData();
}