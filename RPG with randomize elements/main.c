#define _CRT_SECURE_NO_WARNING

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

char CELL_GAME[HEIGHT_GAME][WIDTH_GAME] = { ' ' };

void cell_deployment();
void start_game();
int character_alive();


//전체적인 게임 화면 출력
void cell_deployment() {
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

	//STATS WIDTH
	for (int i = 0; i < WIDTH_STATS; i++) {
		CELL_GAME[0][(WIDTH_GAME - 1) - WIDTH_STATS + i] = CELL_GAME[HEIGHT_STATS - 1][(WIDTH_GAME - 1) - WIDTH_STATS + i] = '-';
	}

	//STATS HEIGHT
	for (int i = 0; i < HEIGHT_STATS; i++) {
		CELL_GAME[i][(WIDTH_GAME - 1) - WIDTH_STATS] = CELL_GAME[i][WIDTH_GAME - 1] = '|';
	}

	//INNER STATS CELL
	for (int i = 1; i < HEIGHT_STATS - 1; i++) {
		for (int k = (WIDTH_GAME - 1) - WIDTH_STATS; k < WIDTH_GAME - 1; k++) {
			CELL_GAME[i][k] = ' ';
		}
	}

	//BEHAVE WIDTH
	for(int i = 0; i < WIDTH_BEHAVE; i++) {
		CELL_GAME[0][i] = CELL_GAME[HEIGHT_BEHAVE - 1][i] = '-';
	}

	//BEHAVE HEIGHT

	//INNER BEHAVE CELL
	for (int i = 1; i < HEIGHT_BEHAVE - 1; i++) {
		for (int k = 1; k < WIDTH_BEHAVE - 1; k++) {
			CELL_GAME[i][k] = ' ';
		}
	}
}


//게임을 시작하고 캐릭터 생성
void start_game() {

}


//캐릭터 생존 여부
int character_alive() {

}




int main(void) {

	cell_deployment();
	start_game();
	while (character_alive()) {

	}

	return 0;
}