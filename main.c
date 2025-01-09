#include <stdlib.h>
#include <stdio.h>

#include "opt.h"
#include "questions.h"

int main(int argc, char* argv[])
{
	project_opt_t* args = NULL;
	
	args = project_opt_parse_args(argc, argv);
	if(args != NULL)
	{
		project_opt_summarize_args(args);
		
		/*
			To see the available options in args, have a look at opt.h.
			Do not free any member of this struct. Use project_opt_free_args 
			instead.
		*/
		
		switch(args->question)
		{
			case 1:
				/*question_1(args); or question_1(args->x_0, [...]);*/
				question_1(args->input_filename, args->output_filename, args->x_0, args->y_0);
				break;
			case 2:
				question_2(args->x_0, args->y_0);
				break;
			case 3:
				question_3(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion);
				break;
			case 4:
				question_4(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion);
				break;
			case 5:
				question_5(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion, args->min_size);
				break;
			case 6:
				question_6(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion, args->min_size, args->max_size);
				break;
			case 7:
				question_7(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion, args->min_size, args->max_size);
				break;
			/* [...] */
			default:
				fprintf(stderr, "Question %d: no answer.\n", args->question);
				break;
		}
		
		project_opt_free_args(args), args = NULL;
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
