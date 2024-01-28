#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <array>
#include <vector>
using namespace std;

int main()
{
    int                         myInt[100000];
    std::array<int, 100000>     myArr;
    std::vector<int>            myVec;

    srand(time(NULL));

    chrono::high_resolution_clock::time_point timeStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i)
    {
        myInt[i] = rand() % 100 + 1;
    }
    chrono::high_resolution_clock::time_point timeEnd = chrono::high_resolution_clock::now();
    chrono::milliseconds execTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

    cout << "myInt array running time is " << execTime.count() << " ms" << endl;




    timeStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i)
    {
        myArr[i] = rand() % 100 + 1;
    }
    timeEnd = chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

    cout << "myInt std::array running time is " << execTime.count() << " ms" << endl;



    timeStart = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i)
    {
        myVec.push_back(rand() % 100 + 1);
    }
    timeEnd = chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart);

    cout << "myInt std::vector running time is " << execTime.count() << " ms" << endl;


    return 0;
}
