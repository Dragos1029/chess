#include <iostream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
#include <stdio.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void whitebg() {
    SetConsoleTextAttribute(console, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void blackbg() {
    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void printGame() {
    bool white = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (white) whitebg();
            printf("  ");
            blackbg();
            white = !white;
        }
        printf("\n");
        white = !white;
    }
}

int main() {
    printGame();
}
