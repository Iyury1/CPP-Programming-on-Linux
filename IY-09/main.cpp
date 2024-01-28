#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream myFile(argv[1]);
    string line;
    int i;
    if (argc != 2)
    {
        cout << "Invalid arguments. Provide a file path" << endl;
        cout << "Usage IY_09 <filepath>" << endl;
        return(1);
    }
    if (myFile.is_open())
    {
        i = 0;
        while (getline(myFile, line))
        {
            i++;
            if (i < 10)
                cout << line << endl;
        }
        myFile.close();
    }
    return 0;
}
