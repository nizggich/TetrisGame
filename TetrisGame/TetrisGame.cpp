#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <map>
#include <array>
#include <conio.h>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

const int FIGURE_SIZE = 4;

int countLateralDisplacement = 0;
int speed = 700;
int score = 0;
int lines = 0;

int heighestPointOfStorage = 18;
bool gameOver = true;

const int width = 16; 
const int height = 18;

int widthOfNextFigureZone = 0;
int heightOfNextFigureZone = 0;

int startOfNextFigureZone = 19;

enum figureType {I = 1, J = 2, O = 3, L = 4, T = 5, S = 6, Z = 7};
figureType curFigureType;
figureType nextFigureType;

//координаты зоны отрисовки x - от 21 до 24, у - от 2 до 4

const array <int, 4> nextFigureZoneIx { 21, 22, 23, 24 };
const array <int, 4> nextFigureZoneIy { 3, 3, 3, 3 };

const array <int, 4> nextFigureZoneJx { 23, 23, 23, 22 };
const array <int, 4> nextFigureZoneJy { 2, 3, 4, 4 };

const array <int, 4> nextFigureZoneLx { 22, 22, 22, 23 };
const array <int, 4> nextFigureZoneLy { 2, 3, 4, 4 };

const array <int, 4> nextFigureZoneOx {21, 22, 21, 22}; 
const array <int, 4> nextFigureZoneOy {2, 2, 3, 3}; 

const array <int, 4> nextFigureZoneTx { 21, 22, 23, 22 };
const array <int, 4> nextFigureZoneTy { 2, 2, 2, 3 };

const array <int, 4> nextFigureZoneSx { 22, 23, 21, 22 };
const array <int, 4> nextFigureZoneSy { 2, 2, 3, 3 };

const array <int, 4> nextFigureZoneZx { 21, 22, 22, 23 };
const array <int, 4> nextFigureZoneZy { 2, 2, 3, 3 };


const map<figureType, pair<array<int, 4>, array<int, 4>>> nextFigures = {
	{I, make_pair(nextFigureZoneIx, nextFigureZoneIy)},
	{J, make_pair(nextFigureZoneJx, nextFigureZoneJy)},
	{L, make_pair(nextFigureZoneLx, nextFigureZoneLy)},
	{O, make_pair(nextFigureZoneOx, nextFigureZoneOy)},
	{T, make_pair(nextFigureZoneTx, nextFigureZoneTy)},
	{S, make_pair(nextFigureZoneSx, nextFigureZoneSy)},
	{Z, make_pair(nextFigureZoneZx, nextFigureZoneZy)}
};

int nextFigureX[4];
int nextFigureY[4];

const array <int, 4> Ix { 6, 7, 8, 9 };
const array <int, 4> Iy { 1, 1, 1, 1 };

const array <int, 4> Jx { 7, 7, 7, 6 };
const array <int, 4> Jy { 1, 2, 3, 3 };

const array <int, 4> Lx{ 7, 7, 7, 8 };
const array <int, 4> Ly{ 1, 2, 3, 3 };

const array <int, 4> Ox { 7, 8, 7, 8 };
const array <int, 4> Oy { 1, 1, 2, 2 };

const array <int, 4> Tx { 6, 7, 8, 7 };
const array <int, 4> Ty { 1, 1, 1, 2 };

const array <int, 4> Sx { 7, 8, 6, 7 };
const array <int, 4> Sy { 1, 1, 2, 2 };

const array <int, 4> Zx { 6, 7, 7, 8 };
const array <int, 4> Zy { 1, 1, 2, 2 };

const map<figureType, pair<array<int, 4>, array<int, 4>>> figures = {
	{I, make_pair(Ix, Iy)},
	{J, make_pair(Jx, Jy)},
	{L, make_pair(Lx, Ly)},
	{O, make_pair(Ox, Oy)},
	{T, make_pair(Tx, Ty)},
	{S, make_pair(Sx, Sy)},
	{Z, make_pair(Zx, Zy)}
};

const int ISmallRotatingPointIndex = 1;
const int ILargeRotatingPointIndex = 3;

const int JSmallRotatingPointIndex = 1;
const int JLargeRotatingPointIndex = 3;

const int LSmallRotatingPointIndex = 1;
const int LLargeRotatingPointIndex = 3;

const int OSmallRotatingPointIndex = -1;
const int OLargeRotatingPointIndex = -1; 

const int TSmallRotatingPointIndex = 1;
const int TLargeRotatingPointIndex = -1;

const int SSmallRotatingPointIndex = 0;
const int SLargeRotatingPointIndex = 2;

const int ZSmallRotatingPointIndex = 1;
const int ZLargeRotatingPointIndex = 3;

const map<figureType, pair<int, int>> rotatingPointIndeces = {
	{I, make_pair(ISmallRotatingPointIndex, ILargeRotatingPointIndex)},
	{J, make_pair(JSmallRotatingPointIndex, JLargeRotatingPointIndex)},
	{L, make_pair(LSmallRotatingPointIndex, LLargeRotatingPointIndex)},
	{O,	make_pair(OSmallRotatingPointIndex, OLargeRotatingPointIndex)},
	{T, make_pair(TSmallRotatingPointIndex, TLargeRotatingPointIndex)},
	{S, make_pair(SSmallRotatingPointIndex, SLargeRotatingPointIndex)},
	{Z, make_pair(ZSmallRotatingPointIndex, ZLargeRotatingPointIndex)}
};

int currentFigureX[FIGURE_SIZE];
int currentFigureY[FIGURE_SIZE];
int storage[height][width];

int smallRotatingZoneX[4];
int smallRotatingZoneY[4];
int largeRotatingZoneX[4];
int largeRotatingZoneY[4];

int smallRotatingZoneIx[]{ 7, 6, 7, 8 };
int smallRotatingZoneIy[]{ 0, 1, 2, 1 };
int largeRotatingZoneIx[]{ 7, 9, 7, 5 };
int largeRotatingZoneIy[]{ 3, 1, -1, 1 };

int smallRotatingZoneLJx[] { 7, 6, 7, 8 };
int smallRotatingZoneLJy[] { 1, 2, 3, 2 };
int largeRotatingZoneLJx[] { 8, 8, 6, 6 };
int largeRotatingZoneLJy[] { 3, 1, 1 ,3 };

int smallRotatingZoneTx[]{ 7, 6, 7, 8 };
int smallRotatingZoneTy[]{ 0, 1, 2, 1 };

int smallRotatingZoneSZx[] { 7, 6, 7, 8 };
int smallRotatingZoneSZy[] { 0, 1, 2, 1 };
int largeRotatingZoneSZx[] { 8, 8, 6, 6 };
int largeRotatingZoneSZy[] { 2, 0, 0 ,2 };


figureType getRandomFigureType() {
	srand(time(NULL));
	return figureType(1 + rand() % 7);
}

void setNewFigureType() {
	curFigureType = figureType(nextFigureType);
	nextFigureType = getRandomFigureType();
}

void setNextFigureZoneDemensions() {
	switch(nextFigureType) {
	case  I: 
	case  J: 
	case  L:
		widthOfNextFigureZone = 8;
		heightOfNextFigureZone = 7;
		break;
	case T:
	case S:
	case Z:
		widthOfNextFigureZone = 7;
		heightOfNextFigureZone = 6;
		break;
	case O:
		widthOfNextFigureZone = 6;
		heightOfNextFigureZone = 6;
		break;
	}
}

void fillCurrentFigureArrByType() {

	pair<array<int, 4>, array<int, 4>> figure = figures.at(curFigureType);
	array<int, 4> figureX = figure.first;
	array<int, 4> figureY = figure.second;

	for (int i = 0; i < FIGURE_SIZE; i++) {
		currentFigureX[i] = figureX[i];
		currentFigureY[i] = figureY[i];
	}
}

void fillNextFigureArrByType() {
	pair<array<int, 4>, array<int, 4>> figure = nextFigures.at(nextFigureType);
	array<int, 4> figureX = figure.first;
	array<int, 4> figureY = figure.second;

	for (int i = 0; i < FIGURE_SIZE; i++) {
		nextFigureX[i] = figureX[i];
		nextFigureY[i] = figureY[i];
	}
}

void fillStorage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				storage[i][j] = 1;
			}
			else if (i == height - 1) {
				storage[i][j] = 2;
			}
			else {
				storage[i][j] = 0;
			}
		}
	}
}

void fillCurrentRotatingZonesByType() {
	switch (curFigureType) {
		case L:
		case J:
			for (int i = 0; i < FIGURE_SIZE; i++) {
				smallRotatingZoneX[i] = smallRotatingZoneLJx[i];
				smallRotatingZoneY[i] = smallRotatingZoneLJy[i];

				largeRotatingZoneX[i] = largeRotatingZoneLJx[i];
				largeRotatingZoneY[i] = largeRotatingZoneLJy[i];
			}
			break;
		case S:
		case Z:
			for (int i = 0; i < FIGURE_SIZE; i++) {
				smallRotatingZoneX[i] = smallRotatingZoneSZx[i];
				smallRotatingZoneY[i] = smallRotatingZoneSZy[i];

				largeRotatingZoneX[i] = largeRotatingZoneSZx[i];
				largeRotatingZoneY[i] = largeRotatingZoneSZy[i];
			}
			break;
		case I:
			for (int i = 0; i < FIGURE_SIZE; i++) {
				smallRotatingZoneX[i] = smallRotatingZoneIx[i];
				smallRotatingZoneY[i] = smallRotatingZoneIy[i];

				largeRotatingZoneX[i] = largeRotatingZoneIx[i];
				largeRotatingZoneY[i] = largeRotatingZoneIy[i];
			}
			break;
		case T:
			for (int i = 0; i < FIGURE_SIZE; i++) {
				smallRotatingZoneX[i] = smallRotatingZoneTx[i];
				smallRotatingZoneY[i] = smallRotatingZoneTy[i];

				largeRotatingZoneX[i] = 0;
				largeRotatingZoneY[i] = 0;
			}
			break;
	}
}


void rotateFigure() {

	pair<int, int> rotatingPoints = rotatingPointIndeces.at(curFigureType);
	int smallRotatingPoint = rotatingPoints.first;
	int largeRotatingPoint = rotatingPoints.second;

	if (smallRotatingPoint > 0 && largeRotatingPoint < 0) {
		return;
	}

	for (int i = 0; i < FIGURE_SIZE; i++) {
		if (i == smallRotatingPoint) continue;

		int x = currentFigureX[i];
		int y = currentFigureY[i];

		for (int j = 0; j < FIGURE_SIZE; j++) {
			int k = j == 3 ? 0 : j + 1;
			if (i!= largeRotatingPoint && (x == smallRotatingZoneX[j] && y == smallRotatingZoneY[j])) {
				int val = storage[smallRotatingZoneY[k]][smallRotatingZoneX[k]];
				if (val == 1 || val == 2) return;
			}
			else if (x == largeRotatingZoneX[j] && y == largeRotatingZoneY[j]) {
				int val = storage[largeRotatingZoneY[k]][largeRotatingZoneX[k]];
				if (val == 1 || val == 2) return;
			}
		}
	}

	for (int i = 0; i < FIGURE_SIZE; i++) {

		int x = currentFigureX[i];
		int y = currentFigureY[i];

		if (i == smallRotatingPoint) continue;

		for (int j = 0; j < FIGURE_SIZE; j++) {

			if (i != largeRotatingPoint) {
				if (x == smallRotatingZoneX[j] && y == smallRotatingZoneY[j]) {

					if (j == 3) {
						currentFigureX[i] = smallRotatingZoneX[0];
						currentFigureY[i] = smallRotatingZoneY[0];
						break;
					}
					else {
						currentFigureX[i] = smallRotatingZoneX[j + 1];
						currentFigureY[i] = smallRotatingZoneY[j + 1];
						break;
					}

				}
			} else {
				if (x == largeRotatingZoneX[j] && y == largeRotatingZoneY[j]) {
					if (j == 3) {
						currentFigureX[i] = largeRotatingZoneX[0];
						currentFigureY[i] = largeRotatingZoneY[0];
						break;
					}
					else {
						currentFigureX[i] = largeRotatingZoneX[j + 1];
						currentFigureY[i] = largeRotatingZoneY[j + 1];
						break;
					}
				}
			}
		}
	}
}

void shiftDown() {
	for (int i = 0; i < FIGURE_SIZE; i++) {
		currentFigureY[i] += 1;
		smallRotatingZoneY[i] += 1;
		largeRotatingZoneY[i] += 1;
	}
}

boolean shiftLeft() {

	for (int i = 0; i < FIGURE_SIZE; i++) {
		int x = currentFigureX[i];
		int y = currentFigureY[i];

		if (storage[y][x - 1] == 1 || storage[y][x - 1] == 2) {
			return false;
		}
	}
	
	if (countLateralDisplacement++ == 3) {
		countLateralDisplacement = 0;
		return false;
	}

	
	for (int i = 0; i < FIGURE_SIZE; i++) {
		currentFigureX[i] -= 1;
		smallRotatingZoneX[i] -= 1;
		largeRotatingZoneX[i] -= 1;
	}
	
	return true;
}

boolean shiftRight() {

	for (int i = 0; i < FIGURE_SIZE; i++) {
		int x = currentFigureX[i];
		int y = currentFigureY[i];

		if (storage[y][x + 1] == 1 || storage[y][x + 1] == 2) {
			return false;
		}
	}

	if (countLateralDisplacement++ == 3) {
		countLateralDisplacement = 0;
		return false;
	}


	for (int i = 0; i < FIGURE_SIZE; i++) {
		currentFigureX[i] += 1;
		smallRotatingZoneX[i] += 1;
		largeRotatingZoneX[i] += 1;
	}

	return true;
}

void deleteBlocksFromStorage() {
	boolean forDelete = false;
	for (int i = heighestPointOfStorage; i < height - 1; i++) {
		forDelete = true;
		for (int j = 1; j < width - 1; j++) {

			if (storage[i][j] == 0) {
				forDelete = false;
				break;
			}
		}

		if (forDelete) {
			for (int k = 1; k < width - 1; k++) {
				storage[i][k] = 0;
			}

			for (int z = i; z > heighestPointOfStorage; z--) {
				for (int l = 1; l < width - 1; l++) {
					storage[z][l] = storage[z - 1][l];
				}
			}

			for (int l = 1; l < width - 1; l++) {
				storage[heighestPointOfStorage][l] = 0;
			}

			lines++;
			score += 100;
		}

	}
}


void setUp() {
	gameOver = false;
	curFigureType = getRandomFigureType();
	nextFigureType = getRandomFigureType();
	setNextFigureZoneDemensions();
	fillCurrentFigureArrByType();
	fillNextFigureArrByType();
	fillCurrentRotatingZonesByType();
	fillStorage();
	score = 0;
	lines = 0;
}


void addBlocksToStorage() {

	for (int i = 0; i < FIGURE_SIZE; i++) {

		if (storage[currentFigureY[i]][currentFigureX[i]] == 2) { //+1

			for (int i = 0; i < FIGURE_SIZE; i++) {
				currentFigureY[i] -= 1;
			}

			for (int j = 0; j < FIGURE_SIZE; j++) {

				int x = currentFigureX[j];
				int y = currentFigureY[j];

				if (y <= 3) {
					setUp();
					break;
				} else if (heighestPointOfStorage > y) {
					heighestPointOfStorage = y;
				}

				storage[y][x] = 2;
			}
			setNewFigureType();
			setNextFigureZoneDemensions();
			fillCurrentFigureArrByType();
			fillNextFigureArrByType();
			fillCurrentRotatingZonesByType();
			score += 10;
			speed = 900;
			break;
		}
	}
}


void Draw() {

	system("cls");

	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width + 12; j++) {
			bool isPrinted = false;


			if (i < heightOfNextFigureZone && j > width) {						
				if (j >= width && j <= startOfNextFigureZone) {
					printf(" ");
				}
				
				if (i > 0 && i < heightOfNextFigureZone - 1 && (j > startOfNextFigureZone && j < startOfNextFigureZone + widthOfNextFigureZone)) {
					for (int k = 0; k < FIGURE_SIZE; k++) {
						if (i == nextFigureY[k] && j == nextFigureX[k]) {
							printf("X");
							isPrinted = true;
						}
					}

					if (!isPrinted) {
						printf(" ");
					}
				}
				
				if ((i == 0 || i == heightOfNextFigureZone - 1) && (j >= startOfNextFigureZone && j < startOfNextFigureZone + widthOfNextFigureZone)) {
					printf("#");
				}

				if ((i > 0 && i < heightOfNextFigureZone - 1) && ((j == startOfNextFigureZone) || (j == startOfNextFigureZone + widthOfNextFigureZone - 2))) {
					printf("#");
				}

				isPrinted = true;
			}

			if (i == heightOfNextFigureZone && j == width + 2) {
				printf("NEXT FIGURE");
			}

			if (i == heightOfNextFigureZone + 2 && j == width + 3) {
				printf("SCORE: %d", score);
			}

			if (i == heightOfNextFigureZone + 3 && j == width + 3) {
				printf("LINES: %d", lines);
			}

			if (i == heightOfNextFigureZone + 5 && j == width + 3) {
				printf("Control (only US layout): ");
			}

			if (i == heightOfNextFigureZone + 6 && j == width + 3) {
				printf("w - rotate figure");
			}

			if (i == heightOfNextFigureZone + 7 && j == width + 3) {
				printf("a - move the figure to the left ");
			}

			if (i == heightOfNextFigureZone + 8 && j == width + 3) {
				printf("d - move the figure to the right");
			}

			if (i == heightOfNextFigureZone + 9 && j == width + 3) {
				printf("s - speed up the fall of a figure down");
			}

			if (i == heightOfNextFigureZone + 10 && j == width + 3) {
				printf("x - restart game");
			}


			if (j == 0 || j == width - 1) {
				printf("#");
				isPrinted = true;
			}

			for (int k = 0; k < FIGURE_SIZE; k++) {
				if (i == currentFigureY[k] && j == currentFigureX[k]) {
					printf("X");
					isPrinted = true;
				}
			}

			if (j < width && storage[i][j] == 2) {
				printf("#");
				isPrinted = true;
			}

			if (!isPrinted) {
				printf(" ");;
			}

		}
		
		printf("\n");
	}


	for (int i = 0; i < width; i++) {
		printf("#");
	}

}

void Input(){
	speed = 900;
	
	if ( _kbhit()) {
		switch (_getch()) {
		case 'x':
			setUp();
			break;
		case 'w':
			shiftDown();
			rotateFigure();
			break;
		case 'a':
			speed = 500;
			if (!shiftLeft()) shiftDown();
			break;
		case 's':
			speed = 100;
			shiftDown();
			break;
		case 'd':
			speed = 500;
			if (!shiftRight()) shiftDown();
			break;
		default:
			shiftDown();
		}
	} else {
		shiftDown();
	}
}


void Logic() {
	addBlocksToStorage();
	deleteBlocksFromStorage();
}

int main() {
	setUp();
	while (!gameOver) {
		Draw();
		Sleep(speed);
		Input();
		Logic();
	}

}



