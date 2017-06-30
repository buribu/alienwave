/* This file is part of Alienwave, a game by Alessandro Pira */

#include <curses.h>
#include "defs.h"
#include "util.h"

extern int x_ofs;
extern int y_ofs;
extern int term_x;
extern int term_y;
extern WINDOW *term; /* our terminal */

/* Explosion blitting */

/* All the explosion functions must be called with the coordinates
of the center point as parameters */

void blit_explosion_1(int x, int y)
{
/*
 .
#@#
 "
*/
	SET_COLOR(COL_DARKYELLOW);
	if (is_y_range(y-1))
	{
		mvwaddch(term,y-1,x,(chtype)'.');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)'#');
		SET_COLOR(COL_DARKRED);
		mvwaddch(term,y,x,(chtype)'@');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)'#');
	}
	if (is_y_range(y+1))
	{
		mvwaddch(term,y+1,x,(chtype)'"');
	}
	SET_COLOR(COL_BKG);
}

void clear_explosion_1(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y-1))
	{
		mvwaddch(term,y-1,x,(chtype)' ');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)' ');
		mvwaddch(term,y,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)' ');
	}
	if (is_y_range(y+1))
	{
		mvwaddch(term,y+1,x,(chtype)' ');
	}
}

void blit_explosion_2(int x, int y)
{
/*
 @ 
@#@
 @ 
*/
	SET_COLOR(COL_DARKRED);
	if (is_y_range(y-1))
	{
		mvwaddch(term,y-1,x,(chtype)'@');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)'#');
		SET_COLOR(COL_RED);
		mvwaddch(term,y,x,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)'#');
	}
	if (is_y_range(y+1))
	{
		mvwaddch(term,y+1,x,(chtype)'@');
	}
	SET_COLOR(COL_BKG);
}

void clear_explosion_2(int x, int y)
{
	clear_explosion_1(x,y);
}

void blit_explosion_3(int x, int y)
{
/*
  .
 #@#
#@#@#
 #@#
  "
*/

	SET_COLOR(COL_DARKRED);
	if (is_y_range(y-2))
	{
		mvwaddch(term,y-2,x,(chtype)'.');
	}
	if (is_y_range(y-1))
	{
		if (is_x_range(x-1)) mvwaddch(term,y-1,x-1,(chtype)'#');
		SET_COLOR(COL_RED);
		mvwaddch(term,y-1,x,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+1)) mvwaddch(term,y-1,x+1,(chtype)'#');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-2)) mvwaddch(term,y,x-2,(chtype)'#');
		SET_COLOR(COL_RED);
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)'@');
		SET_COLOR(COL_YELLOW);
		mvwaddch(term,y,x,(chtype)'#');
		SET_COLOR(COL_RED);
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+2)) mvwaddch(term,y,x+2,(chtype)'#');
	}
	if (is_y_range(y+1))
	{
		if (is_x_range(x-1)) mvwaddch(term,y+1,x-1,(chtype)'#');
		SET_COLOR(COL_RED);
		mvwaddch(term,y+1,x,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+1)) mvwaddch(term,y+1,x+1,(chtype)'#');
	}
	if (is_y_range(y+2))
	{
		mvwaddch(term,y+2,x,(chtype)'"');
	}
	SET_COLOR(COL_BKG);
}

void clear_explosion_3(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y-2))
	{
		mvwaddch(term,y-2,x,(chtype)' ');
	}
	if (is_y_range(y-1))
	{
		if (is_x_range(x-1)) mvwaddch(term,y-1,x-1,(chtype)' ');
		mvwaddch(term,y-1,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y-1,x+1,(chtype)' ');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-2)) mvwaddch(term,y,x-2,(chtype)' ');
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)' ');
		mvwaddch(term,y,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)' ');
		if (is_x_range(x+2)) mvwaddch(term,y,x+2,(chtype)' ');
	}
	if (is_y_range(y+1))
	{
		if (is_x_range(x-1)) mvwaddch(term,y+1,x-1,(chtype)' ');
		mvwaddch(term,y+1,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y+1,x+1,(chtype)' ');
	}
	if (is_y_range(y+2))
	{
		mvwaddch(term,y+2,x,(chtype)' ');
	}
}

void blit_explosion_4(int x, int y)
{
/*
   .
  @#@
 @#@#@
@#@#@#@
 @#@#@
  @#@
   "
*/
	SET_COLOR(COL_DARKYELLOW);
	if (is_y_range(y-3))
	{
		mvwaddch(term,y-3,x,(chtype)'.');
	}
	if (is_y_range(y-2))
	{
		if (is_x_range(x-1)) mvwaddch(term,y-2,x-1,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		mvwaddch(term,y-2,x,(chtype)'#');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+1)) mvwaddch(term,y-2,x+1,(chtype)'@');
	}
	if (is_y_range(y-1))
	{
		if (is_x_range(x-2)) mvwaddch(term,y-1,x-2,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x-1)) mvwaddch(term,y-1,x-1,(chtype)'#');
		SET_COLOR(COL_RED);
		mvwaddch(term,y-1,x,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+1)) mvwaddch(term,y-1,x+1,(chtype)'#');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+2)) mvwaddch(term,y-1,x+2,(chtype)'@');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-3)) mvwaddch(term,y,x-3,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x-2)) mvwaddch(term,y,x-2,(chtype)'#');
		SET_COLOR(COL_RED);
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)'@');
		SET_COLOR(COL_YELLOW);
		mvwaddch(term,y,x,(chtype)'#');
		SET_COLOR(COL_RED);
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+2)) mvwaddch(term,y,x+2,(chtype)'#');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+3)) mvwaddch(term,y,x+3,(chtype)'@');
	}
	if (is_y_range(y+1))
	{
		if (is_x_range(x-2)) mvwaddch(term,y+1,x-2,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x-1)) mvwaddch(term,y+1,x-1,(chtype)'#');
		SET_COLOR(COL_RED);
		mvwaddch(term,y+1,x,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		if (is_x_range(x+1)) mvwaddch(term,y+1,x+1,(chtype)'#');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+2)) mvwaddch(term,y+1,x+2,(chtype)'@');
	}
	if (is_y_range(y+2))
	{
		if (is_x_range(x-1)) mvwaddch(term,y+2,x-1,(chtype)'@');
		SET_COLOR(COL_DARKRED);
		mvwaddch(term,y+2,x,(chtype)'#');
		SET_COLOR(COL_DARKYELLOW);
		if (is_x_range(x+1)) mvwaddch(term,y+2,x+1,(chtype)'@');
	}
	if (is_y_range(y+3))
	{
		mvwaddch(term,y+3,x,(chtype)'"');
	}
	SET_COLOR(COL_BKG);
}

void clear_explosion_4(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y-3))
	{
		mvwaddch(term,y-3,x,(chtype)' ');
	}
	if (is_y_range(y-2))
	{
		if (is_x_range(x-1)) mvwaddch(term,y-2,x-1,(chtype)' ');
		mvwaddch(term,y-2,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y-2,x+1,(chtype)' ');
	}
	if (is_y_range(y-1))
	{
		if (is_x_range(x-2)) mvwaddch(term,y-1,x-2,(chtype)' ');
		if (is_x_range(x-1)) mvwaddch(term,y-1,x-1,(chtype)' ');
		mvwaddch(term,y-1,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y-1,x+1,(chtype)' ');
		if (is_x_range(x+2)) mvwaddch(term,y-1,x+2,(chtype)' ');
	}
	if (is_y_range(y))
	{
		if (is_x_range(x-3)) mvwaddch(term,y,x-3,(chtype)' ');
		if (is_x_range(x-2)) mvwaddch(term,y,x-2,(chtype)' ');
		if (is_x_range(x-1)) mvwaddch(term,y,x-1,(chtype)' ');
		mvwaddch(term,y,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y,x+1,(chtype)' ');
		if (is_x_range(x+2)) mvwaddch(term,y,x+2,(chtype)' ');
		if (is_x_range(x+3)) mvwaddch(term,y,x+3,(chtype)' ');
	}
	if (is_y_range(y+1))
	{
		if (is_x_range(x-2)) mvwaddch(term,y+1,x-2,(chtype)' ');
		if (is_x_range(x-1)) mvwaddch(term,y+1,x-1,(chtype)' ');
		mvwaddch(term,y+1,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y+1,x+1,(chtype)' ');
		if (is_x_range(x+2)) mvwaddch(term,y+1,x+2,(chtype)' ');
	}
	if (is_y_range(y+2))
	{
		if (is_x_range(x-1)) mvwaddch(term,y+2,x-1,(chtype)' ');
		mvwaddch(term,y+2,x,(chtype)' ');
		if (is_x_range(x+1)) mvwaddch(term,y+2,x+1,(chtype)' ');
	}
	if (is_y_range(y+3))
	{
		mvwaddch(term,y+3,x,(chtype)' ');
	}
}

void blit_explosion(int x, int y, int dim)
{
	switch (dim)
	{
	case 1:
		blit_explosion_1(x,y);
		break;
	case 2:
		blit_explosion_2(x,y);
		break;
	case 3:
		blit_explosion_3(x,y);
		break;
	case 4:
		blit_explosion_4(x,y);
		break;
	}
}

void clear_explosion(int x, int y, int dim)
{
	switch (dim)
	{
	case 1:
		clear_explosion_1(x,y);
		break;
	case 2:
		clear_explosion_2(x,y);
		break;
	case 3:
		clear_explosion_3(x,y);
		break;
	case 4:
		clear_explosion_4(x,y);
		break;
	}
}

/* End of explosion blitting */

void blit_big_alien(int x, int y)
{
/*
Big Alien:

|-v-|
| o |
 \_/
*/
	if (is_y_range(y))
	{
		SET_COLOR(COL_GREEN);
		mvwprintw(term,y,x,"|-");
		SET_COLOR(COL_BLUE);
		wprintw(term,"v");
		SET_COLOR(COL_GREEN);
		wprintw(term,"-|");
	}
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_GREEN);
		mvwprintw(term,y+1,x,"| ");
		SET_COLOR(COL_CYAN);
		wprintw(term,"o");
		SET_COLOR(COL_GREEN);
		wprintw(term," |");
	}
	if (is_y_range(y+2))
	{
		SET_COLOR(COL_GREEN);
		mvwprintw(term,y+2,x+1,"\\_/");
	}
	SET_COLOR(COL_BKG);
}

void clear_big_alien(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x,      "     ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x,  "     ");
	if (is_y_range(y+2)) mvwprintw(term,y+2,x+1, "   ");
}

void blit_lit_alien(int x,int y)
{
/*
Little Alien:

W_W
 "
*/
	if (is_y_range(y))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y,x,"W W");
		SET_COLOR(COL_WHITE);
		mvwaddch(term,y,x+1,(chtype)'_');
	}
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_RED);
		mvwprintw(term,y+1,x+1,"\"");
	}
	SET_COLOR(COL_BKG);
}

void clear_lit_alien(int x, int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x,"   ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x+1," ");
}

void blit_ball_alien(int x,int y)
{
/*
/^\
\_/
*/
	SET_COLOR(COL_DARKMAGENTA);
	if (is_y_range(y)) mvwprintw(term,y,x,"/^\\");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x,"\\_/");
	SET_COLOR(COL_BKG);
}

void clear_ball_alien(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x,"   ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x,"   ");
}

void blit_slime_alien(int x,int y)
{
/*
/~T~\
\/|\/
*/
	if (is_y_range(y))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y,x,"/");
		SET_COLOR(COL_RED);
		wprintw(term,"~T~");
		SET_COLOR(COL_BLUE);
		wprintw(term,"\\");
	}
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y+1,x,"\\/");
		SET_COLOR(COL_RED);
		wprintw(term,"|");
		SET_COLOR(COL_BLUE);
		wprintw(term,"\\/");
	}
	SET_COLOR(COL_BKG);
}

void clear_slime_alien(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x,"     ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x,"     ");
}

void blit_tiny_alien(int x,int y)
{
/*
o
*/
	SET_COLOR(COL_GREEN);
	if (is_y_range(y)) mvwprintw(term,y,x,"o");
	SET_COLOR(COL_BKG);
}

void clear_tiny_alien(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x," ");
}

void blit_fire(int x,int y)
{
	if (is_y_range(y))
	{
		SET_COLOR(COL_RED);
		mvwaddch(term,y,x,(chtype)'!');
		SET_COLOR(COL_BKG);
	}
}

void clear_fire(int x, int y)
{
	if (is_y_range(y))
	{
		SET_COLOR(COL_BKG);
		mvwaddch(term,y,x,(chtype)' ');
	}
}

void blit_ship(int x,int y)
{
/* This is the player's ship:
  /^\
 | _ |
< /_\ >
 ^^^^^
*/

	if (is_y_range(y))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y,x+2,  "/^\\");
	}
	
	if (is_y_range(y+1))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+1,x+1,"| ");
		SET_COLOR(COL_DARKCYAN);
		wprintw(term,"_");
		SET_COLOR(COL_GRAY);
		wprintw(term," |");
	}

	if (is_y_range(y+2))
	{
		SET_COLOR(COL_GRAY);
		mvwprintw(term,y+2,x,"< ");
		SET_COLOR(COL_DARKCYAN);
		wprintw(term,"/_\\");
		SET_COLOR(COL_GRAY);
		wprintw(term," >");
	}

	if (is_y_range(y+3))
	{
		SET_COLOR(COL_YELLOW);
		mvwprintw(term,y+3,x+1,"^");
		SET_COLOR(COL_RED);
		wprintw(term,"^^^");
		SET_COLOR(COL_YELLOW);
		wprintw(term,"^");
	}

	SET_COLOR(COL_BKG);
}

void clear_ship(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y)) mvwprintw(term,y,x+2,    "   ");
	if (is_y_range(y+1)) mvwprintw(term,y+1,x+1, "     ");
	if (is_y_range(y+2)) mvwprintw(term,y+2,x,  "       ");
	if (is_y_range(y+3)) mvwprintw(term,y+3,x+1, "     ");
}

void blit_shield(int x,int y,int intensity)
{
/* This is the shield:

/~~~^~~~\

*/
	int col1=COL_DARKGREEN,col2=COL_DARKGREEN,col3=COL_DARKGREEN;
	switch (intensity)
	{
	case 3:
		col2=COL_GREEN;
		col3=COL_CYAN;
		break;
	case 2:
		col3=COL_GREEN;
		break;
	}

	if (is_x_range(x))
	{
		SET_COLOR(col1);
		mvwprintw(term,y,x,"/");
	}
	SET_COLOR(col2);
	mvwprintw(term,y,x+1,"~~");
	SET_COLOR(col3);
	wprintw(term,"~^~");
	SET_COLOR(col2);
	wprintw(term,"~~");
	if (is_x_range(x+8))
	{
		SET_COLOR(col1);
		wprintw(term,"\\");
	}
	SET_COLOR(COL_BKG);
}

void blit_shield_charge(int x, int y, int length)
{
	int i;
	for (i=0;i<length;i++)
	{
		switch(i)
		{
		case 0:
			SET_COLOR(COL_DARKYELLOW);
			break;
		case 5:
			SET_COLOR(COL_DARKRED);
			break;
		case 10:
			SET_COLOR(COL_RED);
			break;
		case 15:
			SET_COLOR(COL_YELLOW);
			break;
		}
		mvprintw(y,i+x,"-");
	}
	SET_COLOR(COL_BKG);
}

void clear_shield(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_x_range(x))
	{
		mvwprintw(term,y,x," ");
	}
	mvwprintw(term,y,x+1,"       ");
	if (is_x_range(x+8))
	{
		wprintw(term," ");
	}
}

void clear_shield_charge(int x, int y)
{
	SET_COLOR(COL_BKG);
	mvwprintw(term,y,x,"                    ");
}

void blit_score(int x, int y, int score)
{
	SET_COLOR(COL_WHITE);
	mvwprintw(term,y,x,"%d",score);
	SET_COLOR(COL_BKG);
}

void blit_xzarna(int x,int y,unsigned int extra)
{
/*
 /^~~^~~^\
( o o o o )
 \ ~\~/~ /
  > O O <
 (_/\_/\_)
*/
	int eye_col = (extra & 0xFF);
	unsigned char eggs    = ((extra & 0xFF00) >> 8);
	if (is_y_range(y))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y,x+1,"/");
		SET_COLOR(COL_RED);
		wprintw(term,"^");
		SET_COLOR(COL_BLUE);
		wprintw(term,"~~");
		SET_COLOR(COL_RED);
		wprintw(term,"^");
		SET_COLOR(COL_BLUE);
		wprintw(term,"~~");
		SET_COLOR(COL_RED);
		wprintw(term,"^");
		SET_COLOR(COL_BLUE);
		wprintw(term,"\\");
	}
	if (is_y_range(y+1))
	{
		int cnt=0;
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y+1,x,"(");
		SET_COLOR(COL_GREEN);
		while (cnt<4)
		{
			if (eggs & (1<<(cnt++)))
				wprintw(term," o");
			else
				wprintw(term,"  ");
		}
		SET_COLOR(COL_BLUE);
		wprintw(term," )");
	}
	if (is_y_range(y+2))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y+2,x+1,"\\ ~");
		SET_COLOR(COL_DARKCYAN);
		wprintw(term,"\\");
		SET_COLOR(COL_BLUE);
		wprintw(term,"~");
		SET_COLOR(COL_DARKCYAN);
		wprintw(term,"/");
		SET_COLOR(COL_BLUE);
		wprintw(term,"~ /");
	}
	if (is_y_range(y+3))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y+3,x+2,"> ");
		SET_COLOR(eye_col);
		wprintw(term,"O O");
		SET_COLOR(COL_BLUE);
		wprintw(term," <");
	}
	if (is_y_range(y+4))
	{
		SET_COLOR(COL_BLUE);
		mvwprintw(term,y+4,x+1,"(_");
		SET_COLOR(COL_DARKRED);
		wprintw(term,"/\\_/\\");
		SET_COLOR(COL_BLUE);
		wprintw(term,"_)");
	}
	SET_COLOR(COL_BKG);
}

void clear_xzarna(int x,int y)
{
	SET_COLOR(COL_BKG);
	if (is_y_range(y))
	{
		mvwprintw(term,y,x+1,"         ");
	}
	if (is_y_range(y+1))
	{
		mvwprintw(term,y+1,x,"           ");
	}
	if (is_y_range(y+2))
	{
		mvwprintw(term,y+2,x+1,"         ");
	}
	if (is_y_range(y+3))
	{
		mvwprintw(term,y+3,x+2,"       ");
	}
	if (is_y_range(y+4))
	{
		mvwprintw(term,y+4,x+1,"         ");
	}
}

void blit_borders(int color)
{
	int i;
	SET_COLOR(color);
	if (y_ofs-1 >= 0)
	{
		for (i=x_ofs;i<80+x_ofs;i++)
			mvwaddch(term,y_ofs-1,i,(chtype)'-');
	}
	if (y_ofs+25 < term_y)
	{
		for (i=x_ofs;i<80+x_ofs;i++)
			mvwaddch(term,y_ofs+25,i,(chtype)'-');
	}

	if (x_ofs-1 >= 0)
	{
		for (i=y_ofs;i<25+y_ofs;i++)
			mvwaddch(term,i,x_ofs-1,(chtype)'|');
	}
	if (x_ofs+80 < term_x)
	{
		for (i=y_ofs;i<25+y_ofs;i++)
			mvwaddch(term,i,x_ofs+80,(chtype)'|');
	}

	if ((x_ofs-1 >= 0) && (y_ofs-1 >= 0))
		mvwaddch(term,y_ofs-1,x_ofs-1,(chtype)'+');
	if ((x_ofs-1 >= 0) && (y_ofs+25 < term_y))
		mvwaddch(term,y_ofs+25,x_ofs-1,(chtype)'+');
	if ((x_ofs+80 < term_x) && (y_ofs-1 >= 0))
		mvwaddch(term,y_ofs-1,x_ofs+80,(chtype)'+');
	if ((x_ofs+80 < term_x) && (y_ofs+25 < term_y))
		mvwaddch(term,y_ofs+25,x_ofs+80,(chtype)'+');

	SET_COLOR(COL_BKG);
}

