#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRANSITION 2	//遷移数
#define STATE 2	//状態数
#define NUMBER 16	//ボールの数
#define STRING 10	//文字列

// ボールの色を数字で識別
#define GREEN 0
#define RED 1
#define BLUE 2
#define WHITE 3

#define SPAN_1	3
#define SPAN_2	7
#define SPAN_3	11

#define TSUBO_NUM 4	//ツボの数


void Ball_color(int ball[NUMBER])
{
		for(int i = 0; i < NUMBER; i++)
		{
				if(i <= SPAN_1)
						ball[i] = GREEN;
				else if(i > SPAN_1 && i <= SPAN_2)
						ball[i] = RED;
				else if(i > SPAN_2 && i <= SPAN_3)
						ball[i] = BLUE;
				else
						ball[i] = WHITE;
		}
}

//つぼに入っているボールの数を0に初期化
void ball_count_init(int ball_count[TSUBO_NUM])
{
		for(int i = 0; i < TSUBO_NUM; i++)
			ball_count[i] = 0;
}

// 初期値を-1にして、入っているか否かを識別
void tsubo_init(int tsubo[TSUBO_NUM][NUMBER])
{
		for(int i = 0; i < TSUBO_NUM; i++)
			for(int j = 0; j < NUMBER; j++)
				tsubo[i][j] = -1;
}

// ボールをツボの中に入れる
void ball_put_in(int tsubo[TSUBO_NUM][NUMBER], int ball[NUMBER], int ball_count[TSUBO_NUM])
{
		for(int i = 0; i < TSUBO_NUM; i++)
		{
			int count = i;
			for(int j = 0; j < TSUBO_NUM; j++)
			{
				tsubo[i][j] = ball[count];
				count += 4;
				ball_count[i] += 1;
			}
		}
}



void test_print(int tsubo[TSUBO_NUM][NUMBER], int ball_count[TSUBO_NUM])
{
		for(int i = 0; i < TSUBO_NUM; i++)
		{
			printf("つぼ%dの個数:%3d(", i, ball_count[i]);
			
			for(int j = 0; j < ball_count[i]; j++)
			{
				printf("%2d", tsubo[i][j]);
				if(j != ( ball_count[i] - 1) )
					putchar(',');
				else if(j == ( ball_count[i] - 1) )
					putchar(')');
			}
			putchar('\n');
		}
}


