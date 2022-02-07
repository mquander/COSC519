#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "change_priority.c"


// this array below saves the process names and should be passed to other functions

char processpolicyarr[5][50] = 
{
	"firefox",
	"",
	"bash",
	"",
	""
};

// this int is the cputhreshold, should default to 85 and will be apssed to other functions
int cputhreshhold = 5;

int stringInputValidation(char* processname){
	int valid = 1;
	if (strlen(processname)<2 || strcmp(processname,"") == 0 || strcmp(processname, "\n") == 0 || strcmp(processname,"\0") == 0){
		//skipping blanks / null / newlines
		valid = 0;
	}
	return valid;
}

void policyfile()
{
	FILE *fp = fopen("policyfile.txt", "w+");
	fprintf(fp, "%s\n", processpolicyarr[0]);
	fprintf(fp, "%s\n", processpolicyarr[1]);
	fprintf(fp, "%s\n", processpolicyarr[2]);
	fprintf(fp, "%s\n", processpolicyarr[3]);
	fprintf(fp, "%s\n", processpolicyarr[4]);
	// file doesn't exist
	fclose(fp);
}

void printcurrentpolicy () 
{
	printf("1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n",processpolicyarr [0], processpolicyarr[1],
			processpolicyarr[2], processpolicyarr[3], processpolicyarr[4]);
}
void updatepolicy(){
	FILE * fp;
	char line[100];
	
	fp = fopen("./policyfile.txt", "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	for (int i=0; i<5; i++)
	{
		fgets(line, sizeof(line), fp);
		line[strlen(line)-1] = '\0';       
		strcpy(processpolicyarr[i], line);
	};
	fclose(fp);
}

void continueedits(); 

int welcome() 
{
	//the beginning code is a welcome message and a switch case statement that allows the user to
	//We OUCHEEA
	//update the policy and CPU threshold. The system check should be running as soon as this is started.
	char selection[5];
	do{
		printf("\nWelcome to Policy Priorities. Please select an option.\n"
			"1. Add process to policy\n"
			"2. Remove process from policy.\n"
			"3. View current policies.\n"
			"4. Change CPU utilization threshold. \n"
			"5. Enter 5 to run the program. \n"
			"6. Press 6 to quit the program. \n"
			"\nPlease make a selection: ");

		updatepolicy();
		fgets(selection, 5, stdin);

		switch(selection[0])
		{
			case '1' : //adds a process, prompting for a replacement
				printf("Please enter the name of the process to be added to the policy design.\n");
				char newprocessname[120];
				fgets(newprocessname, 120, stdin);
				char replace[2];
				printf("Which process will be replaced by %s", newprocessname);
				printcurrentpolicy ();
				fgets(replace, 2, stdin);
				int n = strlen(newprocessname);
				newprocessname[n-1] = '\0';
				printf("Updated Policy:\n");
				int processnum = (int)(replace[0]-49);
				strcpy(processpolicyarr[processnum], newprocessname);
				printcurrentpolicy ();
				policyfile();
				continueedits();
				break;
			case '2' : //removes a process
				printcurrentpolicy ();
				printf("Please select which process will be removed from the policy design.\n");
				char removepro[2];
				fgets(removepro, 2, stdin);
				int processnumt = (int)(removepro[0]-49);
				strcpy(processpolicyarr[processnumt], "");
				printcurrentpolicy ();
				policyfile ();
				continueedits();
				break;
			case '3' ://prints current policy
				printf("\nCurrent process policy: \n");
				printcurrentpolicy ();
				continueedits();
				break;
			case '4' ://updates CPU threshold
				printf("Enter new CPU threshold: ");
				scanf("%d", &cputhreshhold);
				fgetc(stdin);
				printf("CPU thresh: %d ", cputhreshhold);
				continueedits();
				break;
			case '5' ://run program in background (case 5 updated by MJQ 4/24)
				printf("Program about to run.\n");
				FILE *fp;
				fp = fopen("Log.txt", "a"); // open log.txt to write/indicate priorities that have changed
				
				int * temparray;
				// continually monitors cpu usage, once exceeded it executes statements in if statement
				if(check_CPU_threshold(cputhreshhold)){
					// code below executes once threshold is reached	
					for(int i = 0; i < 5; i++){
						if(stringInputValidation(processpolicyarr[i]) == 1){ // validate string of process, skip blanks, null, new lines
							printf("Process: %s\n", processpolicyarr[i]); // to check current process to be update, can delete this line
							temparray = get_process_by_name(processpolicyarr[i]); // get int[] of the pids and store in temp int[]
							prio(temparray); // loops thru int[] array of pids and sets priority for each element/pid in array
							
						}else{
							continue; // skips iteration if process string is blank, null, or newline
						}	
					}
				}
				//writing out to the file
				//priority number will be saved to Log.txt file 
				//log will appended everytime the program is run
				 int i = 0;
				 while(i < 5){
				 	// writing priority to log.txt, can update what exactly is written to the file
				 	if(stringInputValidation(processpolicyarr[i]) == 1){
				 		fprintf(fp, "Updated priority for %s\n", processpolicyarr[i]);
				 		
				 	}
				 	i++;
				 }
				fclose(fp);
				
				break;

			case '6' ://quit
				exit(0);
		}
	}while((selection[0]) > 6 || (selection [0]) < 1);

	policyfile();
}

void continueedits() 
{ // still executes welcome() with invalid input?
	char yesorno = 'y';
	printf("Continue editing the policy? y/n: ");
	scanf(" %c", &yesorno);
	fgetc(stdin);
	if (yesorno == 'N' || yesorno == 'n'){
		//welcome();
		exit(0);
	};	
}

int main (int argc, char *argv[]) 
{
	if( access( "policyfile.txt", F_OK ) == 0 ) 
	{
    		// file exists
	} 
	else 
	{
		policyfile();
	}
	welcome();
	return 0;
}

