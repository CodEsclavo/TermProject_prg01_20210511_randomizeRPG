//����Ʈ ����Į���� RPG

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>

//���� ������ ũ��
#define HEIGHT_GAME 56
#define WIDTH_GAME 210

#define HEIGHT_TEXT 24
#define WIDTH_TEXT 128

#define HEIGHT_STATS 24
#define WIDTH_STATS 40

#define HEIGHT_BEHAVE 24
#define WIDTH_BEHAVE 210

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
			gotoxy(k, i); printf(" ");
		}
	}

	for (int n = 33; n < 55; n++) {
		for (int l = 1; l < 209; l++) {
			gotoxy(l, n); printf(" ");
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
	int HP;
	int Distance;
};

struct NPC {
	char name[50];
	int LVL;
	int HP;
};

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
void confirm() {

	gotoxy(5, 33); printf("���͸� �Է��Ͽ� �Ѿ��....");

	gotoxy(5, 34); char submit = _getch();

	if (submit == "\r") {

		gotoxy(5, 36); printf("Loading.");

		for (int i = 0; i < 7; i++) {
			Sleep(400);
			printf(".");
		}
	}
}

int yes_or_no() {
	char choice[2] = { 0 };
	gotoxy(10, 33); printf("(Y or N)");
	gotoxy(10, 34); scanf_s("%s", &choice,2);

	if (choice[0] == 'Y' || choice[0] == 'y') {
		return 1;
	}

	else {
		return 0;
	}
}


// ������
wep* weapons(int wepnum) {

	//�����
	
	if (wepnum == 0) {

		wep knife = {
		"Į",
		rand() % 10 + 5,
		rand() % 10 + 10,
		25 + (int)knife.atk * 0.8 + knife.durability
		};

		wep* knife_p = &knife;

		return knife_p;
	}
	
	else if (wepnum == 1) {

		wep bat = {
		"�߱���Ʈ",
		rand() % 13 + 12,
		rand() % 12 + 15,
		45 + (int)bat.atk * 0.8 + bat.durability
		};

		wep* bat_p = &bat;

		return bat_p;
	}
	
	else if (wepnum == 2) {

		wep g_club = {
		"����ä",
		rand() % 10 + 15,
		rand() % 13 + 10,
		65 + (int)g_club.atk * 0.8 + g_club.durability
		};

		wep* g_club_p = &g_club;

		return g_club_p;
	}
	
	else if (wepnum == 3) {

		wep imprv_firearm = {
		"���� �ѱ�",
		rand() % 10 + 25,
		rand() % 5 + 10,
		50 + (int)imprv_firearm.atk * 0.8 + imprv_firearm.durability
		};

		wep* imprv_firearm_p = &imprv_firearm;

		return imprv_firearm_p;
	}
	
	else if (wepnum == 4) {

		wep revolver = {
		"������",
		rand() % 20 + 30,
		rand() % 10 + 20,
		150 + (int)revolver.atk * 0.6 + revolver.durability
		};
		wep* revolver_p = &revolver;

		return revolver_p;
	}
	
	else if (wepnum == 5) {

		wep shotgun = {
		"��ź��",
		rand() % 50 + 50,
		rand() % 5 + 15,
		175 + (int)shotgun.atk * 0.65 + shotgun.durability
		};

		wep* shotgun_p = &shotgun;

		return shotgun_p;
	}
	
	else if (wepnum == 6) {

		wep hunting_rifle = {
		"��ɿ� ����",
		rand() % 20 + 70,
		rand() % 20 + 25,
		170 + (int)hunting_rifle.atk * 0.7 + hunting_rifle.durability
		};

		wep* hunting_rifle_p = &hunting_rifle;

		return hunting_rifle_p;
	}
	
	else if (wepnum == 7) {

		wep assault_rifle = {
		"���ݼ���",
		rand() % 40 + 100,
		rand() % 10 + 40,
		275 + assault_rifle.durability
		};

		wep* assault_rifle_p = &assault_rifle;

		return assault_rifle_p;
	}
	
	else if (wepnum == 8) {

		wep railgun = {
		"���ϰ�",
		rand() % 50 + 200,
		rand() % 10 + 20,
		500
		};

		wep* railgun_p = &railgun;

		return railgun_p;
	}

	else {
		wep fist = {
			"�ָ�",
			5,
			99999,
			0
		};
		wep* fist_p = &fist;
		return fist_p;
	}

}

armr* armours(int defnum) {

	//����

	if (defnum == 0) {

		armr rags = {
		"������",
		rand() % 10 + 10,
		30 + (int)rags.def * 0.8
		};

		armr* rags_p = &rags;

		return rags_p;
	}
	
	else if (defnum == 1) {

		armr light_armour = {
		"������ ��",
		rand() % 5 + 15,
		55 + (int)light_armour.def * 0.8
		};

		armr* light_armour_p = &light_armour;

		return light_armour_p;
	}
	
	else if (defnum == 2) {

		armr stabprf_vest = {
		"��˺�",
		rand() % 20 + 35,
		70 + (int)stabprf_vest.def * 0.75
		};

		armr* stabprf_vest_p = &stabprf_vest;

		return stabprf_vest_p;
	}
	
	else if (defnum == 3) {

		armr bulletprf_vest = {
		"��ź����",
		rand() % 20 + 50,
		120 + (int)bulletprf_vest.def * 0.6
		};

		armr* bulletprf_vest_p = &bulletprf_vest;

		return bulletprf_vest_p;
	}
	
	else if (defnum == 4) {

		armr exo_skeleton = {
				"���ҽ��̷���",
				500,
				2000
		};

		armr* exo_skeleton_p = &exo_skeleton;

		return exo_skeleton_p;
	}

}

//������ �����ϰ� ĳ���� ����
char* set_name() {

	static char player_name[17] = "\0";

	printf("ĳ���� �̸��� �����ϼ���. (�������� ���� �ִ� 17��, �ѱ� �ִ� 8��) : ");

	scanf_s("%s", player_name, sizeof(player_name));

	return player_name;
}

struct main_character* initialize() {

	struct main_character* temp = malloc(sizeof(struct main_character));

	strcpy(temp->name, set_name());

	confirm();

	system("cls");

	temp->Distance = 137;

	temp->HP = 50 + (137 - temp->Distance) * 5;

	return temp;

}

void hit_the_road() {

	int rslt = DICEROLL(2);

	if (rslt == 1) {
		gotoxy(10, 21); printf("���� ���� ��.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
	}

	else {
		gotoxy(10, 21); printf("���� �� ���� ������.");
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

void battle(struct main_character* player) {

	char monster[20];

	int num = rand() % 4;

	switch (num) {

	case 0:
		strcpy(monster, "����");
		break;

	case 1:
		strcpy(monster, "���̴�");
		break;

	case 2:
		strcpy(monster, "�Ŵ����");
		break;

	case 3:
		strcpy(monster, "����ü");
		break;

	case 4:
		strcpy(monster, "���� ���");
		break;
	}

	int monster_HP = rand() % 300 + (137 - player->Distance);

	int monster_atk = rand() % 30;

	clear_cell();

	gotoxy(10, 1); printf("%s��/�� ��Ÿ����.", monster);

	confirm();

	clear_cell();

	int select;

	int use_num;

	while (TRUE) {

		gotoxy(10, 1); printf("�ָӴ� ������ ��");
		for (int i = 0; i < 5; i++) {
			printf(". ");
			Sleep(100);
		}

		wep weapon = *weapons(DICEROLL(9));

		gotoxy(10, 2); printf("��������: %s", weapon.name);

		armr armour = *armours(DICEROLL(4));

		gotoxy(10, 3); printf("������: %s", armour.name);

		confirm();

		clear_cell();

		gotoxy(10, 2); printf("���� �Ͻðڽ��ϱ�?");

		gotoxy(10, 3); printf("1. �����ϱ� 2. ����ϱ� 2. ��������");

		gotoxy(10, 34); scanf_s("%d", &select);

		clear_cell();

		if (select == 1) {

			gotoxy(10, 1); printf("%s�� ����, %d�� ���ظ� ������", player->name, weapon.atk);

			if (monster_atk - armour.def <= 0) {
				gotoxy(10, 3); printf("%s�� ����, 0�� ���ظ� �޾Ҵ�", monster);
			}

			else {
				gotoxy(10, 3); printf("%s�� ����, %d�� ���ظ� �޾Ҵ�", monster, monster_atk - armour.def);
				player->HP -= (monster_atk - armour.def);
			}

			monster_HP -= ((137 - player->Distance) * 5 + weapon.atk);

			gotoxy(50, 7); printf("%s�� ü��: %d", monster, monster_HP);

			gotoxy(195, 9); printf("%d/%d", player->HP, 50 + (137 - player->Distance));

			confirm();

			clear_cell();

			if (player->HP <= 0 || monster_HP <= 0) {
				break;
			}
		}

		else if (select == 2) {
			clear_cell();
			gotoxy(10, 3); printf("%s�� ����, %d�� ���ظ� �޾Ҵ�", monster, rand() % 20);
			gotoxy(50, 7); printf("%s�� ü��: %d", monster, monster_HP);
			confirm();
			if (player->HP <= 0 || monster_HP <= 0) {
				break;
			}
			clear_cell();
		}

		else {
			gotoxy(10, 1); printf("%s��/�� �ڷ���ä �����ƴ�", monster);
			confirm();
			break;
		}
	}

	if (player->HP <= 0) {

		clear_cell();

		gotoxy(10, 1); printf("!!!%s�� ����߽��ϴ�!!!", player->name);

		gotoxy(10, 2); printf("GAME OVER");

		confirm();

		system("cls");

		exit(0);
	}

	else {
		clear_cell();
		gotoxy(10, 1); printf("%s�� �����ƴ�", monster);
		confirm();
		player->Distance -= rand() % 3 + 1;
	}
}

//��ī���� ����

void meet_monster(struct main_character* player) {

	battle(player);
}

void robbed(struct main_character* player) {

	struct NPC robber = {
		"����",
		rand() % 10 - 5 + (137 - player->Distance),
		rand() % 300 + (137 - player->Distance) * 15
	};

	clear_cell();

	gotoxy(10, 1); printf("Ǯ������ %s��/�� ��Ÿ����.", robber.name);

	confirm();

	clear_cell();

	int select;

	int use_num;

	while (TRUE) {

		gotoxy(10, 1); printf("�ָӴ� ������ ��");
		for (int i = 0; i < 5; i++) {
			printf(". ");
			Sleep(100);
		}

		wep weapon = *weapons(DICEROLL(9));

		gotoxy(10, 2); printf("��������: %s", weapon.name);

		armr armour = *armours(DICEROLL(4));

		gotoxy(10, 3); printf("������: %s", armour.name);

		confirm();

		clear_cell();

		gotoxy(10, 2); printf("���� �Ͻðڽ��ϱ�?");

		gotoxy(10, 3); printf("1. �����ϱ� 2. ����ϱ� 2. ��������");

		gotoxy(10, 34); scanf_s("%d", &select);

		clear_cell();

		if (select == 1) {

			gotoxy(10, 1); printf("%s�� ����, %d�� ���ظ� ������", player->name, weapon.atk);

			if (robber.LVL * 5 - armour.def <= 0) {
				gotoxy(10, 3); printf("%s�� ����, 0�� ���ظ� �޾Ҵ�", robber.name);
			}

			else {
				gotoxy(10, 3); printf("%s�� ����, %d�� ���ظ� �޾Ҵ�", robber.name, robber.LVL * 5 - armour.def);
				player->HP -= (robber.LVL * 5 - armour.def);
			}

			robber.HP -= ((137 - player->Distance) + weapon.atk);

			gotoxy(50, 3); printf("������ ü��: %d", robber.HP);

			gotoxy(195, 9); printf("%d/%d", player->HP, 50 + (137 - player->Distance) * 5);

			confirm();

			clear_cell();
			if (player->HP <= 0 || robber.HP <= 0) {
				break;
			}
		}

		else if (select == 2) {
			clear_cell();
			gotoxy(10, 3); printf("%s�� ����, %d�� ���ظ� �޾Ҵ�", robber.name, rand() % 20);
			gotoxy(50, 3); printf("������ ü��: %d", robber.HP);
			confirm();
			clear_cell();
			if (player->HP <= 0 || robber.HP <= 0) {
				break;
			}
		}

		else {
			gotoxy(10, 1); printf("%s��/�� �ڷ���ä �����ƴ�", robber.name);
			confirm();
			break;
		}
	}

	if (player->HP <= 0) {

		clear_cell();

		gotoxy(10, 1); printf("!!!%s�� ����߽��ϴ�!!!", player->name);

		gotoxy(10, 2); printf("GAME OVER");

		confirm();

		system("cls");

		exit(0);
	}

	else if (robber.HP <= 0) {
		clear_cell();
		gotoxy(10, 1); printf("%s�� �����ƴ�", robber.name);
		confirm();
		player->Distance -= rand() % 3 + 1;
	}
}

void sleeping(struct main_character* player) {
	gotoxy(10, 1); printf("������ �������� ����ϴ�, ���ڸ��δ� �ȼ������ΰŰ���");
	gotoxy(10, 2); printf("�޽��Ͻðڽ��ϱ�?");
	int choice;

	choice = yes_or_no();

	clear_cell();

	if (choice == 1) {
		player->HP += 100;
		gotoxy(10, 1); printf("ǫ ����� ����� ��ģ��");
		confirm();
		clear_cell();
	}

	else {
		player->Distance--;
		gotoxy(10, 1); printf("�޽��ϱ⿣ ���� �����帥��");
		confirm();
		clear_cell();
	}
}

void approach(struct main_character* player) {

	int encounter_location = rand() % 100;
	int choice;

	if (encounter_location >= 1 && encounter_location <= 50) {
		gotoxy(10, 1); printf("�տ� �� �������� �ִ�. �ȿ��� ��ô�� ��������.");
		gotoxy(10, 2); printf("�ٰ��� ���ðڽ��ϱ�?");

		int encounter;

		choice = yes_or_no();

		if (choice == 1) {

			clear_cell();

			encounter = DICEROLL(3);

			switch (encounter) {
			case 1:
				meet_monster(player);
				break;
			case 2:
				robbed(player);
				break;
			case 3:
				sleeping(player);
				break;
			}

		}

		else {
			clear_cell();
			gotoxy(10, 1); printf("������ �������� �ڷ���ä ���� ������");
			confirm();
		}
	}

	else if (encounter_location > 50 && encounter_location <= 75) {
		gotoxy(10, 1); printf("�տ� �� ��ǹ��� �ִ�.");
		gotoxy(10, 2); printf("�� ���ðڽ��ϱ�?");

		int encounter;

		choice = yes_or_no();

		if (choice == 1) {

			clear_cell();

			encounter = DICEROLL(3);

			switch (encounter) {
			case 1:
				meet_monster(player);
				break;
			case 2:
				robbed(player);
				break;
			case 3:
				sleeping(player);
				break;
			}
		}

		else {
			clear_cell();
			gotoxy(10, 1); printf("������ ��ǹ��� �ڷ���ä ���� ������");
			confirm();
		}
	}

	else if (encounter_location == 100) {
		gotoxy(10, 1); printf("�氡�� ������ ���ͼ��Ͱ� ���ִ�");
		gotoxy(10, 2); printf("������ �����ðڽ��ϱ�?");
		choice = yes_or_no();

		clear_cell();

		if (choice == 1) {
			int hitch;
			gotoxy(10, 1); printf("������ ������ ���� ���࿡�� �� �ڶ��� �þ���� �ִ�, ��� �Ͻðڽ��ϱ�?");
			gotoxy(10, 2); printf("1.���� �¿��޶�� ��Ź�Ѵ� 2.���� ���Ѵ´� 3.�׳� ����");
			gotoxy(10, 34); scanf_s("%d", &hitch);
			clear_cell();

			if (hitch == 1 || hitch == 2) {
				gotoxy(10, 1); printf("�� ���п� ���� �̵��� �� �־���");
				confirm();
			}

			else {
				gotoxy(10, 1); printf("���� �ڷ��ϰ� ���� ������");
				confirm();
			}
		}

		else {
			clear_cell();
			gotoxy(10, 1); printf("���� �ڷ��ϰ� ���� ������");
			confirm();
		}

		player->Distance -= rand() % 3 + 1;
	}

	else {

		gotoxy(10, 1);	printf("�տ� �� ���� �ִ�.");
		printf(" �ȿ��� ��ô�� ��������");
		gotoxy(10, 2); printf("�ٰ��� ���ðڽ��ϱ�?");

		int encounter;

		choice = yes_or_no();

		if (choice == 1) {

			clear_cell();

			encounter = DICEROLL(3);

			switch (encounter) {
			case 1:
				meet_monster(player);
				break;
			case 2:
				robbed(player);
				break;
			case 3:
				sleeping(player);
				break;
			}
		}

		else {
			clear_cell();
			gotoxy(10, 1); printf("���� �ڷ���ä ���� ������");
			confirm();
		}
	}
}

int next_behave() {

	int X;

	gotoxy(10, 1); printf("���� �Ͻðڽ��ϱ�?");
	gotoxy(10, 3); printf("1. �� �� ����");
	gotoxy(10, 4); printf("2. �޽��ϱ�");
	gotoxy(10, 6); printf("3. �����ϱ�");

	gotoxy(10, 8); scanf_s("%d", &X);

	while (X != 1 && X != 2 && X != 3 && X != 4) {

		clear_cell();

		gotoxy(10, 1); printf("!!ERROR!! �ٽ� �Է��ϼ���");
		Sleep(3000);

		for (int k = 1; k < 50; k++) {
			gotoxy(k, 1); printf(" ");
		}

		gotoxy(10, 1); printf("���� �Ͻðڽ��ϱ�?");
		gotoxy(10, 3); printf("1. �� �� ����");
		gotoxy(10, 4); printf("2. �޽��ϱ�");
		gotoxy(10, 6); printf("3. �����ϱ�");

		gotoxy(10, 8); scanf_s("%d", &X);
		
	}

	clear_cell();

	return X;

}

void player_action(struct main_character* player) {

	int running = TRUE;

	while (running) {

		int temp = next_behave();

		if (temp == 1) {
			hit_the_road();
			approach(player);
			break;
		}

		else if (temp == 2) {
			clear_cell();
			gotoxy(10, 1); printf("�޽���.");
			for (int i = 0; i < 7; i++) {
				Sleep(250);
				printf(".");
			}

			if (player->HP + 50 > (137 - player->Distance) * 5) {
				player->HP = 50 + (137 - player->Distance) * 5;
			}

			gotoxy(10, 2); printf("50�� ü���� ȸ���߽��ϴ�.");
			player->HP += 50;
			confirm();
			clear_cell();
			break;
		}

		else {

			printf("������ �����Ͻðڽ��ϱ�?");
			int close = yes_or_no();

			if (close == 1) {
				system("cls");
				exit(0);
			}

			else {
				clear_cell();
				continue;
			}

			break;
		}
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
	gotoxy(180, 9); printf("HP");
	gotoxy(195, 9); printf("%d/%d", temp->HP, 50 + (137 - temp->Distance) * 5);
	gotoxy(180, 12); printf("Distance");
	gotoxy(195, 12); printf("%d", temp->Distance);

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

	struct main_character player = *initialize();

	system("cls");

	printf("20xx��, ����� ���� �ұ濡 �۽ο���\n");
	Sleep(500);
	printf("�ٴٴ� ������ ���� ������ ��� ����ü�� ����� �� �Ͽ���. ������, �η��� ������� �ʾҴ�!\n");
	Sleep(1000);
	printf("���������� Ȳ��ȭ�� ���迡�� ������� �Ϻδ� ����ȭ�� ���¿� �ﴭ�� ��ư��� �ִ�.\n");
	Sleep(800);
	printf("�� ���迡�� ������ �������� ��ȭ���� %s ��/�� �������� ������ ���빮������ ���� ������ �������Ѵ�.........", player.name);
	Sleep(1000);

	confirm();

	system("cls");

	while (&player.HP > 0) {

		display(&player);
		player_action(&player);
		if (player.HP > 50 + (137 - player.Distance) * 5) {
			player.HP = 50 + (137 - player.Distance) * 5;
		}
		if (player.Distance == 0) {
			system("cls");
			printf("���� %s�� ���빮���忡 �����ߴ�.", player.name);
			Sleep(1000);
			printf("������ ���빮���嵵 ���� �ұ��� ���� ���� ������ ����̴�.");
			Sleep(1000);
			printf("�����ٴϴ� ���ص��� �����ٺ��� �� ���̷� ���ִ� %s���� �� � �����̳� ������ ǥ���̶�� ã�ƺ� �� ������.", player.name);
			Sleep(1000);
			printf("������ ���� ��½�̴� ������ �ϰ� �Ŵ��� ����� ���� �������� �߰����� �Ű��...................");

			confirm();
			system("cls");

			printf("�÷������ּż� �����մϴ�");
			confirm();

			exit(0);
		}
		player.Distance--;
		system("cls");
	}
	return 0;
}