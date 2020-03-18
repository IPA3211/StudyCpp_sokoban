#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "charactor.h"

enum class mode {
    IN,
    OUT
};

struct trimedStirng
{
    int x = 0, y = 0;
    std::string str;
};

struct gameSaveDatas{
    int stage;
    int time;
    std::string map;
    std::vector<undo_data_form> undo;
};



class fileio
{
private:
    std::ifstream file;
    char * fileName;
    mode opend_type;
public:
    fileio(char * _fileName, mode _type);

    static void showFile(char * _fileName);
    static bool saveGame(char * _fileName, const gameSaveDatas &data);

    std::vector<trimedStirng> filetrimByline(const std::string &_ruler);
    

    ~fileio();
};