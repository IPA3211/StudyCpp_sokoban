#pragma once

class transform
{
private:
    int x, y;
public:
    transform();
    ~transform();
    transform(const int &_x, const int &_y);

    void setX(const int &_x);
    void setY(const int &_y);
    void setXY(const int &_x, const int &_y);

    void moveUp(const int &amount);
    void moveDown(const int &amount);
    void moveLeft(const int &amount);
    void moveRight(const int &amount);

    int getX() const;
    int getY() const;
    void getXY(int &_x, int &_y);

    transform& operator=(const transform &other);
    transform operator+(const transform &other);
    transform operator-(const transform &other);

};