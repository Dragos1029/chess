#include <iostream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
#include <stdio.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

/*
 * 0  = blank
 * 1  = blank
 * 2  = black pawn
 * 3  = white pawn
 * 4  = black bishop
 * 5  = white bishop
 * 6  = black knight
 * 7  = white knight
 * 8  = black rook
 * 9  = white rook
 * 10 = black queen
 * 11 = white queen
 * 12 = black king
 * 13 = white king
*/

int game [8][8] = {
    8 , 6 , 4 , 10, 12, 4 , 6 , 8 ,
    2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 ,
    9 , 7 , 5 , 11, 13, 5 , 7 , 9
};

char posToChar[7][9] = {
    "        ", "  PAWN  ", " BISHOP ", " KNIGHT ", "  ROOK  ", "  QUEEN ", "  KING  "
};

void whitebg(bool isWhitePiece) {
    int background = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    int foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (isWhitePiece) foreground = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(console, background | foreground | 0x1000);
}

void blackbg(bool isWhitePiece) {
    int foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (isWhitePiece) foreground = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(console, foreground);
}

void blackbg() {
    int foreground = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
    SetConsoleTextAttribute(console, foreground);
}

void whitebg() {
    int background = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE;
    SetConsoleTextAttribute(console, background);
}

void printGame() {
    bool white = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            //bool isWhitePiece = game[i][j] % 2;
            if (white) whitebg(); else blackbg();
            printf(posToChar[0]);
            white = !white;
        }
        blackbg();
        printf("\n");
        for (int j = 0; j < 8; j++) {
            bool isWhitePiece = game[i][j] % 2;
            if (white) whitebg(isWhitePiece); else blackbg(isWhitePiece);
            printf(posToChar[game[i][j] / 2]);
            //printf("   ");
            white = !white;
        }
        blackbg();
        printf("\n");
        for (int j = 0; j < 8; j++) {
            //bool isWhitePiece = game[i][j] % 2;
            if (white) whitebg(); else blackbg();
            printf(posToChar[0]);
            white = !white;
        }
        blackbg();
        printf("\n");
        white = !white;
    }
}

int main() {
    printGame();
}
