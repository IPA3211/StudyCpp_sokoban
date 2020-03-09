#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "header/fileio.h"

fileio::fileio(char * _fileName, mode _type){
    file.open(_fileName);
    if(file.is_open()){
        std::cout<<"opened"<<std::endl;
    }
    else
        std::cout<<"fail"<<std::endl;

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