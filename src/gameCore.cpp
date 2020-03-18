#include <iostream>
#include <sstream>
#include <termios.h>
#include <unistd.h>
#include <thread>

#include "header/gameCore.h"
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"

gameCore::gameCore(){
    fileio file("src/data/map.txt", mode::IN);

    stages = file.filetrimByline("map");
    
    stage = 0;
    playTime = 0;

    playingMap = new map();
}

void gameCore::ChangeInputType(bool type){
    struct termios t;

    if(type){
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }
    else{
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag |= ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }
}

void gameCore::drawGameView(){
    //system("clear");
    std::cout << "STAGE\t   " << stage + 1<<std::endl;
   
    playingMap -> showMap(); 
    std::cout << playTime / 10 << "." << playTime % 10 << std::endl;
}

bool gameCore::gameInput(){
    ChangeInputType(true);

    char input;
    std::cin >> input; 

    switch (input)
    {
    case 'w':
    case 'a':
    case 's':
    case 'd':
        player -> move(input, *playingMap);
        break;

    case 'r':
        restrat();
        break;
    case 'u':
        player -> undo(*playingMap);
        break;

    case 27:
        stopTimer();
        bool flag = true;
        while(flag){
            switch (showGamePauseUI())
            {
            case '1':
                startTimer();
                flag = false;
                break;
            case '2':
                saveGame();
                break;
            case '3':
                loadGame();
                break;
            case '4':
                showReadMe();
                break;
            case '5':
                return false; // game out
                break;
            
            default:
                break;
            }
        }
        break;
    }

    return true;
}

void gameCore::timer(){
    while(isTimerStart){
        playTime++;
        //drawGameView();
        usleep(100 * 1000);
    }
}

void gameCore::startTimer(){
    if(timer_th != nullptr){
        delete timer_th;
        timer_th = nullptr;
    }

    isTimerStart = true;
    timer_th = new std::thread(&gameCore::timer, this);
    timer_th -> detach();
}

void gameCore::stopTimer(){
    isTimerStart = false;
}

void gameCore::start(){
    while(true){
        switch (showGameStartUI())
        {
        case '1':
            startNewGame();
            return;
            break;
        case '2':
            loadGame();
            return;
            break;
        case '3':
            showRanking();
            break;
        case '4':
            showReadMe();
            break;
        case '5':
            return;
            break;

        default:
            
            break;
        }
    }
}

bool gameCore::update(){
    do{
    drawGameView();
    }while(gameInput());
}

void gameCore::restrat(){
    playingMap->buildMap(stages.at(stage).str, transform(stages.at(stage).x, stages.at(stage).y));
    player = playingMap -> getPlayer();
}

void gameCore::undo(){
}

void gameCore::startNewGame(){
    stage = 0;

    playingMap -> buildMap(stages.at(stage).str, transform(stages.at(stage).x, stages.at(stage).y));
    playingMap -> showMap();
    player = playingMap -> getPlayer();

    startTimer();
    update();
}

bool gameCore::saveGame(){
    gameSaveDatas s;

    s.map = playingMap -> map2String();
    s.stage = stage;
    s.time = 0;

    if(fileio::saveGame("save" , s)){
        system("clear");
        std::cout<< "저장 완료" << std::endl;
        std::cin.ignore();
        std::cin.get();
    }
}
bool gameCore::loadGame(){
    fileio io("save",  mode::IN);
    std::vector<trimedStirng> load;
    load = io.filetrimByline("map");

    playingMap -> buildMap(load.at(0).str, transform(load.at(0).x, load.at(0).y));
    player = playingMap -> getPlayer();

    std::istringstream iss(load.at(1).str);

    iss >> stage >> playTime;

    startTimer();
    update();
}

bool gameCore::showRanking(){
}

bool gameCore::showReadMe(){
    system("clear");
    fileio::showFile("src/data/help.txt");
    std::cin.ignore();
    std::cin.get();
}

char gameCore::showGameStartUI() {
    //system("clear");
    ChangeInputType(false);

    using std::cout;
    using std::endl;
    using std::cin;

    char in;


    cout << "SOKOBAN" << endl;

    cout << "\n메뉴" << endl;
    cout << "1. 새로운 게임" << endl;
    cout << "2. 이어하기" << endl;
    cout << "3. 랭킹" << endl;
    cout << "4. 설명" << endl;
    cout << "5. 종료" << endl;
    
    bool temp = false;
    
    do{
        temp = false;
        cout << "입력 : ";
        cin >> in;

        if(!('1' <= in && '5' >= in)){
            temp = true;
            cout << "잘못된 입력입니다" << endl;
        }
    }
    while(temp);

    return in;
}

char gameCore::showGamePauseUI(){

    system("clear");
    ChangeInputType(false);
    
    using std::cout;
    using std::endl;
    using std::cin;

    char in;

    cout << "PAUSE" << endl;

    cout << "\n메뉴" << endl;
    cout << "1. 계속하기" << endl;
    cout << "2. 저장" << endl;
    cout << "3. 불러오기" << endl;
    cout << "4. 설명" << endl;
    cout << "5. 종료" << endl;
    
    bool temp = false;
    
    do{
        temp = false;
        cout << "입력 : ";
        cin >> in;

        if(!('1' <= in && '5' >= in)){
            temp = true;
            cout << "잘못된 입력입니다" << endl;
        }
    }
    while(temp);
}

void gameCore::gameCoreFree(){
    delete playingMap;
    delete player;
    delete timer_th;

    playingMap = nullptr;
    player = nullptr;
    timer_th = nullptr;

    stages.clear();
}

gameCore::~gameCore(){
    gameCoreFree();
}