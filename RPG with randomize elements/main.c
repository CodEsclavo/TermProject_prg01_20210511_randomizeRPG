//포스트 아포칼립스 RPG

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>

//게임 셀들의 크기
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
			gotoxy(k, i); printf(" ");
		}
	}

	for (int n = 33; n < 55; n++) {
		for (int l = 1; l < 209; l++) {
			gotoxy(l, n); printf(" ");
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
	char class[10];
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

typedef struct {
	wep Weapons[5];
	armr Armours[5];
	meds Meds[10];
} inventory;

typedef struct  {
	wep weapons;
	armr armours;
} equipments;

typedef struct {
	wep Weapons[2];
	armr Armours[2];
	meds Medications[3];
} shop;



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
void confirm() {

	gotoxy(5, 33); printf("엔터를 입력하여 넘어가기....");

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
	if (wepnum == -1) {
		wep fist = {
			"주먹",
			5,
			99999,
			0
		};
	}

	else if (wepnum == 0) {

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

	static char array[50] = "\0";

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

	strcpy(temp->name, set_name());

	strcpy(temp->class, set_class(temp->name));

	confirm();

	system("cls");

	printf("###초기 스탯을 설정합니다.###\n");

	for (int i = 0; i < 6; i++) {
		player_stats[i] += 1;
	}

	int *stats = stat_distribution(player_stats, 10, temp->name);

	for (int i = 0; i < 6; i++) {
		temp->stats[i] = stats[i];
	}

	confirm();

	temp->LVL = 1;

	temp->HP = (50 + temp->LVL * 10 + temp->stats[3] * 5);

	temp->money = 100;

	return temp;

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

void battle(struct main_character* player, equipments* equip, inventory* inv, NPC monster) {

	clear_cell();

	int select;

	int use_num;

	while (player->HP != 0 || monster.HP != 0) {

		gotoxy(10, 2); printf("무얼 하시겠습니까?");

		gotoxy(10, 3); printf("1. 공격 2. 의약품 3. 도망");

		gotoxy(10, 34); scanf_s("%d", &select);

		clear_cell();
		if (select == 1) {

			gotoxy(10, 1); printf("%s의 공격, %d의 피해를 입혔다", player->name, equip->weapons.atk);

			gotoxy(10, 3); printf("%s의 공격, %d의 피해를 받았다", monster.name, equip->armours.def);

			monster.HP -= (player->stats[0] + equip->weapons.atk);

			player->HP -= (monster.stats[0] - equip->armours.def);

			confirm();

			clear_cell();
		}

		else if (select == 2) {
			int num_item = 0;
			for (int i = 0; i < 10; i++) {
				if (inv->Meds[i].name != NULL) {
					num_item++;
				}
			}

			if (num_item == 0) {
				gotoxy(10, 1); printf("소지하고있는 의약품이 없습니다.");

				confirm();

				clear_cell();

				continue;
			}

			gotoxy(10, 1); printf("의약품");

			for (int i = 0; i < num_item; i++) {
				if (i <= 5) {
					gotoxy(10 + i * 5, 3); printf("%d. %s", i, inv->Meds[i].name);
				}
				else {
					gotoxy(10 + i * 5, 4); printf("%d. %s", i, inv->Meds[i].name);
				}
			}

			gotoxy(10, 6); printf("사용할 아이템 선택");

			gotoxy(10, 34); scanf_s("%d", &use_num);

			if (player->HP += inv->Meds[use_num - 1].heal_amount <= 50 + player->LVL * 10 + player->stats[3] * 5) {

				gotoxy(10, 1); printf("%d의 체력을 회복했습니다.", inv->Meds[use_num - 1].heal_amount);

				player->HP += inv->Meds[use_num - 1].heal_amount;

				confirm();
			}

			else {

				gotoxy(10, 1); printf("%d의 체력을 회복했습니다.", player->LVL * 10 + player->stats[3] * 5 - player->HP);

				player->HP = 50 + player->LVL * 10 + player->stats[3] * 5;

				confirm();
			}

			clear_cell();		

			continue;
		}

		else {
			break;
		}
	}

	if (player->HP <= 0) {

		clear_cell();

		gotoxy(10, 1); printf("!!!%s가 사망했습니다!!!", player->name);

		gotoxy(10, 2); printf("GAME OVER");

		confirm();
	}

	else if (monster.HP <= 0) {
		clear_cell();
		gotoxy(10, 1); printf("%s를 물리쳤다", monster.name);
		gotoxy(10, 2); printf("%d골드를 얻었다", monster.money);
	}

	player->money += monster.money;

}

//인카운터 설정
void visit_shop(struct main_character* player, inventory* inv) {

	wep blank_w = { NULL };

	armr blank_a = { NULL };

	meds blank_m = { NULL };

	shop product = { NULL };

	clear_cell();

	gotoxy(10, 1); printf("선반에 여러가지 물건이 진열되어있다, 상점인 듯하다");
	
	while (TRUE) {

		int choice, type, select, buy, sell, count = 0;

		gotoxy(10, 2); printf("무엇을 하시겠습니까?");
		gotoxy(10, 4); printf("1. 구매하기 2. 판매하기 3.나가기 4.협박하기");

		gotoxy(10, 34); scanf_s("%d", &choice);

		clear_cell();

		if (choice == 1) {

			gotoxy(10, 1); printf("무엇을 구매하시겠습니까?");
			gotoxy(10, 2); printf("1.무기 2.방어구 3.의약품");

			gotoxy(10, 34); scanf_s("%d", &type);

			if (type == 1) {
				for (int i = 0; i < 2; i++) {
					product.Weapons[i] = weapons(DICEROLL(9) - 1);
					gotoxy(10, 1); printf("무기류");
					gotoxy(10, 2); printf("%d. %s", i + 1, product.Weapons[i].name);

					gotoxy(10, 34); scanf_s("%d", &buy);

					if (product.Weapons[buy].value > player->money) {
						clear_cell();
						gotoxy(10, 1); printf("돈이 부족합니다!");
						confirm();
						continue;
					}

					else {

						clear_cell();

						for (int i = 0; i < 5; i++) {
							if (inv->Weapons[i].name != NULL) {
								count++;
							}

							if (count == 5) {
								gotoxy(10, 1); printf("인벤토리의 공간이 부족합니다!");
								continue;
							}

							else {
								for (int i = 0; i < 5; i++) {
									if (inv->Weapons[i].name == NULL) {
										inv->Weapons[i] = product.Weapons[buy];
										gotoxy(10, 1); printf("%s를 구매했습니다", inv->Weapons[i].name);
										confirm();
									}
								}
								continue;
							}
						}
					}
				}
			}

			else if (type == 2) {
				for (int i = 0; i < 2; i++) {
					product.Armours[i] = armours(DICEROLL(5) - 1);
					gotoxy(10, 1); printf("방어구류");
					gotoxy(10, 2); printf("%d. %s", i + 1, product.Armours[i].name);

					gotoxy(10, 34); scanf_s("%d", &buy);

					if (product.Armours[buy].value > player->money) {
						clear_cell();
						gotoxy(10, 1); printf("돈이 부족합니다!");
						confirm();
						continue;
					}

					else {

						clear_cell();

						for (int i = 0; i < 5; i++) {
							if (inv->Armours[i].name != NULL) {
								count++;
							}

							if (count == 5) {
								gotoxy(10, 1); printf("인벤토리의 공간이 부족합니다!");
								continue;
							}

							else {
								for (int i = 0; i < 5; i++) {
									if (inv->Armours[i].name == NULL) {
										inv->Armours[i] = product.Armours[buy];
										gotoxy(10, 1); printf("%s를 구매했습니다", inv->Armours[i].name);
										confirm();
									}
								}
								continue;
							}
						}
					}
				}
			}

			else {
				for (int i = 0; i < 3; i++) {
					product.Medications[i] = medications(DICEROLL(4));
					gotoxy(10, 1); printf("의약품");
					gotoxy(10, 2); printf("%d. %s", i + 1, product.Medications[i].name);

					gotoxy(10, 34); scanf_s("%d", &buy);

					if (product.Medications[buy].value > player->money) {
						clear_cell();
						gotoxy(10, 1); printf("돈이 부족합니다!");
						confirm();
						continue;
					}

					else {

						clear_cell();

						for (int i = 0; i < 10; i++) {
							if (inv->Meds[i].name != NULL) {
								count++;
							}

							if (count == 5) {
								gotoxy(10, 1); printf("인벤토리의 공간이 부족합니다!");
								continue;
							}

							else {
								for (int i = 0; i < 10; i++) {
									if (inv->Meds[i].name == NULL) {
										inv->Meds[i] = product.Medications[buy];
										gotoxy(10, 1); printf("%s를 구매했습니다", inv->Meds[i].name);
										confirm();
									}
								}
								continue;
							}
						}
					}
				}
			}
		}

		else if (choice == 2) {

			gotoxy(10, 1); printf("뭘 파시겠습니다");
			gotoxy(10, 3); printf("1. 무기");
			gotoxy(10, 4); printf("2. 방어구");
			gotoxy(10, 5); printf("3. 의약품");
			gotoxy(10, 7); printf("나가기: BackSpace");

			gotoxy(10, 34); select = _getch();

			clear_cell();

			if (select == 1) {
				gotoxy(10, 1); for (int i = 0; i < 5; i++) {
					printf("%d. %s ", i + 1, inv->Weapons[i].name);
				}
				gotoxy(10, 3); printf("판매할 물건을 골라주세요");
				gotoxy(10, 4); printf("나가기: BackSpace");
				gotoxy(10, 34); sell = _getch();

				if (sell == '\b') {
					continue;
				}

				player->money += inv->Weapons[sell].value;

				clear_cell();
				gotoxy(10, 1); printf("%s를 팔아 %d골드를 벌었다", inv->Weapons[sell].name, inv->Weapons[sell].value);

				confirm();
				inv->Weapons[sell] = blank_w;

				continue;
			}
			else if (select == 2) {
				gotoxy(10, 1); for (int i = 0; i < 5; i++) {
					printf("%d. %s ", i + 1, inv->Armours[i].name);
				}
				gotoxy(10, 3); printf("판매할 물건을 골라주세요");
				gotoxy(10, 4); printf("나가기: BackSpace");
				gotoxy(10, 34); sell = _getch();

				if (sell == '\b') {
					continue;
				}

				player->money += inv->Armours[sell].value;
				clear_cell();
				gotoxy(10, 1); printf("%s를 팔아 %d골드를 벌었다", inv->Armours[sell].name, inv->Armours[sell].value);

				confirm();
				inv->Armours[sell] = blank_a;

				continue;
			}
			else if (select == 3) {
				gotoxy(10, 1); for (int i = 0; i < 10; i++) {
					printf("%d. %s ", i + 1, inv->Meds[i].name);
				}
				gotoxy(10, 3); printf("판매할 물건을 골라주세요");
				gotoxy(10, 4); printf("나가기: BackSpace");
				gotoxy(10, 34); sell = _getch();

				if (sell == '\b') {
					continue;
				}

				player->money += inv->Meds[sell].value;
				clear_cell();
				gotoxy(10, 1); printf("%s를 팔아 %d골드를 벌었다", inv->Meds[sell].name, inv->Meds[sell].value);

				confirm();
				inv->Meds[sell] = blank_m;

				continue;
			}
			else {
				gotoxy(10, 1); printf("밖으로 나왔다");
				confirm();
				break;
			}
		}

		else if (choice == 3) {
			gotoxy(10, 1); printf("밖으로 나왔다");
			confirm();
			break;
		}

		else {

		}
	}
}

void meet_monster(struct main_character* player, equipments* equip, inventory* inv) {

	NPC monster = creat_monster(player->LVL);

	gotoxy(10, 1); printf("%s가 나타났다.", monster.name);

	battle(player, equip, inv, monster);

}

void robbed() {

}

//아이템 획득
void earn_item(inventory* inv) {

	int earn;

	while (TRUE) {

		clear_cell();

		gotoxy(10, 1); printf("물건이 떨어져 있다. 주우시겠습니까?");

		earn = yes_or_no();

		if (earn != 1) {

			clear_cell();

			gotoxy(10, 1); printf("뭔가 좀 꺼림직하다, 그냥 가자.");

			confirm();

			break;
		}

		int item_type = DICEROLL(3);

		int item_num;

		int inventory_filled = 0;

		int inv_num;

		int clear_inv;

		if (item_type == 1) {

			item_num = DICEROLL(10) - 1;

			wep new_wep = weapons(item_num);

			for (int i = 0; i < 5; i++) {
				if (inv->Weapons[i].name != NULL) {
					inventory_filled++;
				}
			}

			if (inventory_filled == 5) {

				clear_cell();
				gotoxy(10, 1); printf("인벤토리에 공간이 없습니다.");
				gotoxy(10, 2); printf("다른 아이템을 버리시겠습니까?");
				clear_inv = yes_or_no();

				if (clear_inv == 1) {
					clear_cell();
					gotoxy(10, 1); printf("버릴 아이템을 선택해주세요.");
					gotoxy(10, 2); for (int i = 0; i < 5; i++) {
						printf("%d. %s ", i + 1, inv->Weapons[i].name);
					}

					gotoxy(10, 4); scanf_s("%d", &clear_inv);

					inv->Weapons[clear_inv] = new_wep;

					clear_cell();
					gotoxy(10, 1); printf("%s를 습득했습니다.", inv->Weapons[clear_inv].name);
					confirm();
				}

				else {
					break;
				}
			}

			else {
				for (int i = 0; i < 5; i++) {
					if (inv->Weapons[i].name == NULL) {
						inv->Weapons[i] = new_wep;
						inv_num -= i;
						break;
					}
				}
				gotoxy(10, 3); printf("%s를 획득했습니다.", inv->Weapons[inv_num].name);
			}

		}

		else if (item_type == 2) {

			item_num = DICEROLL(6) - 1;

			armr new_armr = armours(item_num);

			for (int i = 0; i < 5; i++) {
				if (inv->Armours[i].name != NULL) {
					inventory_filled++;
				}
			}

			if (inventory_filled == 5) {

				clear_cell();
				gotoxy(10, 1); printf("인벤토리에 공간이 없습니다.");
				gotoxy(10, 2); printf("다른 아이템을 버리시겠습니까?");
				clear_inv = yes_or_no();

				if (clear_inv == 1) {
					clear_cell();
					gotoxy(10, 1); printf("버릴 아이템을 선택해주세요.");
					gotoxy(10, 2); for (int i = 0; i < 5; i++) {
						printf("%d. %s ", i + 1, inv->Armours[i].name);
					}

					gotoxy(10, 4); scanf_s("%d", &clear_inv);

					inv->Armours[clear_inv] = new_armr;

					clear_cell();
					gotoxy(10, 1); printf("%s를 습득했습니다.", inv->Armours[clear_inv].name);
					confirm();
				}

			else {
				for (int i = 0; i < 5; i++) {
					if (inv->Armours[i].name == NULL) {
						inv->Armours[i] = new_armr;
						inv_num -= i;
						break;
					}
				}
				gotoxy(10, 3); printf("%s를 획득했습니다.", inv->Armours[inv_num].name);
			}
		}
	}

		else {

			item_num = DICEROLL(5) - 1;

			meds new_med = medications(item_num);

			for (int i = 0; i < 10; i++) {
				if (inv->Meds[i].name != NULL) {
					inventory_filled++;
				}
			}

			if (inventory_filled == 10) {

				clear_cell();
				gotoxy(10, 1); printf("인벤토리에 공간이 없습니다.");
				gotoxy(10, 2); printf("다른 아이템을 버리시겠습니까?");
				clear_inv = yes_or_no();

				if (clear_inv == 1) {
					clear_cell();
					gotoxy(10, 1); printf("버릴 아이템을 선택해주세요.");
					gotoxy(10, 2); for (int i = 0; i < 10; i++) {
						printf("%d. %s ", i + 1, inv->Meds[i].name);
					}

					gotoxy(10, 4); scanf_s("%d", &clear_inv);

					inv->Meds[clear_inv] = new_med;

					clear_cell();
					gotoxy(10, 1); printf("%s를 습득했습니다.", inv->Meds[clear_inv].name);
					confirm();
				}

				else {
					break;
				}
			}

			else {
				for (int i = 0; i < 10; i++) {
					if (inv->Meds[i].name == NULL) {
						inv->Meds[i] = new_med;
						inv_num -= i;
						break;
					}
				}
				gotoxy(10, 3); printf("%s를 획득했습니다.", inv->Meds[inv_num].name);
			}
		}
	}
}

void approach(struct main_character* player, equipments* equip, inventory* inv) {

	int encounter_location = rand() % 4 + 1;
	int choice;

	switch (encounter_location) {
	case 1:
		gotoxy(10, 1); printf("앞에 웬 판잣집이 있다. 안에서 기척이 느껴진다.");
		gotoxy(10, 2); printf("다가가 보시겠습니까?");

		int encounter;

		choice = yes_or_no();

		clear_cell();

		if (choice == 1) {

			encounter = DICEROLL(4);

			switch (encounter) {
			case 1:
				visit_shop(player, inv);
				break;
			case 2:
				meet_monster(player, equip, inv);
				break;
			case 3:
				robbed();
				break;
			case 4:
				earn_item(inv);
				break;
			}

		}

		else {
			gotoxy(10, 1); printf("수상한 판잣집을 뒤로한채 길을 떠났다");
			confirm();
		}
		break;

	case 2:
		gotoxy(10, 1); printf("앞에 웬 폐건물이 있다.");
		gotoxy(10, 2); printf("들어가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {

			encounter = DICEROLL(4);

			switch (encounter) {
			case 1:
				visit_shop(player, inv);
				break;
			case 2:
				meet_monster(player, equip, inv);
				break;
			case 3:
				robbed();
				break;
			case 4:
				earn_item(inv);
				break;
			}
		}

		else {
			gotoxy(10, 1); printf("수상한 폐건물을 뒤로한채 길을 떠났다");
			confirm();
		}
		break;

	case 3:
		gotoxy(10, 1); printf("앞에 웬 멀쩡한 건물이 있다.");
		gotoxy(10, 2); printf("들어가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {

			encounter = DICEROLL(4);

			switch (encounter) {
			case 1:
				visit_shop(player, inv);
				break;
			case 2:
				meet_monster(player, equip, inv);
				break;
			case 3:
				robbed();
				break;
			case 4:
				earn_item(inv);
				break;
			}
		}

		else {
			gotoxy(10, 1); printf("수상한 건물을 뒤로한채 길을 떠났다");
			confirm();
		}
		break;

	case 4:
		gotoxy(10, 1);	printf("앞에 웬 움막이 있다.");
		printf(" 안에서 기척이 느껴진다");
		gotoxy(10, 2); printf("다가가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {

			encounter = DICEROLL(4);

			switch (encounter) {
			case 1:
				visit_shop(player, inv);
				break;
			case 2:
				meet_monster(player, equip, inv);
				break;
			case 3:
				robbed();
				break;
			case 4:
				earn_item(inv);
				break;
			}
		}

		else {
			gotoxy(10, 1); printf("움막을 뒤로한채 길을 떠났다");
			confirm();
		}

		break;

	case 5:
		gotoxy(10, 1); printf("앞에 군용벙커가 있다.");
		gotoxy(10, 2); printf("들어가 보시겠습니까?");

		choice = yes_or_no();

		if (choice == 1) {

			encounter = DICEROLL(4);

			switch (encounter) {
			case 1:
				visit_shop(player, inv);
				break;
			case 2:
				meet_monster(player, equip, inv);
				break;
			case 3:
				robbed();
				break;
			case 4:
				earn_item(inv);
				break;
			}
		}

		else {
			gotoxy(10, 1); printf("벙커를 뒤로한채 길을 떠났다");
			confirm();
		}

		break;
	}
}

int next_behave() {

	int X;

	gotoxy(10, 1); printf("무얼 하시겠습니까?");
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

		gotoxy(10, 1); printf("무얼 하시겠습니까?");
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

void player_action(struct main_character* player, equipments* equip_p, inventory* inv_p) {

	int running = TRUE;

	while (running) {

		int temp = next_behave();

		if (temp == 1) {
			hit_the_road();
			approach(player, equip_p, inv_p);
			break;
		}

		else if (temp == 2) {
			clear_cell();

			int chk_belong = TRUE;

			int select;

			while (chk_belong) {

				gotoxy(10, 1); printf("소지품 확인");
				gotoxy(10, 3); printf("1. 무기");
				gotoxy(10, 4); printf("2. 방어구");
				gotoxy(10, 5); printf("3. 의약품");
				gotoxy(10, 7); printf("나가기: BackSpace");

				gotoxy(10, 8); select = _getch();

				clear_cell();

				if (select == 1) {
					gotoxy(20, 1); printf("무기류");
					gotoxy(10, 3);
					for (int i = 0; i < 5; i++) {
						if (inv_p->Weapons[i].name == NULL) {
							printf(" ");
						}
						else {
							printf("%d,%s ", i + 1, inv_p->Weapons[i].name);
						}
					}

					wep temp = { NULL };

					gotoxy(10, 5); printf("무기를 장착하려면 해당 번호를 입력하세요");
					gotoxy(10, 6); printf("인벤토리에서 나가려면 \'<-\'를 누르세요");
					gotoxy(10, 8); int wep_s = _getch();

					if (wep_s == 1) {
						temp = equip_p->weapons;
						equip_p->weapons = inv_p->Weapons[0];
						inv_p->Weapons[0] = temp;
						continue;
					}

					else if (wep_s == 2) {
						temp = equip_p->weapons;
						equip_p->weapons = inv_p->Weapons[1];
						inv_p->Weapons[1] = temp;
						continue;
					}

					else if (wep_s == 3) {
						temp = equip_p->weapons;
						equip_p->weapons = inv_p->Weapons[2];
						inv_p->Weapons[2] = temp;
						continue;
					}

					else if (wep_s == 4) {
						temp = equip_p->weapons;
						equip_p->weapons = inv_p->Weapons[3];
						inv_p->Weapons[3] = temp;
						continue;
					}

					else if (wep_s == 5) {
						temp = equip_p->weapons;
						equip_p->weapons = inv_p->Weapons[4];
						inv_p->Weapons[4] = temp;
						continue;
					}

					else if (wep_s == '\b') {
						clear_cell();
						continue;
					}

					else {
						clear_cell();
						gotoxy(10, 1); printf("다시 입력하세요");
						continue;
					}
				}

				else if (select == 2) {
					gotoxy(20, 1); printf("방어구류");
					gotoxy(10, 3);
					for (int i = 0; i < 5; i++) {
						if (inv_p->Weapons[i].name == NULL) {
							printf(" ");
						}
						else {
							printf("%d,%s ", i + 1, inv_p->Weapons[i].name);
						}
					}

					armr temp = { NULL };

					gotoxy(10, 5); printf("방어구를 장착하려면 해당 번호를 입력하세요");
					gotoxy(10, 6); printf("인벤토리에서 나가려면 \'<-\'를 누르세요");
					gotoxy(10, 8); int armr_s = _getch();

					if (armr_s == 1) {
						temp = equip_p->armours;
						equip_p->armours = inv_p->Armours[0];
						inv_p->Armours[0] = temp;
						clear_cell();
						continue;
					}

					else if (armr_s == 2) {
						temp = equip_p->armours;
						equip_p->armours = inv_p->Armours[1];
						inv_p->Armours[1] = temp;
						clear_cell();
						continue;
					}

					else if (armr_s == 3) {
						temp = equip_p->armours;
						equip_p->armours = inv_p->Armours[2];
						inv_p->Armours[2] = temp;
						clear_cell();
						continue;
					}

					else if (armr_s == 4) {
						temp = equip_p->armours;
						equip_p->armours = inv_p->Armours[3];
						inv_p->Armours[3] = temp;
						clear_cell();
						continue;
					}

					else if (armr_s == 5) {
						temp = equip_p->armours;
						equip_p->armours = inv_p->Armours[4];
						inv_p->Armours[4] = temp;
						clear_cell();
						continue;
					}

					else if (armr_s == '\b') {
						clear_cell();
						continue;
					}

					else {
						clear_cell();
						gotoxy(10, 1); printf("다시 입력하세요");
						continue;
					}
				}

				else if (select == 3) {

				}

				else if (select == '\b') {
					running = FALSE;
					clear_cell();
					break;
				}

				else {
					clear_cell();
					gotoxy(10, 1); printf("다시 입력하세요");
					continue;
				}
			}
		}

		else if (temp == 3) {
			clear_cell();
			gotoxy(10, 1); printf("휴식중.");
			for (int i = 0; i < 7; i++) {
				Sleep(250);
				printf(".");
			}
			gotoxy(10, 2); printf("50의 체력을 회복했습니다.");
			player->HP += 50;
			confirm();
			clear_cell();
			break;
		}

		else {

			printf("게임을 종료하시겠습니까?");
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
	inventory inv = { NULL };
	equipments equip = {
		weapons(-1),
		armours(0)
	};

	system("cls");

	while (player->HP > 0) {

		display(player);
		player_action(player, &inv, &equip);
		system("cls");

	}
	return 0;
}