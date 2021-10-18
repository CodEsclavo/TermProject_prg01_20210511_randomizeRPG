//����Ʈ ����Į���� RPG

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define HEIGHT_GAME 56
#define WIDTH_GAME 210

#define HEIGHT_TEXT 24
#define WIDTH_TEXT 128

#define HEIGHT_STATS 24
#define WIDTH_STATS 40

#define HEIGHT_BEHAVE 24
#define WIDTH_BEHAVE 210

#define LVLup_stats 3

char CELL_GAME[HEIGHT_GAME][WIDTH_GAME] = { ' ' };

void gotoxy(int, int);

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//��ü���� ���� ȭ�� ��ġ
void cell_deployment() {

	//GAME CELL
	for (int i = 1; i < HEIGHT_GAME - 1; i++) {
		for (int k = 1; k < WIDTH_GAME - 1; k++) {
			CELL_GAME[i][k]= ' ';
		}
	}

	for (int i = 0; i < HEIGHT_GAME; i++) {
		CELL_GAME[i][0] = CELL_GAME[i][WIDTH_GAME - 1] = '|';
	}

	for (int i = 0; i < WIDTH_GAME; i++) {
		CELL_GAME[0][i] = CELL_GAME[HEIGHT_GAME - 1][i] = '-';
	}

	// TEXT CELL

	//TEXT WIDTH
	for (int i = 0; i < WIDTH_TEXT; i++) {
		CELL_GAME[HEIGHT_TEXT - 1][i] = '-';
	}

	//TEXT HEIGHT
	for (int i = 0; i < HEIGHT_TEXT; i++) {
		CELL_GAME[i][WIDTH_TEXT - 1] = '|';
	}
	
	//STATS CELL

	//STATS WIDTH
	for (int i = 0; i < WIDTH_STATS; i++) {
		CELL_GAME[HEIGHT_STATS - 1][(WIDTH_GAME - 1) - WIDTH_STATS + i] = '-';
	}

	//STATS HEIGHT
	for (int i = 0; i < HEIGHT_STATS; i++) {
		CELL_GAME[i][(WIDTH_GAME - 1) - WIDTH_STATS] = '|';
	}

	//BEHAVE CELL

	//BEHAVE WIDTH
	for (int i = 0; i < WIDTH_BEHAVE - 1; i++) {
		CELL_GAME[(HEIGHT_GAME - 1) - HEIGHT_BEHAVE][i] = '-';
	}
}

//�����з�
//1:����,2:������,3:���,4:�����,5:���,6:���
int class_rating[6] = { 1,2,3,4,5,6 };
int player_class;

//1.�� 2.ȭ�� 3.������ 4.���� 5.���
int player_stats[5] = { 1,1,1,1,1 };


struct main_character {
	char name[17];
	int LVL;
	int class;
	int stats[5];
	int HP;
	int money;
} player;

//��ü ������
typedef struct object_build {
	char name[50];
	int LVL;
	int stats[5];
	int HP;
	int money;
} NPC;

//���� ������
struct item_wep {
	char name[50];
	int atk;
	int durability;
	int value;
};

//�� ������
struct item_armr {
	char name[50];
	int def;
	int value;
};

//�Ǿ�ǰ ������
struct item_meds {
	char name[50];
	int heal_amount;
	int value;
};

struct {
	int Weapons[10];
	int Armours[10];
	int Meds[10];
} player_inventory;

void cell_deployment();

int DICEROLL(int);
void DICE_rolling();
void check_N_confirm();
int yes_or_no();

int LVL_scailing(char[], int);
void creat_monster(int);
struct item_wep weapons(int);
struct item_armr armours(int);
struct item_meds medications(int);

int* stat_distribution(int[], int, char[]);
const char* setting_name();
int setting_class(char[]);

void visit_shop();
void meet_monster();
void robbed();
void meet_animal();
void earn_item();

void approach();
void hit_the_road();
void battle();
void display(int, int);


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

	char submit[30];

	printf("\n\n�ƹ��ų� �Է��Ͽ� �Ѿ��....\n");

	scanf_s("%s", submit, 30);

	printf("\nLoading.");

	for (int i = 0; i < 7; i++) {
		Sleep(400);
		printf(".");
	}

	system("cls");
}

int yes_or_no() {
	char choice[2] = { 0 };
	printf("(Y or N)\n");
	scanf_s("%s", &choice,2);

	if (choice[0] == 'Y' || choice[0] == 'y') {
		return 1;
	}

	else {
		return 0;
	}
}


//���� ���� �����ϸ�
int LVL_scailing(char index[20], int player_LVL) {

	int object_LVL;

	if (player_LVL >= 10) {
		object_LVL = rand() % (int)player_LVL * 0.15  + (int)player_LVL * 0.92;
	}
	else {
		object_LVL = rand() % (player_LVL + 1);
	}

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

	if (index == "HP") {
		int object_HP = (10 + object_LVL * 5);
		return object_HP;
	}

	if (index == "money") {
		int money = rand() % (50 + object_LVL * 10);
		return money;
	}

}

//���� ���� ����, ��������
void creat_monster(int player_level) {

	NPC ghoul = {
		"����",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC raider = {
		"���̴�",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC radsquito = {
		"���� ���",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC roach = {
		"�Ŵ����",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC subject = {
		"����ü",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};
}


// ������
struct item_wep weapons(int wepnum) {

	//�����
	if (wepnum == 0) {

		struct item_wep knife = {
		"Į",
		rand() % 10 + 5,
		rand() % 10 + 10,
		25 + (int)knife.atk * 0.8 + knife.durability
		};

		return knife;
	}
	
	else if (wepnum == 1) {

		struct item_wep bat = {
		"�߱���Ʈ",
		rand() % 13 + 12,
		rand() % 12 + 15,
		45 + (int)bat.atk * 0.8 + bat.durability
		};

		return bat;
	}
	
	else if (wepnum == 2) {

		struct item_wep g_club = {
		"����ä",
		rand() % 10 + 15,
		rand() % 13 + 10,
		65 + (int)g_club.atk * 0.8 + g_club.durability
		};

		return g_club;
	}
	
	else if (wepnum == 3) {

		struct item_wep imprv_firearm = {
		"���� �ѱ�",
		rand() % 10 + 25,
		rand() % 5 + 10,
		50 + (int)imprv_firearm.atk * 0.8 + imprv_firearm.durability
		};

		return imprv_firearm;
	}
	
	else if (wepnum == 4) {

		struct item_wep revolver = {
		"������",
		rand() % 20 + 30,
		rand() % 10 + 20,
		150 + (int)revolver.atk * 0.6 + revolver.durability
		};

		return revolver;
	}
	
	else if (wepnum == 5) {

		struct item_wep shotgun = {
		"��ź��",
		rand() % 50 + 50,
		rand() % 5 + 15,
		175 + (int)shotgun.atk * 0.65 + shotgun.durability
		};

		return shotgun;
	}
	
	else if (wepnum == 6) {

		struct item_wep hunting_rifle = {
		"��ɿ� ����",
		rand() % 20 + 70,
		rand() % 20 + 25,
		170 + (int)hunting_rifle.atk * 0.7 + hunting_rifle.durability
		};

		return hunting_rifle;
	}
	
	else if (wepnum == 7) {

		struct item_wep assault_rifle = {
		"���ݼ���",
		rand() % 40 + 100,
		rand() % 10 + 40,
		275 + assault_rifle.durability
		};

		return assault_rifle;
	}
	
	else if (wepnum == 8) {

		struct item_wep railgun = {
		"���ϰ�",
		rand() % 50 + 200,
		rand() % 10 + 20,
		500
		};

		return railgun;
	}
	
	else {

		struct item_wep fat_boy = {
			"�� ����",
			99999,
			1,
			9999
		};

		return fat_boy;
	}
}

struct item_armr armours(int defnum) {

	//����

	if (defnum == 0) {

		struct item_armr rags = {
		"������",
		rand() % 10 + 10,
		30 + (int)rags.def * 0.8
		};

		return rags;
	}
	
	else if (defnum == 1) {

		struct item_armr light_armour = {
		"������ ��",
		rand() % 5 + 15,
		55 + (int)light_armour.def * 0.8
		};

		return light_armour;
	}
	
	else if (defnum == 2) {

		struct item_armr stabprf_vest = {
		"��˺�",
		rand() % 20 + 35,
		70 + (int)stabprf_vest.def * 0.75
		};

		return stabprf_vest;
	}
	
	else if (defnum == 3) {

		struct item_armr bulletprf_vest = {
		"��ź����",
		rand() % 20 + 50,
		120 + (int)bulletprf_vest.def * 0.6
		};

		return bulletprf_vest;
	}
	
	else if (defnum == 4) {

		struct item_armr exo_skel = {
				"���ҽ��̷���",
				500,
				2000
		};

		return exo_skel;
	}
	
	else {

		struct item_armr goliath = {
				"\"�񸮾�\" ��ü��ȭ ��Ʈ",
				9999,
				99999
		};

		return goliath;
	}
}

struct item_meds medications(int mednum) {

	//�Ǿ�ǰ��

	if (mednum == 0) {

		struct item_meds enrgbar = {
		"��������",
		5,
		30
		};

		return enrgbar;
	}

	else if (mednum == 1) {

		struct item_meds bandage = {
		"�ش�",
		15,
		75
		};

		return bandage;
	}

	else if (mednum == 2) {

		struct item_meds painkiller = {
		"������",
		17.5,
		85
		};

		return painkiller;
	}

	else if (mednum == 3) {

		struct item_meds first_aid = {
		"���޻���",
		35,
		155
		};

		return first_aid;
	}

	else {
		struct item_meds survival_kit = {
		"�����̹� ŰƮ",
		55,
		275
		};

		return survival_kit;
	}
}



//���� �й�
int* stat_distribution(int top_stats[5], int point_remain, char player_name[17]) {

	printf("\n������ ���Ȱ� ��ġ�� �Է��ϼ���. (point remain : %d)\n(1:�� 2:ȭ�� 3:������ 4:���� 5:���)\n( ex) 1 2 : �� + 2 )\n", point_remain);

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

		top_stats[select_stat - 1] += used_point;
		invested_point += used_point;
		printf("\n����� ����Ʈ : %d, �ܿ� ����Ʈ : %d\n", invested_point, stat_points - invested_point);
	}

	printf("\n�й� �Ϸ�!\n\n%s�� �ɷ�ġ\n|| �� : %d || ȭ�� : %d || ������ : %d || ���� : %d || ��� : %d ||\n", player_name, top_stats[0], top_stats[1], top_stats[2], top_stats[3], top_stats[4]);

	return top_stats;
}

//������ �����ϰ� ĳ���� ����
const char* setting_name() {

	static char player_name[17] = "\0";

	printf("ĳ���� �̸��� �����ϼ���. (�������� ���� �ִ� 17��, �ѱ� �ִ� 8��) : ");

	scanf_s("%s", player_name, sizeof(player_name));

	return player_name;
}

int setting_class(char player_name[17]) {

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

	return player_class;
}


struct main_character initialize () {

}


//��ī���� ����
void visit_shop() {
	printf("���ݿ� �������� ������ �����Ǿ��ִ�, ������ ���ϴ�\n");
	
}

void meet_monster() {

}

void robbed() {

}

void meet_animal() {

}

//������ ȹ��
void earn_item() {

}



void approach() {

	int encounter_location = rand() % 4 + 1;
	int choice;

	switch (encounter_location) {
	case 1:
		printf("\n�տ� �� �������� �ִ�.\n");
		printf("�ȿ��� ��ô�� ��������\n");
		printf("�ٰ��� ���ðڽ��ϱ�?\n");

		choice = yes_or_no();

		if (choice == 1) {
			

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?\n");

			printf("���� ������ �������� �ڷ���ä ���� �Ű��.\n");

		}

		break;
	case 2:
		printf("\n�տ� �� ��ǹ��� �ִ�.\n");
		printf("�� ���ðڽ��ϱ�?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.\n");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?\n");

			printf("���� ������ ��ǹ��� �ڷ���ä ���� �Ű��.\n");

		}

		break;
	case 3:
		printf("\n�տ� �� ������ �ǹ���/�� �ִ�.\n");
		printf("�� ���ðڽ��ϱ�?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.\n");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?\n");

			printf("���� ������ ������ �ǹ��� �ڷ���ä ���� �Ű��.\n");

		}

		break;
	case 4:
		printf("\n�տ� �� ���� �ִ�.\n");
		printf("�ȿ��� ��ô�� ��������\n");
		printf("�ٰ��� ���ðڽ��ϱ�?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.\n");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?\n");

			printf("���� ������ ���� �ڷ���ä ���� �Ű��.\n");

		}

		break;
	case 5:
		printf("\n�տ� �� ��Ŀ�� �ִ�.\n");
		printf("�� ���ðڽ��ϱ�?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.\n");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?\n");

			printf("���� ������ ��Ŀ�� �ڷ���ä ���� �Ű��.\n");

		}

		break;
	case 6:
		printf("\n�� ��Ÿ��� ���� �ִ�.\n");

		break;
	}
}

void hit_the_road() {

}

void battle() {

}

void display(char p_name[17], int p_HP, int p_stats[5], int p_money) {

	for (int i = 0; i < HEIGHT_GAME; i++) {
		for (int k = 0; k < WIDTH_GAME; k++) {
			printf("%c", CELL_GAME[i][k]);
		}
		printf("\n");
	}
	
	gotoxy(188, 1); printf("STATUS");
	gotoxy(180, 2); printf("Name");
	gotoxy(200, 2); printf("%s", p_name);
	gotoxy(180, 4); printf("HP");
	gotoxy(200, 4); printf("%d", p_HP);
	gotoxy(180, 5); printf("Strength");
	gotoxy(200, 5); printf("%d", p_stats[0]);
	gotoxy(180, 6); printf("Charming");
	gotoxy(200, 6); printf("%d", p_stats[1]);
	gotoxy(180, 7); printf("Endurance");
	gotoxy(200, 7); printf("%d", p_stats[2]);
	gotoxy(180, 8); printf("Intelligence");
	gotoxy(200, 8); printf("%d", p_stats[3]);
	gotoxy(180, 9); printf("Luck");
	gotoxy(200, 9); printf("%d", p_stats[4]);
	gotoxy(180, 10); printf("Money");
	gotoxy(200, 10); printf("%d", p_money);
}

int main(void) {

	srand(time(NULL));

	cell_deployment();

	strcpy_s(player.name, 17, setting_name());

	player.class = setting_class(player.name);

	check_N_confirm();

	printf("###�ʱ� ������ �����մϴ�.###\n");

	* player.stats = stat_distribution(player_stats, 10, player.name);

	check_N_confirm();

	player.LVL = 1;

	player.HP = (50 + player.LVL * 10 + player.stats[2] * 5);
	
	player.money = 100;

	while (player.HP > 0) {

		display(player.name, player.HP, *player.stats, player.money);
		hit_the_road();
		approach();
		system("cls");

	}

	/*
	chapter1_enter(player_class);
	chapter_proceed(player_LVL);
	chapter1_end(player_class);
	*/
	

	return 0;
}