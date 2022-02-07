#include<stdlib.h>
#include<stdio.h>
#include<argp.h>
#include<pthread.h>

const char *argp_program_version = "thread 1.0";
const char *argp_program_bug_address = "fred@email.org";
static char doc[] ="a program to demonstrate argument parsing and threading";
static char args_doc[] = "INT1 INT2";

void *child_func(void *param);

static struct argp_option options[] = {
	{"verbose", 'v', 0,   0, "produce verbose output" },
	{"output", 'o', "FILE", 0, "Output to FILE"},
	{ 0 },
};

typedef struct {
	char *arg_output;
	int arg_num[1];
	int arg_verbose;
} args_t;

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
	/* Get the input argument from argp_parse, which we know is a pointer to our 		arguments structure. */
	args_t *arguments = state->input;
	
	switch (key) {
	case 'v':
		arguments->arg_verbose = 1;
		break;
	case 'o':
		arguments->arg_output = arg;
		break;
	case ARGP_KEY_ARG:
		if (state->arg_num >= 1)
		/* Too many arguments. */
			argp_usage (state);
		arguments->arg_num[state->arg_num] = atoi(arg);
		break;
	case ARGP_KEY_END:
		if (state->arg_num < 1)
		/* Not enough arguments. */
			argp_usage (state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };


pthread_t tid, t;
int i, j;

int main(int argc, char** argv){
	
	args_t argument;
	argument.arg_num[0] = 0;
	argument.arg_verbose = 0;
	argument.arg_output = "-";
	
	argp_parse(&argp, argc, argv, 0, 0, &argument);
	
	int N = argument.arg_num[0];
	pthread_t t_ids[N];
	int data[N];
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	i = 0;
	while(i < N){
	data[i] = i + 1;
		
		pthread_create(&t_ids[i], NULL, child_func, &data[i]); //&tid
		//t_ids[i] = tid;
		printf("Creating thread %d\n", i+1);
		i++;
	}
	//i=0;
	j = 0;
	while(j < N){
		
		pthread_join(t_ids[j], NULL);		
		printf("Joining thread %d\n", j+1);
		j++;
	}
	
	return 0;
}
void *child_func(void *param){
	int *p = (int *)param;
	int v = *p;
	printf("Hello world! I am thread %d\n", v); //   tid
	pthread_exit(NULL);
	
}

