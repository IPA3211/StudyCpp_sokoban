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

    map_data = new char *[_ms.getY()];
    for(int i = 0; i < _ms.getY(); i++){
        map_data[i] = new char [_ms.getX()];
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
            if(map_data[i][j] == 'O' + '@'){
                std::cout << '@';
            }
            else if(map_data[i][j] == '$' + 'O'){
                std::cout << '$';
            }
            else
                std::cout << map_data[i][j];
        }
        std::cout << std::endl;
    }
}

char map::getDataInfo(const transform &_position){
    return map_data[_position.getX()][_position.getY()];
}

bool map::isCanSwap(const transform &_index, const transform &_direction){
    transform index2 = _index;

    index2 = index2 + _direction;

    const int x1 = _index.getX();
    const int y1 = _index.getY();

    const int x2 = index2.getX();
    const int y2 = index2.getY();

    if(map_data[x1][y1] == '@' || map_data[x1][y1] == '@' + 'O'){
        if(map_data[x2][y2] == ' '){
            swap(_index, index2);
            return true;
        }
        else if(map_data[x2][y2] == 'O'){
            swap(_index, index2);
            return true;
        }
        else if(map_data[x2][y2] == '$' || map_data[x2][y2] == '$' + 'O') {// $
            if(isCanSwap(index2, _direction)){
                swap(_index, index2);
                return true;
            }
            else 
                return;
        }
        else{
            return false;
        }
    }

    if(map_data[x1][y1] == '$'|| map_data[x2][y2] == '$' + 'O'){ // $
        if(map_data[x2][y2] == ' '){
            swap(_index, index2);
            return true;
        }
        else if(map_data[x2][y2] == 'O'){
            swap(_index, index2);
            return true;
        }
        else 
            return false;
    }
}

void map::swap(const transform &index, const transform &index2){

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