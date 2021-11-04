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

//��ǥ ����
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

// �� ����
void clear_cell() {
	for (int i = 1; i < 23; i++) {
		for (int k = 1; k < 127; k++) {
			printf(" ");
		}
	}
}

//�����з�
//1:����,2:������,3:���,4:�����,5:���,6:���
int player_class;

//1.�� 2.ȭ�� 3.������ 4.���� 5.���
int player_stats[6] = { 0 };

struct main_character {
	char name[17];
	int LVL;
	char class[20];
	int stats[6];
	int HP;
	int money;
} player;

//��ü ������
typedef struct {
	char name[50];
	int LVL;
	int stats[5];
	int HP;
	int money;
} NPC;

//���� ������
typedef struct {
	char name[50];
	int atk;
	int durability;
	int value;
} wep;

//�� ������
typedef struct {
	char name[50];
	int def;
	int value;
} armr;

//�Ǿ�ǰ ������
typedef struct {
	char name[50];
	int heal_amount;
	int value;
} meds;

struct inventory {
	int Weapons[10];
	int Armours[10];
	int Meds[10];
} Inv;
/*
struct equipments {
	wep;
	armr;
} equip;
*/
void cell_deployment();

int DICEROLL(int);
void DICE_rolling();
void check_N_confirm();
int yes_or_no();

int LVL_scailing(char[], int);
NPC creat_monster(int);
wep weapons(int);
armr armours(int);
meds medications(int);

int *stat_distribution(int[], int, char[]);
char* set_name();
char *set_class(char[]);
struct main_character *initialize();

void visit_shop();
void meet_monster();
void robbed();
void meet_animal();
void earn_item();

void approach();
void hit_the_road();
void battle();

int next_behave();
void display(struct main_character);

//�ֻ��� ������
int DICEROLL(int side) {
	int result = rand() % (side - 1) + 1;
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
NPC creat_monster(int player_level) {

	int num = rand() % 4;
	
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

	switch (num) {

	case 0:
		return ghoul;
		break;

	case 1:
		return raider;
		break;

	case 2:
		return radsquito;
		break;

	case 3:
		return roach;
		break;

	case 4:
		return subject;
		break;
	}

}


// ������
wep weapons(int wepnum) {

	//�����
	if (wepnum == 0) {

		wep knife = {
		"Į",
		rand() % 10 + 5,
		rand() % 10 + 10,
		25 + (int)knife.atk * 0.8 + knife.durability
		};

		return knife;
	}
	
	else if (wepnum == 1) {

		wep bat = {
		"�߱���Ʈ",
		rand() % 13 + 12,
		rand() % 12 + 15,
		45 + (int)bat.atk * 0.8 + bat.durability
		};

		return bat;
	}
	
	else if (wepnum == 2) {

		wep g_club = {
		"����ä",
		rand() % 10 + 15,
		rand() % 13 + 10,
		65 + (int)g_club.atk * 0.8 + g_club.durability
		};

		return g_club;
	}
	
	else if (wepnum == 3) {

		wep imprv_firearm = {
		"���� �ѱ�",
		rand() % 10 + 25,
		rand() % 5 + 10,
		50 + (int)imprv_firearm.atk * 0.8 + imprv_firearm.durability
		};

		return imprv_firearm;
	}
	
	else if (wepnum == 4) {

		wep revolver = {
		"������",
		rand() % 20 + 30,
		rand() % 10 + 20,
		150 + (int)revolver.atk * 0.6 + revolver.durability
		};

		return revolver;
	}
	
	else if (wepnum == 5) {

		wep shotgun = {
		"��ź��",
		rand() % 50 + 50,
		rand() % 5 + 15,
		175 + (int)shotgun.atk * 0.65 + shotgun.durability
		};

		return shotgun;
	}
	
	else if (wepnum == 6) {

		wep hunting_rifle = {
		"��ɿ� ����",
		rand() % 20 + 70,
		rand() % 20 + 25,
		170 + (int)hunting_rifle.atk * 0.7 + hunting_rifle.durability
		};

		return hunting_rifle;
	}
	
	else if (wepnum == 7) {

		wep assault_rifle = {
		"���ݼ���",
		rand() % 40 + 100,
		rand() % 10 + 40,
		275 + assault_rifle.durability
		};

		return assault_rifle;
	}
	
	else if (wepnum == 8) {

		wep railgun = {
		"���ϰ�",
		rand() % 50 + 200,
		rand() % 10 + 20,
		500
		};

		return railgun;
	}
	
	else {

		wep fat_boy = {
			"�� ����",
			99999,
			1,
			9999
		};

		return fat_boy;
	}
}

armr armours(int defnum) {

	//����

	if (defnum == 0) {

		armr rags = {
		"������",
		rand() % 10 + 10,
		30 + (int)rags.def * 0.8
		};

		return rags;
	}
	
	else if (defnum == 1) {

		armr light_armour = {
		"������ ��",
		rand() % 5 + 15,
		55 + (int)light_armour.def * 0.8
		};

		return light_armour;
	}
	
	else if (defnum == 2) {

		armr stabprf_vest = {
		"��˺�",
		rand() % 20 + 35,
		70 + (int)stabprf_vest.def * 0.75
		};

		return stabprf_vest;
	}
	
	else if (defnum == 3) {

		armr bulletprf_vest = {
		"��ź����",
		rand() % 20 + 50,
		120 + (int)bulletprf_vest.def * 0.6
		};

		return bulletprf_vest;
	}
	
	else if (defnum == 4) {

		armr exo_skel = {
				"���ҽ��̷���",
				500,
				2000
		};

		return exo_skel;
	}
	
	else {

		armr goliath = {
				"\"�񸮾�\" ��ü��ȭ ��Ʈ",
				9999,
				99999
		};

		return goliath;
	}
}

meds medications(int mednum) {

	//�Ǿ�ǰ��

	if (mednum == 0) {

		meds enrgbar = {
		"��������",
		5,
		30
		};

		return enrgbar;
	}

	else if (mednum == 1) {

		meds bandage = {
		"�ش�",
		15,
		75
		};

		return bandage;
	}

	else if (mednum == 2) {

		meds painkiller = {
		"������",
		17.5,
		85
		};

		return painkiller;
	}

	else if (mednum == 3) {

		meds first_aid = {
		"���޻���",
		35,
		155
		};

		return first_aid;
	}

	else {
		meds survival_kit = {
		"�����̹� ŰƮ",
		55,
		275
		};

		return survival_kit;
	}
}



//���� �й�
int *stat_distribution(int temp_stats[6], int point_remain, char player_name[17]) {

	printf("\n������ ���Ȱ� ��ġ�� �Է��ϼ���. (point remain : %d)\n(1:�� 2:ȭ�� 3:������ 4:���� 5:���)\n( ex) 1 2 : �� + 2 )\n", point_remain);

	*temp_stats = malloc(sizeof(int) * 6);

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

		temp_stats[select_stat] += used_point;
		invested_point += used_point;
		printf("\n����� ����Ʈ : %d, �ܿ� ����Ʈ : %d\n", invested_point, stat_points - invested_point);
	}

	printf("\n�й� �Ϸ�!\n\n%s�� �ɷ�ġ\n|| �� : %d || ȭ�� : %d || ������ : %d || ���� : %d || ��� : %d ||\n", player_name, temp_stats[1], temp_stats[2], temp_stats[3], temp_stats[4], temp_stats[5]);

	return temp_stats;
}

//������ �����ϰ� ĳ���� ����
char* set_name() {

	static char player_name[17] = "\0";

	printf("ĳ���� �̸��� �����ϼ���. (�������� ���� �ִ� 17��, �ѱ� �ִ� 8��) : ");

	scanf_s("%s", player_name, sizeof(player_name));

	return player_name;
}

char* set_class(char player_name[17]) {

	printf("\n%s�� ������ ���ϱ� ���� �ֻ����� �����ϴ�.\n\n", player_name);

	player_class = DICEROLL(6);

	static char array[20] = "\0";

	int* a = &array;

	DICE_rolling();

	switch (player_class) {
	case 1:
		printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
		printf("%s�� ������ ���� �Դϴ�.\n", player_name);
		a = "����";
		break;
	case 2:
		printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
		printf("%s�� ������ ������ �Դϴ�.\n", player_name);
		a = "������";
		break;
	case 3:
		printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
		printf("%s�� ������ ��� �Դϴ�.\n", player_name);
		a = "���";
		break;
	case 4:
		printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
		printf("%s�� ������ ����� �Դϴ�.\n", player_name);
		a = "�����";
		break;
	case 5:
		printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
		printf("%s�� ������ ��� �Դϴ�.\n", player_name);
		a = "���";
		break;
	case 6:
		printf("�ֻ��� %d(��)�� ���Խ��ϴ�.\n\n", player_class);
		printf("%s�� ������ ��� �Դϴ�.\n", player_name);
		a = "���";
		break;
	}

	return array;
}

struct main_character* initialize() {

	struct main_character* temp = malloc(sizeof(struct main_character));

	strcpy_s(temp->name, 17, set_name());

	strcpy_s(temp->class, 20, set_class(temp->name));

	check_N_confirm();

	system("cls");

	printf("###�ʱ� ������ �����մϴ�.###\n");

	for (int i = 0; i < 6; i++) {
		player_stats[i] += 1;
	}

	int *temp_stats = stat_distribution(player_stats, 10, temp->name);

	for (int i = 0; i < 6; i++) {
		temp->stats[i] = temp_stats[i];
	}

	check_N_confirm();

	temp->LVL = 1;

	temp->HP = (50 + temp->LVL * 10 + temp->stats[3] * 5);

	temp->money = 100;

	return temp;
}


void approach() {

	int encounter_location = rand() % 5 + 1;
	int choice;

	switch (encounter_location) {
	case 1:
		gotoxy(1, 1); printf("�տ� �� �������� �ִ�.");
		printf("�ȿ��� ��ô�� ��������");
		printf("�ٰ��� ���ðڽ��ϱ�?");

		choice = yes_or_no();

		if (choice == 1) {


		}

		else {
			printf("������ �Ͻðڽ��ϱ�?");

			printf("���� ������ �������� �ڷ���ä ���� �Ű��.");

		}

		break;
	case 2:
		gotoxy(1, 1); printf("�տ� �� ��ǹ��� �ִ�.");
		printf("�� ���ðڽ��ϱ�?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?");

			printf("���� ������ ��ǹ��� �ڷ���ä ���� �Ű��.");

		}

		break;
	case 3:
		gotoxy(1, 1); printf("�տ� �� ������ �ǹ���/�� �ִ�.");
		printf("�� ���ðڽ��ϱ�?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?");

			printf("���� ������ ������ �ǹ��� �ڷ���ä ���� �Ű��.");

		}

		break;
	case 4:
		gotoxy(1, 1);	printf("�տ� �� ���� �ִ�.");
		printf("�ȿ��� ��ô�� ��������");
		printf("�ٰ��� ���ðڽ��ϱ�?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?");

			printf("���� ������ ���� �ڷ���ä ���� �Ű��.");

		}

		break;
	case 5:
		gotoxy(1, 1); printf("�տ� �� ��Ŀ�� �ִ�.");
		printf("�� ���ðڽ��ϱ�?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("������ �ٰ������� �α�ô�� ��������.");

		}

		else {
			printf("������ �Ͻðڽ��ϱ�?");

			printf("���� ������ ��Ŀ�� �ڷ���ä ���� �Ű��.");

		}

		break;
	case 6:
		gotoxy(1, 1); printf("�� ��Ÿ��� ���� �ִ�.");

		break;
	}
}

void hit_the_road() {

	int rslt = DICEROLL(2);

	if (rslt == 1) {
		gotoxy(1, 21); printf("���� ���� ��.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
	}

	else {
		gotoxy(1, 21); printf("���� �� ���� ������.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
	}

	for (int i = 0; i < 6; i++) {
		printf(".");
		Sleep(300);
	}

	clear_cell();
} 

void battle(struct main_character temp) {

	NPC monster = creat_monster(temp.LVL);

}

//��ī���� ����
void visit_shop() {
	gotoxy(10, 1); printf("���ݿ� �������� ������ �����Ǿ��ִ�, ������ ���ϴ�\n");
	
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

int next_behave() {

	int X;

	gotoxy(10, 1); printf("���� �Ͻðڽ��ϱ�?\n");
	gotoxy(10, 3); printf("1. �� �� ����");
	gotoxy(10, 4); printf("2. ����ǰ Ȯ��");
	gotoxy(10, 5); printf("3. �޽��ϱ�");
	gotoxy(10, 6); printf("4. �����ϱ�");

	gotoxy(10, 8); scanf_s("%d", &X);

	while (X != 1 && X != 2 && X != 3 && X != 4) {

		for (int i = 0; i < 8; i++) {
			for (int k = 1; k < 50; k++) {
					gotoxy(k, i); printf(" ");
			}
		}

		gotoxy(10, 1); printf("!!ERROR!! �ٽ� �Է��ϼ���");
		Sleep(3000);

		for (int k = 1; k < 50; k++) {
			gotoxy(k, 1); printf(" ");
		}

		gotoxy(10, 1); printf("���� �Ͻðڽ��ϱ�?\n");
		gotoxy(10, 3); printf("1. �� �� ����");
		gotoxy(10, 4); printf("2. ����ǰ Ȯ��");
		gotoxy(10, 5); printf("3. �޽��ϱ�");
		gotoxy(10, 6); printf("4. �����ϱ�");

		gotoxy(10, 8); scanf_s("%d", &X);
		
	}

	

	for (int i = 1; i < 8; i++) {
		for (int k = 1; k < 50; k++) {
			gotoxy(k, i); printf(" ");
		}
	}

	return X;

}

void player_action() {

	int temp = next_behave();

	switch (temp) {
	case 1: 
		hit_the_road();
		approach();
		break;

	case 2:

		break;

	case 3:
		gotoxy(10, 1); printf("�޽���.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
		printf("50�� ü���� ȸ���߽��ϴ�.");
		player.HP += 50;
		check_N_confirm();
		clear_cell();
		break;

	case 4:
		printf("������ �����Ͻðڽ��ϱ�?");
		int close = yes_or_no();

		if (close == 1) {
			exit(0);
		}

		else {

		}

		break;
	}
}

void display(struct main_character *temp) {

	for (int i = 0; i < HEIGHT_GAME; i++) {
		for (int k = 0; k < WIDTH_GAME; k++) {
			printf("%c", CELL_GAME[i][k]);
		}
		printf("\n");
	}
	
	gotoxy(188, 1); printf("STATUS");
	gotoxy(185, 5); printf("Name");
	gotoxy(195, 5); printf("%s", temp->name);
	gotoxy(185, 6); printf("Class");
	gotoxy(195, 6); printf("%s", temp->class);
	gotoxy(180, 9); printf("HP");
	gotoxy(195, 9); printf("%d/%d", temp->HP, 50 + temp->LVL * 10 + temp->stats[3] * 5);
	gotoxy(180, 10); printf("Strength");
	gotoxy(195, 10); printf("%d", temp->stats[1]);
	gotoxy(180, 11); printf("Charming");
	gotoxy(195, 11); printf("%d", temp->stats[2]);
	gotoxy(180, 12); printf("Endurance");
	gotoxy(195, 12); printf("%d", temp->stats[3]);
	gotoxy(180, 13); printf("Intelligence");
	gotoxy(195, 13); printf("%d", temp->stats[4]);
	gotoxy(180, 14); printf("Luck");
	gotoxy(195, 14); printf("%d", temp->stats[5]);
	gotoxy(180, 15); printf("Money");
	gotoxy(195, 15); printf("%d", temp->money);

}

int main(void) {

	srand(time(NULL));

	printf("��üȭ�� �÷��̸� �����մϴ�.\n");
	printf("���� ���۱���\n");

	for (int i = 5; i > 0; i--) {
		gotoxy(0, 3); printf("%d", i);
		Sleep(1000);
	}

	system("cls");

	cell_deployment();

	struct main_character *player = initialize();

	while (player->HP > 0) {

		display(player);
		player_action();
		system("cls");

	}

	return 0;
}