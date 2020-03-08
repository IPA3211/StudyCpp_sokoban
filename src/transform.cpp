#include "header/transform.h"

transform::transform(){
    x = 0;
    y = 0;
}

transform::~transform(){

}

transform:: transform(const int &_x, const int &_y){
    x = _x; 
    y = _y;
}

void transform::setX(const int &_x){    x = _x;}
void transform::setY(const int &_y){    y = _y;}
void transform::setXY(const int &_x, const int &_y){    x = _x; y = _y;}

void transform::moveUp(const int &amount = 1){  y -= amount;}
void transform::moveDown(const int &amount = 1){y += amount;}
void transform::moveLeft(const int &amount = 1){x -= amount;}
void transform::moveRight(const int &amount = 1){x += amount;}

int transform::getX() const {return x;}
int transform::getY() const {return y;}
void transform::getXY(int &_x, int &_y){_x = x; _y = y;}

transform& transform::operator=(const transform &other){
    setXY(other.x, other.y);
    return *this;
}
transform& transform::operator+(const transform &other){
    x += other.x;
    y += other.y;
    return *this;
}
transform& transform::operator-(const transform &other){
    x -= other.x;
    y -= other.y;
    return *this;
}
