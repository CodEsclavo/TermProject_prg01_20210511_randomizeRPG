//����Ʈ ����Į���� RPG

#define _CRT_SECURE_NO_WARNING

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
/*
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
*/

char player_name[17] = "\0";

//�����з�
//1:����,2:������,3:���,4:�����,5:���,6:���
int class_rating[6] = { 1,2,3,4,5,6 };
int player_class;

//�ʱ� �÷��̾� ����
int player_LVL = 1;

//�ʱ� �÷��̾� ����
//1:�� 2:ȭ�� 3:��ø 4:���� 5:���
int player_stats[5] = { 1,1,1,1,1 };

struct object_build {
	char name[21];
	int LVL;
	int stats[5];
	int money;
	//��ü Ư�� �ο� ����//
};

int DICEROLL(int);
void DICE_rolling();
void check_N_confirm();
int LVL_scailing(char, int);
void cell_deployment();
void stat_distribution(int);
void start_game();
void creat_monster();

bool character_alive();


//�ֻ��� ������
int DICEROLL(int side) {
	int result = rand() % side;
	return result;
}

void DICE_rolling() {

	Sleep(300);

	printf("Rolling the DICE");

	for (int i = 0; i < 6; i++) {
		printf(".");
		Sleep(250);
	}

	printf("\n\n");
}

//������ Ȯ���ϰ� ����
void check_N_confirm() {

	char submit[3];

	printf("\n\n�ƹ��ų� �Է��Ͽ� �Ѿ��....\n");

	scanf_s("%s", submit, 3);

	printf("\nLoading.");

	for (int i = 0; i < 7; i++) {
		Sleep(400);
		printf(".");
	}

	system("cls");
}

//���� ���� �����ϸ�
int LVL_scailing(char index, int player_LVL) {

	int object_LVL = rand() % (player_LVL + 6) - 3;

	if (index == "LVL") {
		return object_LVL;
	}

	if (index == "stats") {

		int stats_draw[5] = { 1,1,1,1,1 };

		for (int i = 1; i < 10 + object_LVL * 3; i++) {
			int stat_index = rand() % 4;
			stats_draw[stat_index]++;
		}

		return stats_draw;
	}

	if (index == "money") {
		int money = rand() % (50 + object_LVL * 10);
		return money;
	}

}

void draw_monster() {

}


//���� ��ī���� ����
void random_encounter(int diceroll) {
	int encounter_slot[1];
}


//��ü���� ���� ȭ�� ��ġ
/*
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
*/


//���� �й�
void stat_distribution(int point_remain) {

	printf("\n������ ���Ȱ� ��ġ�� �Է��ϼ���. (point remain : %d)\n(1:�� 2:ȭ�� 3:��ø 4:���� 5:���)\n( ex) 1 2 : �� + 2 )\n", point_remain);

	int stat_points = point_remain;
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

		player_stats[select_stat - 1] += used_point;
		invested_point += used_point;
		printf("����� ����Ʈ : %d, �ܿ� ����Ʈ : %d\n", invested_point, stat_points - invested_point);
	}

	printf("\n�й� �Ϸ�!\n\n%s�� �ɷ�ġ\n|| �� : %d || ȭ�� : %d || ��ø : %d || ���� : %d || ��� : %d ||", player_name, player_stats[0], player_stats[1], player_stats[2], player_stats[3], player_stats[4]);

}


//������ �����ϰ� ĳ���� ����
void start_game() {

	printf("ĳ���� �̸��� �����ϼ���. (�������� ���� �ִ� 17��, �ѱ� �ִ� 8��) : ");

	scanf_s("%s", player_name, 17);

	printf("\n%s�� ������ ���ϱ� ���� �ֻ����� �����ϴ�.\n\n", player_name);

	player_class = class_rating[DICEROLL(6)];

	DICE_rolling();

	switch (player_class) {
		case 1:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ���� �Դϴ�.\n", player_name);
			break;
		case 2:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ������ �Դϴ�.\n", player_name);
			break;
		case 3:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ��� �Դϴ�.\n", player_name);
			break;
		case 4:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ����� �Դϴ�.\n", player_name);
			break;
		case 5:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ��� �Դϴ�.\n", player_name);
			break;
		case 6:
			printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
			printf("%s�� ������ ��� �Դϴ�.\n", player_name);
			break;
	}

	check_N_confirm();

	printf("###�ʱ� ������ �����մϴ�.###\n");

	stat_distribution(10);

	//���� �Ұ���
	struct object_build player = {
		player_name,
		1,
		player_stats,
		100
	};

}

//���� �������� ��������
void creat_moster() {
	int monster_slot[5];

	struct object_build ghoul = {
		"����",
		LVL_scailing("LVL", player.LVL),
		LVL_scailing("stats", player.LVL),
		LVL_scailing("money", player.LVL)
	};
}

//ĳ���� ���� ����
bool character_alive() {

}




int main(void) {

	srand(time(NULL));

	//cell_deployment();

	start_game();

	chapter1_enter(player_class);
	chapter_proceed(player_LVL);
	chapter1_end(player_class);

	

	return 0;

}