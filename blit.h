/* This file is part of Alienwave, a game by Alessandro Pira */

#ifndef _BLIT_H
#define _BLIT_H

void blit_explosion_1(int,int);
void blit_explosion_2(int,int);
void blit_explosion_3(int,int);
void blit_explosion_4(int,int);

void clear_explosion_1(int,int);
void clear_explosion_2(int,int);
void clear_explosion_3(int,int);
void clear_explosion_4(int,int);

void blit_explosion(int,int,int);
void clear_explosion(int,int,int);

void blit_big_alien(int,int);
void clear_big_alien(int,int);

void blit_lit_alien(int,int);
void clear_lit_alien(int,int);

void blit_ball_alien(int x,int y);
void clear_ball_alien(int x,int y);

void blit_slime_alien(int x,int y);
void clear_slime_alien(int x,int y);

void blit_tiny_alien(int x,int y);
void clear_tiny_alien(int x,int y);

void blit_fire(int,int);
void clear_fire(int,int);

void blit_ship(int,int);
void clear_ship(int,int);

void blit_shield(int,int,int);
void blit_shield_charge(int,int,int);
void clear_shield(int,int);
void clear_shield_charge(int,int);

void blit_score(int,int,int);

void blit_xzarna(int,int,int);
void clear_xzarna(int,int);

void blit_borders(int);

#endif //_BLIT_H
