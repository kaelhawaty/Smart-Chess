#include "Header.h"

int kingPos[4] = {7,4,0,4};

Move possibleMoves[30];

void copyP(Move a[], Move b[]){ // Copy structures from one array to another
    for(int i = 0 ; i < 30; i++){
        a[i] = b[i];
    }
}

static int registerMove(int x1, int y1, int moves){
     possibleMoves[moves].x = x1;
     possibleMoves[moves].y = y1;
     return moves+1;
}
void setDefault(Move possibleMoves[]){
    for(int i = 0; i < 30; i++){
        possibleMoves[i].x = -1;
        possibleMoves[i].y = -1;
    }
}
int whiteOrBlack(char a[][8], char type, int x, int y){
			if(islower(type)){
      		return !islower(a[x][y]);
      }
      return !isupper(a[x][y]);
}

int cPMP(char a[][8], int x, int y, int d,int d1, int moves){ //computePossibleMovesPishop
    for(int n = 1 , i = x + n*d, j = y+n*d1; i < 8 && i >= 0 && j <8 && j>= 0; ){
        if(a[i][j] != '-' && a[i][j] != '.'){
            if(!(islower(a[x][y]) ^ islower(a[i][j]))){
                break;
            }
        }
        moves = registerMove(i,j,moves);
        if((islower(a[x][y]) ^ islower(a[i][j])) && a[i][j] != '-' && a[i][j] != '.'){
            break;
        }
        n++;
        i = x + n*d;
        j = y + n*d1;
    }
    return moves;
}
void computeKing(char a[][8], int x, int y){
    int moves = 0;
  	char temp[8][8];
  	Move k[30];
  	setDefault(k);
  	copyCheckBoard(temp ,a);
  	for(int t = -1; t <= 1; t++){
           for(int f = -1; f <= 1; f++){
              if(x+t >= 0 && x+t < 8 && y+f >= 0 && y+f < 8 && whiteOrBlack(a, a[x][y], x+t, y+f) && (t || f )){
                  	temp[x+t][y+f] = a[x][y];
                	temp[x][y] = '.';
                	if(islower(a[x][y])){
                        if(!isChecked(temp, x+t, y+f,  0)){
                            k[moves].x = x+t;
                            k[moves].y = y+f;
                            moves++;
                        }
                    }else{
                        if(!isChecked(temp, x+t, y+f, 1)){
                            k[moves].x = x+t;
                            k[moves].y = y+f;
                            moves++;
                        }

                    }
                    temp[x][y] = a[x][y];
                    temp[x+t][y+f] = a[x+t][y+f];

            }
        }
    }
   copyP(possibleMoves,k);
}
void computeQueen(char a[][8], int x, int y){
    setDefault(possibleMoves);
    int moves = 0;
    moves = cPMP(a,x,y, 1 , 1,moves);
    moves = cPMP(a,x,y, 1 , -1,moves);
    moves = cPMP(a,x,y, -1 , 1,moves);
    moves = cPMP(a,x,y, -1 , -1,moves);
    moves = cPMP(a,x,y, -1 , 0,moves);
    moves = cPMP(a,x,y, 1 , 0,moves);
    moves = cPMP(a,x,y, 0 , -1,moves);
    moves = cPMP(a,x,y, 0 , 1,moves);
}
void computeBishop(char a[][8], int x, int y){
    setDefault(possibleMoves);
    int moves = 0;
    moves = cPMP(a,x,y, 1 , 1,moves);
    moves = cPMP(a,x,y, 1 , -1,moves);
    moves = cPMP(a,x,y, -1 , 1,moves);
    moves = cPMP(a,x,y, -1 , -1,moves);
}

void computeRooks(char a[][8], int x, int y){
      setDefault(possibleMoves);
      int moves = 0;
      moves = cPMP(a,x,y, -1 , 0,moves);
      moves = cPMP(a,x,y, 1 , 0,moves);
      moves = cPMP(a,x,y, 0 , -1,moves);
      moves = cPMP(a,x,y, 0 , 1,moves);
}
void computeKnight(char a[][8], int x, int y){
    setDefault(possibleMoves);
    int moves = 0;
  for (int i = -2; i <= 2; i += 4){
  	for(int j = -1; j <= 1; j += 2 ){
         if(x+i >= 0 && x+i < 8 && y+j >= 0 && y+j < 8 && whiteOrBlack(a,a[x][y], x+i, y+j) ){
              moves = registerMove(x+i, y+j, moves);
         }
         if(y+i >= 0 && y+i < 8 && x+j >= 0 && x+j < 8 &&  whiteOrBlack(a,a[x][y], x+j, y+i) ){
              moves = registerMove(x+j, y+i, moves);
         }
    	}
    }
}
void computePawn(char a[][8], int x, int y){
    setDefault(possibleMoves);
    int moves = 0;
    if(isupper(a[x][y])){
        if(x == 1){
            if((a[x+2][y] == '-' || a[x+2][y] == '.') &&(a[x+1][y] == '-' || a[x+1][y] == '.') ){
                moves = registerMove(x+2, y, moves);
            }
        }
        for (int i = -1; i <= 1; i += 2){
            if (x+1 < 8 && (a[x+1][y] == '-' || a[x+1][y] == '.') ){
                moves = registerMove(x+1, y, moves);
            }
            if(x+1 < 8 && y+i < 8 && y+i >=0){
                if(islower(a[x+1][y+i])){
                    moves = registerMove(x+1, y+i, moves);
                }
            }

        }
    }
    else{
        if(x == 6){
            if((a[x-2][y] == '-' || a[x-2][y] == '.') && (a[x-1][y] == '-' || a[x-1][y] == '.')){
                moves = registerMove(x-2, y, moves);
            }
        }
        for (int i = -1; i <= 1; i += 2){
            if (x-1 >= 0 && (a[x-1][y] == '-' || a[x-1][y] == '.') ){
                moves = registerMove(x-1, y, moves);
            }
            if(x-1 >= 0 && y+i < 8 && y+i >=0 ){
                if(isupper(a[x-1][y+i])){
                    moves = registerMove(x-1, y+i, moves);
                }
            }

        }
    }

}

int checkPossibility(int x , int y){
    int flag = 0;
    for(int i = 0; possibleMoves[i].x != -1 && i < 30 && !flag; i++){
        if(x == possibleMoves[i].x && y == possibleMoves[i].y){
            flag = 1;
        }
    }
    return flag;
}
int isCheckedAfter(char a[][8], int x, int y,int x2,int y2){
    int ans;
    char temp = a[x2][y2];
    a[x2][y2] = a[x][y];
    a[x][y] = '.';
    ans = isChecked(a,kingPos[isupper(a[x2][y2])*2], kingPos[isupper(a[x2][y2])*2+1],isupper(a[x2][y2]));
    a[x][y] = a[x2][y2];
    a[x2][y2] = temp;
    return ans;
}
int tryMove(char a[8][8], int x , int y, int x2, int y2){
    if(a[x][y] != '-' && a[x][y] != '.'){
    		int flag = 0;
      		switch(tolower(a[x][y])){
            		case 'p':
            		    if(!isCheckedAfter(a, x,y, x2 ,y2)){
                          computePawn(a,x,y);
                      		flag = checkPossibility(x2 , y2);
            		    }
                  		break;
                	case 'n':
                		if(!isCheckedAfter(a, x,y, x2 ,y2)){
                          computeKnight(a,x,y);
                      		flag = checkPossibility(x2 , y2);
            		    }
                  		break;
                	case 'r':
                		if(!isCheckedAfter(a, x,y, x2 ,y2)){
                          computeRooks(a,x,y);
                      		flag = checkPossibility(x2 , y2);
            		    }
                  		break;
                	case 'b':
                		if(!isCheckedAfter(a, x,y, x2 ,y2)){
                          computeBishop(a,x,y);
                      		flag = checkPossibility(x2 , y2);
            		    }
                 	    break;
                	case 'q':
                		if(!isCheckedAfter(a, x,y, x2 ,y2)){
                          computeQueen(a,x,y);
                      		flag = checkPossibility(x2 , y2);
            		    }
                  		break;
                	case 'k':
                		computeKing(a, x , y);
                		flag = checkPossibility(x2 , y2);
                  		break;
            }
            return flag;
    }else{
    	return 0;
    }
}
void doMove(char a[8][8], char moveInput[5]){
    int x = moveInput[1]- '1' , x2 = moveInput[3]- '1';
    int y = moveInput[0]- 'A', y2 = moveInput[2]-'A';
    if (a[x][y] == 'K'){
      kingPos[2] = x2;
      kingPos[3] = y2;
    }else if (a[x][y] == 'k'){
      kingPos[0] = x2;
      kingPos[1] = y2;
    }
    if(a[x2][y2] != '-' && a[x2][y2] != '.'){
        changeNumOfDead(a[x2][y2], 1);
    }
    recordMove(moveInput, a[x2][y2]);
    a[x2][y2] = a[x][y];
    a[x][y] = squareColor(x, y);
    if(moveInput[4] != 0){
        a[x2][y2] = moveInput[4];
    }
}
int fFP(char a[][8], int x, int y, int d,int d1){ //Find first piece
    int n, i ,j;
    for(n = 1 , i = x + n*d, j = y+n*d1; i < 8 && i >= 0 && j <8 && j>= 0; ){
        if(a[i][j] != '-' && a[i][j] != '.')
            break;

        n++;
        i = x + n*d;
        j = y + n*d1;
    }
    if(i < 8 && i >= 0 && j <8 && j>= 0){
        char t = tolower(a[i][j]);
        if((d == 0 || d1 == 0) && isupper(a[i][j]) != isupper(a[x][y]) && (t == 'q' || t == 'r' ||  (t == 'k' && n == 1 ) )){
            return 1;
        }
        if((d && d1) && isupper(a[i][j]) != isupper(a[x][y]) && (t == 'q' || t == 'b' ||  (t == 'k' && n == 1 ) || (t == 'p' && n == 1 && ((islower(a[x][y])) ? (d == -1) : (d == 1)) ))){
            return 1;
        }
    }
    return 0;
}
int isChecked(char a[][8],int x, int y, int color){
    int flag = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(i == 0 && j == 0){continue;}
            flag = fFP(a, x, y,i ,j);
            if(flag){return flag;}
        }
    }

    for (int i = -2; i <= 2; i += 4){
  	for(int j = -1; j <= 1; j += 2 ){
         if(x+i >= 0 && x+i < 8 && y+j >= 0 && y+j < 8 && color != isupper(a[x+i][y+j]) && tolower(a[x+i][y+j]) == 'n' ){
            flag = 1;
            return flag;
        }
         if(y+i >= 0 && y+i < 8 && x+j >= 0 && x+j < 8 && color != isupper(a[x+j][y+i]) && tolower(a[x+j][y+i]) == 'n' ){
              flag = 1;
            return flag;
        }
      }
    }
    return flag;
}
