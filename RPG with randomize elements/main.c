#define _CRT_SECURE_NO_WARNING

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define HEIGHT_GAME 60
#define WIDTH_GAME 80

#define HEIGHT_TEXT 30
#define WIDTH_TEXT 45

#define HEIGHT_STATS 30
#define WIDTH_STATS 25

#define HEIGHT_BEHAVE 20
#define WIDTH_BEHAVE 80

#define LVLup_stats 3

char CELL_GAME[HEIGHT_GAME][WIDTH_GAME] = { ' ' };
char character_name[17] = "\0";

//직업분류
//1:거지,2:성직자,3:목수,4:개장수,5:기사,6:농부
int class_rating[6] = { 1,2,3,4,5,6 };
int player_class;

//초기 플레이어 레벨
int player_LVL = 1;

//초기 플레이어 스텟
//1:힘 2:체력 3:민첩 4:지능 5:운
int player_stats[5] = { 1 };

int DICEROLL(int);
void cell_deployment();
void start_game();
void LVL_scailing(int);
bool character_alive();

int DICEROLL(int side) {
	int result = rand() % side;
	return result;
}

//전체적인 게임 화면 배치
void cell_deployment() {

	// TEXT CELL

	//TEXT WIDTH
	for (int i = 0; i < WIDTH_TEXT; i++) {
		CELL_GAME[0][i] = CELL_GAME[HEIGHT_TEXT - 1][i] = '-';
	}

	//TEXT HEIGHT
	for (int i = 0; i < HEIGHT_TEXT; i++) {
		CELL_GAME[i][0] = CELL_GAME[i][WIDTH_TEXT - 1] = '|';
	}

	//INNER TEXT CELL
	for (int i = 1; i < HEIGHT_TEXT - 1; i++) {
		for (int k = 1; k < WIDTH_TEXT - 1; k++) {
			CELL_GAME[i][k] = ' ';
		}
	}

	//STATS CELL

	//STATS WIDTH
	for (int i = 0; i < WIDTH_STATS; i++) {
		CELL_GAME[0][(WIDTH_GAME - 1) - WIDTH_STATS + i] = CELL_GAME[HEIGHT_STATS - 1][(WIDTH_GAME - 1) - WIDTH_STATS + i] = '-';
	}

	//STATS HEIGHT
	for (int i = 0; i < HEIGHT_STATS; i++) {
		CELL_GAME[i][(WIDTH_GAME - 1) - WIDTH_STATS] = CELL_GAME[i][WIDTH_GAME - 1] = '|';
	}

	//INNER STATS CELL
	for (int i = 0; i < HEIGHT_STATS - 1; i++) {
		for (int k = WIDTH_GAME - WIDTH_STATS; k < WIDTH_GAME - 1; k++) {
			CELL_GAME[i][k] = ' ';
		}
	}

	//BEHAVE CELL

	//BEHAVE WIDTH
	for(int i = 0; i < WIDTH_BEHAVE - 1; i++) {
		CELL_GAME[(HEIGHT_GAME - 1) - HEIGHT_BEHAVE][i] = CELL_GAME[HEIGHT_GAME - 1][i] = '-';
	}

	//BEHAVE HEIGHT
	for (int i = (HEIGHT_GAME - 1) - HEIGHT_BEHAVE; i < HEIGHT_GAME - 1; i++) {
		CELL_GAME[i][0] = CELL_GAME[i][WIDTH_BEHAVE] = '|';
	}
	//INNER BEHAVE CELL
	for (int i = HEIGHT_GAME - HEIGHT_BEHAVE; i < HEIGHT_GAME - 1; i++) {
		for (int k = 1; k < WIDTH_BEHAVE - 1; k++) {
			CELL_GAME[i][k] = ' ';
		}
	}
}


//게임을 시작하고 캐릭터 생성
void start_game() {

	char submit[1];

	printf("캐릭터 이름을 설정하세요. (숫자포함 영문 최대 17자, 한글 최대 8자) : ");

	scanf_s("%s", character_name, 17);

	printf("\n%s의 직업을 정하기 위해 주사위를 굴립니다.\n\n", character_name);

	Sleep(500);
	
	printf("Rolling the DICE");

	for (int i = 0; i < 6; i++) {
		printf(".");
		Sleep(250);
	}

	printf("\n\n");
	
	player_class = class_rating[DICEROLL(6)];

	switch (player_class) {
		case 1:
			printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
			printf("%s의 직업은 거지 입니다.\n", character_name);
			break;
		case 2:
			printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
			printf("%s의 직업은 성직자 입니다.\n", character_name);
			break;
		case 3:
			printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
			printf("%s의 직업은 목수 입니다.\n", character_name);
			break;
		case 4:
			printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
			printf("%s의 직업은 개장수 입니다.\n", character_name);
			break;
		case 5:
			printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
			printf("%s의 직업은 기사 입니다.\n", character_name);
			break;
		case 6:
			printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
			printf("%s의 직업은 농부 입니다.\n", character_name);
			break;
	}

	printf("\n\n아무거나 입력하여 넘어가기....\n");

	scanf_s("%s", submit, 1);

	printf("\nLoading.");

	for (int i = 0; i < 7; i++) {
		Sleep(400);
		printf(".");
	}
	
	system("cls");

	printf("###초기 스탯을 설정합니다.###\n");

	printf("\n투자할 스탯과 수치을 입력하세요 ( ex) 1 2 )\n(1:힘 2:체력 3:민첩 4:지능 5:운)\n");

	int stat_points = 10;
	int invested_point = 0;
	int select_stat;
	int used_point = 0;
	


	while (invested_point != stat_points) {

		scanf_s("%d %d", &select_stat, &used_point);

		if (invested_point + used_point > stat_points) {
			while (invested_point + used_point > stat_points) {
				printf("!!!WARNING!!!\n!!!stat point overflow!!!");
				Sleep(1000);
				printf("\n다시 입력하세요\n");
				scanf_s("%d %d", &select_stat, &used_point);
			}
		}

		if (select_stat < 1 || select_stat > 5) {
			while (select_stat < 1 || select_stat > 5) {
				printf("!!!WARNING!!!\n!!!stat index error!!!");
				Sleep(1000);
				printf("\n다시 입력하세요\n");
				scanf_s("%d %d", &select_stat, &used_point);
			}
		}

		player_stats[select_stat-1] += used_point;
		invested_point += used_point;
		printf("사용한 포인트 : %d, 잔여 포인트 : %d\n", invested_point, stat_points - invested_point);
	}
	printf("분배 완료\n\n| 힘 : %d | 체력 : %d | 민첩 : %d | 지능 : %d | 행운 : %d |", player_stats[0], player_stats[1], player_stats[2], player_stats[3], player_stats[4]);
}


void LVL_scailing(int player_LVL) {


}

//캐릭터 생존 여부
bool character_alive() {

}




int main(void) {
	srand(time(NULL));

	cell_deployment();
	start_game();
	LVL_scailing(player_LVL);
	while (character_alive()) {

	}

	return 0;
}