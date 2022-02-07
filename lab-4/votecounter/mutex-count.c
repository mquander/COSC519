#include <stdio.h>
#include <pthread.h>

int votes = 0;

pthread_mutex_t mutex;
pthread_mutexattr_t attr;

void *countvotes(void *param) {
	
	int i;
	pthread_mutex_lock(&mutex);
	for (i = 0; i < 10000000; i++) {
		votes += 1;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}
	
int main() {
	
	pthread_mutex_init(&mutex, &attr);
	pthread_t tid1, tid2, tid3, tid4, tid5;
	pthread_create(&tid1, NULL, countvotes, NULL);
	pthread_create(&tid2, NULL, countvotes, NULL);
	pthread_create(&tid3, NULL, countvotes, NULL);
	pthread_create(&tid4, NULL, countvotes, NULL);
	pthread_create(&tid5, NULL, countvotes, NULL);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);
	
	printf("Vote total is %d\n", votes);
	
	return 0;
}
