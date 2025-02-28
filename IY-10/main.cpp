#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_THREADS 8

struct threadParam
{
	int 		t_id;
	char		t_FileName[30];
};

void * ReadFile(void *tParam)
{
	struct threadParam *mData;
	mData = (struct threadParam*) tParam;
   	int i, initPos;
	initPos = mData->t_id * 10000 * 27;
	string line;

    ifstream myFile(mData->t_FileName);
    if (myFile.is_open())
    {
        i = 0;
	myFile.seekg(initPos, ios::beg);
        while (getline(myFile, line) && i < 10000)
        {
            i++;
            //if (i == 1 || i == 10000)

            if (i < 20000)
                cout << "Thread " << mData->t_id << " : " << line << endl;
        }
        myFile.close();
    }
    else
    {
	    cout << "Can not open file "  << " for reading" << endl;
    }
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_t threads[MAX_THREADS];
    struct threadParam mTD[MAX_THREADS];
    int j, rc;
	
	if (argc != 2)
    {
        cout << "Invalid arguments. Provide a file path" << endl;
        cout << "Usage IY_09 <filepath>" << endl;
        return(1);
    }

	for (j = 0; j<MAX_THREADS; j++)
	{
		mTD[j].t_id = j;
		memset(mTD[j].t_FileName, '\0', sizeof(mTD[j].t_FileName));
		memcpy(mTD[j].t_FileName, argv[1], strlen(argv[1]));
		rc = pthread_create(&threads[j], NULL, ReadFile, (void*)&mTD[j]);
		if (rc)
		{
			cout << "Error creating thread, " << rc << endl;
			exit(-1);
		}
	}

	pthread_exit(NULL);
    return 0;
}
