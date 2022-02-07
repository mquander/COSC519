#include <unistd.h>
#include <stdio.h>
#include <pthread.h>


void pickup_forks(int philosopher_number);
void return_forks(int philosopher_number);
void *runner_func(void *param);


int STICKS[5] = {1, 1, 1, 1, 1};
int PHIL[5] = {0, 1, 2, 3, 4};

pthread_mutex_t mutex;
pthread_mutexattr_t attr;
pthread_cond_t cond_var;

int ROUND = 0;
		
void *runner_func(void *param){
	int *p = (int *)param;
	int q = *p;
	
	// call functions from here (within their threads)
	pickup_forks(q);
	return_forks(q);
	
	pthread_exit(NULL);

}
int main(){

	
	
	while(ROUND < 3){
	
		printf("ROUND %d\n", ROUND);
		pthread_t t_ids[5];
		
	
		pthread_mutex_init(&mutex, &attr);
		pthread_cond_init(&cond_var, NULL);
	
		int i = 0;
		while(i < 5){
			pthread_create(&t_ids[i], NULL, runner_func, &PHIL[i]);
			printf("Philosopher %d is now thinking\n", i);
		
				
			i++;
		}
		int j = 0;
		
		while(j < 5){
			pthread_join(t_ids[j], NULL);
			printf("Philosopher %d ROUND %d is DONE\n", j, ROUND);
			j++;
		}
		

		ROUND++;
	}
	printf("Dinner party has ended\n");
}



void pickup_forks(int philosopher_number){
	
	//pthread_mutex_lock(&mutex);
	printf("PHIL[%d] Picking up forks\n", philosopher_number);
	
	
	while(STICKS[philosopher_number] != 1 || STICKS[(philosopher_number+1) % 5] != 1){ 
	
		if(STICKS[philosopher_number] != 1)
			printf("PHIL[%d] waiting for stick %d\n", philosopher_number, philosopher_number);
		
		else if(STICKS[(philosopher_number+1) % 5] != 1)
			printf("PHIL[%d] waiting for stick %d\n", philosopher_number, (philosopher_number+1) % 5);
		
		else
			printf("PHIL[%d] waiting for stick %d and %d\n", philosopher_number, philosopher_number, (philosopher_number+1) % 5);
		
		pthread_cond_wait(&cond_var, &mutex);
	}
	
	STICKS[philosopher_number] = 0;
	STICKS[(philosopher_number+1) % 5] = 0;
	
	printf("PHIL[%d] Eating...\n", philosopher_number);
	printf("STICKS[%d%d%d%d%d]\n", STICKS[0], STICKS[1], STICKS[2], STICKS[3], STICKS[4]);
	
	sleep(1);
	
	pthread_cond_signal(&cond_var);
	pthread_mutex_unlock(&mutex);
	

}
void return_forks(int philosopher_number){

	pthread_mutex_lock(&mutex);
	printf("PHIL[%d] returning forks\n", philosopher_number);
	
	STICKS[philosopher_number] = 1;
	STICKS[(philosopher_number+1) % 5] = 1;
	
	printf("STICKS[%d%d%d%d%d]\n", STICKS[0], STICKS[1], STICKS[2], STICKS[3], STICKS[4]);
	
	pthread_cond_signal(&cond_var);
	pthread_mutex_unlock(&mutex);

}
