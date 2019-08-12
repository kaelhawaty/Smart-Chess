/*This is a header file which contains C function declarations and macro definitions
 to be shared between several source files.*/
#ifndef Header
#define Header
#include <bits/stdc++.h>
using namespace std;

typedef struct{
    int x;
    int y;
} Move;//This structure saves the coordinate of any cell in the board.
typedef struct{
    char m[5]; // moves array
    char k; // killed
} Recorder;
//variables and data structures.
extern char a[8][8];//All pieces of the board in their positions, which are printed on the screen.
extern int pointerUndo;//to keep track the number of undoes.
extern char chessBoard[8][8];//The initial board
extern int kingPos[4];//to get the king position at any time during the game.
extern char BestMove[5];//the best move generated from AI.
extern Recorder undoArray[1000];//array to save all turns and kills.
extern int turn;//turn get values of 0 for first player and 1 for second player.
extern Move possibleMoves[30];//this array has the all possible moves of a piece.
extern char deadWhitePieces[5];//stores the number of each white dead piece.
extern char deadBlackPieces[5];//stores the number of each black dead piece.
extern char names[5][10];//stores the name of pieces.
// functions.
int tryMove(char a[8][8], int x , int y, int x2, int y2);//function return 1 if there is a possible move from position one(x, y) to position two (x2, y2)
void copyCheckBoard(char temp[][8], char a[][8]);//copy the board from array to another one.
char* lastPosition();//to determine the last position (the last one put in the stack of undo array)
void computeKing(char a[][8], int x, int y);//compute the possible moves of king.
void computeQueen(char a[][8], int x, int y);//compute the possible moves of queen.
void computeBishop(char a[][8], int x, int y);//compute the possible moves of bishop.
void computeRooks(char a[][8], int x, int y);//compute the possible moves of rook.
void computeKnight(char a[][8], int x, int y);//compute the possible moves of knight.
void computePawn(char a[][8], int x, int y);//compute the possible moves of pawn.
char squareColor(int x, int y);
int isCheckedAfter(char a[][8], int x, int y, int x2, int y2);//return 1 if there will be a check after move from x, y to x2, y2.
int isCheckmate();//return 1 if there is a checkmate.
int isStalemate();//return 1 if there is a stalemate.
int isChecked(char a[][8],int x, int y, int color);//return 1 if the king is under check.
void compute(char a[8][8], int x , int y);//compute any piece and get its possible moves.
void doMove(char a[8][8], char moveInput[5]);//to do a valid move.
int redo(char a[][8]);//redo function.
int undo(char a[][8]);//undo function.
void changeNumOfDead(char a, int k);//takes a dead piece and count it with dead pieces.
void recordMove(char moveInput[5], char killed);//to record the move and number of dead.
int doTurn(int turn, char moveInput[5]);//do the turn.
float minimax(char a[][8], int depth, int maximizing, float alpha, float beta, int depthInitial );
int load();//load function.
int save();//save function.
#endif

