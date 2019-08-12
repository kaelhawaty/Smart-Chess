#include "Header.h"

char BestMove[5];
int z = 0;
float King[8][8] =  {
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    { -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    { -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    {  2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0 },
    {  2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0}
};
float Queen[8][8] =  {
    { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
    { -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    { -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    { -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    {  0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    { -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    { -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
    { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
};
float Rook[8][8] =  {
    {  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    {  0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {  0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0}
};
float Bishop[8][8] =  {
    { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    { -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    { -1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
    { -1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
    { -1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
    { -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
    { -1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
    { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
};
float Knight[8][8] =  {
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
    {-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
    {-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
    {-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
    {-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
    {-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
    {-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
};
float Pawn[8][8] =  {
   {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    {5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
    {1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
    {0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
    {0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
    {0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
    {0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
    {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};
float pieceValue(char t, int x, int y){
    float value = 0;
    switch(tolower(t)){
        case 'p':
            value+= (islower(t)) ? 10 : -10;
            value+= (islower(t)) ? Pawn[x][y] : -Pawn[7-x][7-y];
            break;
        case 'n':
            value+= (islower(t)) ? 30 : -30;
            value+= (islower(t)) ? Knight[x][y] : -Knight[7-x][7-y];
            break;
        case 'b':
            value+= (islower(t)) ? 30 : -30;
            value+= (islower(t)) ? Bishop[x][y] : -Bishop[7-x][7-y];
            break;
        case 'r':
            value+= (islower(t)) ? 50 : -50;
            value+= (islower(t)) ? Rook[x][y] : -Rook[7-x][7-y];
            break;
        case 'q':
            value+= (islower(t)) ? 90 : -90;
            value+= (islower(t)) ? Queen[x][y] : -Queen[7-x][7-y];
            break;
        case 'k':
            value+= (islower(t)) ? 900 : -900;
            value+= (islower(t)) ? King[x][y] : -King[7-x][7-y];
            break;
    }
    return value;

}


float evaluateBoard(char a[][8]){
    float value = 0;
    for(int i = 0; i < 8 ; i++){
        for(int j = 0; j < 8; j++){
            if(a[i][j] != '.' && a[i][j] != '-'){
                value += pieceValue(a[i][j], i, j);
            }
        }
    }
    return value;
}
void compute(char a[8][8], int x , int y){
    if(a[x][y] != '-' && a[x][y] != '.'){
      		switch(tolower(a[x][y])){
            		case 'p':
                        computePawn(a,x,y);
                  		break;
                	case 'n':
                        computeKnight(a,x,y);
                  		break;
                	case 'r':
                        computeRooks(a,x,y);
                  		break;
                	case 'b':
                        computeBishop(a,x,y);
                 	    break;
                	case 'q':
                        computeQueen(a,x,y);
                  		break;
                	case 'k':
                		computeKing(a, x , y);
                  		break;
            }
    }
}

float minimax(char a[][8], int depth, int maximizing, float alpha, float beta, int depthInitial ){
    if(depth  == 0 || isCheckmate() || (z = isStalemate())){
        if(z){
            z = 0;
            return 0;
        }
        return evaluateBoard(a);
    }
    if(maximizing){
    float maxEval = -9999;
       for(int i = 0; i < 8 ; i++){
        for(int j = 0; j < 8; j++){
                if(islower(a[i][j]) && maximizing && a[i][j] != '.' && a[i][j] != '-'){
                    if(i == 5 && j == 3 && a[4][4] == 'N'){
                        printf("test");
                    }
                    compute(a, i, j);
                    for(int t = 0; possibleMoves[t].x != -1 && i < 30; t++){
                        if(tolower(a[i][j]) == 'k'|| !isCheckedAfter(a, i ,j, possibleMoves[t].x, possibleMoves[t].y )){
                            int x = possibleMoves[t].x;
                            int y = possibleMoves[t].y;
                            char temp = a[x][y];
                            a[x][y] = a[i][j];
                            a[i][j] = '-';
                            int tempx = kingPos[0];
                            int tempy = kingPos[1];
                            if(tolower(a[x][y]) == 'k' ){
                                kingPos[0] = x;
                                kingPos[1] = y;
                            }
                            int promotion = 0;
                            if(a[x][y] == 'p' && x == 0){
                                a[x][y] = 'q';
                                promotion = 1;
                            }
                            float eval = minimax(a, depth -1, !maximizing, alpha, beta,  depthInitial);
                            if(maxEval != max(maxEval,eval) && depth == depthInitial){
                                BestMove[0] = j+ 'A';
                                BestMove[1] = i+ '1';
                                BestMove[2] = y + 'A';
                                BestMove[3] = x + '1';
                                BestMove[4] = '\0';
                                if(promotion){
                                    BestMove[4] = 'q';
                                }
                            }
                            maxEval = max(maxEval, eval);
                            alpha = max(alpha, eval);
                            if(promotion){
                                a[x][y] = 'p';
                                promotion = 0;
                            }
                            a[i][j] = a[x][y];
                            a[x][y] = temp;
                            kingPos[0] = tempx;
                            kingPos[1] = tempy;
                            compute(a, i, j);
                            if(beta <= alpha){
                                break;
                            }
                        }
                    }
                }
                if(beta <= alpha){
                    break;
                }
            }
            if(beta <= alpha){
                break;
            }
        }
        return maxEval;
    }else{
        float minEval = 9999;
       for(int i = 0; i < 8 ; i++){
        for(int j = 0; j < 8; j++){
                if(islower(a[i][j]) == maximizing && a[i][j] != '.' && a[i][j] != '-'){
                    compute(a, i, j);
                    for(int t = 0; possibleMoves[t].x != -1 && i < 30; t++){
                        if(tolower(a[i][j]) == 'k' ||!isCheckedAfter(a, i ,j, possibleMoves[t].x, possibleMoves[t].y )){
                            int x = possibleMoves[t].x;
                            int y = possibleMoves[t].y;
                            char temp = a[x][y];
                            a[x][y] = a[i][j];
                            a[i][j] = '-';
                            int tempx = kingPos[2];
                            int tempy = kingPos[3];
                            if(tolower(a[x][y]) == 'k' ){
                                kingPos[2] = x;
                                kingPos[3] = y;
                            }
                            int promotion = 0;
                            if(a[x][y] == 'P' && x == 7){
                                a[x][y] = 'Q';
                                promotion = 1;
                            }
                            float eval = minimax(a, depth -1, !maximizing, alpha, beta,  depthInitial);
                            if(minEval != min(minEval,eval) && depth == depthInitial){
                                BestMove[0] = j+ 'A';
                                BestMove[1] = i+ '1';
                                BestMove[2] = y + 'A';
                                BestMove[3] = x + '1';
                                BestMove[4] = '\0';
                                if(promotion){
                                    BestMove[4] = 'Q';
                                }
                            }
                            minEval = min(minEval, eval);
                            beta = min(beta, eval);
                            if(promotion){
                                a[x][y] = 'P';
                                promotion = 0;
                            }
                            a[i][j] = a[x][y];
                            a[x][y] = temp;
                            kingPos[2] = tempx;
                            kingPos[3] = tempy;
                            compute(a, i, j);
                            if(beta <= alpha){
                                break;
                            }
                        }
                    }
                }
                if(beta <= alpha){
                break;
                }
            }
            if(beta <= alpha){
                break;
            }
        }
        return minEval;
    }




}

