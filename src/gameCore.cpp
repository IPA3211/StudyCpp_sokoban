#include <iostream>
#include <sstream>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <regex>
#include <algorithm>

#include "header/gameCore.h"
#include "header/charactor.h"
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"

gameCore::gameCore(){

    playingMap = new map();
    
    fileio file("src/data/map.txt", mode::IN);
    file.filetrimByline("map", stages);

    stage = 0;
    playTime = 0;

    file.~fileio();
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
        if (player -> move(input, *playingMap)){
            if(playingMap -> clearCheck()){
                if(stage < stages.size() - 1){
                    stage++;
                    loadStage(stage);
                }
                else{
                    gameClear();
                    gameContinueFlag = true;
                    return false;
                }
            }
        }
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
            case '1': // 계속하기
                startTimer();
                flag = false;
                break;
            case '2': // 게임 저장
                saveGame();
                break;
            case '3': // 불러 오기
                if(loadGame()){
                    startTimer();
                    flag = false;
                }
                break;
            case '4': // 설명
                showReadMe();
                break;
            case '5': // 메인으로
                gameContinueFlag = true;
                return false;
                break;
            case '6': // 종료
                gameContinueFlag = false;
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
        drawGameView();
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

bool gameCore::rankCompare(const trimedStirng &a, const trimedStirng &b){
    return a.x < b.x;
}

bool gameCore::start(){
    while(true){
        switch (showGameStartUI())
        {
        case '1':
            startNewGame(false);
            return gameContinueFlag;
            break;
        case '2':
            startNewGame(true);
            return gameContinueFlag;
            break;
        case '3':
            showRanking();
            return true;
            break;
        case '4':
            showReadMe();
            return true;
            break;
        case '5':
            return false;
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

void gameCore::startNewGame(const bool &isLoadGame){
    
    if(isLoadGame){
        if(!loadGame())
            return;
    }
    else{
        loadStage(0);
    }

    startTimer();
    update();
}

void gameCore::loadStage(const int &_stage){
    stage = _stage;

    playingMap -> buildMap(stages.at(stage).str, transform(stages.at(stage).x, stages.at(stage).y));
    player = playingMap -> getPlayer();

    playingMap -> showMap();
}

bool gameCore::saveGame(){
    gameSaveDatas s;

    s.map = playingMap -> map2String();
    s.stage = stage;
    s.time = playTime;
    s.undo = player -> getUndo();

    if(fileio::saveGame("save" , s)){
        system("clear");
        std::cout<< "저장 완료" << std::endl;
        std::cin.ignore();
        std::cin.get();
    }
}

bool gameCore::loadGame(){
    fileio io("save",  mode::IN);
    std::vector<trimedStirng> trim1, trim2;
    std::vector<undo_data_form> undo_data;

    if(!io.filetrimByline("map", trim1))
        return false;
        
    if(!io.filetrimByline("undo", trim2))
        return false;

    if(trim1.size() == 0){
        std::cout << "SAVE 데이터가 없습니다" << std::endl;
        
    }

    std::cout <<trim1.size();

    playingMap -> buildMap(trim1.at(0).str, transform(trim1.at(0).x, trim1.at(0).y));
    player = playingMap -> getPlayer();


    undo_data.reserve(5);

    undo_data_form f;
    int x, y;

    for(int i = 1; i < trim2.size() - 1; i++){
        std::istringstream issUndo(trim2.at(i).str);
        issUndo >> x >> y >> f.is$moved;
        f.dir.setXY(x, y);
        undo_data.push_back(f);
    }

    player -> setUndo(undo_data);

    std::istringstream iss(trim2.back().str);

    iss >> stage >> playTime;

    io.~fileio();

    return true;
}

bool gameCore::showRanking(){
    system("clear");
    std::vector<trimedStirng> rank_data;
    
    rank_data = loadRankingData();

    if(rank_data.size() == 0){
        system("clear");

        std::cout<< "RANK 데이터가 없습니다" << std::endl;

        std::cin.ignore();
        std::cin.get();

        return false;
    }
    
    std::cout << "\t순위\n" << std::endl;
    std::cout << "순위"<< "\t" << "이름" << "\t" << "기록" << std::endl;;
    for(int i = 0; i < rank_data.size(); i++){
        std::cout << i + 1 << "\t" << rank_data.at(i).str << "\t" << 
        rank_data.at(i).x /10 << "." << rank_data.at(i).x%10 << "s" << std::endl;
    }

    std::cin.ignore();
    std::cin.get();
}

void gameCore::saveRankingUI(){
    system("clear");

    std::string name, idCheck;
    
    std::cout << "기록을 저장합니다" << std::endl;

    do
    {
        std::cout << "이름을 입력해 주세요(특수문자 사용 불가)" << std::endl;
        std::cout << "입력 : ";
        getline(std::cin, name);

        if(name.size() == 0){
            system("clear");
            continue;    
        }
        idCheck = std::regex_replace(name, std::regex("[^0-9a-zA-Z가-힣]{1,10}"), "");

        if(idCheck.compare(name) != 0){
            system("clear");
            std::cout <<" 공백, 특수문자는 허용하지 않습니다. 다시 입력해 주세요" << std::endl;
        }
        else if(name.at(0) >= '0' && name.at(0) <= '9') {
            system("clear");
            std::cout << "첫 글자로 숫자를 사용할 수 없습니다." << std::endl;
        }
        else {
            //std::cout << name << idCheck;
            break;
        }

    } while (true);
    
    saveRankingCore(name);

}



void gameCore::saveRankingCore(const std::string &_name){
    std::vector<trimedStirng> rank_data;
    trimedStirng temp;

    temp.x = playTime;
    temp.str = _name;

    //rank_data = loadRankingData();

    rank_data.push_back(temp);

    std::sort(rank_data.begin(), rank_data.end(), rankCompare);

    //fileio::saveRank("src/data/rank.txt", rank_data);
    
}

std::vector<trimedStirng> gameCore::loadRankingData(){
    fileio io("src/data/rank.txt",  mode::IN);
    std::vector<trimedStirng> rank_data_raw, rank_data;
    trimedStirng temp;

    if(!io.filetrimByline("rank", rank_data_raw))
        return rank_data;

    rank_data.reserve(rank_data_raw.size() + 1);

    for(int i = 0; i < rank_data_raw.size(); i++){
        std::istringstream iss(rank_data_raw.at(i).str);
        iss >> temp.x;
        getline(iss, temp.str);
        rank_data.push_back(temp);
    }

    io.~fileio();
    return rank_data;
}

bool gameCore::showReadMe(){
    system("clear");
    fileio::showFile("src/data/help.txt");
    std::cin.ignore();
    std::cin.get();
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
            system("clear");
            cout << "잘못된 입력입니다" << endl;
        }
    }
    while(temp);

    return in;
}

void gameCore::gameClear(){
    ChangeInputType(false);
    stopTimer();

    system("clear");

    std::cout << "\tGAME CLEAR" << std::endl;
    std::cout << std::endl;

    std::cout << "PLAYING TIME :" << playTime / 10 << "." << playTime % 10 << std::endl;
    std::cout << "기록을 저장하시겠습니까?" << std::endl;

    std::cout << "1. 네" << std::endl;
    std::cout << "2. 아니요" << std::endl;

    bool temp = false;
    char in;
    
    do{
        temp = false;
        std::cout << "입력 : ";
        std::cin >> in;

        if(!('1' <= in && '2' >= in)){
            temp = true;
            system("clear");
            std::cout << "잘못된 입력입니다" << std::endl;
        }
    }
    while(temp);

    if(in == '1'){
        saveRankingUI();
        system("clear");

        std::cout << "저장이 완료되었습니다." << std::endl;
        std::cout << "메인 화면으로 이동합니다" << std::endl;
        std::cin.ignore();
        std::cin.get();
    }
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
    cout << "5. 메인화면" << endl;
    cout << "6. 종료" << endl;
    
    bool temp = false;
    
    do{
        temp = false;
        cout << "입력 : ";
        cin >> in;

        if(!('1' <= in && '6' >= in)){
            temp = true;
            system("clear");
            cout << "잘못된 입력입니다" << endl;
        }
    }
    while(temp);
}

void gameCore::gameCoreFree(){
    if(playingMap != nullptr)
        delete playingMap;
    if(player != nullptr);
        delete player;
    if(timer_th != nullptr);
        delete timer_th;

    playingMap = nullptr;
    player = nullptr;
    timer_th = nullptr;

    isTimerStart = false;
    gameContinueFlag = true;

    stage = 0;
    playTime = 0;

    if(stages.size() != 0)
        stages.clear();
}

gameCore::~gameCore(){
    gameCoreFree();
}