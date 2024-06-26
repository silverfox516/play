#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

// lock 이 없으면 race condition 에 빠질 수 있다.
// 3 -> 1 -> 2 -> 4
// void thr_exit() {
//     done = 1;                    // 1
//     pthread_cond_signal(&c);     // 2
// }
// void thr_join() {
//     if (done == 0)               // 3
//         pthread_cond_wait(&c);   // 4
// }

void thr_exit() {
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void *child(void *arg)
{
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join() {
    pthread_mutex_lock(&m);     // lock m
    while (done == 0)
        pthread_cond_wait(&c, &m);  // unlock m
    pthread_mutex_unlock(&m);       // unlock m
}

int main(int argc, char *argv[])
{
    printf("parent: begin\n");
    pthread_t p;

    pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}
