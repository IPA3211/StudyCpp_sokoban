#pragma once

#include "transform.h"
#include "charactor.h"
#include <string>
#include <vector>

// # = 벽, $ = 박스, @ = player, O = goal,
// O + @ =  player on goal = @
// O + $ =  box on goal = $

typedef char** data;

class charactor;

class map
{
private:
    data map_data = nullptr;
    transform map_size;
    charactor *player = nullptr;

public:
    map();
    map(const transform &_ms);
    map(const std::string &_data, const transform &_ms);



    void freeMapData();

    void resizeMap(const transform &_ms);
    void buildMap(const std::string &str, const transform &_ms);

    void showMap();
    std::string map2String();

    char getDataInfo(const transform &_position);
    
    bool isCanSwap(const transform &index, const transform &direction);
    void swap(const transform &index, const transform &index2);
    void hardSwap(const transform &index, const transform &index2);


    charactor * getPlayer();

    ~map();
};