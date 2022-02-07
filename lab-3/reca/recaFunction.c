#include<stdlib.h>
#include<stdio.h>
#include<argp.h>
#include<sys/wait.h>
#include<unistd.h>

void reca(int n){
	int new_N;
	
	for(int i = 0; i < n; i++){
		if(i == 0){
			new_N = 1;
			printf("%d\n", new_N);
		}
		else if((new_N % i) == 0){
			new_N = new_N / i;
			printf("%d\n", new_N);
		}
		else{
			new_N = (new_N * i);
			printf("%d\n", new_N);
		}
	}
}
