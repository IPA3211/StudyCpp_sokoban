#include "header/map.h"
#include "header/transform.h"
#include <sstream>
#include <iostream>

map::map(){
    map_data = nullptr;
    map_size = transform(0, 0);
}

map::map(const transform &_ms){
    resizeMap(_ms);
}

map::map(const std::string &_data, const transform &_ms){
    resizeMap(_ms);
    std::stringstream ss;

    ss.str(_data);

    int row = 0;
    int col = 0;
    char temp;

    for(int i = 0; i < _data.length(); i++){
        temp = _data.at(i);

        if(temp == '\n'){
            row++;
            col = 0;
        }
        else{
            map_data[row][col] = temp;
            col ++;
        }
        
    }

}

void map::resizeMap(const transform &_ms){
    freeMapData();

    map_size = _ms;

    map_data = new int *[_ms.getY()];
    for(int i = 0; i < _ms.getY(); i++){
        map_data[i] = new int [_ms.getX()];
    }

    for(int i = 0; i < _ms.getY(); i++){
        for(int j = 0; j < _ms.getX(); j++){
            map_data[i][j] = ' ';
        }
    }
}

void map::buildMap(const std::string &str, const transform &_ms){
    map(str, _ms);
}

void map::showMap(){
    for(int i = 0; i < map_size.getY(); i++){
        for(int j = 0; j < map_size.getX(); j++){
            std::cout << static_cast<char>(map_data[i][j]);
        }
        std::cout << std::endl;
    }
}

void map::freeMapData(){
    for(int i = 0; i < map_size.getY(); i++){
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