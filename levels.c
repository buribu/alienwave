/* This file is part of Alienwave, a game by Alessandro Pira */

#include "levels.h"
#include "aliens.h"
#include "xzarna.h"
#include "blit.h"
#include "util.h"
#include "defs.h"

#ifdef DEBUG_LEV
#include <curses.h>
extern WINDOW *term;
#endif

/* Score needed to reach Xzarna */
#ifdef LEV_HARD
#define SCORE_NEED 10000
#else
#ifdef LEV_EASY
#define SCORE_NEED  2000
#endif
#endif

#ifndef SCORE_NEED
#define SCORE_NEED  5000
#endif

extern int score;

extern alien all_aliens[NUM_ALIENS];

extern const bitmask bitmask_big_alien;
extern const bitmask bitmask_lit_alien;
extern const bitmask bitmask_ball_alien;
extern const bitmask bitmask_slime_alien;
extern const bitmask bitmask_tiny_alien;

/* Bytes (actual):
1,2 - Moment of appearence
3 - array number
4 - type of alien
5 - x
6 - y
7 - state
8 - movement function
9 - alien necessary to appear (-1=none)

   Next version could be:
1,2 - Moment of appearence
3   - array number
4   - type of alien
5   - min x
6   - max x
7   - min y
8   - max y
9   - possible state 1
10  - possible state 2
11  - movement function
12  - alien necessary to appear (-1=none)
 */

#define FRAME_SIZE     9

#define MOVE_STRAIGHT  1
#define MOVE_OSCILLATE 2
#define MOVE_DIAGONAL  3
#define MOVE_SERPENT   4

char level_1[] = {
0x00,0x00, 0, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1,
0x00,0x04, 1, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1,
0x00,0x08, 2, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1,
0x00,0x0C, 3, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1,
0x00,0x10, 4, AT_LITTLE, 39,-5, 0, MOVE_STRAIGHT, -1,

0x00,0x30, 5, AT_LITTLE, 39,-5, -1, MOVE_STRAIGHT, -1,
0x00,0x32, 6, AT_LITTLE, 41,-5, -1, MOVE_STRAIGHT, -1,
0x00,0x34, 7, AT_LITTLE, 38,-5, -1, MOVE_STRAIGHT, -1,
0x00,0x36, 8, AT_LITTLE, 40,-5, -1, MOVE_STRAIGHT, -1,
0x00,0x38, 9, AT_LITTLE, 38,-5, -1, MOVE_STRAIGHT, -1,

0x00,0x54, 0, AT_LITTLE,  2,-3,  1, MOVE_DIAGONAL, -1,
0x00,0x58, 1, AT_LITTLE,  5,-3,  1, MOVE_DIAGONAL, -1,
0x00,0x5C, 2, AT_LITTLE,  8,-3,  1, MOVE_DIAGONAL, -1,
0x00,0x60, 3, AT_LITTLE, 11,-3,  1, MOVE_DIAGONAL, -1,
0x00,0x64, 4, AT_LITTLE, 14,-3,  1, MOVE_DIAGONAL, -1,

0x00,0x70, 5, AT_LITTLE, 75,-3, -1, MOVE_DIAGONAL, -1,
0x00,0x74, 6, AT_LITTLE, 72,-3, -1, MOVE_DIAGONAL, -1,
0x00,0x78, 7, AT_LITTLE, 69,-3, -1, MOVE_DIAGONAL, -1,
0x00,0x7C, 8, AT_LITTLE, 66,-3, -1, MOVE_DIAGONAL, -1,
0x00,0x80, 9, AT_LITTLE, 63,-3, -1, MOVE_DIAGONAL, -1,

0x00,0xA0, 0, AT_LITTLE,  2,-3,  2, MOVE_DIAGONAL, -1,
0x00,0xA2, 1, AT_LITTLE,  5,-3,  2, MOVE_DIAGONAL, -1,
0x00,0xA4, 2, AT_LITTLE,  8,-3,  2, MOVE_DIAGONAL, -1,
0x00,0xA6, 3, AT_LITTLE, 11,-3,  2, MOVE_DIAGONAL, -1,
0x00,0xA8, 4, AT_LITTLE, 14,-3,  2, MOVE_DIAGONAL, -1,

0x00,0xB0, 5, AT_LITTLE, 75,-3, -2, MOVE_DIAGONAL, -1,
0x00,0xB2, 6, AT_LITTLE, 72,-3, -2, MOVE_DIAGONAL, -1,
0x00,0xB4, 7, AT_LITTLE, 69,-3, -2, MOVE_DIAGONAL, -1,
0x00,0xB6, 8, AT_LITTLE, 66,-3, -2, MOVE_DIAGONAL, -1,
0x00,0xB8, 9, AT_LITTLE, 63,-3, -2, MOVE_DIAGONAL, -1,

0x00,0xD0, 0, AT_LITTLE, 75,-3,-50, MOVE_OSCILLATE, -1,
0x00,0xD4, 1, AT_LITTLE, 75,-3,-50, MOVE_OSCILLATE, -1,
0x00,0xD8, 2, AT_LITTLE, 75,-3,-50, MOVE_OSCILLATE, -1,
0x00,0xDC, 3, AT_LITTLE, 75,-3,-50, MOVE_OSCILLATE, -1,
0x00,0xE0, 4, AT_LITTLE, 75,-3,-50, MOVE_OSCILLATE, -1,

0x01,0x10, 5, AT_LITTLE,  2,-3, 50, MOVE_OSCILLATE, -1,
0x01,0x14, 6, AT_LITTLE,  2,-3, 50, MOVE_OSCILLATE, -1,
0x01,0x18, 7, AT_LITTLE,  2,-3, 50, MOVE_OSCILLATE, -1,
0x01,0x1C, 8, AT_LITTLE,  2,-3, 50, MOVE_OSCILLATE, -1,
0x01,0x20, 9, AT_LITTLE,  2,-3, 50, MOVE_OSCILLATE, -1,

0x01,0x60, 0, AT_NONE,    0, 0,  0, MOVE_STRAIGHT,  -1,
};

char level_2[] = {
0x00,0x00, 0, AT_BALL,   48,-3,  0, MOVE_SERPENT, -1,
0x00,0x02, 1, AT_TINY,   49,-3,  0, MOVE_SERPENT, -1,
0x00,0x04, 2, AT_TINY,   49,-3,  0, MOVE_SERPENT, -1,
0x00,0x06, 3, AT_TINY,   49,-3,  0, MOVE_SERPENT, -1,
0x00,0x08, 4, AT_TINY,   49,-3,  0, MOVE_SERPENT, -1,

0x00,0x10, 5, AT_BALL,   27,-3,  0, MOVE_SERPENT, -1,
0x00,0x12, 6, AT_TINY,   28,-3,  0, MOVE_SERPENT, -1,
0x00,0x14, 7, AT_TINY,   28,-3,  0, MOVE_SERPENT, -1,
0x00,0x16, 8, AT_TINY,   28,-3,  0, MOVE_SERPENT, -1,
0x00,0x18, 9, AT_TINY,   28,-3,  0, MOVE_SERPENT, -1,

0x00,0x36, 0, AT_BALL,   72,-3,  0, MOVE_SERPENT, -1,
0x00,0x38, 1, AT_TINY,   73,-3,  0, MOVE_SERPENT, -1,
0x00,0x3A, 2, AT_TINY,   73,-3,  0, MOVE_SERPENT, -1,
0x00,0x3C, 3, AT_TINY,   73,-3,  0, MOVE_SERPENT, -1,
0x00,0x3E, 4, AT_TINY,   73,-3,  0, MOVE_SERPENT, -1,

0x00,0x46, 5, AT_BALL,    6,-3,  0, MOVE_SERPENT, -1,
0x00,0x48, 6, AT_TINY,    7,-3,  0, MOVE_SERPENT, -1,
0x00,0x4A, 7, AT_TINY,    7,-3,  0, MOVE_SERPENT, -1,
0x00,0x4C, 8, AT_TINY,    7,-3,  0, MOVE_SERPENT, -1,
0x00,0x4E, 9, AT_TINY,    7,-3,  0, MOVE_SERPENT, -1,

0x00,0x70, 0, AT_BALL,   59,-3,  0, MOVE_SERPENT, -1,
0x00,0x72, 1, AT_TINY,   60,-3,  0, MOVE_SERPENT, -1,
0x00,0x74, 2, AT_TINY,   60,-3,  0, MOVE_SERPENT, -1,
0x00,0x76, 3, AT_TINY,   60,-3,  0, MOVE_SERPENT, -1,
0x00,0x78, 4, AT_TINY,   60,-3,  0, MOVE_SERPENT, -1,

0x00,0x80, 5, AT_BALL,   12,-3,  0, MOVE_SERPENT, -1,
0x00,0x82, 6, AT_TINY,   13,-3,  0, MOVE_SERPENT, -1,
0x00,0x84, 7, AT_TINY,   13,-3,  0, MOVE_SERPENT, -1,
0x00,0x86, 8, AT_TINY,   13,-3,  0, MOVE_SERPENT, -1,
0x00,0x88, 9, AT_TINY,   13,-3,  0, MOVE_SERPENT, -1,

0x00,0xA6, 0, AT_BALL,   39,-3,  0, MOVE_SERPENT, -1,
0x00,0xA8, 1, AT_TINY,   40,-3,  0, MOVE_SERPENT, -1,
0x00,0xAA, 2, AT_TINY,   40,-3,  0, MOVE_SERPENT, -1,
0x00,0xAC, 3, AT_TINY,   40,-3,  0, MOVE_SERPENT, -1,
0x00,0xAE, 4, AT_TINY,   40,-3,  0, MOVE_SERPENT, -1,

0x00,0xB6, 5, AT_BALL,   44,-3,  0, MOVE_SERPENT, -1,
0x00,0xB8, 6, AT_TINY,   45,-3,  0, MOVE_SERPENT, -1,
0x00,0xBA, 7, AT_TINY,   45,-3,  0, MOVE_SERPENT, -1,
0x00,0xBC, 8, AT_TINY,   45,-3,  0, MOVE_SERPENT, -1,
0x00,0xBE, 9, AT_TINY,   45,-3,  0, MOVE_SERPENT, -1,

0x00,0xF5, 0, AT_NONE, 0,0,0, MOVE_STRAIGHT, -1,
};

char level_3[] = {
0x00,0x00, 0, AT_SLIME,  3,-3,  70, MOVE_OSCILLATE, -1,
0x00,0x0D, 1, AT_TINY,  19,11,  -1, MOVE_STRAIGHT,  0,
0x00,0x10, 8, AT_LITTLE, 55,-3,  0, MOVE_STRAIGHT,  -1,
0x00,0x15, 2, AT_TINY,  27,11,  -1, MOVE_STRAIGHT,  0,
0x00,0x1D, 3, AT_TINY,  35,11,  -1, MOVE_STRAIGHT,  0,
0x00,0x25, 4, AT_TINY,  43,11,  -1, MOVE_STRAIGHT,  0,
0x00,0x2D, 5, AT_TINY,  51,11,  -1, MOVE_STRAIGHT,  0,
0x00,0x30, 9, AT_LITTLE, 18,-3,  0, MOVE_STRAIGHT,  -1,
0x00,0x35, 6, AT_TINY,  59,11,  -1, MOVE_STRAIGHT,  0,
0x00,0x3D, 7, AT_TINY,  67,11,  -1, MOVE_STRAIGHT,  0,

0x00,0x49, 1, AT_SLIME, 72,-3, -70, MOVE_OSCILLATE, -1,
0x00,0x56, 2, AT_TINY,  60,11,  -1, MOVE_STRAIGHT,  1,
0x00,0x57, 0, AT_LITTLE, 24,-3,  0, MOVE_STRAIGHT, -1,
0x00,0x5E, 3, AT_TINY,  52,11,  -1, MOVE_STRAIGHT,  1,
0x00,0x66, 4, AT_TINY,  44,11,  -1, MOVE_STRAIGHT,  1,
0x00,0x6E, 5, AT_TINY,  36,11,  -1, MOVE_STRAIGHT,  1,
0x00,0x76, 6, AT_TINY,  28,11,  -1, MOVE_STRAIGHT,  1,
0x00,0x7A, 9, AT_LITTLE, 61,-3,  0, MOVE_STRAIGHT, -1,
0x00,0x7E, 7, AT_TINY,  20,11,  -1, MOVE_STRAIGHT,  1,
0x00,0x86, 8, AT_TINY,  12,11,  -1, MOVE_STRAIGHT,  1,

0x00,0xB0, 0, AT_SLIME,  3,-3,  70, MOVE_OSCILLATE, -1,
0x00,0xBD, 1, AT_TINY,  19,11,  -1, MOVE_STRAIGHT,  0,
0x00,0xC0, 8, AT_LITTLE, 45,-3, -1, MOVE_STRAIGHT,  -1,
0x00,0xC5, 2, AT_TINY,  27,11,  -1, MOVE_STRAIGHT,  0,
0x00,0xCD, 3, AT_TINY,  35,11,  -1, MOVE_STRAIGHT,  0,
0x00,0xD5, 4, AT_TINY,  43,11,  -1, MOVE_STRAIGHT,  0,
0x00,0xDD, 5, AT_TINY,  51,11,  -1, MOVE_STRAIGHT,  0,
0x00,0xE0, 9, AT_LITTLE,  8,-3, -1, MOVE_STRAIGHT,  -1,
0x00,0xE5, 6, AT_TINY,  59,11,  -1, MOVE_STRAIGHT,  0,
0x00,0xED, 7, AT_TINY,  67,11,  -1, MOVE_STRAIGHT,  0,

0x00,0xF9, 1, AT_SLIME, 72,-3, -70, MOVE_OSCILLATE, -1,
0x01,0x06, 2, AT_TINY,  60,11,  -1, MOVE_STRAIGHT,  1,
0x01,0x07, 0, AT_LITTLE, 30,-3, -1, MOVE_STRAIGHT, -1,
0x01,0x0E, 3, AT_TINY,  52,11,  -1, MOVE_STRAIGHT,  1,
0x01,0x16, 4, AT_TINY,  44,11,  -1, MOVE_STRAIGHT,  1,
0x01,0x1E, 5, AT_TINY,  36,11,  -1, MOVE_STRAIGHT,  1,
0x01,0x26, 6, AT_TINY,  28,11,  -1, MOVE_STRAIGHT,  1,
0x01,0x2A, 9, AT_LITTLE, 74,-3, -1, MOVE_STRAIGHT, -1,
0x01,0x2E, 7, AT_TINY,  20,11,  -1, MOVE_STRAIGHT,  1,
0x01,0x36, 8, AT_TINY,  12,11,  -1, MOVE_STRAIGHT,  1,

0x01,0x50, 0, AT_NONE, 0,0,0, MOVE_STRAIGHT, -1,
};

char level_4[] = {
0x00,0x00, 2, AT_BIG,   12,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x03, 3, AT_BIG,   45,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x06, 4, AT_BIG,   75,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x09, 5, AT_BIG,    5,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x0C, 6, AT_BIG,   34,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x0F, 7, AT_BIG,   57,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x12, 8, AT_BIG,   46,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x15, 9, AT_BIG,   61,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x18, 0, AT_BIG,   74,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x1B, 1, AT_BIG,   15,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x1E, 2, AT_BIG,   34,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x21, 3, AT_BIG,   21,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x24, 4, AT_BIG,   51,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x27, 5, AT_BIG,   14,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x2A, 6, AT_BIG,   62,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x2D, 7, AT_BIG,    3,-5,  -1, MOVE_STRAIGHT, -1,

0x00,0x30, 8, AT_BIG,   40,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x33, 9, AT_BIG,   59,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x36, 0, AT_BIG,   13,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x39, 1, AT_BIG,   35,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x3C, 2, AT_BIG,   72,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x3F, 3, AT_BIG,    2,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x42, 4, AT_BIG,   10,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x45, 5, AT_BIG,   51,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x48, 6, AT_BIG,   39,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x4B, 7, AT_BIG,   63,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x4E, 8, AT_BIG,   24,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x51, 9, AT_BIG,   70,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x54, 0, AT_BIG,   42,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x57, 1, AT_BIG,    9,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x5A, 2, AT_BIG,   68,-5,  -1, MOVE_STRAIGHT, -1,
0x00,0x5D, 3, AT_BIG,   40,-5,  -1, MOVE_STRAIGHT, -1,

0x00,0x7B, 0, AT_NONE, 0,0,0, MOVE_STRAIGHT, -1,
};

char *level;

void init_levels()
{
#ifndef RANDOM_LEVELS
// Sequential algorithm
	level=level_1;
#else
// Random algorithm
	switch (rrand(1,4))
	{
	case 1:
		level=level_1;
		break;
	case 2:
		level=level_2;
		break;
	case 3:
		level=level_3;
		break;
	case 4:
		level=level_4;
		break;
	}
#endif
}

char *next_level(const char *actual)
{
	char *next=level_1;
#ifndef RANDOM_LEVELS
// Sequential algorithm
	if (actual==level_1) next = level_2;
	else if (actual==level_2) next = level_3;
	else if (actual==level_3) next = level_4;
	else if ((actual==level_4) && (score >= SCORE_NEED)) next = NULL;
	else next = level_1;

#else
// Random algorithm
	switch (rrand(1,4))
	{
	case 1:
		next=level_1;
		break;
	case 2:
		next=level_2;
		break;
	case 3:
		next=level_3;
		break;
	case 4:
		next=level_4;
		break;
	}
	if (score>=SCORE_NEED)
	{
		next = NULL;
	}
#endif
	return next;
}

int xzarna_level(unsigned short int moment)
{
	static int start_end=0;
	if (!(xzarna_exploding()))
	{
		if (moment == 20)
		{
			start_xzarna();
		}
		else if (moment > 30)
		{
			int i;
			for (i=4;i<NUM_ALIENS;i++)
			{
				if (all_aliens[i].type == AT_NONE)
				{
					if (rrand(1,100)>90)
					{
						int n;
						all_aliens[i].type = AT_LITTLE;
						all_aliens[i].x = rrand(0,77);
						all_aliens[i].y = -3;
						all_aliens[i].state = 0;
						all_aliens[i].blit = blit_lit_alien;
						all_aliens[i].clear = clear_lit_alien;
						all_aliens[i].move = move_alien_straight;
						for (n=0;n<MAX_HEIGHT;n++)
							all_aliens[i].collide[n] = bitmask_lit_alien[n];
					}
				}
			}
		}
		return 0;
	}
	else
	{
		if (start_end++<50)
			return 0;
		else
			return 1;
	}
}

int create_aliens()
{
	static unsigned short int moment=0;
	static int lev_count=0;
	static int ended=0;

	if (ended)
	{
#ifdef DEBUG_LEV
		mvwprintw(term,24,0,"%X over   ",moment++);
		return 1;
#else
	/*** Loop ***/
		ended = 0;
		lev_count = 0;
		moment = 0;
		if (level==NULL)
		{
			return 0;
		}
		else
		{
			level = next_level(level);
		}
#endif
	}

	if (level==NULL)
	{
		ended=xzarna_level(moment);
	}
	else
	{
		while ( moment == ( ((unsigned char)level[lev_count]<<8) | (unsigned char)level[lev_count+1] ) )
		{
			if ( (level[lev_count+8] < 0) ||
			      ((all_aliens[(int)level[lev_count+8]].type != AT_NONE) &&
			       (all_aliens[(int)level[lev_count+8]].type != AT_BIG_EXP) &&
			       (all_aliens[(int)level[lev_count+8]].type != AT_LIT_EXP) &&
			       (all_aliens[(int)level[lev_count+8]].type != AT_LAST)) )
			{
				int ar_num;
				int n;

				ar_num = level[lev_count+2];

				all_aliens[ar_num].type = level[lev_count+3];

				switch (all_aliens[ar_num].type)
				{
				case AT_LITTLE:
					all_aliens[ar_num].blit=blit_lit_alien;
					all_aliens[ar_num].clear=clear_lit_alien;
					for (n=0;n<MAX_HEIGHT;n++)
						all_aliens[ar_num].collide[n]=bitmask_lit_alien[n];
					break;
				case AT_BIG:
					all_aliens[ar_num].blit=blit_big_alien;
					all_aliens[ar_num].clear=clear_big_alien;
					for (n=0;n<MAX_HEIGHT;n++)
						all_aliens[ar_num].collide[n]=bitmask_big_alien[n];
					break;
				case AT_SLIME:
					all_aliens[ar_num].blit=blit_slime_alien;
					all_aliens[ar_num].clear=clear_slime_alien;
					for (n=0;n<MAX_HEIGHT;n++)
						all_aliens[ar_num].collide[n]=bitmask_slime_alien[n];
					break;
				case AT_BALL:
					all_aliens[ar_num].blit=blit_ball_alien;
					all_aliens[ar_num].clear=clear_ball_alien;
					for (n=0;n<MAX_HEIGHT;n++)
						all_aliens[ar_num].collide[n]=bitmask_ball_alien[n];
					break;
				case AT_TINY:
					all_aliens[ar_num].blit=blit_tiny_alien;
					all_aliens[ar_num].clear=clear_tiny_alien;
					for (n=0;n<MAX_HEIGHT;n++)
						all_aliens[ar_num].collide[n]=bitmask_tiny_alien[n];
					break;
				case AT_NONE:
					ended = 1;
					break;
				}

				all_aliens[ar_num].x = (signed char)level[lev_count+4];
				all_aliens[ar_num].y = (signed char)level[lev_count+5];
				all_aliens[ar_num].state = level[lev_count+6];
				switch (level[lev_count+7])
				{
				case MOVE_STRAIGHT:
					all_aliens[ar_num].move = move_alien_straight;
					break;
				case MOVE_OSCILLATE:
					all_aliens[ar_num].move = move_alien_oscillate;
					break;
				case MOVE_DIAGONAL:
					all_aliens[ar_num].move = move_alien_diagonal;
					break;
				case MOVE_SERPENT:
					all_aliens[ar_num].move = move_alien_serpent;
					break;
				}
				all_aliens[ar_num].type = level[lev_count+3];
			}

			lev_count += FRAME_SIZE;
		}
	}
	moment++;

#ifdef DEBUG_LEV
	mvwprintw(term,24,0,"%X   ",moment);
#endif

	return 1;
}

