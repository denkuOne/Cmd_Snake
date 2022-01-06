/*
 * game.h
 *
 *  Created on: 2021/12/27
 *      Author: new-kensyu
 */

#ifndef GAME_H_
#define GAME_H_

enum direction
{
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

enum gameobjects
{
    NOTHING = 0,
    SNAKEBODY = 1,
    SNAKEHEAD = 2,
    ESA = 3
};

struct snake
{
    char *x_cord;
    char *y_cord;
    enum direction dir;
    unsigned char limit;
    unsigned char head;
};

int check_collision(int *);
void clear_board();
void clear_screen();
void draw_screen(int);
void player_input();
void setup_board(unsigned char);
void sleep(int);

#endif /* GAME_H_ */
