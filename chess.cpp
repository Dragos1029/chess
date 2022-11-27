#include <iostream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
#include <stdio.h>
#include <tchar.h>
#include <cstring>
#include <climits>
#include <cmath>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

/*
 * 0  = blank
 * 1  = en passant pawn
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

const int testGame [8][8] = {
/*8*/   8 , 0 , 4 , 10, 12, 4 , 0 , 8 ,
/*7*/   2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 ,
/*6*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*5*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*4*/   0 , 0 , 0 , 0 , 13, 0 , 0 , 0 ,
/*3*/   0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
/*2*/   3 , 3 , 3 , 0 , 0 , 0 , 3 , 0 ,
/*1*/   9 , 0 , 5 , 11, 13, 5 , 0 , 9
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

void resetEnPassant(bool isWhite, int game[][8]) {
    int row;
    if (isWhite)
        row = 5;
    else
        row = 2;
    for (int i = 0; i < 8; i++) {
        if (game[row][i] == 1)
            game[row][i] = 0;
    }
}

//TODO: Add Promotion
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
    
    if (rowDif > maxMoveDistance) {
        if (isFirstMove)
            cout << "Pawn can only advance at most 2 positions!\n";
        else 
            cout << "Pawn can only advance one position!\n";
        return false;
    }
    if (rowDif == 2 && game[move[0][1] - 1][move[0][0]] / 2 != 0) {
        cout << "Pawn can not jump over pieces!\n";
        return false;
    }
    if (destination == 0) {
        bool isDestOnSameColumn = move[0][0] == move[1][0];
        if (!isDestOnSameColumn) {
            cout << "Pawn can only advance in a straight line!\n";
            return false;
        }
    } else {
        if (move[0][0] != (move[1][0] - 1) && move[0][0] != (move[1][0] + 1)) {
            cout << "Pawn can only capture diagonally to the left or right!\n";
            return false;
        }
    }
    game1[move1[1][1]][move1[1][0]] = game1[move1[0][1]][move1[0][0]];
    game1[move1[0][1]][move1[0][0]] = 0;
    if (rowDif == 2) {
        int add;
        if (pieceColor)
            add = -1;
        else add = 1;
        game1[move1[0][1] + add][move1[0][0]] = 1;
    }
    if (destination == 1) {
        int add;
        if (pieceColor)
            add = 1;
        else add = -1;
        game1[move[1][1] + add][move[1][0]] = 0;
    }
    return true;
}

bool bishopValidation(int game[][8], int move[][2]) {
    int columnDif = move[1][0] - move[0][0];
    int rowDif = move[1][1] - move[0][1];
    int rowMod = 1;
    int colMod = 1;
    if (move[0][1] > move[1][1])
        rowMod = -1;
    if (move[0][0] > move[1][0])
        colMod = -1;
    if (columnDif * colMod != rowDif * rowMod) {
        cout << "Bishop can only move diagonaly!\n";
        return false;
    }
    for (int i = 1; i < rowDif * rowMod; i++) {
        int row = move[0][1] + i * rowMod;
        int col = move[0][0] + i * colMod;
        if (game[row][col] / 2 != 0) {
            cout << "Bishop can not jump over pieces\n";
            return false;
        }
    }
    game[move[1][1]][move[1][0]] = game[move[0][1]][move[0][0]];
    game[move[0][1]][move[0][0]] = 0;
    return true;
}

bool knightValidation(int game[][8], int move[][2]) {
    int columnDif = abs(move[1][0] - move[0][0]);
    int rowDif = abs(move[1][1] - move[0][1]);
    bool longCol = columnDif == 2 && rowDif == 1;
    bool longRow = columnDif == 1 && rowDif == 2;
    if (!longRow && !longCol) {
        cout << "Knight can only move in an L shape!\n";
        return false;
    }
    game[move[1][1]][move[1][0]] = game[move[0][1]][move[0][0]];
    game[move[0][1]][move[0][0]] = 0;
    return true;
}

bool rookValidation(int game[][8], int move[][2]) {
    int columnDif = abs(move[1][0] - move[0][0]);
    int rowDif = abs(move[1][1] - move[0][1]);
    bool longCol = rowDif == 0;
    bool longRow = columnDif == 0;
    if (!longRow && !longCol) {
        cout << "Rook can only move in a straight line!\n";
        return false;
    }
    bool isRow = rowDif > columnDif;
    bool ascending = move[1][0] > move[0][0];
    if (isRow)
        ascending = move[1][1] > move[0][1];
    int iMod = -1;
    if (ascending)
        iMod = 1;
    for (int i = 1; i < columnDif + rowDif; i++) {
        int row = move[0][1];
        int column = move[0][0];
        int add = i * iMod;
        if (isRow)
            row += add;
        else column += add;
        if (game[row][column] / 2 != 0) {
            cout << "Rook cannot jump over other pieces!\n";
            return false;
        }
    }
    game[move[1][1]][move[1][0]] = game[move[0][1]][move[0][0]];
    game[move[0][1]][move[0][0]] = 0;
    return true;
}

bool queenValidation(int game[][8], int move[][2]) {
    int columnDif = move[1][0] - move[0][0];
    int rowDif = move[1][1] - move[0][1];
    bool diagonal = abs(columnDif) == abs(rowDif);
    bool vertical = columnDif == 0;
    bool horizontal = rowDif == 0;
    bool straight = vertical || horizontal;
    if (!diagonal && !straight) {
        cout << "Queen can only move in straight or diagonal lines!\n";
        return false;
    }
    int rowMod = 1;
    int colMod = 1;
    if (columnDif < 0)
        colMod = -1;
    if (rowDif < 0)
        rowMod = -1;
    if (horizontal)
        rowMod = 0;
    if (vertical)
        colMod = 0;
    for (int i = 1; i < max(abs(columnDif), abs(rowDif)); i++) {
        int row = move[0][1] + i * rowMod;
        int col = move[0][0] + i * colMod;
        if (game[row][col] / 2 != 0) {
            cout << "Queen can not jump over pieces!\n";
            return false;
        }
    }
    game[move[1][1]][move[1][0]] = game[move[0][1]][move[0][0]];
    game[move[0][1]][move[0][0]] = 0;
    return true;
}

bool kingValidation(int game[][8], int move[][2]) {
    int columnDif = move[1][0] - move[0][0];
    int rowDif = move[1][1] - move[0][1];
    if (abs(columnDif) > 1 || abs(rowDif) > 1) {
        cout << "King can move at most one position!\n";
        return false;
    }
    game[move[1][1]][move[1][0]] = game[move[0][1]][move[0][0]];
    game[move[0][1]][move[0][0]] = 0;
    return true;
}

bool validateMove(int move[][2], int game[][8], bool whiteTurn) {
    if (equalsMove(move)) {
        cout << "You didn't make a move!\n";
        return false;
    }

    int piece = game[move[0][1]][move[0][0]];
    int destination = game[move[1][1]][move[1][0]];
    int pieceColor = (piece - 2) % 2; //0 for black, 1 for white
    int pieceType = piece / 2;

    resetEnPassant(whiteTurn, game);
    if (pieceType != 0 && whiteTurn) {
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
    if (destination / 2 != 0 && destination % 2 == pieceColor) {
        cout << "U can not capture your own piece!\n";
        return false;
    }

    switch (pieceType) {
        case 1:     //pawn
            return pawnValidation(game, move, pieceColor);
            break;

        case 2:     //bishop
            return bishopValidation(game, move);
            break;

        case 3:     //knight
            return knightValidation(game, move);
            break;

        case 4:     //rook
            return rookValidation(game, move);
            break;

        case 5:     //queen
            return queenValidation(game, move);
            break;

        case 6:     //king
            return kingValidation(game, move);
            break;
    
        default:
            cout << "No piece to move!\n";
            break;
    }
    return false;
}

void findKings(int game[][8], int kings[2][2]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piece = game[i][j];
            int pieceType = piece / 2;
            int pieceColor = piece % 2;
            if (pieceType == 6) {
                kings[pieceColor][0] = j;
                kings[pieceColor][1] = i;
            }
        }
    }
}

bool isPosInCheck(int game[][8], int pos[], bool colorToCheck, int posThatChecks[]) {
    int rowPos = pos[1];
    int colPos = pos[0];
    cout << "diagonal check\n";
    for (int rowMod = -1; rowMod <= 1; rowMod += 2) {
        cout << "rowMod: " << rowMod << "\n";
        for (int colMod = -1; colMod <= 1; colMod += 2) {
            cout << "colMod: " << colMod << "\n";
            int i = 0;
            while (true) {
                i++;
                int row = rowPos + rowMod * i;
                int col = colPos + colMod * i;
                if (max(row, col) > 7 || min(row, col) < 0)
                    break;
                cout << "row: " << row << " col: "<< col <<  "\n";
                int piece = game[row][col];
                int pieceType = piece / 2;
                int pieceColor = piece % 2;
                if (pieceType != 0) {
                    if (pieceColor == colorToCheck) {
                        if (pieceType == 2 || pieceType == 5) {
                            posThatChecks[0] = col;
                            posThatChecks[1] = row;
                            return true;
                        } else break;
                    } else break;
                }
            }
        }
    }
    cout << "straight check\n";
    for (int isRow = 0; isRow <= 1; isRow++) {
        cout << "isRow: " << isRow << "\n";
        for (int mod = -1; mod <= 1; mod += 2) {
            cout << "mod: " << mod << "\n";
            int i = 0;
            while (true) {
                i++;
                int row = rowPos + mod * i * isRow;
                int col = colPos + mod * i * (!isRow);
                if (max(row, col) > 7 || min(row, col) < 0)
                    break;
                cout << "row: " << row << " col: "<< col <<  "\n";
                int piece = game[row][col];
                int pieceType = piece / 2;
                int pieceColor = piece % 2;
                if (pieceType != 0) {
                    if (pieceColor == colorToCheck) {
                        if (pieceType == 4 || pieceType == 5) {
                            posThatChecks[0] = col;
                            posThatChecks[1] = row;
                            return true;
                        } else break;
                    } else break;
                }
            }
        }
    }
    return false;
}

int validateCheck(int move[][2], int game[][8], bool whiteTurn) {
    int kings[2][2];
    findKings(game, kings);
    return 0;
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
    int newGame[8][8];
    printf("Next move: ");
    while (!done) {
        getMove(move);
        copyGame(newGame, game);
        bool validMove = validateMove(move, newGame, whiteTurn);
        if (validMove) {
            cout << "Valid move!\n";
            copyGame(game, newGame);
            done = true;
        } else {
            printf("Invalid move!\nTry again: ");
        }
        int check = validateCheck(move, newGame, whiteTurn);
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
    SetConsoleTitle(_T("Chess"));       //Sets the window title
    getch();                            //Waits for a key press
    int game[8][8];
    bool whiteTurn = true;              //False = black's turn
    resetGame(game);                    //Initializing the game
    int done = false;
    while (!done) {
        int pos[2] = {3, 3};
        int posThatChecks[2];
        isPosInCheck(game, pos, 0, posThatChecks);
        printGame(game);                //Displaying the game
        performMove(game, whiteTurn);   //Next move logic
        whiteTurn = !whiteTurn;
    }
    getch();
}
