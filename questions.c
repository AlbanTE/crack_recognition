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

int isVisited(int x, int y, int **visites)
{
	return visites[x][y];
}

pile I_remplissage4(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color))
{
	Color germe_color = img_in->_buffer[x_germe][y_germe];

	pile p = pile_nouv();
	pile cc = pile_nouv();

	p = empiler(x_germe, y_germe, p);

	int **visites = (int **)calloc(img_in->_width, sizeof(int*));
	for(int x=0;x<img_in->_width;x++)
		visites[x] = (int*)calloc(img_in->_height,sizeof(int));

	while (p != NULL)
	{
		int x = p->tx, y = p->ty;
		p = depiler(p);
		cc = empiler(x, y, cc);

		int x1 = MAX(x-1, 0), 					y1 = y;
		int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
		int x3 = x, 							y3 = MAX(y-1, 0);
		int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

        if ((*cmp_color)(img_in->_buffer[x1][y1], germe_color)) if (!visites[x1][y1]) { p = empiler(x1, y1, p); visites[x1][y1] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y2], germe_color)) if (!visites[x2][y2]) { p = empiler(x2, y2, p); visites[x2][y2] = 1; }
		if ((*cmp_color)(img_in->_buffer[x3][y3], germe_color)) if (!visites[x3][y3]) { p = empiler(x3, y3, p); visites[x3][y3] = 1; }
		if ((*cmp_color)(img_in->_buffer[x4][y4], germe_color)) if (!visites[x4][y4]) { p = empiler(x4, y4, p); visites[x4][y4] = 1; }
	}

	pile_free(p);
	for(int x=0;x<img_in->_width;x++)
		free(visites[x]);
	free(visites);

	return cc;
}

pile I_remplissage8(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color))
{
	Color germe_color = img_in->_buffer[x_germe][y_germe];

	pile p = pile_nouv();
	pile cc = pile_nouv();

	p = empiler(x_germe, y_germe, p);

	int **visites = (int **)calloc(img_in->_width, sizeof(int*));
	for(int x=0;x<img_in->_width;x++)
		visites[x] = (int*)calloc(img_in->_height,sizeof(int));

	while (p != NULL)
	{
		int x = p->tx, y = p->ty;
		p = depiler(p);
		cc = empiler(x, y, cc);

		int x1 = MAX(x-1, 0), 					y1 = y;
		int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
		int x3 = x, 							y3 = MAX(y-1, 0);
		int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

        if ((*cmp_color)(img_in->_buffer[x1][y1], germe_color)) if (!visites[x1][y1]) { p = empiler(x1, y1, p); visites[x1][y1] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y2], germe_color)) if (!visites[x2][y2]) { p = empiler(x2, y2, p); visites[x2][y2] = 1; }
		if ((*cmp_color)(img_in->_buffer[x3][y3], germe_color)) if (!visites[x3][y3]) { p = empiler(x3, y3, p); visites[x3][y3] = 1; }
		if ((*cmp_color)(img_in->_buffer[x4][y4], germe_color)) if (!visites[x4][y4]) { p = empiler(x4, y4, p); visites[x4][y4] = 1; }

		if ((*cmp_color)(img_in->_buffer[x1][y3], germe_color)) if (!visites[x1][y3]) { p = empiler(x1, y3, p); visites[x1][y3] = 1; }
		if ((*cmp_color)(img_in->_buffer[x1][y4], germe_color)) if (!visites[x1][y4]) { p = empiler(x1, y4, p); visites[x1][y4] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y3], germe_color)) if (!visites[x2][y3]) { p = empiler(x2, y3, p); visites[x2][y3] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y4], germe_color)) if (!visites[x2][y4]) { p = empiler(x2, y4, p); visites[x2][y4] = 1; }
	}

	pile_free(p);
	for(int x=0;x<img_in->_width;x++)
		free(visites[x]);
	free(visites);

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
            Color c = out->_buffer[j][i];
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

	putchar('\n');
}

// -----------------------------------------------------------------------------------------------------------

int dinf(int xA, int yA, int xB, int yB)
{
	return MAX(abs(xB-xA), abs(yB-yA));
}

float circularite(Image *cc)
{
	int **distances = (int **)calloc(cc->_width, sizeof(int*));
	for(int x=0;x<cc->_width;x++)
		distances[x] = (int*)calloc(cc->_height,sizeof(int));

	int dmax = 1 + MIN(cc->_width, cc->_height);

	for (int x=0; x < cc->_width; x++)
		for (int y=0; y < cc->_height; y++)
			distances[x][y] = (cc->_buffer[x][y]._red == 0 ? 0 : dmax);

	// --------------------------------------------------------
	int dcentres = 0;

	for (int x=0; x < cc->_width; x++)
	{
		for (int y=0; y < cc->_height; y++)
		{
			if (cc->_buffer[x][y]._red == 1)
			{				
				int dmin = dmax;
				for (int x1=MAX(x-1, 0); x1 <= MIN(x+1, cc->_width-1); x1++) 
					for (int y1=MAX(y-1, 0); y1 <= MIN(y+1, cc->_height-1); y1++)
						if (distances[x1][y1] < dmin) dmin = distances[x1][y1];
				
				distances[x][y] = (dmin == dmax ? 1 : dmin + 1);
				if (distances[x][y] > dcentres) dcentres = distances[x][y];
			}
		}
	}

	int rayon = dcentres;
	// printf("Rayon : %d\n", rayon);


	// Calcul du diamètre -------------------------------------
	int xmin = (cc->_width), ymin = (cc->_height), xmax = 0, ymax = 0;

	for (int x=0; x < cc->_width; x++) 
		for (int y=0; y < cc->_height; y++) 
			if (distances[x][y] == 1) 
			{
				// bords = empiler(x, y, bords);
				if (x < xmin) xmin = x;
				if (x > xmax) xmax = x;
				if (y < ymin) ymin = y;
				if (y > ymax) ymax = y;
			}
	
	// printf("xmin : %d\nxmax : %d\nymin : %d\nymax : %d\n", xmin, xmax, ymin, ymax);

	int diametre = MAX(xmax-xmin, ymax-ymin);
	// printf("Diamètre : %d\n", diametre);


	for(int x=0;x<cc->_width;x++)
		free(distances[x]);
	free(distances);

	return (2.f*rayon)/diametre;
}

void question_2(int x, int y)
{
	Image *img = I_read("TP2_img1.pbm");    
	
    pile p = I_remplissage8(img, x, y, color_equals);

	Image *out = pileToImage(p, img->_width, img->_height);

	float circu = circularite(out);
	printf("Circularité de la cc en (%d, %d) = %f\n", x, y, circu);

	writeImage("q2.ppm", out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

// -----------------------------------------------------------------------------------------------------------

pile I_remplissage8_Layered(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color))
{
	Color germe_color = img_in->_buffer[x_germe][y_germe];

	pile cc = pile_nouv();

	int modif = 1;

	// 0 : non visité
	// 1 : candidat
	// 2 : dans la région
	int **visites = (int **)calloc(img_in->_width, sizeof(int*));
	for(int x=0;x<img_in->_width;x++)
		visites[x] = (int*)calloc(img_in->_height,sizeof(int));
	
	visites[x_germe][y_germe] = 2;
	cc = empiler(x_germe, y_germe, cc);

	while (modif)
	{
		modif = 0;
		for (int x=0; x < img_in->_width; x++)
		{
			for (int y=0; y < img_in->_height; y++)
			{
				if (visites[x][y] == 2)
				{
					int x1 = MAX(x-1, 0), 					y1 = y;
					int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
					int x3 = x, 							y3 = MAX(y-1, 0);
					int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

					if (!visites[x1][y1]) visites[x1][y1] = 1;
					if (!visites[x2][y2]) visites[x2][y2] = 1;
					if (!visites[x3][y3]) visites[x3][y3] = 1;
					if (!visites[x4][y4]) visites[x4][y4] = 1;
					if (!visites[x1][y3]) visites[x1][y3] = 1;
					if (!visites[x1][y4]) visites[x1][y4] = 1;
					if (!visites[x2][y3]) visites[x2][y3] = 1;
					if (!visites[x2][y4]) visites[x2][y4] = 1;
				}
			}
		}
		for (int x=0; x < img_in->_width; x++)
			for (int y=0; y < img_in->_height; y++)
				if (visites[x][y] == 1) 
					if ((*cmp_color)(img_in->_buffer[x][y], germe_color)) { visites[x][y] = 2; modif = 1; cc = empiler(x, y, cc); }
	}

	for(int x=0;x<img_in->_width;x++)
		free(visites[x]);
	free(visites);

	return cc;
}

void question_3(char *infile, char *outfile, int x, int y, float reject_criterion)
{
	Image *img = I_read(infile);    
	
    pile p = I_remplissage8(img, x, y, color_less_or_equals);

	Image *out = pileToImage(p, img->_width, img->_height);

	printf("Circularité call\n");
	float circu = circularite(out);
	int reject;
	if (circu > reject_criterion) reject = 0;
	else reject = 1;

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

void question_4(char *infile, char *outfile, int x, int y, float reject_criterion)
{
	Image *img = I_read(infile);    
	
    pile p = I_remplissage8_Layered(img, x, y, color_less_or_equals);

	Image *out = pileToImage(p, img->_width, img->_height);

	float circu = circularite(out);
	int reject;
	if (circu > reject_criterion) reject = 1;
	else reject = 0;

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}