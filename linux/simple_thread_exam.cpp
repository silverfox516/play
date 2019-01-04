#include <stdio.h>
#include <unistd.h>
#include "simple_thread.h"

class ThreadOne : public SimpleThread
{
public:
	int threadLoop();
	int stop();

	ThreadOne() : mExiting(false), mCount(0) {}

private:
	bool mExiting;
	int mCount;
};

int ThreadOne::stop()
{
	mExiting = true;

	return join();
}

int ThreadOne::threadLoop()
{
	printf("go threadLoop()\n");

	while (true) {
		if (mExiting) break;

		mCount++;
		printf("count %d\n", mCount);
		sleep(1);
	}

	printf("stop with %d\n", mCount);

	return mCount;
}

int main()
{
	ThreadOne one;

	one.start();	
	one.start();	
	one.start();	

	sleep(10);

	printf("joind ret %d\n", one.stop());

	return 0;
}
