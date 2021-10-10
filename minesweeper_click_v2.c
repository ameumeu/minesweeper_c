#include <stdio.h>
#include <stdlib.h> 
#include <windows.h> 
#include <time.h>
#include <stdbool.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define SPACE 32

// ①	②	③	④	⑤	⑥	⑦	⑧

// ■□◈▣♠

int found[22][22]={};

int background[22][22] = {0};

int mineMap[50][2];

INPUT_RECORD rc;
DWORD        dw;
COORD pos={0,0};

int mines = 50;
int detectedMines = 0;
int flaggedMines = 0;


void cur(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void zeroMap() {
	int i, j;
	for (i=0; i<22; i++) {
		for (j=0; j<22; j++) {
			background[i][j]=0;
		}
	}
}

void initFound() {
	int i, j;
	for (i=0; i<22; i++) {
		for (j=0; j<22; j++) {
			found[i][j] = -2;
		}
	}
}

void initMines() {
	int i, p, q;
	Sleep(300);
	srand((int)time(NULL));
	for (i=0; i<mines; i++) {
		p = rand()%22;
		q = rand()%22;
		if (background[q][p] != -1) {
			background[q][p] = -1;
			mineMap[i][0] = p;
			mineMap[i][1] = q;
		} else {
			i--;
		}
	}
}

void search(int y, int x) {
	int i, j, cnt=0;
	for (i=y-1; i<y+2; i++) {
		for (j=x-1; j<x+2; j++) {
			if (i >=0 && i <= 21 && j >= 0 && j <= 21) {
				if (background[i][j]==-1) {
					cnt++;
				}
			}
		}
	}
	background[y][x]=cnt;
} 

void initMap() {
	int i, j;
	for(i=0; i<22; i++) {
		for (j=0; j<22; j++) {
			if (background[i][j] != -1) {
				search(i, j);
			}
		}
	}
}

void printMap() {
	cur(0,0);
	int i, j;
	for (i=0; i<22; i++) {
		for (j=0; j<22; j++) {
			if (found[i][j]==-2) {
					printf("■");
			} else {
				switch (found[i][j]) {
					case -1:
						printf("◈");
						break;
					case 0:
						printf("□");
						break;
					case 1:
						printf("①");
						break;
					case 2:
						printf("②");
						break;
					case 3:
						printf("③");
						break;
					case 4:
						printf("④");
						break;
					case 5:
						printf("⑤");
						break;
					case 6:
						printf("⑥");
						break;
					case 7:
						printf("⑦");
						break;
					case 8:
						printf("⑧");
						break;
					case 9:
						printf("♠");
						break;
				}	
			}
		}
		printf("\n");
	}
//	for (i=0; i<22; i++) {
//		for (j=0; j<22; j++) {
//			printf("%d ", found[i][j]);
//		}
//		printf("\n");
//	}
}

bool reveal(int x, int y) {
	int i, j, flag_cnt=0;

	if (found[y][x]==-2) {
		found[y][x]=background[y][x];
		if (found[y][x] != 9 && background[y][x] == -1) {
			return true;
		}
		return false;
	}

	for (i=y-1; i<y+2; i++) {
		for (j=x-1; j<x+2; j++) {
			if (i==y &&j==x) {
					continue;
				}
			if (i >=0 && i <= 21 && j >= 0 && j <= 21) {
				if (found[i][j]==9) {
					flag_cnt++;
				}
			}
		}
	}
	for (i=y-1; i<y+2; i++) {
		for (j=x-1; j<x+2; j++) {
			if (i >=0 && i <= 21 && j >= 0 && j <= 21) {
				if (i==y &&j==x) {
					continue;
				}
				if (found[y][x]-flag_cnt == 0) {
					if (found[i][j] != 9) {
						found[i][j]=background[i][j];
						if (background[i][j]==-1) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void flag (int x, int y) {
	if (found[y][x]==-2) {
		found[y][x] = 9;
		flaggedMines++;
		if (background[y][x] == -1) {
			detectedMines++;
		}
	} else if (found[y][x]==9) {
		found[y][x] = -2;
		flaggedMines--;
		if (background[y][x] == -1) {
			detectedMines--;
		}
	}
}

void endScreen() {
	int i, j;
	for (i=0; i<mines; i++) {

//		printf("%d %d // %d                              \n", mineMap[i][0]*2, mineMap[i][1], background[mineMap[i][1]][mineMap[i][0]]);
		cur(mineMap[i][0]*2, mineMap[i][1]);
		printf("◈");
		Sleep(100);
	}
	Sleep(1000);
}

void check() {
	int i, j;
	if (mines == detectedMines && detectedMines == flaggedMines) {
		cur(2, 3);
		printf("=======================================");
		cur(2, 4);
		printf("=  ====  ====  ==    ==  =======  ==  =");
		cur(2, 5);
		printf("=  ====  ====  ===  ===   ======  ==  =");
		cur(2, 6);
		printf("=  ====  ====  ===  ===    =====  ==  =");
		cur(2, 7);
		printf("=  ====  ====  ===  ===  ==  ===  ==  =");
		cur(2, 8);
		printf("=   ==    ==  ====  ===  ===  ==  ==  =");
		cur(2, 9);
		printf("==  ==    ==  ====  ===  ====  =  ==  =");
		cur(2, 10);
		printf("==  ==    ==  ====  ===  =====    =====");
		cur(2, 11);
		printf("===    ==    =====  ===  ======   ==  =");
		cur(2, 12);
		printf("====  ====  =====    ==  =======  ==  =");
		cur(2, 13);
		printf("=======================================");
	}
}

void gameScreen() {
	int i,j ,x=0, y=0;
	bool endFlag = false;
	int key;
	detectedMines = 0;
	flaggedMines = 0;
	
	initFound();
	zeroMap();
	initMines();
	initMap();
	printMap();
	
	while (1) {
		check();
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rc, 1, &dw); //핸들정보
		x = rc.Event.MouseEvent.dwMousePosition.X; //X좌표 
		y = rc.Event.MouseEvent.dwMousePosition.Y; // Y좌표 

		if (rc.EventType == MOUSE_EVENT){
			if (rc.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
	        	endFlag = reveal(x/2,y);
	        	printMap();
	        	if (endFlag) {
					endScreen();
	        		break;
				}

			} else if (rc.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED){
	        	flag(x/2, y);	
	        	printMap();
	        	Sleep(200);
			}
		}
	}
	

}


void menuScreen() {
	char key;

	
	printf(" _________________\n");
	printf("|  _____________  |\n");
	printf("| | MineSweeper | |\n");
	printf("| |_____________| |\n");
	printf("|_________________|\n\n\n\n\n\n");
	
	printf("상단 바에 우클릭 후 속성 탭에 들어가서\n빠른 \'편집 모드\'와 \'삽입모드\' \n체크를 해제해주세요.\n\n\n");
	printf("조작법은 기본 지뢰찾기와 같습니다.") ;

	Sleep(3000);
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 300*300 , pos, &dw); //화면 지우기        
	cur(0, 0); 
	return;
}


int main() {
	SetConsoleTitle("MineSweeper");
	SMALL_RECT WinRect = {0, 0, 43, 24};   
  	SMALL_RECT* WinSize = &WinRect;
  	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, WinSize);   //Set new size for window
	menuScreen();
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT); // 마우스 입력 모드로 바꾸기 
	while(1) {	
		gameScreen();
	}

}



// _________________ 
//|  _____________  |
//| | MineSweeper | |
//| |_____________| |
//|_________________|


// __  __  _             ___                     _ __           
//|  \/  |(_) _ _   ___ / __| _ __ __  ___  ___ | '_ \ ___  _ _ 
//| |\/| || || ' \ / -_)\__ \ \ V  V // -_)/ -_)| .__// -_)| '_|
//|_|  |_||_||_||_|\___||___/  \_/\_/ \___|\___||_|   \___||_|  

//[..       [..[..[...     [..[........  [.. ..  [..        [..[........[........[.......  [........[.......    
//[. [..   [...[..[. [..   [..[..      [..    [..[..        [..[..      [..      [..    [..[..      [..    [..  
//[.. [.. [ [..[..[.. [..  [..[..       [..      [..   [.   [..[..      [..      [..    [..[..      [..    [..  
//[..  [..  [..[..[..  [.. [..[......     [..    [..  [..   [..[......  [......  [.......  [......  [. [..      
//[..   [.  [..[..[..   [. [..[..            [.. [.. [. [.. [..[..      [..      [..       [..      [..  [..    
//[..       [..[..[..    [. ..[..      [..    [..[. [.    [....[..      [..      [..       [..      [..    [..  
//[..       [..[..[..      [..[........  [.. ..  [..        [..[........[........[..       [........[..      [..
                                                                                                              
                                                                                                              


