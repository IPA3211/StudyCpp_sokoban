#pragma once
#include <vector>
#include "map.h"
#include "charactor.h"

class gameCore
{
private:
    std::vector<map> stages;
    map* playingMap;
    charactor* player = nullptr;
    int stage;
    char input;
    
public:
    gameCore(/* args */);

    void inputTypeChange(bool onOff); // get input without enter key
    
    void start(); // game start
    bool update();// loop while game play

    void gameCoreFree();

    ~gameCore();
};