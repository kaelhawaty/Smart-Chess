#include "Header.h"


Recorder undoArray[1000];
Recorder redoArray[1000];
int pointerUndo = 0;
int pointerRedo = 0;

char* lastPosition(){
    if(pointerUndo == 0){
        return NULL;
    }
    return undoArray[pointerUndo-1].m;
}

 void recordMove(char moveInput[5], char killed){
    for(int i = 0; i < 5; i++){
       undoArray[pointerUndo].m[i] = moveInput[i];
    }
    undoArray[pointerUndo].k = killed;
    pointerUndo++;
    pointerRedo = 0;
}
int redo(char a[][8]){
    if(pointerRedo == 0){
        return 0;
    }
    int x = redoArray[pointerRedo-1].m[1]- '1' , x2 = redoArray[pointerRedo-1].m[3]- '1';
    int y = redoArray[pointerRedo-1].m[0]- 'A', y2 = redoArray[pointerRedo-1].m[2]-'A';
    if(a[x2][y2] != '-' && a[x2][y2] != '.'){
        changeNumOfDead(a[x2][y2], 1);
    }
    undoArray[pointerUndo] = redoArray[pointerRedo-1];
    if(a[x][y] == 'k'){
            kingPos[0] = x2;
            kingPos[1] = y2;
    }
    if(a[x][y] == 'K'){
            kingPos[2] = x2;
            kingPos[3] = y2;
    }
    a[x2][y2] = a[x][y];
    a[x][y] = squareColor(x, y);
    if(redoArray[pointerRedo-1].m[4] != 0){
        a[x2][y2] = redoArray[pointerRedo-1].m[4];
    }
    pointerRedo--;
    pointerUndo++;
    return 1;
}

int undo(char a[][8]){
    if(pointerUndo == 0){
        return 0;
    }
    int x = undoArray[pointerUndo-1].m[3] - '1', x2 = undoArray[pointerUndo-1].m[1] - '1';
    int y = undoArray[pointerUndo-1].m[2] - 'A', y2 = undoArray[pointerUndo-1].m[0] - 'A';
    if(undoArray[pointerUndo-1].m[4] == 0){
        if(a[x][y] == 'k'){
            kingPos[0] = x2;
            kingPos[1] = y2;
        }
        if(a[x][y] == 'K'){
            kingPos[2] = x2;
            kingPos[3] = y2;
        }
        a[x2][y2] = a[x][y];
        a[x][y] = undoArray[pointerUndo-1].k;
    }else{
        a[x2][y2] = a[x][y];
        a[x][y] = undoArray[pointerUndo-1].k;
        if(isupper(a[x2][y2])){
            a[x2][y2] = 'P';
        }else{
            a[x2][y2] = 'p';
        }
    }
    if(undoArray[pointerUndo-1].k != '-' || undoArray[pointerUndo-1].k != '.'){
        changeNumOfDead(a[x][y], -1);
    }
    redoArray[pointerRedo] = undoArray[pointerUndo-1];
    pointerUndo--;
    pointerRedo++;
    return 1;
}
