#include<stdlib.h>
#include<stdio.h>
#include<argp.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char** argv){
	
	int N; char n_String[2];
	printf("Enter a positive integer to calculate the Recaman sequence: ");
	scanf("%d", &N);
	printf("You entered %d\n", N);
	
	sprintf(n_String, "%d", N);
	// itoa(N, n_String, 10);
	char *args[3] = {"./reca", n_String, NULL}; 
	
	pid_t pid = fork();
	
	if(pid == 0){
		// Child 
		execvp("./reca", args);
		return 0;
	}
	wait(0);
	
	printf("Complete\n");
	
	return 0;
}

