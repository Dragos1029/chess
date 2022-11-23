#include <iostream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
#include <stdio.h>
#include <tchar.h>
#include <cstring>

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

int nextMove[2][2] = {-1, -1, -1, -1};

void whitebg(bool isWhitePiece) {
    int background = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    int foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (isWhitePiece) foreground = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(console, background | foreground | 0x1000);
}

void blackbg(bool isWhitePiece) {
    int foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (isWhitePiece) foreground = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
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

void blankRow(bool &white) {
    printf("       ");
    for (int j = 0; j < 8; j++) {
        if (white) whitebg(); else blackbg();
        printf(posToChar[0]);
        white = !white;
    }
    blackbg();
}

void printGame() {
    bool white = 1;
    for (int i = 0; i < 8; i++) {
        blankRow(white);
        int pos = 8 - i;
        printf("\n   %i   ", pos);
        for (int j = 0; j < 8; j++) {
            bool isWhitePiece = game[i][j] % 2;
            if (white) whitebg(isWhitePiece); else blackbg(isWhitePiece);
            printf(posToChar[game[i][j] / 2]);
            white = !white;
        }
        blackbg();
        printf("\n");
        blankRow(white);
        printf("\n");
        white = !white;
    }
    printf("\n          A       B       C       D       E       F       G       H    \n\n");
}

int letterToInt(char letter) {
    switch(letter) {
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        default: return -1;
    }
}

int numberToInt(char letter) {
    switch(letter) {
        case '8': return 0;
        case '7': return 1;
        case '6': return 2;
        case '5': return 3;
        case '4': return 4;
        case '3': return 5;
        case '2': return 6;
        case '1': return 7;
        default: return -1;
    }
}

void toLower(char s[]) {
    int lenght = strlen(s);
    for (int i = 0; i < lenght; i++) {
        s[i] = tolower(s[i]);
    }
}

void getMove() {
    char input[] = "     ";
    bool valid = 0;
    printf("Next move: ");
    while (!valid) {
        valid = 1;
        cin.getline(input, 6);
        if (input[2] == ' ') {
            strcpy(input + 2, input + 3);
        }
        toLower(input);
        for (int i = 0; i < 2; i++) {
            nextMove[i][0] = letterToInt(input[i * 2]);
            if (nextMove[i][0] == -1) {
                valid = 0;
                break;
            }
            nextMove[i][1] = numberToInt(input[i * 2 + 1]);
            if (nextMove[i][1] == -1) {
                valid = 0;
                break;
            }
        }
        if (!valid) 
            printf("Try again: ");
    }
}

void performMove() {
    getMove();
    printf("your move is: ");
    for (int i = 0; i < 2; i++) {
        cout << nextMove[i][0];
        cout << nextMove[i][1];
    }
    printf("\n");
}

int main() {
    SetConsoleTitle(_T("test"));
    getch();
    printGame();
    performMove();
    getch();
}
