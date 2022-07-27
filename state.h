#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE 2	//状態数(自己ループか遷移するか)
#define NUMBER 16	//ボールの個数
#define STRING 10	//文字列数

#define TSUBO_NUM 4	//ツボの数

#define TRANSITION 7	//遷移数の最大値
#define PATTERN 100	//経路の数
#define COLOR 4		//色のパターン


const char str[][STRING] = {"green", "red", "blue", "white"};


// ランダムに状態数を決める, 4 ~ 6回遷移する
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

int kaisa_wa(int n)
{
		return ( n*(n + 1)*(n + 2) )/6;
}

// 自己ループか遷移するかの乱数
int seni_ransu(void)
{
		return rand() % STATE;
} 

int kaijyo(int n)
{
		if(n == 0)
			return 1;
		
		else
		{
			int num = n;
			while(--n > 0)
				num *= n;	
			return num;
		}
}

int bainary(int n)
{
		int b;
		int base = 1;
		while(n > 0)
		{
			b += (n % 2) * base;
			n /= 2;
			base *= 10;
		}
}

void route_test_print(int k, int all_pattern, int route[PATTERN][TRANSITION])
{
		for(int i = 0; i < all_pattern; i++)
		{
			for(int j = 0; j < k; j++)
				printf("%2d", route[i][j]);
			putchar('\n');
		}
}

void route_init(int n, int k, int self_loop, int route[PATTERN][TRANSITION])
{
		for(int i = 0; i < k - 1; i++)
		{
			if(i < self_loop)
				route[n][i] = 0;
			else if(i >= self_loop)
				route[n][i] = 1;
		}
		route[n][k-1] = 1;
}

// 一つ前の配列の要素をコピーする
void route_cp(int k, int n, int route[PATTERN][TRANSITION])
{
		for(int i = 0; i < k; i++)
			route[n][i] = route[n-1][i];
}

// k:状態数 = 遷移数 + 自己ループの回数	遷移数:4
// 0, 1で経路を表現する
void route_search(int k, int self_loop, int all_pattern, int route[PATTERN][TRANSITION])
{
		int j = 0, count = 0;	//カウント変数

		if(self_loop == 0)
			for(int i = 0; i < k; i++)
				route[self_loop][i] = 1;
		
		else if(self_loop > 0)
		{
			route_init(0, k, self_loop, route);
	
			for(int i = 1; i < all_pattern; i++)
			{
				int change;
				route_cp(k, i, route);
				
				//最上位が0から1に変わる
				if(route[i][k-2] == 0)
				{
					j = 0;
					count++;
				}
				
				change = route[i][j+1];
				route[i][j+1] = route[i][j];
				route[i][j] = change;
				j++;
			}
		}		
		route_test_print(k, all_pattern, route);
}

// 自己ループは0、遷移は1とする
void keisan(int k, int all_pattern, int self_loop, double wa[PATTERN], int output_color[TRANSITION], double state_probability[TSUBO_NUM][STATE], double output_probability[TSUBO_NUM][NUMBER])
{
		int route[PATTERN][TRANSITION];

		route_search(k, self_loop, all_pattern, route);
		
		for(int i = 0; i < all_pattern; i++)
			for(int j = 0; j < k; j++)
				wa[i] += state_probability[j][route[i][j]] * output_probability[j][output_color[j]];

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
		double min;

		printf("all_pattern:%d\n", n);
		for(int i = 0; i < n; i++)
				printf("wa[%2d]:%lf\n", i, wa[i]);
		
		for(int i = 0; i < n; i++)
		{
			if(i == 0)
				min = wa[i];
			else
				if(min > wa[i])
					min = wa[i];

		}

		printf("min:%lf\n", min);
}

void loop(int ball_count[NUMBER], double state_probability[TSUBO_NUM][STATE], double output_probability[TSUBO_NUM][NUMBER])
{
		int output_color[TRANSITION];	//ループ4経路の7通り分
		int k = 6;		//ransu();	//状態数を決める変数
		double wa[PATTERN];
		
		int self_loop = k - TSUBO_NUM;	//自己ループする回数 = 状態数 - つぼの個数
		int all_pattern = kaijyo(k - 1) / (kaijyo(k - 1 - self_loop) * kaijyo(self_loop));

		route_switch(output_color, k);
		loop_test_print(k, output_color);
		keisan(k, all_pattern, self_loop, wa, output_color, state_probability, output_probability);
		keisan_print(all_pattern, wa);
}

