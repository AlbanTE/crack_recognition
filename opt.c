#include "opt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

project_opt_t* project_opt_new()
{
	return calloc(1, sizeof(project_opt_t));
}

void project_opt_free_args(project_opt_t* args)
{
	if(args != NULL)
		free(args);
}

project_opt_t* project_opt_parse_args(int argc, char* argv[])
{
	/* Variables used to parse input */
	int i = 0;
	char* checkStr = NULL;
	
	/* All the parameters that can be given in argv */
	int question = 0;
	size_t x_0 = 0;
	size_t y_0 = 0;
	size_t min_size = 2;
	size_t max_size = 5;
	size_t s_x = 1;
	size_t s_y = 1;
	float w = 1.;
	float reject_criterion = 0.5;
	char* input_filename = NULL;
	char* output_filename = NULL;
	char* ns_map = NULL;
	char* graph = NULL;
	
	/* Return variable */
	project_opt_t* ret = NULL;
	ret = project_opt_new();
	
	if(ret == NULL)
		return ret;
	
	/* Retrieve user input and perform basic checks on it (syntaxic) */
	for(i=1; i < argc-1; i++)
	{
		if(strcmp(argv[i], "--question") == 0)
		{
			question = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse question ID.\n");
			i++;
		}
		else if(strcmp(argv[i], "--x_0") == 0)
		{
			x_0 = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse x_0.\n");
			i++;
		}
		else if(strcmp(argv[i], "--y_0") == 0)
		{
			y_0 = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse y_0.\n");
			i++;
		}
		else if(strcmp(argv[i], "--input_filename") == 0)
		{
			input_filename = argv[i+1];
			i++;
		}
		else if(strcmp(argv[i], "--output_filename") == 0)
		{
			output_filename = argv[i+1];
			i++;
		}
		else if(strcmp(argv[i], "--reject_criterion") == 0)
		{
			reject_criterion = strtof(argv[i+1], &checkStr);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse reject_criterion.\n");			
			i++;
		}
		else if(strcmp(argv[i], "--min_size") == 0)
		{
			min_size = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse min_size.\n");
			i++;
		}
		else if(strcmp(argv[i], "--max_size") == 0)
		{
			max_size = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse max_size.\n");
			i++;
		}
		else if(strcmp(argv[i], "--w") == 0)
		{
			w = strtof(argv[i+1], &checkStr);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse w.\n");			
			i++;
		}
		else if(strcmp(argv[i], "--s_x") == 0)
		{
			s_x = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse s_x.\n");
			i++;
		}
		else if(strcmp(argv[i], "--s_y") == 0)
		{
			s_y = strtol(argv[i+1], &checkStr, 10);
			CHECK_ARGV(checkStr, argv[i+1], ret, "Error: cannot parse s_y.\n");
			i++;
		}
		else if(strcmp(argv[i], "--ns_map") == 0)
		{
			ns_map = argv[i+1];
			i++;
		}
		else if(strcmp(argv[i], "--graph") == 0)
		{
			graph = argv[i+1];
			i++;
		}
		else
		{
			fprintf(stderr, "Error: unknown option '%s'\n", argv[i]);
			project_opt_free_args(ret), ret = NULL;
		}
	}
	
	/* Basic checks on user input (logical) */
	if(input_filename == NULL)
	{
		fprintf(stderr, "Error: no input filename was specified (--input).\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	if(output_filename == NULL)
	{
		fprintf(stderr, "Error: no output filename was specified (--output).\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	if(question == 11 && ns_map == NULL)
	{
		fprintf(stderr, "Error: no non-simple map filename was specified (--ns_map).\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	if(question >= 12 && question < 14 && graph == NULL)
	{
		fprintf(stderr, "Error: no graph filename was specified (--graph).\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	if(max_size < min_size)
	{
		fprintf(stderr, "Error: max_size must be > min_size.\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	if(reject_criterion < 0. || reject_criterion > 1.)
	{
		fprintf(stderr, "Error: invalid reject threshold. Must be between 0 and 1.\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	if(w <= 0.)
	{
		fprintf(stderr, "Error: invalid w. Must be > 0.\n");
		project_opt_free_args(ret), ret = NULL;
	}
	
	/* If everything is fine, we fill the structure. */
	if(ret != NULL)
	{
		ret->question = question;
		
		if(ret->question > 0 && ret->question <= 14)
		{
			ret->input_filename = input_filename;
			ret->output_filename = output_filename;
			ret->x_0 = x_0;
			ret->y_0 = y_0;
			ret->reject_criterion = reject_criterion;
			ret->min_size = min_size;
			ret->max_size = max_size;
			ret->w = w;
			ret->s_x = s_x;
			ret->s_y = s_y;
			ret->ns_map = ns_map;
			ret->graph = graph;
		}
		else
		{
			fprintf(stderr, "Error: wrong or missing question ID.\n");
			project_opt_free_args(ret), ret = NULL;
		}
	}
	
	return ret;
}

void project_opt_summarize_args(project_opt_t* args)
{
	if(args != NULL)
	{
		if(args->question > 0 && args->question <= 14)
		{
			printf("Question %d.\n", args->question);
			printf("Input file: %s\n", args->input_filename);
			printf("Output file: %s\n", args->output_filename);
			printf("x_0 = %lu, y_0 = %lu.\n", args->x_0, args->y_0);
			printf("Circularity threshold for rejection: %f.\n", args->reject_criterion);
			printf("Min size: %lu. Max size: %lu.\n", args->min_size, args->max_size);
			printf("Increment w: %f.\n", args->w);
			printf("s_x = %lu, s_y = %lu.\n", args->s_x, args->s_y);
			printf("Non-simple map file: %s.\n", args->ns_map);
			printf("Graph file: %s.\n", args->graph);
		}
		else
		{
			fprintf(stderr, "Error: question ID is incorrect.\n");
		}
	}
	else
	{
		printf("(null).\n");
	}
}
