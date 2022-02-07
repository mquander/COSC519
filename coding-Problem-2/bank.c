#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int ids[] = {0, 1, 2};
int balance = 0;

int receive_deposit(int amount, int id){

	if(id == 0){
		//balance = 340;
		balance = balance + amount;
	}else if(id == 1){
		//balance = 640;
		balance = balance + amount;
	}
	else if(id == 2){
		//balance = 930;
		//balance = balance - amount;
	}
	

}

int withdraw(int id, int amount){
	
	do{
	if((balance - amount) < 0){
	pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	else{	
	if(id == 0){
		
		balance = balance - amount; break;
	}else if(id == 1){
		//balance = 640;
		balance = balance - amount; break;
	}
	else if(id == 2 ){
		//balance = 930;
		balance = balance - amount; break;
	}
	}
	pthread_mutex_lock(&mutex);
	}while(1);
	
}



void *function(void *param){
	int *p = (int *) param;
	int id = *p;
	// lock balance to withdraw
	
	
	
		if(id == 0){
			pthread_mutex_lock(&mutex);
			balance = 340;
			printf("Account A initial balance: %d\n", balance);
			withdraw(0, 60);
			printf("Account A balance after withdraw: %d\n", balance);
			pthread_mutex_unlock(&mutex);
		}else if(id == 1){
			pthread_mutex_lock(&mutex);
			balance = 640;
			printf("Account B initial balance: %d\n", balance);
			withdraw(1, 800);
			printf("Account B balance after withdraw: %d\n", balance);
			pthread_mutex_unlock(&mutex);
		}
		else if(id == 2){
			pthread_mutex_lock(&mutex);
			balance = 930;
			printf("Account C initial balance: %d\n", balance);
			withdraw(2, 520);
			printf("Account C balance after withdraw: %d\n", balance);
			pthread_mutex_unlock(&mutex);
		}
	
	
	//printf("Account %d balance after withdraw: %d\n", id, balance);
	// lock balance to deposit
	pthread_mutex_lock(&mutex);
	
	if(id == 0){
		receive_deposit(220, 0);
		printf("Account %d balance after deposit: %d\n", id, balance);
	}else if(id == 1){
		receive_deposit(300, 1);
		printf("Account %d balance after deposit: %d\n", id, balance);
	}
	else if(id == 2){
		//receive_deposit(220, 0);
		//printf("Account %d balance after deposit: %d\n", id, balance);
		
	}
	pthread_mutex_unlock(&mutex);
	
}

int main(){
	
	pthread_mutex_init(&mutex, NULL);
	pthread_t thread_A, thread_B, thread_C;
	
	pthread_create(&thread_A, NULL, function, &ids[0]); //
	pthread_create(&thread_B, NULL, function, &ids[1]); // t
	pthread_create(&thread_C, NULL, function, &ids[2]); 
	
	/*pthread_create(&thread_A, NULL, withdraw, 60); //
	pthread_create(&thread_A, NULL, deposit, 60); // thread A withdraws adn deposits
	pthread_create(&thread_B, NULL, withdraw, 800); // thread B only deposits
	pthread_create(&thread_C, NULL, withdraw, 500); //thread C withdraws 500 and deposits 220 to A 
	pthread_create(&thread_C, NULL, deposit, 220); //and 300 to B
	pthread_create(&thread_C, NULL, deposit, 300);*/
	
	
	pthread_join(thread_A, NULL);
	pthread_join(thread_B, NULL);
	pthread_join(thread_C, NULL);
}


