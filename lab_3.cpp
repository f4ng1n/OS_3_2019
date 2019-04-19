#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <fstream>

using namespace std;

struct Args {
	int flag_1;
	int flag_2;
};

int filedes[2];

void* func_1(void* args)
{
	Args *arg=(Args*) args;	

	int buf = 0;

	while (arg->flag_1 == 0) 
	{
		buf ++; 
		cout << "Already written in channel: " << buf << endl;
		write(filedes[1], &buf, sizeof(int));		
		sleep(1);
	}	
}

void* func_2(void* args)
{
	Args *arg=(Args*) args;
	int buf;
	while (arg->flag_2 == 0) 
	{
		
		int ret = read(filedes[0], &buf, sizeof(int));
		if (ret == -1)
			{
				if (errno == EAGAIN)
					cout << "Empty buffer: " << strerror(EAGAIN) << endl;
				sleep(1);
			}
		else
			{
				cout << "Ouput to  " << buf << endl;
			}
		sleep(1);
	}
}


int main()
{
	cout <<"\nProgram started!" << endl;
	Args pthread_arg; 

	pthread_arg.flag_1 = 0;
	pthread_arg.flag_2 = 0;

	//pipe2(filedes, O_NONBLOCK);
	
	pipe(filedes);
	int flags = fcntl(filedes[0],F_GETFL);
	int err = fcntl(filedes[0],F_SETFL, flags|O_NONBLOCK);

		 

	pthread_t pthread_1, pthread_2;	

	pthread_create(&pthread_1, NULL, func_1, (void*) &pthread_arg); 
	pthread_create(&pthread_2, NULL, func_2, (void*) &pthread_arg);
 	
	getchar();

	pthread_arg.flag_1 = 1;
	pthread_arg.flag_2 = 1;		

	pthread_join(pthread_1, NULL);	
 	pthread_join(pthread_2, NULL);
 
 	close(filedes[0]);
 	close(filedes[1]);
	cout <<"\nProgram finished!" << endl;
    return 0;
}
