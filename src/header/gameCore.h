#pragma once
#include <vector>
#include <thread>
#include <string>
#include "map.h"
#include "charactor.h"
#include "fileio.h"

class gameCore
{
private:
    std::vector<trimedStirng> stages;
    map* playingMap;
    charactor* player = nullptr;
    std::thread* timer_th = nullptr;

    bool isTimerStart = false;
    bool gameContinueFlag = true;
    int stage, playTime;
    
public:
    gameCore(/* args */);

    
    //GAME UTILITYs
    void ChangeInputType(bool type); // true    : can input without enter
                                     // false   : default setting
    void drawGameView();
    bool gameInput(); // return false is end game;
    void timer();

    void startTimer();
    void stopTimer();

    static bool rankCompare(const trimedStirng &a, const trimedStirng &b);

    //GAME FLOWs
    bool start(); // game start
    bool update();// loop while game play

    //GAME SYSTEMs
    void restrat();
    void undo();
    void startNewGame(const bool &isLoadGame);
    void loadStage(const int &_stage);
    bool saveGame();
    bool loadGame();
    bool showRanking();
    void saveRankingCore(const std::string &_name);
    std::vector<trimedStirng> loadRankingData();
    bool showReadMe();
    void gameClear();

    //GAME UIs
    char showGameStartUI();
    char showGamePauseUI();
    void saveRankingUI();

    //CLASS UTILITYs
    void gameCoreFree();

    ~gameCore();
};