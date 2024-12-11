#include "Image.h"
#include "opt.h"
	
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct spile{
	int tx, ty;
	struct spile *r;
} *pile;

pile pile_nouv();

pile empiler(int x, int y, pile p);

pile depiler(pile p);

void pile_free(pile p);

int isInPile(int x, int y, pile p);

Color getColor(Image *img, int x, int y);

int color_equals(Color c1, Color c2);

pile I_remplissage4(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color));

pile I_remplissage8(Image *img_in, int x_germe, int y_germe, int (*cmp_color)(Color, Color));

void writeImage(char *outname, Image *out);

void question_1(char *filename, char *outname, int x0, int y0);

void question_2(int x, int y);

void question_3(char *infile, char *outfile, int x, int y, float reject_criterion);

void question_4(char *infile, char *outfile, int x, int y, float reject_criterion);