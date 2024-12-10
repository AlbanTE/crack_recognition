#ifndef __OPT_H_
#define __OPT_H_

#include <stddef.h>

#define CHECK_ARGV(checkStr, arg, ret, errText) do \
	{ \
		if((checkStr) == (arg)) \
		{ \
			fprintf(stderr, (errText)); \
			fprintf(stderr, "%s\n", (checkStr)); \
			project_opt_free_args(ret), (ret) = NULL; \
		} \
	} \
	while(0)

typedef struct
{
	int question;
	size_t x_0;
	size_t y_0;
	char* input_filename;
	char* output_filename;
	float reject_criterion;
	size_t min_size;
	size_t max_size;
	float w;
	size_t s_x;
	size_t s_y;
	char* ns_map;
	char* graph;
} project_opt_t;

project_opt_t* project_opt_new();
void project_opt_free_args(project_opt_t* args);
project_opt_t* project_opt_parse_args(int argc, char* argv[]);
void project_opt_summarize_args(project_opt_t* args);

#endif
