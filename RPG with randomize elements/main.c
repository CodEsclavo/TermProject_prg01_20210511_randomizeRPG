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

//�����з�
//1:����,2:������,3:���,4:�����,5:���,6:���
int class_rating[6] = { 1,2,3,4,5,6 };
int player_class;

//�ʱ� �÷��̾� ����
int player_LVL = 1;

//�ʱ� �÷��̾� ����
//1:�� 2:ü�� 3:��ø 4:���� 5:��
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

//��ü���� ���� ȭ�� ��ġ
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


//������ �����ϰ� ĳ���� ����
void start_game() {

	char submit[1];

	printf("ĳ���� �̸��� �����ϼ���. (�������� ���� �ִ� 17��, �ѱ� �ִ� 8��) : ");

	scanf_s("%s", character_name, 17);

	printf("\n%s�� ������ ���ϱ� ���� �ֻ����� �����ϴ�.\n\n", character_name);

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
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ���� �Դϴ�.\n", character_name);
			break;
		case 2:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ������ �Դϴ�.\n", character_name);
			break;
		case 3:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ��� �Դϴ�.\n", character_name);
			break;
		case 4:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ����� �Դϴ�.\n", character_name);
			break;
		case 5:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ��� �Դϴ�.\n", character_name);
			break;
		case 6:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ��� �Դϴ�.\n", character_name);
			break;
	}

	printf("\n\n�ƹ��ų� �Է��Ͽ� �Ѿ��....\n");

	scanf_s("%s", submit, 1);

	printf("\nLoading.");

	for (int i = 0; i < 7; i++) {
		Sleep(400);
		printf(".");
	}
	
	system("cls");

	printf("###�ʱ� ������ �����մϴ�.###\n");

	printf("\n������ ���Ȱ� ��ġ�� �Է��ϼ��� ( ex) 1 2 )\n(1:�� 2:ü�� 3:��ø 4:���� 5:��)\n");

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
				printf("\n�ٽ� �Է��ϼ���\n");
				scanf_s("%d %d", &select_stat, &used_point);
			}
		}

		if (select_stat < 1 || select_stat > 5) {
			while (select_stat < 1 || select_stat > 5) {
				printf("!!!WARNING!!!\n!!!stat index error!!!");
				Sleep(1000);
				printf("\n�ٽ� �Է��ϼ���\n");
				scanf_s("%d %d", &select_stat, &used_point);
			}
		}

		player_stats[select_stat-1] += used_point;
		invested_point += used_point;
		printf("����� ����Ʈ : %d, �ܿ� ����Ʈ : %d\n", invested_point, stat_points - invested_point);
	}
	printf("�й� �Ϸ�\n\n| �� : %d | ü�� : %d | ��ø : %d | ���� : %d | ��� : %d |", player_stats[0], player_stats[1], player_stats[2], player_stats[3], player_stats[4]);
}


void LVL_scailing(int player_LVL) {


}

//ĳ���� ���� ����
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