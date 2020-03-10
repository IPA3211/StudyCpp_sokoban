#include <iostream>

#include "header/gameCore.h"
#include "header/transform.h"
#include "header/fileio.h"
#include "header/map.h"

gameCore::gameCore(){
    fileio file("bin/map.txt", mode::IN);
    
    std::vector<trimedStirng> a;

    a = file.filetrimByline("map");
    
    stages.resize(a.size());

    for(int i = 0; i < a.size(); i++){
        stages.at(i) = (map(a.at(i).str, transform(a.at(i).x, a.at(i).y)));
    }

    stage = 0;
    playingMap = &stages.at(stage);

    player = playingMap -> getPlayer();
}

void gameCore::start(){
    while(update());
}

bool gameCore::update(){
    playingMap -> showMap();
    std::cin >> input;
    player -> move(input, *playingMap);

    
}