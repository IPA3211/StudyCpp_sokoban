#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "header/gameCore.h"
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"

gameCore::gameCore(){
    fileio file("bin/map.txt", mode::IN);

    a = file.filetrimByline("map");
    
    stages.resize(a.size());

    for(int i = 0; i < a.size(); i++){
        stages.at(i).buildMap(a.at(i).str, transform(a.at(i).x, a.at(i).y));
    }
    
    stage = 0;

    playingMap = new map();
    player = playingMap -> getPlayer();
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
    system("clear");
    playingMap -> showMap();
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
        undo();
        break;

    case 27:
        switch (showGamePauseUI())
        {
        case 1:
            break;
        case 2:
            saveGame();
            break;
        case 3:
            loadGame();
            break;
        case 4:
            showReadMe();
            break;
        case 5:
            return false;
            break;
        
        default:
            break;
        }
        break;

    default:
        break;
    }

    return true;
}

void gameCore::start(){

    switch (showGameStartUI())
    {
    case 1:
        startNewGame();
        break;
    case 2:
        loadGame();
        break;
    case 3:
        showRanking();
        break;
    case 4:
        showReadMe();
        break;
    case 5:
        return;
        break;
    
    default:
        
        break;
    }
}

bool gameCore::update(){
    drawGameView();
    return gameInput();
}

void gameCore::restrat(){
    playingMap = &stages.at(stage);
    player = playingMap -> getPlayer();
}

void gameCore::undo(){}

void gameCore::startNewGame(){
    while(update());
}
bool gameCore::saveGame(){}
bool gameCore::loadGame(){}
bool gameCore::showRanking(){}
bool gameCore::showReadMe(){}



const char & gameCore::showGameStartUI() {
    system("clear");
    ChangeInputType(false);

    using std::cout;
    using std::endl;
    using std::cin;

    char in;


    cout << "SOKOBAN" << endl;
    stages.at(1).showMap();

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

const char & gameCore::showGamePauseUI(){

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
    //delete playingMap;
    delete player;

    playingMap = nullptr;
    player = nullptr;

    stages.clear();
}

gameCore::~gameCore(){
    gameCoreFree();
}