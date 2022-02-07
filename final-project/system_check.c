#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
unsigned sleep(unsigned sec);

/* borrowed/modified code from https://www.kgoettler.com/post/proc-stat/ 
	comments added by MJQ to explain each line*/

/* struct to hold data from the /proc/stat file;
the variables will hold the aggregate time values, 
in centiseconds (1/100 of a second), since system boot 
https://man7.org/linux/man-pages/man5/proc.5.html */

struct cpustat {
	unsigned long t_user; // all user processes
	unsigned long t_nice; // lower priority/niced processes
	unsigned long t_system; // kernel processes
	unsigned long t_idle; // idle tasks
	unsigned long t_iowait; // estimate of i/o wait
	unsigned long t_irq; // servicing interrupts
	unsigned long t_softirq; // servicing soft interrupts
};

/* scan the first line of the /proc/stat file and 
	store the values in the struct variables */
void get_stats(struct cpustat *st){

	FILE *fp = fopen("/proc/stat", "r"); //open the /proc/stat file for reading cpu info
	
	char cpu[7];
	
	//read in only the first row of /proc/stat, the aggregate of the CPU's info
	fscanf(fp, "%s %ld %ld %ld %ld %ld %ld %ld", // reads in 1 string and 7 long decimals/ints
		cpu, // cpu aggregate
		&(st->t_user), // user time
		&(st->t_nice),  // nice time
		&(st->t_system), // kernel time
		&(st->t_idle), // idle time
		&(st->t_iowait), // i/o wait time (estimate)
		&(st->t_irq), // irq time
		&(st->t_softirq)); // softirq time
        
	fclose(fp);
	return;
}

/* takes the first cpu info set and current cpu info set to
obtain the previous and current idle times, previous and 
current usage times, and previous and current total cpu times
to calculate the percentage*/
double calculate_load(struct cpustat *prev, struct cpustat *cur){
	// the cpu struct arguments hold the cpu info
	
	// calculate the previous and current idle time (idle+iowait)
	int idle_prev = (prev->t_idle) + (prev->t_iowait);
	int idle_cur = (cur->t_idle) + (cur->t_iowait);
	
	// calculate previous and current usage, from the cpu struct variables
	int usage_prev = (prev->t_user) + (prev->t_nice) + (prev->t_system) + (prev->t_irq) + (prev->t_softirq);
	int usage_cur = (cur->t_user) + (cur->t_nice) + (cur->t_system) + (cur->t_irq) + (cur->t_softirq);

	// calculate the total time (idle+usage), for previous and current
	int total_time_prev = idle_prev + usage_prev;
	int total_time_cur = idle_cur + usage_cur;

	// calculate the change in total time, and the change in idle time (curr-prev)
	double total_time_delta = (double) total_time_cur - (double) total_time_prev;
	double idle_time_delta = (double) idle_cur - (double) idle_prev;

	// total_time_delta - idle_time_delta = total usage time
	// calculate the percentage
	double cpu_perc = ( (total_time_delta - idle_time_delta) / total_time_delta  )*100;

	return cpu_perc;
}
/* end of borrowed/manipulated code */
