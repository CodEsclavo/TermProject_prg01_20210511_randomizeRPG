//포스트 아포칼립스 RPG

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

//좌표 지정
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//전체적인 게임 화면 배치
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

// 셀 정리
void clear_cell() {
	for (int i = 1; i < 23; i++) {
		for (int k = 1; k < 127; k++) {
			printf(" ");
		}
	}
}

//직업분류
//1:거지,2:성직자,3:목수,4:개장수,5:기사,6:농부
int player_class;

//1.힘 2.화술 3.지구력 4.지능 5.행운
int player_stats[6] = { 0 };

struct main_character {
	char name[17];
	int LVL;
	char class[20];
	int stats[6];
	int HP;
	int money;
} player;

//개체 프리셋
typedef struct {
	char name[50];
	int LVL;
	int stats[5];
	int HP;
	int money;
} NPC;

//무기 프리셋
typedef struct {
	char name[50];
	int atk;
	int durability;
	int value;
} wep;

//방어구 프리셋
typedef struct {
	char name[50];
	int def;
	int value;
} armr;

//의약품 프리셋
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

//주사위 굴리기
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

//사항을 확인하고 결정
void check_N_confirm() {

	char submit[30];

	printf("\n\n아무거나 입력하여 넘어가기....\n");

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


//몬스터 레벨 스케일링
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

//몬스터 종류 선언, 랜덤생성
NPC creat_monster(int player_level) {

	int num = rand() % 4;
	
	NPC ghoul = {
		"구울",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC raider = {
		"레이더",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC radsquito = {
		"방사능 모기",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC roach = {
		"거대바퀴",
		LVL_scailing("LVL", player_level),
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	NPC subject = {
		"실험체",
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


// 아이템
wep weapons(int wepnum) {

	//무기류
	if (wepnum == 0) {

		wep knife = {
		"칼",
		rand() % 10 + 5,
		rand() % 10 + 10,
		25 + (int)knife.atk * 0.8 + knife.durability
		};

		return knife;
	}
	
	else if (wepnum == 1) {

		wep bat = {
		"야구배트",
		rand() % 13 + 12,
		rand() % 12 + 15,
		45 + (int)bat.atk * 0.8 + bat.durability
		};

		return bat;
	}
	
	else if (wepnum == 2) {

		wep g_club = {
		"골프채",
		rand() % 10 + 15,
		rand() % 13 + 10,
		65 + (int)g_club.atk * 0.8 + g_club.durability
		};

		return g_club;
	}
	
	else if (wepnum == 3) {

		wep imprv_firearm = {
		"급조 총기",
		rand() % 10 + 25,
		rand() % 5 + 10,
		50 + (int)imprv_firearm.atk * 0.8 + imprv_firearm.durability
		};

		return imprv_firearm;
	}
	
	else if (wepnum == 4) {

		wep revolver = {
		"리볼버",
		rand() % 20 + 30,
		rand() % 10 + 20,
		150 + (int)revolver.atk * 0.6 + revolver.durability
		};

		return revolver;
	}
	
	else if (wepnum == 5) {

		wep shotgun = {
		"산탄총",
		rand() % 50 + 50,
		rand() % 5 + 15,
		175 + (int)shotgun.atk * 0.65 + shotgun.durability
		};

		return shotgun;
	}
	
	else if (wepnum == 6) {

		wep hunting_rifle = {
		"사냥용 소총",
		rand() % 20 + 70,
		rand() % 20 + 25,
		170 + (int)hunting_rifle.atk * 0.7 + hunting_rifle.durability
		};

		return hunting_rifle;
	}
	
	else if (wepnum == 7) {

		wep assault_rifle = {
		"돌격소총",
		rand() % 40 + 100,
		rand() % 10 + 40,
		275 + assault_rifle.durability
		};

		return assault_rifle;
	}
	
	else if (wepnum == 8) {

		wep railgun = {
		"레일건",
		rand() % 50 + 200,
		rand() % 10 + 20,
		500
		};

		return railgun;
	}
	
	else {

		wep fat_boy = {
			"팻 보이",
			99999,
			1,
			9999
		};

		return fat_boy;
	}
}

armr armours(int defnum) {

	//방어구류

	if (defnum == 0) {

		armr rags = {
		"누더기",
		rand() % 10 + 10,
		30 + (int)rags.def * 0.8
		};

		return rags;
	}
	
	else if (defnum == 1) {

		armr light_armour = {
		"가벼운 방어구",
		rand() % 5 + 15,
		55 + (int)light_armour.def * 0.8
		};

		return light_armour;
	}
	
	else if (defnum == 2) {

		armr stabprf_vest = {
		"방검복",
		rand() % 20 + 35,
		70 + (int)stabprf_vest.def * 0.75
		};

		return stabprf_vest;
	}
	
	else if (defnum == 3) {

		armr bulletprf_vest = {
		"방탄조끼",
		rand() % 20 + 50,
		120 + (int)bulletprf_vest.def * 0.6
		};

		return bulletprf_vest;
	}
	
	else if (defnum == 4) {

		armr exo_skel = {
				"엑소스켈레톤",
				500,
				2000
		};

		return exo_skel;
	}
	
	else {

		armr goliath = {
				"\"골리앗\" 신체강화 수트",
				9999,
				99999
		};

		return goliath;
	}
}

meds medications(int mednum) {

	//의약품류

	if (mednum == 0) {

		meds enrgbar = {
		"에너지바",
		5,
		30
		};

		return enrgbar;
	}

	else if (mednum == 1) {

		meds bandage = {
		"붕대",
		15,
		75
		};

		return bandage;
	}

	else if (mednum == 2) {

		meds painkiller = {
		"진통제",
		17.5,
		85
		};

		return painkiller;
	}

	else if (mednum == 3) {

		meds first_aid = {
		"구급상자",
		35,
		155
		};

		return first_aid;
	}

	else {
		meds survival_kit = {
		"서바이벌 키트",
		55,
		275
		};

		return survival_kit;
	}
}



//스탯 분배
int *stat_distribution(int temp_stats[6], int point_remain, char player_name[17]) {

	printf("\n투자할 스탯과 수치를 입력하세요. (point remain : %d)\n(1:힘 2:화술 3:지구력 4:지능 5:행운)\n( ex) 1 2 : 힘 + 2 )\n", point_remain);

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

		temp_stats[select_stat] += used_point;
		invested_point += used_point;
		printf("\n사용한 포인트 : %d, 잔여 포인트 : %d\n", invested_point, stat_points - invested_point);
	}

	printf("\n분배 완료!\n\n%s의 능력치\n|| 힘 : %d || 화술 : %d || 지구력 : %d || 지능 : %d || 행운 : %d ||\n", player_name, temp_stats[1], temp_stats[2], temp_stats[3], temp_stats[4], temp_stats[5]);

	return temp_stats;
}

//게임을 시작하고 캐릭터 생성
char* set_name() {

	static char player_name[17] = "\0";

	printf("캐릭터 이름을 설정하세요. (숫자포함 영문 최대 17자, 한글 최대 8자) : ");

	scanf_s("%s", player_name, sizeof(player_name));

	return player_name;
}

char* set_class(char player_name[17]) {

	printf("\n%s의 직업을 정하기 위해 주사위를 굴립니다.\n\n", player_name);

	player_class = DICEROLL(6);

	static char array[20] = "\0";

	int* a = &array;

	DICE_rolling();

	switch (player_class) {
	case 1:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 거지 입니다.\n", player_name);
		a = "거지";
		break;
	case 2:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 성직자 입니다.\n", player_name);
		a = "성직자";
		break;
	case 3:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 목수 입니다.\n", player_name);
		a = "목수";
		break;
	case 4:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 개장수 입니다.\n", player_name);
		a = "개장수";
		break;
	case 5:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 기사 입니다.\n", player_name);
		a = "기사";
		break;
	case 6:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 농부 입니다.\n", player_name);
		a = "농부";
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

	printf("###초기 스탯을 설정합니다.###\n");

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
		gotoxy(1, 1); printf("앞에 웬 판잣집이 있다.");
		printf("안에서 기척이 느껴진다");
		printf("다가가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {


		}

		else {
			printf("무엇을 하시겠습니까?");

			printf("무언가 수상한 판잣집을 뒤로한채 발을 옮겼다.");

		}

		break;
	case 2:
		gotoxy(1, 1); printf("앞에 웬 폐건물이 있다.");
		printf("들어가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.");

		}

		else {
			printf("무엇을 하시겠습니까?");

			printf("무언가 수상한 폐건물을 뒤로한채 발을 옮겼다.");

		}

		break;
	case 3:
		gotoxy(1, 1); printf("앞에 웬 멀쩡한 건물이/가 있다.");
		printf("들어가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.");

		}

		else {
			printf("무엇을 하시겠습니까?");

			printf("무언가 수상한 멀쩡한 건물을 뒤로한채 발을 옮겼다.");

		}

		break;
	case 4:
		gotoxy(1, 1);	printf("앞에 웬 움막이 있다.");
		printf("안에서 기척이 느껴진다");
		printf("다가가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.");

		}

		else {
			printf("무엇을 하시겠습니까?");

			printf("무언가 수상한 움막을 뒤로한채 발을 옮겼다.");

		}

		break;
	case 5:
		gotoxy(1, 1); printf("앞에 웬 벙커가 있다.");
		printf("들어가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.");

		}

		else {
			printf("무엇을 하시겠습니까?");

			printf("무언가 수상한 벙커를 뒤로한채 발을 옮겼다.");

		}

		break;
	case 6:
		gotoxy(1, 1); printf("앞 길거리에 무언가 있다.");

		break;
	}
}

void hit_the_road() {

	int rslt = DICEROLL(2);

	if (rslt == 1) {
		gotoxy(1, 21); printf("갈길 가는 중.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
	}

	else {
		gotoxy(1, 21); printf("가던 길 마저 가는중.");
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

//인카운터 설정
void visit_shop() {
	gotoxy(10, 1); printf("선반에 여러가지 물건이 진열되어있다, 상점인 듯하다\n");
	
}

void meet_monster() {

}

void robbed() {

}

void meet_animal() {

}

//아이템 획득
void earn_item() {

}

int next_behave() {

	int X;

	gotoxy(10, 1); printf("무얼 하시겠습니까?\n");
	gotoxy(10, 3); printf("1. 갈 길 가기");
	gotoxy(10, 4); printf("2. 소지품 확인");
	gotoxy(10, 5); printf("3. 휴식하기");
	gotoxy(10, 6); printf("4. 종료하기");

	gotoxy(10, 8); scanf_s("%d", &X);

	while (X != 1 && X != 2 && X != 3 && X != 4) {

		for (int i = 0; i < 8; i++) {
			for (int k = 1; k < 50; k++) {
					gotoxy(k, i); printf(" ");
			}
		}

		gotoxy(10, 1); printf("!!ERROR!! 다시 입력하세요");
		Sleep(3000);

		for (int k = 1; k < 50; k++) {
			gotoxy(k, 1); printf(" ");
		}

		gotoxy(10, 1); printf("무얼 하시겠습니까?\n");
		gotoxy(10, 3); printf("1. 갈 길 가기");
		gotoxy(10, 4); printf("2. 소지품 확인");
		gotoxy(10, 5); printf("3. 휴식하기");
		gotoxy(10, 6); printf("4. 종료하기");

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
		gotoxy(10, 1); printf("휴식중.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
		printf("50의 체력을 회복했습니다.");
		player.HP += 50;
		check_N_confirm();
		clear_cell();
		break;

	case 4:
		printf("게임을 종료하시겠습니까?");
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

	printf("전체화면 플레이를 권장합니다.\n");
	printf("게임 시작까지\n");

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