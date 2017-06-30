/* This file is part of Alienwave, a game by Alessandro Pira */

#include <stdlib.h>

extern int term_x;
extern int term_y;
extern int x_ofs;
extern int y_ofs;

int rrand(int min, int max)
{
	return( min+(int) ((float)(max-min)*rand()/(RAND_MAX+1.0)) );
}

int is_y_range(int y)
{
	return ((y>=y_ofs) && (y<term_y-y_ofs));
}

int is_x_range(int x)
{
	return ((x>=x_ofs) && (x<term_x-x_ofs));
}

