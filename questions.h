#include "Image.h"
#include "opt.h"
	
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct spile{
	int tx, ty, size;
	struct spile *r;
} *pile;

typedef struct snoeud {
	int id;
	pile p;
	int pNon8Simple;
} *noeud;

typedef struct slnode {
	noeud n;
	struct slnode *next;
} *lnode;

typedef struct sgraph {
	noeud node1;
	noeud node2;
	struct sgraph *next;
} *graph;

pile pile_nouv();

pile empiler(int x, int y, pile p);

pile depiler(pile p);

void pile_free(pile p);

int isInPile(int x, int y, pile p);

void writeImage(char *outname, Image *out);

void question_1(char *filename, char *outname, int x0, int y0);

void question_2(int x, int y);

void question_3(char *infile, char *outfile, int x, int y, float reject_criterion);

void question_4(char *infile, char *outfile, int x, int y, float reject_criterion);

void question_5(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size);

void question_6(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size);

void question_7(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size);

void question_8(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size, float w);

void question_9(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size, float w);

void question_10(char *infile, char *outfile, int x, int y, float reject_criterion, int min_size, int max_size, float w, int s_x, int s_y);

void question_11(char *infile, char *outfile);

void question_12(char *infile, char *outfile);