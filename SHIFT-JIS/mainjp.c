/*
 * mainjp.c
 *
 *  Created on: 2021/12/27
 *      Author: new-kensyu
 */

#include "game.h"
#include "menus.h"

#include <stdlib.h>

int main()
{
    char input;
    int gameboard_size = 20;
    int gamespeed = 200;

    for (;;)
    {
        input = main_menu_jp();

        switch (input)
        {
        case '1':
        {
            // Game loop
            setup_board(gameboard_size);
            int score = 0;

            do
            {
                draw_screen(score);
                sleep(gamespeed);
                player_input();
            } while (check_collision(&score));

            clear_board();

            if (score != gameboard_size * gameboard_size - 1)
            {
            	printf("ゲームオーバー");
            }
            else
            {
                printf("完璧！");
            }

            sleep(3000);
            record_input_menu_jp(score);
            break;
        }
        case '2':
        {
            settings_menu_jp(&gameboard_size, &gamespeed);
            break;
        }
        case '3':
        {
        	scoreboard_menu_jp();
            break;
        }

        case '4':
        {
            exit(EXIT_SUCCESS);
            break;
        }
        default:{
            flushbuff();
        }
    }
    }

    return 0;
}
