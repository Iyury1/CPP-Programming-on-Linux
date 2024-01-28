#include "mysquare.h"

MySquare::MySquare() : side(0) {}
MySquare::MySquare(int i) : side(i) {}


void MySquare::setSide(int i)
{
    side = i;
}

int MySquare::getArea()
{
    return side*side;
}
