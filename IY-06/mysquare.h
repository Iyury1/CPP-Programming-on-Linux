#ifndef MYSQUARE_H
#define MYSQUARE_H

class MySquare
{
public:
    MySquare();
    MySquare(int i);
    MySquare(float f) = delete;

    void setSide(int i);
    int getArea();
private:
    int side;
};

#endif // MYSQUARE_H
