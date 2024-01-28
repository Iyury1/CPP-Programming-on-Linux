#include "mysquare.h"

MySquare::MySquare()
{
    side = 0;
}

void MySquare::setSide(int i)
{
    side = i;
}

int MySquare::getArea()
{
    return side*side;
}
