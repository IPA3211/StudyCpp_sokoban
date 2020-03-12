#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "header/fileio.h"
#include "header/map.h"

fileio::fileio(char * _fileName, mode _type){
    file.open(_fileName);
    if(file.is_open()){
        std::cout<<"opened"<<std::endl;
    }
    else
        std::cout<<"fail"<<std::endl;
}

void fileio::showFile(char * _fileName){
    std::ifstream f;
    std::string s;
    f.open(_fileName);
    
    // 위치 지정자를 파일 끝으로 옮긴다.
    f.seekg(0, std::ios::end);

    // 그리고 그 위치를 읽는다. (파일의 크기)   
    int size = f.tellg();
    s.resize(size);

    // 위치 지정자를 다시 파일 맨 앞으로 옮긴다
    f.seekg(0, std::ios::beg);

    // 파일 전체 내용을 읽어서 문자열에 저장한다.
    f.read(&s[0], size);
    
    std::cout << s << std::endl;
    f.close();
}


bool fileio::saveGame(char * _fileName, const gameSaveDatas &data){
    std::ofstream f;
    
    f.open(_fileName);

    f << "map\n";
    f << data.map;
    f << "map\n";

    f << data.stage << " ";
    f << data.time;
    f << std::endl;
    f << "end";

    f.close();

    return true;
}

std::vector<trimedStirng> fileio::filetrimByline(const std::string &_ruler){
    std::vector<trimedStirng> strings;
    trimedStirng temp;

    if(file.is_open()){
        while(!file.eof()){
            std::string str;
            getline(file, str);
            if(str.compare(_ruler) == 0 || str.compare("end") == 0){
                if(!(temp.x == 0 && temp.y == 0)){ 
                    // 입력이 있었던 경우에 만 저장
                    temp.str.pop_back();
                    strings.push_back(temp);
                }

                // reset temp
                temp.str.clear();
                temp.x = 0;
                temp.y = 0;
            }  
            else{
                temp.str = temp.str + str + "\n";
                temp.y++;
                if(temp.x < str.length()){
                    temp.x = str.length();
                }
            }
                
        }
    }
    else
    {
        std::cout << "file open fail" << std::endl;
    }
    
    return strings;

}


fileio::~fileio(){
    file.close();
}