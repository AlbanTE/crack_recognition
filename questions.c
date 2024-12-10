#include "questions.h"


pile pile_nouv() { return NULL; }

pile empiler(int x, int y, pile p)
{
	pile t = (pile)malloc(sizeof(struct spile));
	t->tx = x;
	t->ty = y;
	t->r = p;
	return t;
}

pile depiler(pile p)
{
	if (p == NULL) return p;

	pile pr = p->r;
	free(p);
	return pr;
}

void pile_free(pile p)
{
	while (p != NULL)
	{
		pile t = p;
		p = p->r;

		free(t);
	}
}

int isInPile(int x, int y, pile p)
{
	while (p != NULL)
	{
		if (p->tx == x && p->ty == y) return 1;
		else p = p->r;
	}
	return 0;
}

int pile_length(pile p)
{
	int length = 0;
	while (p != NULL) { p = p->r; length++;}
	return length;
}

Color getColor(Image *img, int x, int y)
{
    return img->_buffer[x][img->_height-1 - y];
}

int color_equals(Color c1, Color c2)
{
	float c1_greyscale = 255*(c1._blue + c1._green + c1._red) / 3.f;
	float c2_greyscale = 255*(c2._blue + c2._green + c2._red) / 3.f;

	int c1_intensity = roundf(100 * c1_greyscale) / 100;
	int c2_intensity = roundf(100 * c2_greyscale) / 100;

	return (c1_intensity == c2_intensity);
}

int color_less_or_equals(Color c1, Color c2)
{
	float c1_greyscale = 255*(c1._blue + c1._green + c1._red) / 3.f;
	float c2_greyscale = 255*(c2._blue + c2._green + c2._red) / 3.f;

	int c1_intensity = roundf(100 * c1_greyscale) / 100;
	int c2_intensity = roundf(100 * c2_greyscale) / 100;

	// printf("c1 i : %d\t|\tc2 i : %d\n", c1_intensity, c2_intensity);

	return (c1_intensity <= c2_intensity);
}

pile I_remplissage4(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color))
{
	Color germe_color = getColor(img_in, x_germe, y_germe); // img_in->_buffer[x_germe][y_germe];

	pile p = pile_nouv();
	pile visites = pile_nouv();
	pile cc = pile_nouv();

	p = empiler(x_germe, img_in->_height-1 - y_germe, p);
	visites = empiler(x_germe, img_in->_height-1 - y_germe, visites);

	while (p != NULL)
	{
		int x = p->tx, y = p->ty;
		p = depiler(p);
		cc = empiler(x, y, cc);

		int x1 = MAX(x-1, 0), 					y1 = y;
		int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
		int x3 = x, 							y3 = MAX(y-1, 0);
		int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

        if ((*cmp_color)(img_in->_buffer[x1][y1], germe_color)) if (!isInPile(x1, y1, visites)) { p = empiler(x1, y1, p); visites = empiler(x1, y1, visites); }
		if ((*cmp_color)(img_in->_buffer[x2][y2], germe_color)) if (!isInPile(x2, y2, visites)) { p = empiler(x2, y2, p); visites = empiler(x2, y2, visites); }
		if ((*cmp_color)(img_in->_buffer[x3][y3], germe_color)) if (!isInPile(x3, y3, visites)) { p = empiler(x3, y3, p); visites = empiler(x3, y3, visites); }
		if ((*cmp_color)(img_in->_buffer[x4][y4], germe_color)) if (!isInPile(x4, y4, visites)) { p = empiler(x4, y4, p); visites = empiler(x4, y4, visites); }
	}

	pile_free(p);
	pile_free(visites);

	return cc;
}

pile I_remplissage8(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color))
{
	Color germe_color = getColor(img_in, x_germe, y_germe); // img_in->_buffer[x_germe][y_germe];

	pile p = pile_nouv();
	pile visites = pile_nouv();
	pile cc = pile_nouv();

	p = empiler(x_germe, img_in->_height-1 - y_germe, p);
	visites = empiler(x_germe, img_in->_height-1 - y_germe, visites);

	while (p != NULL)
	{
		int x = p->tx, y = p->ty;
		p = depiler(p);
		cc = empiler(x, y, cc);

		int x1 = MAX(x-1, 0), 					y1 = y;
		int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
		int x3 = x, 							y3 = MAX(y-1, 0);
		int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

        if ((*cmp_color)(img_in->_buffer[x1][y1], germe_color)) if (!isInPile(x1, y1, visites)) { p = empiler(x1, y1, p); visites = empiler(x1, y1, visites); }
		if ((*cmp_color)(img_in->_buffer[x2][y2], germe_color)) if (!isInPile(x2, y2, visites)) { p = empiler(x2, y2, p); visites = empiler(x2, y2, visites); }
		if ((*cmp_color)(img_in->_buffer[x3][y3], germe_color)) if (!isInPile(x3, y3, visites)) { p = empiler(x3, y3, p); visites = empiler(x3, y3, visites); }
		if ((*cmp_color)(img_in->_buffer[x4][y4], germe_color)) if (!isInPile(x4, y4, visites)) { p = empiler(x4, y4, p); visites = empiler(x4, y4, visites); }

		if ((*cmp_color)(img_in->_buffer[x1][y3], germe_color)) if (!isInPile(x1, y3, visites)) { p = empiler(x1, y3, p); visites = empiler(x1, y3, visites); }
		if ((*cmp_color)(img_in->_buffer[x1][y4], germe_color)) if (!isInPile(x1, y4, visites)) { p = empiler(x1, y4, p); visites = empiler(x1, y4, visites); }
		if ((*cmp_color)(img_in->_buffer[x2][y3], germe_color)) if (!isInPile(x2, y3, visites)) { p = empiler(x2, y3, p); visites = empiler(x2, y3, visites); }
		if ((*cmp_color)(img_in->_buffer[x2][y4], germe_color)) if (!isInPile(x2, y4, visites)) { p = empiler(x2, y4, p); visites = empiler(x2, y4, visites); }

	}

	pile_free(p);
	pile_free(visites);

	return cc;
}

Image* pileToImage(pile p, int w, int h)
{
	Image *img = I_new(w, h);

	pile tmp = p;

	while (p != NULL) { I_plotColor(img, p->tx, p->ty, C_new(1,1,1)); p = p->r; }

	pile_free(tmp);

	return img;
}

void writeImage(char *outname, Image *out)
{
	FILE *output = fopen(outname, "w+");
    if (output == NULL) { fprintf(stderr, "Error creating %s file...\n", outname); exit(1); }
    fclose(output);


    Ppm outfile = PPM_nouv(outname, PPM_ECRITURE);
    PPM_initEcriture(outfile, PPM_ASCII, out->_width, out->_height, 8);
    for (int i = 0; i < out->_height; i++)
    {
        for (int j = 0; j < out->_width; j++)
        {
            Color c = getColor(out, j, i);
            fprintf(outfile->_ppmfile, "%d %d %d ", (int) (outfile->_valmax * c._red), (int) (outfile->_valmax * c._green), (int) (outfile->_valmax * c._blue));
        }
        fprintf(outfile->_ppmfile, "\n");
    }
    PPM_fermeture(outfile);
}

void question_1(char *filename, char *outname, int x0, int y0)
{
    Image *img = I_read(filename);    
	
    pile p = I_remplissage8(img, x0, y0, color_less_or_equals);

	Image *out = pileToImage(p, img->_width, img->_height);
	writeImage(outname, out);

	I_free(img);
	I_free(out);
}

int dinf(int xA, int yA, int xB, int yB)
{
	return MAX(abs(xB-xA), abs(yB-yA));
}

float circularite(Image *cc)
{
	int **distances = (int **)calloc(cc->_width, sizeof(int*));
	for(int x=0;x<cc->_width;x++)
		distances[x] = (int*)calloc(cc->_height,sizeof(int));

	for (int x=0; x < cc->_width; x++)
		for (int y=0; y < cc->_height; y++)
			distances[x][y] = (cc->_buffer[x][y]._red == 0 ? 0 : (int) INFINITY);

	// --------------------------------------------------------
	pile tous  = pile_nouv();

	int dcentres = 0;

	for (int x=0; x < cc->_width; x++)
	{
		for (int y=0; y < cc->_height; y++)
		{
			if (cc->_buffer[x][y]._red == 1)
			{
				tous = empiler(x, y, tous);
				
				int dmin = (int) INFINITY;
				for (int x1=MAX(x-1, 0); x1 <= MIN(x+1, cc->_width-1); x1++) 
					for (int y1=MAX(y-1, 0); y1 <= MIN(y+1, cc->_height-1); y1++)
						if (distances[x1][y1] < dmin) dmin = distances[x1][y1];
				
				distances[x][y] = (dmin == (int) INFINITY ? 1 : dmin + 1);
				if (distances[x][y] > dcentres) dcentres = distances[x][y];
			}
		}
	}

	printf("Distances centres : %d\n", dcentres);
	// for (int y = 0; y < cc->_height; y++) printf("%d ", distances[100][y]);

	// TODO : calculer R et D
	// pile centres = pile_nouv();
	// pile bords   = pile_nouv();
	// for (int x=0; x < cc->_width; x++)
	// {
	// 	for (int y=0; y < cc->_height; y++)
	// 	{
	// 		if (distances[x][y] == dcentres) centres = empiler(x, y, centres);
	// 		if (distances[x][y] == 1) bords = empiler(x, y, bords);
	// 	}
	// }

	// pile tmp_centres = centres, tmp_bords = bords;

	// Calcul du rayon ----------------------------------------
	int rayon = dcentres;
	// while (tmp_centres != NULL) 
	// {
	// 	int xc = tmp_centres->tx, yc = tmp_centres->ty;

	// 	while (tmp_bords != NULL) 
	// 	{
	// 		int xb = tmp_bords->tx, yb = tmp_bords->ty;
	// 		rayon = MIN(rayon, dinf(xc, yc, xb, yb));

	// 		tmp_bords = tmp_bords->r;
	// 	}

	// 	tmp_bords = bords;
	// 	tmp_centres = tmp_centres->r;
	// }

	printf("Rayon : %d\n", rayon);


	// Calcul du diamètre -------------------------------------
	pile tmp_tous = tous, tmp_tous2 = tous;

	int diametre = 0;
	while (tmp_tous != NULL)
	{
		int x1 = tmp_tous->tx, y1 = tmp_tous->ty;

		while (tmp_tous2 != NULL)
		{
			int x2 = tmp_tous2->tx, y2 = tmp_tous2->ty;
			diametre = MAX(diametre, dinf(x1, y1, x2, y2));

			tmp_tous2 = tmp_tous2->r;
		}

		tmp_tous2 = tous;
		tmp_tous = tmp_tous->r;
	}

	printf("Diamètre : %d\n", diametre);

	printf("Circularité : %f\n", (2.f*rayon)/diametre);

	pile_free(tous);
	// pile_free(centres);
	// pile_free(bords);


	// --------------------------------------------------------

	// FILE *test = fopen("q2_dist", "w+");
	// for (int x = 0; x < cc->_width; x++)
	// {
	// 	for (int y = 0; y < cc->_height; y++)
	// 	{
	// 		fprintf(test, "%d ", distances[x][y]);
	// 	}
	// 	fprintf(test, "\n");
	// }
	// fclose(test);

	for(int x=0;x<cc->_width;x++)
		free(distances[x]);
	free(distances);

	return 0.f;
}

void question_2(int x, int y)
{
	Image *img = I_read("TP2_img1.pbm");    
	
    pile p = I_remplissage8(img, x, y, color_equals);

	Image *out = pileToImage(p, img->_width, img->_height);

	printf("Call circularite...\n");
	circularite(out);

	writeImage("q2.ppm", out);

	I_free(img);
	I_free(out);
}