#pragma once
#include <string>
#include <vector>
#include <fstream>

enum class mode {
    IN,
    OUT
};

struct trimedStirng
{
    int x = 0, y = 0;
    std::string str;
};



class fileio
{
private:
    std::ifstream file;
    char * fileName;
    mode opend_type;
public:
    fileio(char * _fileName, mode _type);

    std::vector<trimedStirng> filetrimByline(const std::string &_ruler);

    ~fileio();
};