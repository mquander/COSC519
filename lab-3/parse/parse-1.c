#include<stdlib.h>
#include<stdio.h>
#include<argp.h>

const char *argp_program_version = "parse 1.0";
const char *argp_program_bug_address = "fred@email.org";
static char doc[] ="parse -- a program to demonstrate command line argument parsing";
static char args_doc[] = "INT1 INT2";

static struct argp_option options[] = {
	{"verbose", 'v', 0,   0, "produce verbose output" },
	{"output", 'o', "FILE", 0, "Output to FILE"},
	{ 0 },
};

typedef struct {
	char *arg_output;
	int arg_num[2];
	int arg_verbose;
} args_t;

/* Parse a single option. */
static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
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
		if (state->arg_num >= 2)
		/* Too many arguments. */
			argp_usage (state);
		arguments->arg_num[state->arg_num] = atoi(arg);
		break;
	case ARGP_KEY_END:
		if (state->arg_num < 2)
		/* Not enough arguments. */
			argp_usage (state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv) {
	args_t arguments;
	
	/* Default values. */
	arguments.arg_num[0] = 0;
	arguments.arg_num[1] = 0;
	arguments.arg_verbose = 0;
	arguments.arg_output = "-";
	
	/* Parse our arguments; every option seen by parse_opt will
	be reflected in arguments. */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
	printf("Arguments\n"
		"Number One: %d\tNumber Two: %d\n"
		"Verbose: %d\tFile: %s\n",
		arguments.arg_num[0],arguments.arg_num[1],
		arguments.arg_verbose,arguments.arg_output);
	
	return 0;
}
