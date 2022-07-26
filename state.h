#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE 2	//状態数(自己ループか遷移するか)
#define NUMBER 16	//ボールの個数
#define STRING 10	//文字列数

#define TSUBO_NUM 4	//ツボの数

#define TRANSITION 7	//遷移数の最大値
#define PATTERN 50	//経路の数
#define COLOR 4		//色のパターン


const char str[][STRING] = {"green", "red", "blue", "white"};


// ランダムに遷移数を決める, 4 ~ 6回遷移する
int Ransu(void)
{
		int n;
		do{
			n = rand() % 5 + 2;
		}while(n == 2 || n == 3);
		return n;
}

// ランダムに色のパターンを決める
void route_switch(int output_color[PATTERN], int k)
{
		for(int i = 0; i < k; i++)
			output_color[i] = rand() % COLOR;
} 

// 自己ループか遷移するかの乱数
int seni_ransu(void)
{
		return rand() % STATE;
} 
 //階差数列の一般項an= (n*(n + 1) ) / 2
int kaisa_wa(int n)
{
		return ( n*(n + 1)*(n + 2) )/ 6; 
}

// 自己ループは0、遷移は1とする
void keisan(int k, int n, double wa[PATTERN], int output_color[TRANSITION], double state_probability[TSUBO_NUM][STATE], double output_probability[TSUBO_NUM][NUMBER])
{
		int self_loop = k - TSUBO_NUM;	//自己ループする回数 = 状態数 - つぼの個数
		int route[PATTERN];
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < k; j++)
			{
				int loop_n = seni_ransu();
				// 自己ループする回数が残っているときの分岐
				if(self_loop > 0)
				{
					wa[i] += state_probability[j][loop_n] * output_probability[j][output_color[j]];
					if(loop_n == 0) 
						self_loop--;
				}
				// 可能性が遷移しか残っていないときの分岐
				else if(self_loop == 0)
					wa[i] += state_probability[j][1] * output_probability[j][output_color[j]];

			}
		}
}

void loop_test_print(int k, int output_color[TRANSITION])
{

		printf("遷移数:%d\n", k);

		for(int i = 0; i < k; i++)
		{
				printf("%s", str[output_color[i]]);
				if(i >= 0 && i < k - 1)
					printf("→ ");
		}
		putchar('\n');
}

void keisan_print(int n, double wa[PATTERN])
{
		printf("all_pattern:%d\n", n);
		for(int i = 0; i < n; i++)
				printf("wa[%2d]:%lf\n", i, wa[i]);
}

void loop(int ball_count[NUMBER], double state_probability[TSUBO_NUM][STATE], double output_probability[TSUBO_NUM][NUMBER])
{
		int output_color[TRANSITION];	//ループ4経路の7通り分
		int k = Ransu();	//遷移数を決める変数
		int route[PATTERN][TRANSITION + 1];	//経路パターン
		int n = kaisa_wa(k - 2);	//階差数列の和で全経路の通りを求める(項数=遷移数-最初+最後)
		double wa[PATTERN];

		route_switch(output_color, k);
		loop_test_print(k, output_color);
		keisan(k, n, wa, output_color, state_probability, output_probability);
		keisan_print(n, wa);
}

