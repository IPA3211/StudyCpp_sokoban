#include <iostream>
#include <termios.h>
#include <unistd.h>

#include "header/gameCore.h"
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"

gameCore::gameCore(){
    fileio file("src/data/map.txt", mode::IN);

    stages = file.filetrimByline("map");
    
    stage = 0;
    
    playingMap = new map(stages.at(stage).str, transform(stages.at(stage).x, stages.at(stage).y));
    playingMap ->showMap();
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
        bool flag = true;
        while(flag){
            switch (showGamePauseUI())
            {
            case '1':
                flag = false;
                break;
            case '2':
                saveGame();
                getchar();
                break;
            case '3':
                loadGame();
                getchar();
                break;
            case '4':
                showReadMe();
                getchar();
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

void gameCore::start(){
    while(true){
        switch (showGameStartUI())
        {
        case '1':
            startNewGame();
            getchar();
            break;
        case '2':
            loadGame();
            getchar();
            break;
        case '3':
            showRanking();
            getchar();
            break;
        case '4':
            showReadMe();
            getchar();
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
    drawGameView();
    return gameInput();
}

void gameCore::restrat(){
    playingMap->buildMap(stages.at(stage).str, transform(stages.at(stage).x, stages.at(stage).y));
    player = playingMap -> getPlayer();
}

void gameCore::undo(){}

void gameCore::startNewGame(){
    while (update());
    
}
bool gameCore::saveGame(){}
bool gameCore::loadGame(){}
bool gameCore::showRanking(){
}
bool gameCore::showReadMe(){
    std::cout << "ss" << std::endl;
    fileio::showFile("src/data/help.txt");
    std::cin;
}



char gameCore::showGameStartUI() {
    system("clear");
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
    //delete playingMap;
    delete player;

    playingMap = nullptr;
    player = nullptr;

    stages.clear();
}

gameCore::~gameCore(){
    gameCoreFree();
}