#include <iostream>
#include "mysquare.h"

using namespace std;

int main()
{
    MySquare mysqr;
    mysqr.setSide(10);
    cout << "Square area of side length 10 is : " << mysqr.getArea() << endl;
    mysqr.setSide(15);
    cout << "Square area of side length 15 is : " << mysqr.getArea() << endl;
    return 0;
}
