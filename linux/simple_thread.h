#ifndef _SIMPLETHREAD_H
#define _SIMPLETHREAD_H

#include <pthread.h>

class SimpleThread
{
public:
	SimpleThread() : mThread(0) {
		pthread_mutex_init(&mMutex, NULL);
	}

	virtual ~SimpleThread() {
		pthread_mutex_destroy(&mMutex);
	}

	virtual int threadLoop() { return 0; }

	void start() {
		pthread_mutex_lock(&mMutex);
		if (!mThread) {
			pthread_create(&mThread, NULL, SimpleThread::run, (void *)this);
		}
		pthread_mutex_unlock(&mMutex);
	}

	int join() {
		pthread_mutex_lock(&mMutex);
		if (mThread) {
			pthread_join(mThread, NULL);
			mThread = 0;
		}
		pthread_mutex_unlock(&mMutex);
		return retval;
	}

	void setRetval(int r) { retval = r; }

	static void *run(void *data) {
		SimpleThread *pthis = (SimpleThread *)data;
		pthis->setRetval(pthis->threadLoop());
		pthread_exit(NULL);
		return NULL;
	}

private:
	pthread_mutex_t mMutex;
	pthread_t mThread;
	int retval;
};

#endif
