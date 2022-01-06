/*
 * menus.c
 *
 *  Created on: 2021/12/27
 *      Author: new-kensyu
 */

#include "menus.h"
#include "game.h"

#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

void flushbuff(){
    while(getchar() != '\n');
}

char main_menu_jp(){
    clear_screen();
    fflush(stdin);

    printf("######Snake!\n");
    printf("1.遊ぶ\n");
    printf("2.設定\n");
    printf("3.スコア\n");
    printf("4.終了\n");
    printf("選択を入力してください\n");

    return getchar();
}

void record_input_menu_jp(int score){
    clear_screen();
    char initials[4];
    int i;

    printf("スコアは%dポイントです\n", score);
    printf("頭文字を三つまで入力してください\n");
    flushbuff();
    scanf("%3c", initials);

    for(i = 0; i < 3; i++){
        if(initials[i] < 33 || initials[i] > 126){
            initials[i] = '*';
        } else if (initials[i] < 58 && initials[i] > 47){
            initials[i] = '*';
        }
    }
    initials[3] = '\0';

    scoreboard_add_record(initials, score);
    scoreboard_menu();
}

void scoreboard_add_record(char* initials_in, int score_in){
    FILE *fp;
    int i, j, rec_count = 0;

    char initials[9][4] = {"   \0", "   \0", "   \0", "   \0", "   \0", \
    						"   \0", "   \0", "   \0", "   \0",};
    int score[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    char timestamp[9][11];

    if((fp = fopen("scoreboard.txt", "r")) != 0){
        //Determine how many records exist in the scoreboard
        for(i = 0; i < 9; i++){
        	if(fscanf(fp, "%d. %3c %d %s", &rec_count, initials[i], &score[i], timestamp[i]) != 4){
        		break;
        	}
        }

        fclose(fp);
    }

    //Find insertion index of new score
    for(i = 0; i < 9; i++){
    	if(score_in > score[i]) break;
    	else if(score_in == score[i]){
    		i ++;
		break;
    	}
    }

    j = i + 1;
    rec_count++;

    if((fp = fopen("scoreboard.txt", "w")) != 0){
        //Write records
        for(j = 0; j < rec_count; j++){
        	if(j < i){
        		fprintf(fp, "%2d. %3s %5d %s\n", (j + 1), initials[j], score[j], timestamp[j]);
        	} else if(j > i) {
        		fprintf(fp, "%2d. %3s %5d %s\n", (j + 1), initials[j-1], score[j-1], timestamp[j-1]);
        	} else {
        		time_t temp;
                struct tm *date;

        		time(&temp);

                date = localtime(&temp);

        	    if(date->tm_year / 100) date->tm_year += 1900;

        	    fprintf(fp, "%2d. %3s %5d %d/%d/%d\n", (j + 1), initials_in, score_in, date->tm_year, date->tm_mon, date->tm_mday);
        	}
        }

        fclose(fp);
    }
}

void scoreboard_menu_jp(){
    FILE *fp;
    int i, records = 0;
    char record[26];

    clear_screen();
    printf("######Score!\n");

    if((fp = fopen("scoreboard.txt", "r")) != 0){
        //Determine how many records exist in the scoreboard
        for(i = 0; i < 10; i++){
            if(fgets(record, 26, fp) == 0){
                break;
            }
            printf("%s", record);
            records++;
        }

        fclose(fp);
    }

    if(!records) printf("記録されているスコアがありません");

    sleep(5000);
    flushbuff();
}


void settings_menu_jp(int* board_size, int* speed){
    clear_screen();
    int input;

    printf("######Settings!\n");
    printf("ゲーム盤のサイズを入力してください\n");

    scanf("%d", &input);

    if(input < 3){
        printf("小さすぎです\n");
    } else if(input > CHAR_MAX){
        printf("大きすぎです\n");
    } else {
        *board_size = input;
        printf("ゲーム盤のサイズは%dマスになります", input);
    }

    sleep(2000);

    clear_screen();
    printf("######Settings!\n");

    printf("蛇の速度を入力してください。（一秒ごとに何マスを進む）\n");

    scanf("%d", &input);

    if(input > 100){
        printf("速すぎです\n");
    }else if(input <= 0){
        printf("遅すぎです\n");
    }else{
        *speed = 1000/input;
        printf("速度は一秒ごとに%dマスになります", input);
    }

    sleep(2000);
    flushbuff();
}
