#include "Header.h"
char chessBoard[8][8] =  {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'-', '.', '-', '.', '-', '.', '-', '.'},
    {'.', '-', '.', '-', '.','-','.', '-'},
    {'-', '.', '-', '.', '-', '.', '-', '.'},
    {'.', '-', '.', '-', '.','-','.', '-'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};
char deadWhitePieces[5] = {0}; // 0 for pawn, 1 rooks, 2 knight, 3 bishop, 4 queen
char deadBlackPieces[5] = {0}; // 0 for pawn, 1 rooks, 2 knight, 3 bishop, 4 queen
char names[5][10] = {"Pawn", "Rooks", "Knight", "Bishop", "Queen"};
void copyCheckBoard(char temp[][8], char a[][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            temp[i][j] = a[i][j];
        }
    }
}


int checkValidInput(char moveInput[5], int turn){
    int x = moveInput[1]- '1', x2 = moveInput[3] - '1';
    int y = moveInput[0]- 'A';
    if(isupper(a[x][y]) != turn ){
        return 0;
    }
    if('A' > moveInput[0] || moveInput[0] > 'H' || 'A' > moveInput[2] || moveInput[2] > 'H' || '1' > moveInput[1] || moveInput[1] > '8' || '1' > moveInput[3] || moveInput[3] > '8'){
        return 0;
    }
    if(tolower(a[x][y]) ==  'p' &&  ((isupper(a[x][y]))  ? (x == 6 && x2 == 7 ) : (x == 1 && x2 == 0))){
        if(( tolower(moveInput[4]) == 'r' || tolower(moveInput[4]) == 'n' || tolower(moveInput[4]) == 'q' || tolower(moveInput[4]) == 'b') && isupper(moveInput[4]) == turn){
            return 1;
        }
        return 0;
    }else{
        if(moveInput[4] != 0){
            return 0;
        }
    }
    return 1;
}
int doTurn(int turn, char moveInput[5]){
    int flag = 0;// flags
    if(checkValidInput(moveInput, turn%2) && tryMove(a, moveInput[1]- '1',moveInput[0]- 'A', moveInput[3]- '1', moveInput[2]-'A')){
        doMove(a, moveInput);
        flag = 1;
    }
    return flag;
}

int save()
{
    FILE *chess;
    chess = fopen("game.txt", "w");
    for(int i = 0; i < pointerUndo; i++){
        for(int j = 0; j < 5; j++){
          fprintf(chess, "%c" , undoArray[i].m[j]);
        }
    }
    fclose(chess);
    return 1;
}
int load(){
    FILE *chess;
    chess = fopen("game.txt", "r");
    int i = 0;
    if(chess == NULL){
        return 0;
    }
    copyCheckBoard(a,chessBoard);
    kingPos[0] = 7;
    kingPos[1] = 4;
    kingPos[2] = 0;
    kingPos[3] = 4;
    for(int i = 0; i < 5 ; i++){
        deadWhitePieces[i] = 0;
        deadBlackPieces[i] = 0;
    }
    turn = 0;
    char temp[1000][5];
    int c;
    int counter = 0;
    while(1) {
      for(int i = 0; i < 5 && c != -1; i++){
        c = fgetc(chess);
        temp[counter/5][i] = c;
        counter++;
      }
      if(c == -1) {
         break;
      }
   }
    for(int i = 0; i < counter/5; i++){
        doTurn(turn, temp[i]);
        turn++;
    }
    return 1;
}


char squareColor(int x, int y){
  return ((x+y)%2) ? '.' : '-';
}
int canReach(int x, int y, int color){
  int flag = 0;
  for(int i = 0; i < 8 && !flag; i++){
    for(int j = 0; j < 8 && !flag; j++){
      if(isupper(a[i][j]) == color  && a[i][j] != '.' && a[i][j] != '-' && tolower(a[i][j]) != 'k')
      	flag = tryMove(a,i , j, x , y);
    }
  }
  return flag;
}
int isStalemate(){
    int flag = 0;
    char *moveInput;
    moveInput = lastPosition();
    int xw = kingPos[0], yw = kingPos[1], xb = kingPos[2], yb = kingPos[3];
    if(moveInput == NULL || isChecked(a, xw, yw, 0) || isChecked(a, xb, yb, 1))
        return 0;
    flag = 1;
    computeKing(a, xw, yw);
    if (possibleMoves[0].x != -1 && possibleMoves[0].y != -1 && flag)
                    flag = 0;
    if(flag){
        int i, j;
        for(i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                if(islower(a[i][j])){
                    compute(a, i, j);
                    for(int t = 0; possibleMoves[t].x != -1 && i < 30; t++){
                        if (possibleMoves[t].x != -1 && possibleMoves[t].y != -1 && flag && !isCheckedAfter(a, i, j, possibleMoves[t].x, possibleMoves[t].y))
                                    flag = 0;
                    }
                }
            }
        }
    }
    if (!flag){
            flag = 1;
            computeKing(a, xb, yb);
            if (possibleMoves[0].x != -1 && possibleMoves[0].y != -1 && flag)
                        flag = 0;
            if (flag){
                int i, j;
                for(i = 0; i < 8; i++){
                for (j = 0; j < 8; j++){
                    if(isupper(a[i][j])){
                        compute(a, i, j);
                    for(int t = 0; possibleMoves[t].x != -1 && i < 30; t++){
                        if (possibleMoves[t].x != -1 && possibleMoves[t].y != -1 && flag && !isCheckedAfter(a, i, j, possibleMoves[t].x, possibleMoves[t].y))
                                    flag = 0;
                    }
                }
            }
        }
      }
    }

    return flag ? 6 : 0;

}
int isCheckmate(){
    int flag = 0;
    char *moveInput;
    moveInput = lastPosition();
    if(moveInput == NULL){
        return 0;
    }
    int xw = kingPos[0], yw = kingPos[1], xb = kingPos[2], yb = kingPos[3];
    if (isChecked(a,xb,yb, 1) == 1){
      flag = 1;
      computeKing(a,xb, yb);
      if(possibleMoves[0].x != -1){
            flag = 0;
      }
      if(flag){
        int x = moveInput[3] - '1';
        int y = moveInput[2] - 'A';
        if(a[x][y] == 'n'){
          flag = !canReach(x, y, 1);
        }else{
            int d =((x-xb) != 0) ? ((x-xb)/abs((x-xb))) : 0;
            int d1 =((y-yb) != 0) ? ((y-yb)/abs((y-yb))) : 0;
            for(int n = 1 , i = xb + n*d, j = yb+n*d1; i < 8 && i >= 0 && j <8 && j>= 0 && !(i == x && j == y) && flag ; ){
                flag = !canReach(i,j, 1);
                n++;
                i = xb + n*d;
                j = yb + n*d1;
            }
            if(flag){
                flag = !canReach(x, y, 1);
            }
          }
        }
      }
    if(flag){
        return flag;
    }
    if (isChecked(a,xw,yw, 0) == 1){
      flag = 2;
      computeKing(a,xw, yw);
      if(possibleMoves[0].x != -1){
            flag = 0;
      }
      if(flag){
        int x = moveInput[3] - '1';
        int y = moveInput[2] - 'A';
        if(a[x][y] == 'N'){
          flag = (canReach(x, y, 0)) ? 0 : 2;
        }else{
            int d =((x-xw) != 0) ? ((x-xw)/abs((x-xw))) : 0;
            int d1 =((y-yw) != 0) ? ((y-yw)/abs((y-yw))) : 0;
            for(int n = 1 , i = xw + n*d, j = yw+n*d1; i < 8 && i >= 0 && j <8 && j>= 0 && !(i == x && j == y) && flag ; ){
                flag = (canReach(i,j, 0)) ? 0 : 2;
                n++;
                i = xw + n*d;
                j = yw + n*d1;
            }
            if(flag){
                flag = (canReach(x, y, 0)) ? 0 : 2;
                }
              }
            }
        }
        return flag;
}
void blOwh(char a, int n, int k){
  if (islower(a)){
      deadWhitePieces[n]+= k;
  }else{
      deadBlackPieces[n]+= k;
  }
}

void changeNumOfDead(char a, int k){
switch(tolower(a)){
      case 'p' :
    		blOwh(a, 0, k);
        	break;
      case 'r' :
    		blOwh(a, 1, k);
        	break;
      case 'n' :
    		blOwh(a, 2, k);
        	break;
      case 'b' :
    		blOwh(a, 3, k);
        	break;
      case 'q' :
    		blOwh(a, 4, k);
        	break;
    }
}


