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
	int HP;
	int Distance;
};

struct NPC {
	char name[50];
	int LVL;
	int HP;
};

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


// 아이템
wep* weapons(int wepnum) {

	//무기류
	
	if (wepnum == 0) {

		wep knife = {
		"칼",
		rand() % 10 + 5,
		rand() % 10 + 10,
		25 + (int)knife.atk * 0.8 + knife.durability
		};

		wep* knife_p = &knife;

		return knife_p;
	}
	
	else if (wepnum == 1) {

		wep bat = {
		"야구배트",
		rand() % 13 + 12,
		rand() % 12 + 15,
		45 + (int)bat.atk * 0.8 + bat.durability
		};

		wep* bat_p = &bat;

		return bat_p;
	}
	
	else if (wepnum == 2) {

		wep g_club = {
		"골프채",
		rand() % 10 + 15,
		rand() % 13 + 10,
		65 + (int)g_club.atk * 0.8 + g_club.durability
		};

		wep* g_club_p = &g_club;

		return g_club_p;
	}
	
	else if (wepnum == 3) {

		wep imprv_firearm = {
		"급조 총기",
		rand() % 10 + 25,
		rand() % 5 + 10,
		50 + (int)imprv_firearm.atk * 0.8 + imprv_firearm.durability
		};

		wep* imprv_firearm_p = &imprv_firearm;

		return imprv_firearm_p;
	}
	
	else if (wepnum == 4) {

		wep revolver = {
		"리볼버",
		rand() % 20 + 30,
		rand() % 10 + 20,
		150 + (int)revolver.atk * 0.6 + revolver.durability
		};
		wep* revolver_p = &revolver;

		return revolver_p;
	}
	
	else if (wepnum == 5) {

		wep shotgun = {
		"산탄총",
		rand() % 50 + 50,
		rand() % 5 + 15,
		175 + (int)shotgun.atk * 0.65 + shotgun.durability
		};

		wep* shotgun_p = &shotgun;

		return shotgun_p;
	}
	
	else if (wepnum == 6) {

		wep hunting_rifle = {
		"사냥용 소총",
		rand() % 20 + 70,
		rand() % 20 + 25,
		170 + (int)hunting_rifle.atk * 0.7 + hunting_rifle.durability
		};

		wep* hunting_rifle_p = &hunting_rifle;

		return hunting_rifle_p;
	}
	
	else if (wepnum == 7) {

		wep assault_rifle = {
		"돌격소총",
		rand() % 40 + 100,
		rand() % 10 + 40,
		275 + assault_rifle.durability
		};

		wep* assault_rifle_p = &assault_rifle;

		return assault_rifle_p;
	}
	
	else if (wepnum == 8) {

		wep railgun = {
		"레일건",
		rand() % 50 + 200,
		rand() % 10 + 20,
		500
		};

		wep* railgun_p = &railgun;

		return railgun_p;
	}

	else {
		wep fist = {
			"주먹",
			5,
			99999,
			0
		};
		wep* fist_p = &fist;
		return fist_p;
	}

}

armr* armours(int defnum) {

	//방어구류

	if (defnum == 0) {

		armr rags = {
		"누더기",
		rand() % 10 + 10,
		30 + (int)rags.def * 0.8
		};

		armr* rags_p = &rags;

		return rags_p;
	}
	
	else if (defnum == 1) {

		armr light_armour = {
		"가벼운 방어구",
		rand() % 5 + 15,
		55 + (int)light_armour.def * 0.8
		};

		armr* light_armour_p = &light_armour;

		return light_armour_p;
	}
	
	else if (defnum == 2) {

		armr stabprf_vest = {
		"방검복",
		rand() % 20 + 35,
		70 + (int)stabprf_vest.def * 0.75
		};

		armr* stabprf_vest_p = &stabprf_vest;

		return stabprf_vest_p;
	}
	
	else if (defnum == 3) {

		armr bulletprf_vest = {
		"방탄조끼",
		rand() % 20 + 50,
		120 + (int)bulletprf_vest.def * 0.6
		};

		armr* bulletprf_vest_p = &bulletprf_vest;

		return bulletprf_vest_p;
	}
	
	else if (defnum == 4) {

		armr exo_skeleton = {
				"엑소스켈레톤",
				500,
				2000
		};

		armr* exo_skeleton_p = &exo_skeleton;

		return exo_skeleton_p;
	}

}

//게임을 시작하고 캐릭터 생성
char* set_name() {

	static char player_name[17] = "\0";

	printf("캐릭터 이름을 설정하세요. (숫자포함 영문 최대 17자, 한글 최대 8자) : ");

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
		gotoxy(10, 21); printf("갈길 가는 중.");
		for (int i = 0; i < 7; i++) {
			Sleep(250);
			printf(".");
		}
	}

	else {
		gotoxy(10, 21); printf("가던 길 마저 가는중.");
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
		strcpy(monster, "구울");
		break;

	case 1:
		strcpy(monster, "레이더");
		break;

	case 2:
		strcpy(monster, "거대바퀴");
		break;

	case 3:
		strcpy(monster, "실험체");
		break;

	case 4:
		strcpy(monster, "방사능 모기");
		break;
	}

	int monster_HP = rand() % 300 + (137 - player->Distance);

	int monster_atk = rand() % 30;

	clear_cell();

	gotoxy(10, 1); printf("%s이/가 나타났다.", monster);

	confirm();

	clear_cell();

	int select;

	int use_num;

	while (TRUE) {

		gotoxy(10, 1); printf("주머니 뒤지는 중");
		for (int i = 0; i < 5; i++) {
			printf(". ");
			Sleep(100);
		}

		wep weapon = *weapons(DICEROLL(9));

		gotoxy(10, 2); printf("뽑은무기: %s", weapon.name);

		armr armour = *armours(DICEROLL(4));

		gotoxy(10, 3); printf("뽑은방어구: %s", armour.name);

		confirm();

		clear_cell();

		gotoxy(10, 2); printf("무얼 하시겠습니까?");

		gotoxy(10, 3); printf("1. 공격하기 2. 방어하기 2. 도망가기");

		gotoxy(10, 34); scanf_s("%d", &select);

		clear_cell();

		if (select == 1) {

			gotoxy(10, 1); printf("%s의 공격, %d의 피해를 입혔다", player->name, weapon.atk);

			if (monster_atk - armour.def <= 0) {
				gotoxy(10, 3); printf("%s의 공격, 0의 피해를 받았다", monster);
			}

			else {
				gotoxy(10, 3); printf("%s의 공격, %d의 피해를 받았다", monster, monster_atk - armour.def);
				player->HP -= (monster_atk - armour.def);
			}

			monster_HP -= ((137 - player->Distance) * 5 + weapon.atk);

			gotoxy(50, 7); printf("%s의 체력: %d", monster, monster_HP);

			gotoxy(195, 9); printf("%d/%d", player->HP, 50 + (137 - player->Distance));

			confirm();

			clear_cell();

			if (player->HP <= 0 || monster_HP <= 0) {
				break;
			}
		}

		else if (select == 2) {
			clear_cell();
			gotoxy(10, 3); printf("%s의 공격, %d의 피해를 받았다", monster, rand() % 20);
			gotoxy(50, 7); printf("%s의 체력: %d", monster, monster_HP);
			confirm();
			if (player->HP <= 0 || monster_HP <= 0) {
				break;
			}
			clear_cell();
		}

		else {
			gotoxy(10, 1); printf("%s을/를 뒤로한채 도망쳤다", monster);
			confirm();
			break;
		}
	}

	if (player->HP <= 0) {

		clear_cell();

		gotoxy(10, 1); printf("!!!%s가 사망했습니다!!!", player->name);

		gotoxy(10, 2); printf("GAME OVER");

		confirm();

		system("cls");

		exit(0);
	}

	else {
		clear_cell();
		gotoxy(10, 1); printf("%s를 물리쳤다", monster);
		confirm();
		player->Distance -= rand() % 3 + 1;
	}
}

//인카운터 설정

void meet_monster(struct main_character* player) {

	battle(player);
}

void robbed(struct main_character* player) {

	struct NPC robber = {
		"강도",
		rand() % 10 - 5 + (137 - player->Distance),
		rand() % 300 + (137 - player->Distance) * 15
	};

	clear_cell();

	gotoxy(10, 1); printf("풀숲에서 %s이/가 나타났다.", robber.name);

	confirm();

	clear_cell();

	int select;

	int use_num;

	while (TRUE) {

		gotoxy(10, 1); printf("주머니 뒤지는 중");
		for (int i = 0; i < 5; i++) {
			printf(". ");
			Sleep(100);
		}

		wep weapon = *weapons(DICEROLL(9));

		gotoxy(10, 2); printf("뽑은무기: %s", weapon.name);

		armr armour = *armours(DICEROLL(4));

		gotoxy(10, 3); printf("뽑은방어구: %s", armour.name);

		confirm();

		clear_cell();

		gotoxy(10, 2); printf("무얼 하시겠습니까?");

		gotoxy(10, 3); printf("1. 공격하기 2. 방어하기 2. 도망가기");

		gotoxy(10, 34); scanf_s("%d", &select);

		clear_cell();

		if (select == 1) {

			gotoxy(10, 1); printf("%s의 공격, %d의 피해를 입혔다", player->name, weapon.atk);

			if (robber.LVL * 5 - armour.def <= 0) {
				gotoxy(10, 3); printf("%s의 공격, 0의 피해를 받았다", robber.name);
			}

			else {
				gotoxy(10, 3); printf("%s의 공격, %d의 피해를 받았다", robber.name, robber.LVL * 5 - armour.def);
				player->HP -= (robber.LVL * 5 - armour.def);
			}

			robber.HP -= ((137 - player->Distance) + weapon.atk);

			gotoxy(50, 3); printf("강도의 체력: %d", robber.HP);

			gotoxy(195, 9); printf("%d/%d", player->HP, 50 + (137 - player->Distance) * 5);

			confirm();

			clear_cell();
			if (player->HP <= 0 || robber.HP <= 0) {
				break;
			}
		}

		else if (select == 2) {
			clear_cell();
			gotoxy(10, 3); printf("%s의 공격, %d의 피해를 받았다", robber.name, rand() % 20);
			gotoxy(50, 3); printf("강도의 체력: %d", robber.HP);
			confirm();
			clear_cell();
			if (player->HP <= 0 || robber.HP <= 0) {
				break;
			}
		}

		else {
			gotoxy(10, 1); printf("%s을/를 뒤로한채 도망쳤다", robber.name);
			confirm();
			break;
		}
	}

	if (player->HP <= 0) {

		clear_cell();

		gotoxy(10, 1); printf("!!!%s가 사망했습니다!!!", player->name);

		gotoxy(10, 2); printf("GAME OVER");

		confirm();

		system("cls");

		exit(0);
	}

	else if (robber.HP <= 0) {
		clear_cell();
		gotoxy(10, 1); printf("%s를 물리쳤다", robber.name);
		confirm();
		player->Distance -= rand() % 3 + 1;
	}
}

void sleeping(struct main_character* player) {
	gotoxy(10, 1); printf("안쪽은 생각보다 깔끔하다, 잠자리로는 안성맞춤인거같다");
	gotoxy(10, 2); printf("휴식하시겠습니까?");
	int choice;

	choice = yes_or_no();

	clear_cell();

	if (choice == 1) {
		player->HP += 100;
		gotoxy(10, 1); printf("푹 잤더니 기운이 넘친다");
		confirm();
		clear_cell();
	}

	else {
		player->Distance--;
		gotoxy(10, 1); printf("휴식하기엔 힘이 넘쳐흐른다");
		confirm();
		clear_cell();
	}
}

void approach(struct main_character* player) {

	int encounter_location = rand() % 100;
	int choice;

	if (encounter_location >= 1 && encounter_location <= 50) {
		gotoxy(10, 1); printf("앞에 웬 판잣집이 있다. 안에서 기척이 느껴진다.");
		gotoxy(10, 2); printf("다가가 보시겠습니까?");

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
			gotoxy(10, 1); printf("수상한 판잣집을 뒤로한채 길을 떠났다");
			confirm();
		}
	}

	else if (encounter_location > 50 && encounter_location <= 75) {
		gotoxy(10, 1); printf("앞에 웬 폐건물이 있다.");
		gotoxy(10, 2); printf("들어가 보시겠습니까?");

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
			gotoxy(10, 1); printf("수상한 폐건물을 뒤로한채 길을 떠났다");
			confirm();
		}
	}

	else if (encounter_location == 100) {
		gotoxy(10, 1); printf("길가에 검은색 인터셉터가 서있다");
		gotoxy(10, 2); printf("가까이 가보시겠습니까?");
		choice = yes_or_no();

		clear_cell();

		if (choice == 1) {
			int hitch;
			gotoxy(10, 1); printf("가까이 가보니 옆의 일행에게 차 자랑을 늘어놓고 있다, 어떻게 하시겠습니까?");
			gotoxy(10, 2); printf("1.옆에 태워달라고 부탁한다 2.차를 빼앗는다 3.그냥 간다");
			gotoxy(10, 34); scanf_s("%d", &hitch);
			clear_cell();

			if (hitch == 1 || hitch == 2) {
				gotoxy(10, 1); printf("차 덕분에 쉽게 이동할 수 있었다");
				confirm();
			}

			else {
				gotoxy(10, 1); printf("차를 뒤로하고 길을 떠났다");
				confirm();
			}
		}

		else {
			clear_cell();
			gotoxy(10, 1); printf("차를 뒤로하고 길을 떠났다");
			confirm();
		}

		player->Distance -= rand() % 3 + 1;
	}

	else {

		gotoxy(10, 1);	printf("앞에 웬 움막이 있다.");
		printf(" 안에서 기척이 느껴진다");
		gotoxy(10, 2); printf("다가가 보시겠습니까?");

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
			gotoxy(10, 1); printf("움막을 뒤로한채 길을 떠났다");
			confirm();
		}
	}
}

int next_behave() {

	int X;

	gotoxy(10, 1); printf("무얼 하시겠습니까?");
	gotoxy(10, 3); printf("1. 갈 길 가기");
	gotoxy(10, 4); printf("2. 휴식하기");
	gotoxy(10, 6); printf("3. 종료하기");

	gotoxy(10, 8); scanf_s("%d", &X);

	while (X != 1 && X != 2 && X != 3 && X != 4) {

		clear_cell();

		gotoxy(10, 1); printf("!!ERROR!! 다시 입력하세요");
		Sleep(3000);

		for (int k = 1; k < 50; k++) {
			gotoxy(k, 1); printf(" ");
		}

		gotoxy(10, 1); printf("무얼 하시겠습니까?");
		gotoxy(10, 3); printf("1. 갈 길 가기");
		gotoxy(10, 4); printf("2. 휴식하기");
		gotoxy(10, 6); printf("3. 종료하기");

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
			gotoxy(10, 1); printf("휴식중.");
			for (int i = 0; i < 7; i++) {
				Sleep(250);
				printf(".");
			}

			if (player->HP + 50 > (137 - player->Distance) * 5) {
				player->HP = 50 + (137 - player->Distance) * 5;
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
	gotoxy(180, 9); printf("HP");
	gotoxy(195, 9); printf("%d/%d", temp->HP, 50 + (137 - temp->Distance) * 5);
	gotoxy(180, 12); printf("Distance");
	gotoxy(195, 12); printf("%d", temp->Distance);

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

	struct main_character player = *initialize();

	system("cls");

	printf("20xx년, 세계는 핵의 불길에 휩싸였다\n");
	Sleep(500);
	printf("바다는 마르고 땅은 갈라져 모든 생명체가 사라진 듯 하였다. 하지만, 인류는 멸망하지 않았다!\n");
	Sleep(1000);
	printf("핵전쟁으로 황폐화된 세계에서 사람들의 일부는 흉포화된 폭력에 억눌려 살아가고 있다.\n");
	Sleep(800);
	printf("그 세계에서 대전의 전설적인 잡화상인 %s 은/는 전설속의 시장인 남대문시장을 향해 모험을 떠나려한다.........", player.name);
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
			printf("드디어 %s는 남대문시장에 도착했다.", player.name);
			Sleep(1000);
			printf("하지만 남대문시장도 핵의 불길을 피할 수는 없었던 모양이다.");
			Sleep(1000);
			printf("굴러다니는 잔해들을 내려다보며 그 사이로 서있는 %s에겐 그 어떤 낙담이나 슬픔의 표정이라곤 찾아볼 수 없었다.", player.name);
			Sleep(1000);
			printf("오히려 더욱 번쩍이는 눈빛을 하고 거대한 대륙이 있을 북쪽으로 발걸음을 옮겼다...................");

			confirm();
			system("cls");

			printf("플레이해주셔서 감사합니다");
			confirm();

			exit(0);
		}
		player.Distance--;
		system("cls");
	}
	return 0;
}