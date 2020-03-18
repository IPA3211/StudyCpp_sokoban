#include "header/map.h"
#include "header/transform.h"
#include "header/charactor.h"
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
            if(temp == '@'){
                player = new charactor(transform(row, col));
            }
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
    resizeMap(_ms);
    int row = 0;
    int col = 0;
    char temp;

    for(int i = 0; i < str.length(); i++){
        temp = str.at(i);

        if(temp == '\n'){
            row++;
            col = 0;
        }
        else{
            if(temp == '@'){
                player = new charactor(transform(row, col));
            }
            map_data[row][col] = temp;
            col ++;
        }
        
    }
}

void map::showMap(){
    std::cout << map2String();
}

std::string map::map2String(){
    std::string s;
    
    s.reserve(map_size.getX() * map_size.getY());

    for(int i = 0; i < map_size.getY(); i++){
        for(int j = 0; j < map_size.getX(); j++){
            if(map_data[i][j] == '@' + 1){
                s.push_back('@');
            }
            else if(map_data[i][j] == '$' + 1){
                s.push_back('$');
            }
            else
                s.push_back(map_data[i][j]);
        }
        s.push_back('\n');
    }

    return s;
}

char map::getDataInfo(const transform &_position){
    return map_data[_position.getX()][_position.getY()];
}

bool map::isCanSwap(const transform &_index, const transform &_direction, bool is$moved){
    transform index2 = _index;

    index2 = index2 + _direction;

    const int x1 = _index.getX();
    const int y1 = _index.getY();

    const int x2 = index2.getX();
    const int y2 = index2.getY();

    is$moved = false;
    
    if(map_data[x1][y1] == '@' || map_data[x1][y1] == '@' + 1){
        if(map_data[x2][y2] == ' '){
            swap(_index, index2);
            return true;
        }
        else if(map_data[x2][y2] == 'O'){
            swap(_index, index2);
            return true;
        }
        else if(map_data[x2][y2] == '$' || map_data[x2][y2] == '$' + 1) {// $
            if(isCanSwap(index2, _direction)){
                is$moved = true;
                swap(_index, index2);
                return true;
            }
            else 
                return false;
        }
        else{
            return false;
        }
    }

    if(map_data[x1][y1] == '$'|| map_data[x1][y1] == '$' + 1){ // $
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

void map::swap(const transform &_index, const transform &_index2){
    
    const int x1 = _index.getX();
    const int y1 = _index.getY();

    const int x2 = _index2.getX();
    const int y2 = _index2.getY();
    
    if(getDataInfo(_index) == '$' + 1){
        //' $O'
        if(getDataInfo(_index2) == 'O'){
            //' O$'
            std::swap(map_data[x1][y1], map_data[x2][y2]);
        }
        else{
            //'$OO'
            map_data[x1][y1] = 'O';
            map_data[x2][y2] = '$';
        }
    }
    else if(getDataInfo(_index) == '$'){
        //' $O'
        if(getDataInfo(_index2) == 'O'){
            //'  $'
            map_data[x1][y1] = ' ';
            map_data[x2][y2] = '$'+1;
        }
        else{
            //'$ O'
            std::swap(map_data[x1][y1], map_data[x2][y2]);
        }
    }  
    else if(getDataInfo(_index) == '@' + 1){
        //' @O'
        if(getDataInfo(_index2) == 'O'){
            //' O@'
            std::swap(map_data[x1][y1], map_data[x2][y2]);
        }
        else{
            //'@OO'
            map_data[x1][y1] = 'O';
            map_data[x2][y2] = '@';
        }
    }
    else if(getDataInfo(_index) == '@'){
        //' @O'
        if(getDataInfo(_index2) == 'O'){
            //'  @'
            
            map_data[x1][y1] = ' ';
            map_data[x2][y2] = '@'+1;
        }
        else{
            //'@ O'
            std::swap(map_data[x1][y1], map_data[x2][y2]);
        }
    }  
    else if(getDataInfo(_index) == '$'){
        //' $O'
        if(getDataInfo(_index2) == 'O'){
            //'  @'
            
            map_data[x1][y1] = ' ';
            map_data[x2][y2] = '$'+1;
        }
        else{
            //'$ O'
            std::swap(map_data[x1][y1], map_data[x2][y2]);
        }
    }
}

void map::hardSwap(const transform &_index, const transform &_index2){

    const int x1 = _index.getX();
    const int y1 = _index.getY();

    const int x2 = _index2.getX();
    const int y2 = _index2.getY();

    std::swap(map_data[x1][y1], map_data[x2][y2]);
}

charactor * map::getPlayer(){
    return player;
}

void map::freeMapData(){
    for(int i = 0; i < map_size.getY(); i++){
        delete [] map_data[i];
        map_data[i] = nullptr;
    }    

    delete [] map_data;
    map_data = nullptr;

    map_size = transform(0, 0);

    delete player;
    player = nullptr;
}

map::~map(){
    freeMapData();
}