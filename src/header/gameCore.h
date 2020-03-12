#pragma once
#include <vector>
#include <thread>
#include "map.h"
#include "charactor.h"
#include "fileio.h"

class gameCore
{
private:
    std::vector<trimedStirng> stages;
    map* playingMap;
    charactor* player = nullptr;
    std::thread* timer_th;
    int stage, playTime;
    
public:
    gameCore(/* args */);

    
    //GAME UTILITYs
    void ChangeInputType(bool type); // true    : can input without enter
                                     // false   : default setting
    void drawGameView();
    bool gameInput(); // return false is end game;
    void static timer();

    //GAME FLOWs
    void start(); // game start
    bool update();// loop while game play

    //GAME SYSTEMs
    void restrat();
    void undo();
    void startNewGame();
    bool saveGame();
    bool loadGame();
    bool showRanking();
    bool showReadMe();

    //GAME UIs
    char showGameStartUI();
    char showGamePauseUI();

    //CLASS UTILITYs
    void gameCoreFree();

    ~gameCore();
};