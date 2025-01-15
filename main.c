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
				/*
				Une des limitations de cet algoritme est que si le point de départ choisi est très blanc, on va trop de pixels détéctés par l'algorithme.
				*/
				question_1(args->input_filename, args->output_filename, args->x_0, args->y_0);
				break;
			case 2:
				/*
				La circularité d'un carré de coté c vaut 1. En effet, son rayon vaut c/2 et son diamètre vaut c. La circularité est donc égale à 2*r/d = 1.
				La circularité d'un rectangle de dimension 1 x c est 0. En effet, son rayon vaut 0 (car il n'a pas de centre, que un bord) et son diamètre vaut c. La circularité est donc égale à 0.
				*/
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
			case 8:
				/*
				Le seuil Tn augmente au minimum de w à chaque itération, donc il tend a beaucoup augmenté ce qui conduit à accepter trop de pixels trop clairs.
				*/
				question_8(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion, args->min_size, args->max_size, args->w);
				break;
			case 9:
				/*
				Lorsque nous sommes au creux d'un fissure, Vn est généralement assez étiré et sa circularité est donc proche de 0.
				En revanche, sur un revêtement sain, Vn est plus grand et unidirectionnel, sa circularité est donc proche de 1.
				Ces comportements influent donc sur la valeur de Tn de manière intéréssante.
				En effet, si l'on se situe dans une fissure, on ne va que très peu augmenter Tn, ce qui permet de détecter uniquement les autres pixels de la fissure.
				Si l'on se situe sur un revêtement sain, on va augmenter Tn de manière plus importante, ce qui permet de détecter les pixels de fissures.
				*/
				question_9(args->input_filename, args->output_filename, args->x_0, args->y_0, args->reject_criterion, args->min_size, args->max_size, args->w);
				break;
			case 10:
				question_10(args->input_filename, args->output_filename, args->reject_criterion, args->min_size, args->max_size, args->w, args->s_x, args->s_y);
				break;
			case 11:
				question_11(args->input_filename, args->ns_map);
				break;
			case 12:
				question_12(args->input_filename, args->ns_map, args->graph);
				break;
			/*
			Pour la question 13, je ne comprends pas la question.
			On cherche à lancer un algorithme de remplissage sur les centres des composantes quasi-connexes de l'image, or pour trouver ces centres il faut trouver les points simples et non simples.
			Pour cela on utilise la méthode du nombre de Yokoï, mais pour ce faire l'image doit être en noir et blanc pour distinguer le fond et la forme.
			Cela n'a pas de sens de chercher à détécter une fissure sur une image en noir et blanc...
			*/
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
