#include "questions.h"
#include "Image.h"

int seuil = 255;

pile pile_nouv() { return NULL; }

pile empiler(int x, int y, pile p)
{
	pile t = (pile)malloc(sizeof(struct spile));
	t->tx = x;
	t->ty = y;
	t->r = p;
	if (p == NULL) t->size = 1;
	else t->size = p->size + 1;
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

float intensite(Color c)
{
	return (c._blue + c._green + c._red) / 3.f;
}

int color_equals(Color c, int intensity)
{
	int c_int = (int) (255*intensite(c));

	return (c_int == intensity);
}

int color_less_or_equals(Color c, int intensity)
{
	int c_int = (int) (255*intensite(c));

	return (c_int <= intensity);
}

int isVisited(int x, int y, int **visites)
{
	return visites[x][y];
}

pile I_remplissage4(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, int))
{
	Color germe_color = img_in->_buffer[x_germe][y_germe];
	int it = (int) (255*intensite(germe_color));

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

		if ((*cmp_color)(img_in->_buffer[x4][y4], it)) if (!visites[x4][y4]) { p = empiler(x4, y4, p); visites[x4][y4] = 1; }
        if ((*cmp_color)(img_in->_buffer[x1][y1], it)) if (!visites[x1][y1]) { p = empiler(x1, y1, p); visites[x1][y1] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y2], it)) if (!visites[x2][y2]) { p = empiler(x2, y2, p); visites[x2][y2] = 1; }
		if ((*cmp_color)(img_in->_buffer[x3][y3], it)) if (!visites[x3][y3]) { p = empiler(x3, y3, p); visites[x3][y3] = 1; }
	}

	pile_free(p);
	for(int x=0;x<img_in->_width;x++)
		free(visites[x]);
	free(visites);

	return cc;
}

pile I_remplissage8(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, int))
{
	Color germe_color = img_in->_buffer[x_germe][y_germe];
	int it = (int) (255*intensite(germe_color));

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

		if ((*cmp_color)(img_in->_buffer[x4][y4], it)) if (!visites[x4][y4]) { p = empiler(x4, y4, p); visites[x4][y4] = 1; }
        if ((*cmp_color)(img_in->_buffer[x1][y1], it)) if (!visites[x1][y1]) { p = empiler(x1, y1, p); visites[x1][y1] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y2], it)) if (!visites[x2][y2]) { p = empiler(x2, y2, p); visites[x2][y2] = 1; }
		if ((*cmp_color)(img_in->_buffer[x3][y3], it)) if (!visites[x3][y3]) { p = empiler(x3, y3, p); visites[x3][y3] = 1; }

		if ((*cmp_color)(img_in->_buffer[x1][y3], it)) if (!visites[x1][y3]) { p = empiler(x1, y3, p); visites[x1][y3] = 1; }
		if ((*cmp_color)(img_in->_buffer[x1][y4], it)) if (!visites[x1][y4]) { p = empiler(x1, y4, p); visites[x1][y4] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y3], it)) if (!visites[x2][y3]) { p = empiler(x2, y3, p); visites[x2][y3] = 1; }
		if ((*cmp_color)(img_in->_buffer[x2][y4], it)) if (!visites[x2][y4]) { p = empiler(x2, y4, p); visites[x2][y4] = 1; }
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

	while (p != NULL) { if ((0 <= p->tx && p->tx < w) && (0 <= p->ty && p->ty < h)) {I_plotColor(img, p->tx, p->ty, C_new(1,1,1));} else { /*fprintf(stderr, "(%d, %d) out of bounds !\n", p->tx, p->ty);*/ } p = p->r; }

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

	int rayon = MAX(0, dcentres-1);
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

	return (diametre != 0 ? (2.f*rayon)/diametre : 1);
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

void question_3(char *infile, char *outfile, int x, int y, float reject_criterion)
{
	Image *img = I_read(infile);    
	
    pile p = I_remplissage8(img, x, y, color_less_or_equals);

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

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

pile AjouterPixelBresenham(pile p, int xA, int yA, int dx, int dy, int x, int y)
{
	if (abs(dy) > abs(dx)) 
	{ 
		int tmpx = (x-xA), tmpy = (y-yA);

		int tmp = tmpy; tmpy = tmpx, tmpx = tmp; 

		x = xA + tmpx;
		y = yA + tmpy;
	}
	if (dy < 0) y = y - 2*(y-yA);
	if (dx < 0) x = x - 2*(x-xA);

	p = empiler(x, y, p);
	return p;
}

//	Cette fonction renvoie une pile contenant toutes les coordonnées des pixels appartenant à la droite AB
pile bresenham(int xA, int yA, int xB, int yB)
{
	pile p = pile_nouv();

	int dx, dy, incrd1, incrd2, d, x_curr, y_curr;

	dx=xB-xA; dy=yB-yA;
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	if (abs(dy) > abs(dx)) { int tmp = dy; dy = dx, dx = tmp; }

	incrd1=2*dy; incrd2=2*(dy-dx);
	x_curr = xA; y_curr = yA; d=2*dy-dx;
	while (x_curr<=xB)
	{
		p = AjouterPixelBresenham(p, xA, yA, xB-xA, yB-yA, x_curr, y_curr);
		x_curr+=1;
		if(d<0) {d=d+incrd1;} else {y_curr++; d=d+incrd2;}
	}


	// printf("A : (%d, %d) | B : (%d, %d)\n", xA, yA, xB, yB);
	// pile tmp = p;
	// while (tmp != NULL) { printf("(%d, %d)\n", tmp->tx, tmp->ty); tmp = tmp->r; }

	return p;
}

pile I_remplissage8_Layered(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, int), int min_size, int max_size, int adapt_threshold)
{
	Color germe_color;
	int it;

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

	if (adapt_threshold)
	{
		// TODO QUESTION 7
		germe_color = img_in->_buffer[x_germe][y_germe];
		germe_color = C_new(2*germe_color._red, 2*germe_color._green, 2*germe_color._blue);
		it = (int) (255*intensite(germe_color));
		printf("Intensité new germe : 2*%d\n", it/2);

		for (int i = 0; i < 2; i++)
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
						if ((*cmp_color)(img_in->_buffer[x][y], it)) { visites[x][y] = 2; modif = 1; cc = empiler(x, y, cc); }

		}
		
		// Après 2 itérations
		pile tmp_cc = cc;
		int xmax = cc->tx, ymax = cc->ty;
		printf("Init max : (%d, %d)\n", xmax, ymax);

		while (tmp_cc != NULL)
		{
			int x = tmp_cc->tx, y = tmp_cc->ty;
			if (!(x == x_germe && y == y_germe) && (intensite(img_in->_buffer[x][y]) < intensite(img_in->_buffer[xmax][ymax]))) // (dinf(x_germe, y_germe, x, y) < dinf(x_germe, y_germe, xmax, ymax))
				{ xmax = x; ymax = y; }
			tmp_cc = tmp_cc->r;
		}
		
		printf("Found max : (%d, %d)\n\n", xmax, ymax);

		int y0_bres = (ymax-y_germe)/(xmax-x_germe)*(0 - x_germe) + y_germe;
		int ymax_bres = (ymax-y_germe)/(xmax-x_germe)*(img_in->_width-1 - x_germe) + y_germe;
		// printf("Test bresenham x=0 : %d\n", y0_bres);
		// printf("Test bresenham x=width : %d\n", ymax_bres);

		// pile droite = bresenham(x_germe, y_germe, xmax, ymax, 0, img_in->_width-1);
		pile droite = bresenham(0, y0_bres, img_in->_width-1, ymax_bres);
		
		// Image *droite_img = pileToImage(droite, img_in->_width, img_in->_height);
		// writeImage("q7_droite.ppm", droite_img);
		// I_free(droite_img);
		

		int region_size = 16;
		int histogramme[255/region_size];
		for (int i = 0; i < 255/region_size; i++) histogramme[i] = 0;

		pile ptr_droite = droite;
		while (droite != NULL)
		{
			int x = droite->tx, y = droite->ty;
			if (((0 <= x) && (x < img_in->_width)) && ((0 <= y) && (y < img_in->_height)))
			{
				int intens = (int) (255/region_size * intensite(img_in->_buffer[x][y]));
				histogramme[intens]++;
			}
			
			droite = droite->r;
		}

		pile_free(ptr_droite);

		FILE *histo = fopen("histo.csv", "w+");
		if (histo == NULL) {
			perror("Erreur lors de l'ouverture du fichier");
			exit(EXIT_FAILURE);
		}

		fprintf(histo, "Intensite, Nombre de pixels\n");
		for (int i = 0; i < 255/region_size; i++) {
			fprintf(histo, "%d, %d\n", i, histogramme[i]);
		}

		fclose(histo);

		int ppml = ((it/2)/region_size); // Initialiser avec la plus grande valeur possible

		for (int i = 1; i < 255/region_size - 1; i++) {
			if (histogramme[i] < histogramme[i - 1] && histogramme[i] < histogramme[i + 1]) {
				ppml = i; // Ici je prends juste le plus grand min local
				// printf("i_min = %d\n", i);
				// break;
			}
		}

		int intensity_opti = (255/region_size)*ppml + (255/region_size)/2;
		printf("Intensité q7 : %d\n", intensity_opti);
		it = intensity_opti;

		// it = 6*region_size + region_size/2;

		for (int x=0; x < img_in->_width; x++)
				for (int y=0; y < img_in->_height; y++)
					if (visites[x][y] != 0) 
						visites[x][y] = 0;
		visites[x_germe][y_germe] = 2; 

		pile_free(cc);
		cc = pile_nouv();
		cc = empiler(x_germe, y_germe, cc);
	}
	else it = (int) (255*intensite(img_in->_buffer[x_germe][y_germe]));

	modif = 1;
	// Algorithme principal
	while (modif)
	{
		// printf("iter\n");
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

					if (!visites[x1][y1]) visites[x1][y1] = 1; // else printf("(%d, %d) déjà vu\n", x1, y1);
					if (!visites[x2][y2]) visites[x2][y2] = 1; // else printf("(%d, %d) déjà vu\n", x2, y2);
					if (!visites[x3][y3]) visites[x3][y3] = 1; // else printf("(%d, %d) déjà vu\n", x3, y3);
					if (!visites[x4][y4]) visites[x4][y4] = 1; // else printf("(%d, %d) déjà vu\n", x4, y4);
					if (!visites[x1][y3]) visites[x1][y3] = 1; // else printf("(%d, %d) déjà vu\n", x1, y3);
					if (!visites[x1][y4]) visites[x1][y4] = 1; // else printf("(%d, %d) déjà vu\n", x1, y4);
					if (!visites[x2][y3]) visites[x2][y3] = 1; // else printf("(%d, %d) déjà vu\n", x2, y3);
					if (!visites[x2][y4]) visites[x2][y4] = 1; // else printf("(%d, %d) déjà vu\n", x2, y4);
				}
			}
		}
		for (int x=0; x < img_in->_width; x++)
			for (int y=0; y < img_in->_height; y++)
				if (visites[x][y] == 1) 
					if ((*cmp_color)(img_in->_buffer[x][y], it)) { visites[x][y] = 2; modif = 1; cc = empiler(x, y, cc); }
					// else {printf("Considéré mais nan (%d, %d), it = %d\n", x, y, (int) (255*intensite(img_in->_buffer[x][y])));}

		if ((max_size != -1) && (cc->size >= max_size)) break;

		if ((min_size != -1) && (cc->size >= min_size)) modif = 0;
		else if ((min_size != -1) && (modif == 0))
		{
			// Ajouter avec condition modifiee
			int xi = 0, yi = 0;
			float imin = 1; // 1 = intensité max car rgb entre 0 et 1 dans la structure Color

			for (int x=0; x < img_in->_width; x++)
				for (int y=0; y < img_in->_height; y++)
					if (visites[x][y] == 1) 
						if (intensite(img_in->_buffer[x][y]) < imin)
						{
							xi = x, yi = y;
							imin = intensite(img_in->_buffer[x][y]);
						}
			
			visites[xi][yi] = 2; modif = 1; cc = empiler(xi, yi, cc);
		}
	}

	if (min_size != -1) 
	{
		modif = 1;
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
						if ((*cmp_color)(img_in->_buffer[x][y], it)) { visites[x][y] = 2; modif = 1; cc = empiler(x, y, cc); }
			
			if ((max_size != -1) && (cc->size >= max_size)) break;
		}
	}

	for(int x=0;x<img_in->_width;x++)
		free(visites[x]);
	free(visites);

	return cc;
}

void question_4(char *infile, char *outfile, int x, int y, float reject_criterion)
{
	Image *img = I_read(infile);    
	
    pile p = I_remplissage8_Layered(img, x, y, color_less_or_equals, -1, -1, 0);

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

void question_5(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size)
{
	Image *img = I_read(infile);    
	
    pile p = I_remplissage8_Layered(img, x, y, color_less_or_equals, min_size, -1, 0);
	printf("Taille région : %d\n", p->size);

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

void question_6(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size)
{
	Image *img = I_read(infile);    
	
    pile p = I_remplissage8_Layered(img, x, y, color_less_or_equals, min_size, max_size, 0);
	printf("Taille région : %d\n", p->size);

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

void question_7(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size)
{
	Image *img = I_read(infile);    
	
	printf("Min size : %d\n\n", min_size);

    pile p = I_remplissage8_Layered(img, x, y, color_less_or_equals, (min_size != 2 ? min_size : -1), (max_size != 5 ? max_size : -1), 1);
	printf("Taille région : %d\n", p->size);

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

pile I_remplissage8_Variable(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, int), int min_size, int max_size, int adapt_threshold, float w, int adapt_w)
{
	Color germe_color = img_in->_buffer[x_germe][y_germe];;
	int it = (int) (255*intensite(germe_color));
	//printf("it : %d\n", it);

	pile cc = pile_nouv();
	pile candidats = pile_nouv();
	pile accepted = pile_nouv();

	int modif = 1;

	// 0 : non visité
	// 1 : candidat
	// 2 : dans la région
	int **visites = (int **)calloc(img_in->_width, sizeof(int*));
	for(int x=0;x<img_in->_width;x++)
		visites[x] = (int*)calloc(img_in->_height,sizeof(int));
	
	visites[x_germe][y_germe] = 2;
	cc = empiler(x_germe, y_germe, cc);
	accepted = empiler(x_germe, y_germe, accepted);

	if (adapt_threshold && it < seuil)
	{
		germe_color = C_new(2*germe_color._red, 2*germe_color._green, 2*germe_color._blue);
		
		for (int i = 0; i < 2; i++)
		{
			pile_free(candidats);
			candidats = pile_nouv();

			pile tmp_accepted = accepted;
			while (tmp_accepted != NULL) {
				int x = tmp_accepted->tx, y = tmp_accepted->ty;

				int x1 = MAX(x-1, 0), 					y1 = y;
				int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
				int x3 = x, 							y3 = MAX(y-1, 0);
				int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

				if (!visites[x1][y1]) { candidats = empiler(x1, y1, candidats); visites[x1][y1] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y1);
				if (!visites[x2][y2]) { candidats = empiler(x2, y2, candidats); visites[x2][y2] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y2);
				if (!visites[x3][y3]) { candidats = empiler(x3, y3, candidats); visites[x3][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x3, y3);
				if (!visites[x4][y4]) { candidats = empiler(x4, y4, candidats); visites[x4][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x4, y4);
				if (!visites[x1][y3]) { candidats = empiler(x1, y3, candidats); visites[x1][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y3);
				if (!visites[x1][y4]) { candidats = empiler(x1, y4, candidats); visites[x1][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y4);
				if (!visites[x2][y3]) { candidats = empiler(x2, y3, candidats); visites[x2][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y3);
				if (!visites[x2][y4]) { candidats = empiler(x2, y4, candidats); visites[x2][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y4);

				tmp_accepted = tmp_accepted->r;
			}

			pile_free(accepted);
			accepted = pile_nouv();

			pile tmp_candidats = candidats;
			while (tmp_candidats != NULL) {
				int x = tmp_candidats->tx, y = tmp_candidats->ty;

				if ((*cmp_color)(img_in->_buffer[x][y], it)) 
				{ 
					visites[x][y] = 2; cc = empiler(x, y, cc); accepted = empiler(x, y, accepted);
				}

				tmp_candidats = tmp_candidats->r;
			}
		}
		
		// Récupérer le pixel le plus sombre (= meilleure direction de la fissure)
		pile tmp_cc = cc;
		int xmax = cc->tx, ymax = cc->ty;
		while (tmp_cc != NULL)
		{
			int x = tmp_cc->tx, y = tmp_cc->ty;
			if (!(x == x_germe && y == y_germe) && (intensite(img_in->_buffer[x][y]) < intensite(img_in->_buffer[xmax][ymax]))) // (dinf(x_germe, y_germe, x, y) < dinf(x_germe, y_germe, xmax, ymax)))
				{ xmax = x; ymax = y; }
			tmp_cc = tmp_cc->r;
		}
		// printf("Found max : (%d, %d)\n\n", xmax, ymax);


		// Calcul de la droite de Bresenham étendue
		int y0_bres;
		int ymax_bres;
		if (xmax == x_germe) { // Ligne verticale
			y0_bres = y_germe;  
			ymax_bres = y_germe; 
		} else { // Cas général
			y0_bres = (ymax - y_germe) / (xmax - x_germe) * (0 - x_germe) + y_germe;
			ymax_bres = (ymax - y_germe) / (xmax - x_germe) * (img_in->_width - 1 - x_germe) + y_germe;
		}
		pile droite = bresenham(0, y0_bres, img_in->_width-1, ymax_bres);
		

		// Histogramme à partir de la droite
		int region_size = 16;
		int histogramme[255/region_size];
		for (int i = 0; i < 255/region_size; i++) histogramme[i] = 0;

		pile ptr_droite = droite;
		while (droite != NULL)
		{
			int x = droite->tx, y = droite->ty;
			if (((0 <= x) && (x < img_in->_width)) && ((0 <= y) && (y < img_in->_height)))
			{
				int intens = (int) (255/region_size * intensite(img_in->_buffer[x][y]));
				histogramme[intens]++;
			}
			
			droite = droite->r;
		}

		pile_free(ptr_droite);

		int ppml = ((it/2)/region_size); // Initialiser avec la plus grande valeur possible

		for (int i = 1; i < 255/region_size - 1; i++) {
			if (histogramme[i] < histogramme[i - 1] && histogramme[i] < histogramme[i + 1]) {
				ppml = i; // Ici je prends juste le plus grand min local
				// printf("i_min = %d\n", i);
				// break;
			}
		}

		int intensity_opti = (255/region_size)*ppml + (255/region_size)/2;
		// printf("Intensité optimale : %d\n", intensity_opti);
		it = intensity_opti;

		// Reset le tableau de visites
		tmp_cc = cc;
		while (tmp_cc != NULL)
		{
			int x = tmp_cc->tx, y = tmp_cc->ty;
			if (visites[x][y] != 0) 
				visites[x][y] = 0;
			tmp_cc = tmp_cc->r;
		}
		visites[x_germe][y_germe] = 2; 

		// Reset les piles
		pile_free(cc);
		cc = pile_nouv();
		cc = empiler(x_germe, y_germe, cc);

		pile_free(candidats);
		candidats = pile_nouv();

		pile_free(accepted);
		accepted = pile_nouv();
		accepted = empiler(x_germe, y_germe, accepted);
	}
	else it = (int) (255*intensite(img_in->_buffer[x_germe][y_germe]));

	int it_max_cc;

	modif = 1;
	// Algorithme principal
	while (modif && it < seuil)
	{
		modif = 0;
		it_max_cc = 0;

		// printf("Nouvelle intensité : %d\n", it);
		pile_free(candidats);
		candidats = pile_nouv();

		pile tmp_accepted = accepted;
		while (tmp_accepted != NULL) {
			int x = tmp_accepted->tx, y = tmp_accepted->ty;

			int x1 = MAX(x-1, 0), 					y1 = y;
			int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
			int x3 = x, 							y3 = MAX(y-1, 0);
			int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

			if (!visites[x1][y1]) { candidats = empiler(x1, y1, candidats); visites[x1][y1] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y1);
			if (!visites[x2][y2]) { candidats = empiler(x2, y2, candidats); visites[x2][y2] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y2);
			if (!visites[x3][y3]) { candidats = empiler(x3, y3, candidats); visites[x3][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x3, y3);
			if (!visites[x4][y4]) { candidats = empiler(x4, y4, candidats); visites[x4][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x4, y4);
			if (!visites[x1][y3]) { candidats = empiler(x1, y3, candidats); visites[x1][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y3);
			if (!visites[x1][y4]) { candidats = empiler(x1, y4, candidats); visites[x1][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y4);
			if (!visites[x2][y3]) { candidats = empiler(x2, y3, candidats); visites[x2][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y3);
			if (!visites[x2][y4]) { candidats = empiler(x2, y4, candidats); visites[x2][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y4);

			tmp_accepted = tmp_accepted->r;
		}

		pile_free(accepted);
		accepted = pile_nouv();

		pile tmp_candidats = candidats;
		while (tmp_candidats != NULL) {
			int x = tmp_candidats->tx, y = tmp_candidats->ty;

			if ((*cmp_color)(img_in->_buffer[x][y], it)) 
			{ 
				visites[x][y] = 2; modif = 1; cc = empiler(x, y, cc); accepted = empiler(x, y, accepted);
				int it_x = (int) 255*intensite(img_in->_buffer[x][y]);
				it_max_cc = MAX(it_max_cc, it_x);
			}

			tmp_candidats = tmp_candidats->r;
		}

		if ((max_size != -1) && (cc->size >= max_size)) break;

		if ((min_size != -1) && (cc->size >= min_size)) modif = 0;
		else if ((min_size != -1) && (modif == 0))
		{
			// Ajouter avec condition modifiee
			int xi = 0, yi = 0;
			float imin = 1; // 1 = intensité max car rgb entre 0 et 1 dans la structure Color

			pile tmp_candidats = candidats;
			while (tmp_candidats != NULL) {
				int x = tmp_candidats->tx, y = tmp_candidats->ty;

				if (intensite(img_in->_buffer[x][y]) < imin)
				{
					xi = x, yi = y;
					imin = intensite(img_in->_buffer[x][y]);
				}

				tmp_candidats = tmp_candidats->r;
			}
			
			visites[xi][yi] = 2; modif = 1; cc = empiler(xi, yi, cc); accepted = empiler(xi, yi, accepted);
			// int it_x = (int) 255*intensite(img_in->_buffer[xi][yi]);
			// it_max_cc = MAX(it_max_cc, it_x);
		}

		Image *current_img = NULL;
		if (adapt_w) current_img = pileToImage(cc, img_in->_width, img_in->_height);
		it = MAX(it, it_max_cc) + (adapt_w ? w * circularite(current_img) : w);
		if (adapt_w) I_free(current_img);
	}

	if (min_size != -1 && it < seuil) 
	{
		modif = 1;
		while (modif)
		{
			modif = 0;
			it_max_cc = 0;

			// printf("Nouvelle intensité : %d\n", it);
			pile_free(candidats);
			candidats = pile_nouv();

			pile tmp_accepted = accepted;
			while (tmp_accepted != NULL) {
				int x = tmp_accepted->tx, y = tmp_accepted->ty;

				int x1 = MAX(x-1, 0), 					y1 = y;
				int x2 = MIN(x+1, img_in->_width-1),	y2 = y;
				int x3 = x, 							y3 = MAX(y-1, 0);
				int x4 = x, 							y4 = MIN(y+1, img_in->_height-1);

				if (!visites[x1][y1]) { candidats = empiler(x1, y1, candidats); visites[x1][y1] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y1);
				if (!visites[x2][y2]) { candidats = empiler(x2, y2, candidats); visites[x2][y2] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y2);
				if (!visites[x3][y3]) { candidats = empiler(x3, y3, candidats); visites[x3][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x3, y3);
				if (!visites[x4][y4]) { candidats = empiler(x4, y4, candidats); visites[x4][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x4, y4);
				if (!visites[x1][y3]) { candidats = empiler(x1, y3, candidats); visites[x1][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y3);
				if (!visites[x1][y4]) { candidats = empiler(x1, y4, candidats); visites[x1][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x1, y4);
				if (!visites[x2][y3]) { candidats = empiler(x2, y3, candidats); visites[x2][y3] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y3);
				if (!visites[x2][y4]) { candidats = empiler(x2, y4, candidats); visites[x2][y4] = 1; } // else printf("(%d, %d) déjà vu\n", x2, y4);

				tmp_accepted = tmp_accepted->r;
			}

			pile_free(accepted);
			accepted = pile_nouv();

			pile tmp_candidats = candidats;
			while (tmp_candidats != NULL) {
				int x = tmp_candidats->tx, y = tmp_candidats->ty;

				if ((*cmp_color)(img_in->_buffer[x][y], it)) 
				{ 
					visites[x][y] = 2; modif = 1; cc = empiler(x, y, cc); accepted = empiler(x, y, accepted);
					int it_x = (int) 255*intensite(img_in->_buffer[x][y]);
					it_max_cc = MAX(it_max_cc, it_x);
				}

				tmp_candidats = tmp_candidats->r;
			}
			
			Image *current_img = NULL;
			if (adapt_w) current_img = pileToImage(cc, img_in->_width, img_in->_height);
			it = MAX(it, it_max_cc) + (adapt_w ? w * circularite(current_img) : w);
			if (adapt_w) I_free(current_img);

			// printf("New adds : %d\n", accepted->size);
		
			if ((max_size != -1) && (cc->size >= max_size)) break;
		}
	}

	if (it >= seuil) {
		pile_free(cc);
		cc = pile_nouv();
	}

	pile_free(candidats);
	pile_free(accepted);

	for(int x=0;x<img_in->_width;x++)
		free(visites[x]);
	free(visites);

	return cc;
}

void question_8(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size, float w)
{
	Image *img = I_read(infile);    
	
	printf("Min size : %d\n\n", min_size);

    pile p = I_remplissage8_Variable(img, x, y, color_less_or_equals, (min_size != 2 ? min_size : -1), (max_size != 5 ? max_size : -1), 1, w, 0);
	printf("Taille région : %d\n", p->size);

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

void question_9(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size, float w)
{
	Image *img = I_read(infile);    
	
	printf("Min size : %d\n\n", min_size);

    pile p = I_remplissage8_Variable(img, x, y, color_less_or_equals, (min_size != 2 ? min_size : -1), (max_size != 5 ? max_size : -1), 1, w, 1);
	printf("Taille région : %d\n", (p ? p->size : 0));

	Image *out = pileToImage(p, img->_width, img->_height);

	pile_free(p);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

Image* bufferToImage(int **buffer, int width, int height)
{
	Image *img = I_new(width, height);

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			if (buffer[i][j] == 1) I_plotColor(img, i, j, C_new(1,1,1));

	return img;	
}

void question_10(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size, float w, int s_x, int s_y)
{
	seuil = 70;

	int useW = 1;

	Image *img = I_read(infile);

	int **visites = (int **)calloc(img->_width, sizeof(int*));
	for(int x=0;x<img->_width;x++)
		visites[x] = (int*)calloc(img->_height,sizeof(int));

	for (int i = 0; i < img->_width/s_x; i++) {
		for (int j = 0; j < img->_height/s_y; j++) {
			printf("Launching (%d, %d)\n", i*s_x, j*s_y);
			pile pij = pile_nouv();
			if (useW) pij = I_remplissage8_Variable(img, i*s_x, j*s_y, color_less_or_equals, (min_size != 2 ? min_size : -1), (max_size != 5 ? max_size : -1), 1, w, 1);
			else pij = I_remplissage8_Layered(img, i*s_x, j*s_y, color_less_or_equals, (min_size != 2 ? min_size : -1), (max_size != 5 ? max_size : -1), 1);
			
			// printf("Fusing...\n");
			while (pij != NULL) {
				pile t = pij;
				int px = pij->tx, py = pij->ty;
				visites[px][py] = 1;
				pij = pij->r;
				free(t);
			}
			free(pij);
		}
	}

    // pile p = I_remplissage8_Variable(img, x, y, color_less_or_equals, (min_size != 2 ? min_size : -1), (max_size != 5 ? max_size : -1), 1, w, 1);
	int size = 0;
	for (int i = 0; i < img->_width; i++)
		for (int j = 0; j < img->_height; j++)
			if (visites[i][j] == 1) size++;
	
	printf("Taille région : %d\n", size);

	Image *out = bufferToImage(visites, img->_width, img->_height);

	for(int x=0;x<img->_width;x++)
		free(visites[x]);
	free(visites);

	float circu = circularite(out);
	int reject = (circu > reject_criterion);

	printf("Circularité : %f\n", circu);
	printf("Forme germée %s.\n", (reject ? "rejetée" : "acceptée"));

	writeImage(outfile, out);

	I_free(img);
	I_free(out);

	putchar('\n');
}

int yokoi(int **image, int x, int y, int quatre_connexe)
{
	int x1 = (quatre_connexe ? image[x-1][y+1] : 1 - image[x-1][y+1]);
    int x2 = (quatre_connexe ? image[x-0][y+1] : 1 - image[x-0][y+1]);
    int x3 = (quatre_connexe ? image[x+1][y+1] : 1 - image[x+1][y+1]);
    int x4 = (quatre_connexe ? image[x+1][y+0] : 1 - image[x+1][y+0]);
    int x5 = (quatre_connexe ? image[x+1][y-1] : 1 - image[x+1][y-1]);
    int x6 = (quatre_connexe ? image[x-0][y-1] : 1 - image[x-0][y-1]);
    int x7 = (quatre_connexe ? image[x-1][y-1] : 1 - image[x-1][y-1]);
    int x8 = (quatre_connexe ? image[x-1][y-0] : 1 - image[x-1][y-0]);

	int r = ( x8*(1-x1*x2) + x2*(1-x3*x4) + x4*(1-x5*x6) + x6*(1-x7*x8) );
	printf("%d ", r);

	return r;
}

int isSimple(int **image, int x, int y)
{
	return (1 == yokoi(image, x+1, y+1, 0));
}

void question_11(char *infile, char* outfile)
{
	Image *img = I_read(infile);

	int **buffer = (int **)calloc(img->_width+2, sizeof(int*));
	for(int x=0;x<img->_width+2;x++)
		buffer[x] = (int*)calloc(img->_height+2,sizeof(int));
	
	for (int i = 0; i < img->_width; i++) {
		for (int j = 0; j < img->_height; j++) {
			int color = img->_buffer[i][j]._red; // 1 si blanc, 0 si noir

			buffer[1+i][1+j] = color;
		}
	}

	Image *out = I_new(img->_width, img->_height);
	Color white = C_new(1, 1, 1);

	for (int j = 0; j < img->_height; j++) {
		for (int i = 0; i < img->_width; i++) {
			if (img->_buffer[i][j]._red == 1) {
				int r = yokoi(buffer, i+1, j+1, 0);
				if (r == 2)
					out->_buffer[i][j] = white;
			}
			else printf("0 ");
		}
		printf("\n");
	}

	printf("\n");

	writeImage(outfile, out);

	for (int j = 0; j < img->_height+2; j++) {
		for (int i = 0; i < img->_width+2; i++) {
			printf("%d ", buffer[i][j]);
		}
		printf("\n");
	}


	for(int x=0;x<img->_width+2;x++)
		free(buffer[x]);
	free(buffer);

	I_free(img);
}