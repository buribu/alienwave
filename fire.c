/* This file is part of Alienwave, a game by Alessandro Pira */

#include "fire.h"
#include "blit.h"
#include "aliens.h"
#include "xzarna.h"

extern int x_ofs;
extern int y_ofs;
extern alien all_aliens[NUM_ALIENS];

fire all_fires[NUM_FIRES];

void new_fire(int x, int y)
{
	int n=0;
	while ( (all_fires[n].x >= 0) && (++n<NUM_FIRES) ) ;

	if (n<=NUM_FIRES)
	{
		all_fires[n].x = x;
		all_fires[n].y = y;
	}
}

void init_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		all_fires[i].x = -1;
	}
}

void blit_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].x >= 0)
		{
			blit_fire(all_fires[i].x+x_ofs,all_fires[i].y+y_ofs);
		}
	}
}

void delete_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].x >= 0)
		{
			clear_fire(all_fires[i].x+x_ofs,all_fires[i].y+y_ofs);
		}
	}
}

void move_fires()
{
	int i;
	for (i=0;i<NUM_FIRES;i++)
	{
		if (all_fires[i].x >= 0)
		{
			int n;
			all_fires[i].y--;
			if (all_fires[i].y<0)
			{
				all_fires[i].x = -1;
			}
			else
			{
				while ((n=collide_aliens(all_fires[i].x,all_fires[i].y))>=0)
				{
					blow_alien(n);
					all_fires[i].x = -1;
				}
				if (collide_queen(all_fires[i].x,all_fires[i].y,COL_FIRE)>=0)
				{
					all_fires[i].x = -1;
				}
			}
		}
	}
}

