#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include "system_check.c"

int size; // global variable to initialize correct size in prio()
static int process_ids[10];
int *get_process_by_name(char* processpolicyarr){

	char path[56];
		
		char command[60] = "pidof ";
		FILE *fp = popen( strcat(command, processpolicyarr), "r");
	
		if(fp == NULL) // error check openning file
		{
				printf("Error in finding process: %s. \n", processpolicyarr);
		}

		fgets(path, sizeof(path), fp);
			
	
		char pathcopy[56]; 
		strcpy(pathcopy, path); // path & pathcopy are the string of pids for the process
			
		// variable to hold tokens of string
		char* token = strtok(pathcopy, " "); // first token of the string of pids
	
			
		// each token needs to be stored separately, in an array
		char* array[15];
		array[0] = token;	
		int j = 1;
		// loop through and store each token into array
		while(token != NULL){
			token = strtok(NULL, " ");
			array[j] = token;
			j++;
		}
			
		// redeclare int array (process_ids) with correct size to store int values of pids
			
		process_ids[--j];	
		size = j;
		int i = 0;
		// loop through array and convert string pids to ints and store in array
		while(i < j){
			process_ids[i] = atoi(array[i]);
			i++;
		}
			
		int status = pclose(fp);
		if(status == -1){
			printf("Error in closing");
		}
		//resets command string Important.
		command[7] = '\0';
			


	return process_ids;

}

void prio(int pids[]){

	// loop through array pids[], passed as an argument, and set the priorities
    	// checks if priority was set successfully
    	for (int i = 0; i < size; i++){
    	
    		int check = setpriority(PRIO_PROCESS, pids[i], -11);
    		if ( check != -1){
			printf("Priority set sucess!\n");
		}
		
		int get_prio = getpriority(PRIO_PROCESS, pids[i]);
		if(get_prio != -1){
			printf("Priority of %d is %d\n",pids[i], get_prio);
		}
	
	}
}

int check_CPU_threshold(int threshold){

	int threshold_reached = 0; // "true/false" value to return from the function
	int status = 1;
	struct cpustat info_0, info_1; // struct variable from system_check.c to hold cpu info
	float calc;
	
	// continually check cpu percentage usage
	while (status){
		get_stats(&info_0);
		sleep(1);
		get_stats(&info_1);
		printf("CPU: %lf%%\n", calc = calculate_load(&info_0, &info_1));
					
		//if cpu percentage usage exceeds threshold, break out of loop and return "true" (value 1)
		if(calc > threshold){
			printf("CPU threshold exceeded! \n");
			threshold_reached = 1;
			status = 0;  //change the value to 0 to exit out of the while loop
		}
				
	}
	return threshold_reached;
}
