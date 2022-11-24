#include <iostream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
#include <stdio.h>
#include <tchar.h>
#include <cstring>
#include <climits>

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

//The start of a game of chess
const int initGame [8][8] = {
/*8*/   8 , 6 , 4 , 10, 12, 4 , 6 , 8 ,
/*7*/   2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
/*6*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*5*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*4*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*3*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*2*/   3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 ,
/*1*/   9 , 7 , 5 , 11, 13, 5 , 7 , 9
/* */
/*      A   B   C   D   E   F   G   H      */
};

//Converts piece codes to names
const char posToChar[7][9] = {
    "        ", "  PAWN  ", " BISHOP ", " KNIGHT ", "  ROOK  ", "  QUEEN ", "  KING  "
};

//Sets the background to white and the foreground to the specified color
void whitebg(bool isWhitePiece) {
    int background = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    int foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (isWhitePiece) foreground = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(console, background | foreground | 0x1000);
}

//Sets the background to black and the foreground to the specified color
void blackbg(bool isWhitePiece) {
    int foreground = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (isWhitePiece) foreground = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(console, foreground);
}

void blackbg() {    //Sets the background to black
    int foreground = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
    SetConsoleTextAttribute(console, foreground);
}

void whitebg() {    //Sets the background to white
    int background = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE;
    SetConsoleTextAttribute(console, background);
}

//Prints a blank row with alternating black & white background
void blankRow(bool &white) {    
    printf("       ");
    for (int j = 0; j < 8; j++) {
        if (white) whitebg(); else blackbg();
        printf(posToChar[0]);
        white = !white;
    }
    blackbg();
}

void printGame(int game[][8]) {
    bool white = 1;                 //Decides if the tile is black or white
    for (int i = 0; i < 8; i++) {
        blankRow(white);            //Prints a blank row
        int pos = 8 - i;
        printf("\n   %i   ", pos);  //Numbering for collumns
        for (int j = 0; j < 8; j++) {
            bool isWhitePiece = game[i][j] % 2; //Gets piece color
            if (white)
                whitebg(isWhitePiece);          //Sets colors
            else 
                blackbg(isWhitePiece);
            printf(posToChar[game[i][j] / 2]);  //Prints piece name
            white = !white;
        }
        blackbg();      //Makes sure that new line isn't colored
        printf("\n");
        blankRow(white);
        printf("\n");
        white = !white;
    }
    //Labeling for columns
    printf("\n          A       B       C       D       E       F       G       H    \n\n");
}

int letterToInt(char letter) {  //Converts letters to position
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

int numberToInt(char letter) {  //Convers number char to position
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

void toLower(char s[]) {    //Lowers the letters from a char array
    int lenght = strlen(s);
    for (int i = 0; i < lenght; i++) {
        s[i] = tolower(s[i]);
    }
}

void getMove(int nextMove[][2]) {
    char input[] = "     ";
    bool valid = 0;
    //We continue asking the user until we have a valid move
    while (!valid) {
        valid = 1;
        cin.getline(input, 6);
        if (cin.fail()) {
            //Clears the console in case the user types more than 5 chars
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        if (input[2] == ' ') {
            //Deletes the space in case the user added a space between coords
            strcpy(input + 2, input + 3);
        }
        //We make all letters lowercase for easier parsing
        toLower(input);
        for (int i = 0; i < 2; i++) {
            //We convert the leter to a position
            nextMove[i][0] = letterToInt(input[i * 2]);
            if (nextMove[i][0] == -1) {
                //If the response is invalid we exit the loop and repeat the question
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

void copyMove(int move1[][2], int move2[][2]) {
    for (int i = 0; i < 2; i++) {
        move1[i][0] = move2[i][0];
        move1[i][1] = move2[i][1];
    }
}

void copyGame(int game1[][8], int game2[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game1[i][j] = game2[i][j];
        }
    }
}

void invertMove(int move1[][2], int move2[][2]) {
    for (int i = 0; i < 2; i++) {
        move1[i][0] = 7 - move2[i][0];
        move1[i][1] = 7 - move2[i][1];
    }
}

void invertGame(int game1[][8], int game2[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game1[i][j] = game2[7 - i][7 - j];
        }
    }
}

bool equalsMove(int move[][2]) {
    return move[0][0] == move[1][0] && move[0][1] == move[1][1];
}

bool pawnValidation(int game1[][8], int move1[][2], int pieceColor) {
    int game[8][8];
    int move[2][2];

    if (pieceColor == 0) {
        invertGame(game, game1);
        invertMove(move, move1);
    } else {
        copyGame(game, game1);
        copyMove(move, move1);
    }

    int destination = game[move[1][1]][move[1][0]];
    int destinationType = destination / 2;
    bool isFirstMove;
    bool isDirectionCorrect;
    int rowDif;
    int maxMoveDistance;

    isFirstMove = move[0][1] == 6;
    isDirectionCorrect = move[0][1] > move[1][1];
    rowDif = move[0][1] - move[1][1];

    if (!isDirectionCorrect) {
        cout << "Pawn can only go fowards!\n";
        return false;
    }

    if (isFirstMove)
        maxMoveDistance = 2;
    else
        maxMoveDistance = 1;
    
    if (destinationType == 0) {
        bool isDestOnSameColumn = move[0][0] == move[1][0];
        if (!isDestOnSameColumn) {
            cout << "Pawn can only advance in a straight line!\n";
            return false;
        }
        if (rowDif > maxMoveDistance) {
            if (isFirstMove)
                cout << "Pawn can only advance at most 2 positions!\n";
            else 
                cout << "Pawn can only advance one position!\n";
            return false;
        } else
            return true;
    } else {
        if (rowDif != 1) {
            cout << "Pawn can only advance one position!\n";
            return false;
        }
        if (!(move[0][0] == (move[1][0] - 1)) || (move[0][0] == (move[1][0] + 1))) {
            cout << "Pawn can only capture diagonally to the left or right!\n";
            return false;
        } else
            return true;
    }
}

bool validateMove(int move[][2], int game[][8], bool whiteTurn) {
    if (equalsMove(move)) {
        cout << "You didn't make a move!\n";
        return false;
    }

    int piece = game[move[0][1]][move[0][0]];
    int pieceColor = piece % 2; //0 for black, 1 for white
    int pieceType = piece / 2;

    if (whiteTurn) {
        if (pieceColor == 0) {
            cout << "It's white's turn!\n";
            return false;
        }
    } else {
        if (pieceColor == 1) {
            cout << "It's black's turn!\n";
            return false;
        }
    }
    
    switch (pieceType) {
        case 1:     //pawn
            return pawnValidation(game, move, pieceColor);
            break;

        case 2:     //bishop
            break;

        case 3:     //knight
            break;

        case 4:     //rook
            break;

        case 5:     //queen
            break;

        case 6:     //king
            break;
    
        default:
            break;
    }
    return false;
}

void performMove(int game[][8], bool &whiteTurn) {
    int move[2][2] = {-1, -1, -1, -1};
    /* 
     * A move consists of 2 sets of coodinates
     * First set is the coords for the piece we want to move
     * Second set is the coords for the place we want to move the piece to
     * A set is made of column nr and row nr
     */
    bool done = false;
    printf("Next move: ");
    while (!done) {
        getMove(move);
        bool validMove = validateMove(move, game, whiteTurn);
        if (validMove) {
            cout << "Valid move!\n";
            game[move[1][1]][move[1][0]] = game[move[0][1]][move[0][0]];
            game[move[0][1]][move[0][0]] = 0;
            done = true;
        } else {
            printf("Invalid move!\nTry again: ");
        }
    }
}

void resetGame(int game[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            game[i][j] = initGame[i][j];
        }
    }
}

int main() {
    SetConsoleTitle(_T("Chess"));    //Sets the window title
    getch();                        //Waits for a key press
    int game[8][8];
    bool whiteTurn = true;          //False = black's turn
    resetGame(game);                //Initializing the game
    int done = false;
    while (!done) {
        printGame(game);                //Displaying the game
        performMove(game, whiteTurn);   //Next move logic
        whiteTurn = !whiteTurn;
    }
    getch();
}
