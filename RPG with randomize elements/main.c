//포스트 아포칼립스 RPG

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

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
	for (int i = 0; i < WIDTH_BEHAVE - 1; i++) {
		CELL_GAME[(HEIGHT_GAME - 1) - HEIGHT_BEHAVE][i] = CELL_GAME[HEIGHT_GAME - 1][i] = '-';
	}

	//BEHAVE HEIGHT
	for (int i = (HEIGHT_GAME - 1) - HEIGHT_BEHAVE; i < HEIGHT_GAME - 1; i++) {
		CELL_GAME[i][0] = CELL_GAME[i][WIDTH_BEHAVE - 1] = '|';
	}
	//INNER BEHAVE CELL
	for (int i = HEIGHT_GAME - HEIGHT_BEHAVE; i < HEIGHT_GAME - 1; i++) {
		for (int k = 1; k < WIDTH_BEHAVE - 1; k++) {
			CELL_GAME[i][k] = ' ';
		}
	}
}

//직업분류
//1:거지,2:성직자,3:목수,4:개장수,5:기사,6:농부
int class_rating[6] = { 1,2,3,4,5,6 };
int player_class;


//개체 프리셋
struct object_build {
	char name[50];
	int LVL;
	int class;
	int stats[5];
	int HP;
	int money;
	//개체 특성 부여 공간//
};

//무기 프리셋
struct item_wep {
	char name[50];
	int atk;
	int durability;
	int value;
};

//방어구 프리셋
struct item_armr {
	char name[50];
	int def;
	int value;
};

//의약품 프리셋
struct item_medical {
	char name[50];
	int heal_amount;
	int value;
};

struct player_inventory {
	int Weapons[8];
	int Armours[6];
	int Meds[5];
};

int DICEROLL(int);
void DICE_rolling();
void check_N_confirm();
int yes_or_no();

int LVL_scailing(char, int);
void creat_monster(int);

void cell_deployment();

int* stat_distribution(int[], int, char);
const char* setting_name();
int setting_class();
int setting_stats();

void visit_shop();
void meet_monster();
void robbed();
void meet_animal();
void earn_item();

int setting_stats();
void hit_the_road();


//주사위 굴리기
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

//스탯 분배
int* stat_distribution(int top_stats[5], int point_remain, char player_name) {

	printf("\n투자할 스탯과 수치를 입력하세요. (point remain : %d)\n(1:힘 2:화술 3:민첩 4:지능 5:행운)\n( ex) 1 2 : 힘 + 2 )\n", point_remain);

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

		top_stats[select_stat - 1] += used_point;
		invested_point += used_point;
		printf("사용한 포인트 : %d, 잔여 포인트 : %d\n", invested_point, stat_points - invested_point);
	}

	printf("\n분배 완료!\n\n%s의 능력치\n|| 힘 : %d || 화술 : %d || 민첩 : %d || 지능 : %d || 행운 : %d ||\n", player_name, top_stats[0], top_stats[1], top_stats[2], top_stats[3], top_stats[4]);

	return top_stats;
}

//게임을 시작하고 캐릭터 생성
const char* setting_name() {

	static char player_name[17] = "\0";
	
	printf("캐릭터 이름을 설정하세요. (숫자포함 영문 최대 17자, 한글 최대 8자) : ");

	scanf_s("%s", player_name, sizeof(player_name));

	return player_name;
}

int setting_class() {

	player_class = class_rating[DICEROLL(6)];

	DICE_rolling();

	return player_class;
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
void creat_monster(int player_level) {

	struct object_build ghoul = {
		"구울",
		LVL_scailing("LVL", player_level),
		6,
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	struct object_build raider = {
		"레이더",
		LVL_scailing("LVL", player_level),
		6,
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	struct object_build radsquito = {
		"방사능 모기",
		LVL_scailing("LVL", player_level),
		6,
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	struct object_build roach = {
		"거대바퀴",
		LVL_scailing("LVL", player_level),
		6,
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

	struct object_build subject = {
		"실험체",
		LVL_scailing("LVL", player_level),
		6,
		LVL_scailing("stats", player_level),
		LVL_scailing("HP", player_level),
		LVL_scailing("money", player_level)
	};

}


// 아이템
void items_weps() {

	//무기류
	struct item_wep knife = {
		"칼",
		rand() % 10 + 5,
		rand() % 10 + 10,
		25 + (int)knife.atk * 0.8 + knife.durability
	};

	struct item_wep bat = {
		"야구배트",
		rand() % 13 + 12,
		rand() % 12 + 15,
		45 + (int)bat.atk * 0.8 + bat.durability
	};

	struct item_wep g_club = {
		"골프채",
		rand() % 10 + 15,
		rand() % 13 + 10,
		65 + (int)g_club.atk * 0.8 + g_club.durability
	};

	struct item_wep imprv_firearm = {
		"급조 총기",
		rand() % 10 + 25,
		rand() % 5 + 10,
		50 + (int)imprv_firearm.atk * 0.8 + imprv_firearm.durability
	};

	struct item_wep revolver = {
		"리볼버",
		rand() % 20 + 30,
		rand() % 10 + 20,
		150 + (int)revolver.atk * 0.6 + revolver.durability
	};

	struct item_wep shotgun = {
		"산탄총",
		rand() % 50 + 50,
		rand() % 5 + 15,
		175 + (int)shotgun.atk * 0.65 + shotgun.durability
	};

	struct item_wep hunting_rifle = {
		"사냥용 소총",
		rand() % 20 + 70,
		rand() % 20 + 25,
		170 + (int)hunting_rifle.atk * 0.7 + hunting_rifle.durability
	};

	struct item_wep assault_rifle = {
		"돌격소총",
		rand() % 40 + 100,
		rand() % 10 + 40,
		275 + assault_rifle.durability
	};

	struct item_wep railgun = {
		"레일건",
		rand() % 50 + 200,
		rand() % 10 + 20,
		500
	};

	struct item_wep fat_boy = {
		"팻 보이",
		99999,
		1,
		9999
	};
}

void item_defs() {

	//방어구류
	struct item_armr rags = {
		"누더기",
		rand() % 10 + 10,
		30 + (int)rags.def * 0.8
	};

	struct item_armr light_armour = {
		"가벼운 방어구",
		rand() % 5 + 15,
		55 + (int)light_armour.def * 0.8
	};

	struct item_armr stabprf_vest = {
		"방검복",
		rand() % 20 + 35,
		70 + (int)stabprf_vest.def * 0.75
	};

	struct item_armr bulletprf_vest = {
		"방탄조끼",
		rand() % 20 + 50,
		120 + (int)bulletprf_vest.def * 0.6
	};

	struct item_armr exo_suit = {
		"엑소스켈레톤",
		500,
		2000
	};

	struct item_armr goliath = {
		"\"골리앗\" 신체강화 수트",
		9999,
		99999
	};
}

void item_meds() {

	//의약품류
	struct item_medical enrgbar = {
		"에너지바",
		5,
		30
	};

	struct item_medical bandage = {
		"붕대",
		15,
		75
	};

	struct item_medical painkiller = {
		"진통제",
		17.5,
		85
	};

	struct item_medical first_aid = {
		"구급상자",
		35,
		155
	};

	struct item_medical survival_kit = {
		"서바이벌 키트",
		55,
		275
	};

}


//인카운터 설정
void visit_shop() {
	printf("선반에 여러가지 물건이 진열되어있다, 상점인 듯하다\n");
	
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

//랜덤 인카운터 불러오기
void random_encounter(int diceroll) {

	int encounter_slot[5];



}

void approch() {

	int encounter_location = rand() % 4 + 1;
	int choice;

	switch (encounter_location) {
	case 1:
		printf("\n앞에 웬 판잣집이 있다.\n");
		printf("안에서 기척이 느껴진다\n");
		printf("다가가 보시겠습니까?\n");

		choice = yes_or_no();

		if (choice == 1) {
			

		}

		else {
			printf("무엇을 하시겠습니까?\n");

			printf("무언가 수상한 판잣집을 뒤로한채 발을 옮겼다.\n");

		}

		break;
	case 2:
		printf("\n앞에 웬 폐건물이 있다.\n");
		printf("들어가 보시겠습니까?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.\n");

		}

		else {
			printf("무엇을 하시겠습니까?\n");

			printf("무언가 수상한 폐건물을 뒤로한채 발을 옮겼다.\n");

		}

		break;
	case 3:
		printf("\n앞에 웬 멀쩡한 건물이/가 있다.\n");
		printf("들어가 보시겠습니까?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.\n");

		}

		else {
			printf("무엇을 하시겠습니까?\n");

			printf("무언가 수상한 멀쩡한 건물을 뒤로한채 발을 옮겼다.\n");

		}

		break;
	case 4:
		printf("\n앞에 웬 움막이 있다.\n");
		printf("안에서 기척이 느껴진다\n");
		printf("다가가 보시겠습니까?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.\n");

		}

		else {
			printf("무엇을 하시겠습니까?\n");

			printf("무언가 수상한 움막을 뒤로한채 발을 옮겼다.\n");

		}

		break;
	case 5:
		printf("\n앞에 웬 벙커가 있다.\n");
		printf("들어가 보시겠습니까?\n");

		choice = yes_or_no();

		if (choice == 1) {
			printf("가까이 다가갔더니 인기척이 느껴졌다.\n");

		}

		else {
			printf("무엇을 하시겠습니까?\n");

			printf("무언가 수상한 벙커를 뒤로한채 발을 옮겼다.\n");

		}

		break;
	case 6:
		printf("\n앞 길거리에 무언가 있다.\n");

		break;
	}
}

void hit_the_road() {

}

void battle() {

}


int main(void) {

	srand(time(NULL));

	cell_deployment();

	char* player_name = setting_name();

	printf("\n%s의 직업을 정하기 위해 주사위를 굴립니다.\n\n", player_name);

	int player_class = setting_class();

	switch (player_class) {
	case 1:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 거지 입니다.\n", player_name);
		break;
	case 2:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 성직자 입니다.\n", player_name);
		break;
	case 3:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 목수 입니다.\n", player_name);
		break;
	case 4:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 개장수 입니다.\n", player_name);
		break;
	case 5:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 기사 입니다.\n", player_name);
		break;
	case 6:
		printf("주사위 %d(이)가 나왔습니다.\n\n", player_class);
		printf("%s의 직업은 농부 입니다.\n", player_name);
		break;
	}

	check_N_confirm();

	printf("###초기 스탯을 설정합니다.###\n");

	int stats[5] = { 1,1,1,1,1 };

	int player_stats = stat_distribution(stats, 10, player_name);

	struct object_build player = {
		player_name,
		1,
		player_class,
		player_stats,
		50 + player.stats[2] * 5,
		100
	};

	while (player.HP > 0) {
		hit_the_road();
		approch();
	}
	

	/*
	chapter1_enter(player_class);
	chapter_proceed(player_LVL);
	chapter1_end(player_class);
	*/
	

	return 0;

}