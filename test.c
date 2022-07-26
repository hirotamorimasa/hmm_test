#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./ball_color.h"
#include "./probability.h"
#include "./state.h"

#define STATE 2	//状態数 (自己ループか遷移するか)
#define NUMBER 16	//ボールの個数
#define STRING 10	//文字列数

#define TSUBO_NUM 4 //ツボの数


int main(void)
{
		double state_probability[TSUBO_NUM][STATE];	//状態確率a11~a2eにあたる
		double output_probability[TSUBO_NUM][NUMBER];	//出力確率b11~b2eにあたる
		
		int ball[NUMBER];	
		int tsubo[TSUBO_NUM][NUMBER];	//ツボの中に入っているボールの番号
		int ball_count[TSUBO_NUM];
		
		srand(time(NULL));
		
		//ball_color.h
		include_ball_color(ball, tsubo, ball_count);

		//probability.h
		probability_print(state_probability, output_probability, ball_count);
		
		//state.h
		loop(ball_count, state_probability, output_probability);

		return 0;
}


