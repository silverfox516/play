#ifndef _SIMPLETHREAD_H
#define _SIMPLETHREAD_H

#include <pthread.h>

class SimpleThread
{
public:
	SimpleThread() {}
	virtual ~SimpleThread() {}

	virtual int run() { return 0; }

	void start() {
		pthread_create(&mThread, NULL, SimpleThread::_run, (void *)this);
	}

	int join() {
		pthread_join(mThread, NULL);
		return retval;
	}

	void setRetval(int r) { retval = r; }

	static void *_run(void *data) {
		SimpleThread *pthis = (SimpleThread *)data;
		pthis->setRetval(pthis->run());
		pthread_exit(NULL);
		return NULL;
	}

private:
	pthread_t mThread;
	int retval;
};

#endif
