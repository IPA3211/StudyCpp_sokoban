#include <iostream>
#include "header/transform.h"

int main(void){

    transform a;
    transform b(1, 1);

    a = b;

    std::cout << a.getX() << " " << a.getY() << std::endl;
    
    a + b;

    std::cout << a.getX() << " " << a.getY() << std::endl;
    
    a - b;
    
    std::cout << a.getX() << " " << a.getY() << std::endl;    

    return 0;
}