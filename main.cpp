#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Header.h"
#define MAX_WINDOWS_WIDTH 512
#define MAX_WINDOWS_HEIGHT 512
char moveInput[5];
char a[8][8];
bool quit = false;
int turn = 0;
int flagMute , flagGrave;
int fl;
SDL_Rect draw_rect;
SDL_Window *window, *graveYard;
SDL_Renderer * renderer, *rendererG;
SDL_Texture *start, *pieces, *yard, *cover;
SDL_Rect start_rect, grave_rect;
int countAlive(char a[][8]){
    int counter = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(a[i][j] != '-' && a[i][j] != '.'){
                counter++;
            }
        }
    }
    return counter;
}

void generateRect(int x, int y){
    draw_rect.x = 64*x;
    draw_rect.y = 64*y;
    draw_rect.h = 64;
    draw_rect.w = 64;
}
void print(){
    SDL_RenderClear(renderer);
    int i, j, x;
    SDL_RenderCopy(renderer, start, NULL, &start_rect);
    if(moveInput[0] != 0){
        pieces  =  IMG_LoadTexture(renderer, "images/select.png");
        generateRect(moveInput[0] - 'A' , moveInput[1] - '1');
        SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
        SDL_DestroyTexture(pieces);
        compute(a,moveInput[1] - '1', moveInput[0] - 'A' );
        pieces  =  IMG_LoadTexture(renderer, "images/possible.png");
        for(int i = 0; i < 30 && possibleMoves[i].x != -1; i++){
            if(tolower(a[moveInput[1] - '1'][moveInput[0] - 'A' ]) == 'k' || !isCheckedAfter(a, moveInput[1] - '1', moveInput[0] - 'A' , possibleMoves[i].x, possibleMoves[i].y)){
                generateRect( possibleMoves[i].y, possibleMoves[i].x);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
            }
        }
        SDL_DestroyTexture(pieces);
    }
    if(isChecked(a,kingPos[0], kingPos[1], 0)){
        pieces  =  IMG_LoadTexture(renderer, "images/check.png");
        generateRect(kingPos[1] , kingPos[0]);
        SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
        SDL_DestroyTexture(pieces);
    }
    if(isChecked(a,kingPos[2], kingPos[3], 1)){
        pieces  =  IMG_LoadTexture(renderer, "images/check.png");
        generateRect(kingPos[3] , kingPos[2]);
        SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
        SDL_DestroyTexture(pieces);
    }
    for(i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
        switch(tolower(a[i][j]))
        {
            case 'p':
            {
                pieces = isupper(a[i][j]) ? IMG_LoadTexture(renderer, "images/BlackPawn.png") : IMG_LoadTexture(renderer, "images/WhitePawn.png");
                generateRect(j, i);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
                break;
                }
            case 'r':
            {
                pieces = isupper(a[i][j]) ? IMG_LoadTexture(renderer, "images/BlackRook.png") : IMG_LoadTexture(renderer, "images/WhiteRook.png");
                generateRect(j, i);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
                break;
                }

                case 'n':
            {
                pieces = isupper(a[i][j]) ? IMG_LoadTexture(renderer, "images/BlackKnight.png") : IMG_LoadTexture(renderer, "images/WhiteKnight.png");
                generateRect(j, i);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
                break;
                }
                case 'b':
            {
               pieces = isupper(a[i][j]) ? IMG_LoadTexture(renderer, "images/BlackBishop.png") : IMG_LoadTexture(renderer, "images/WhiteBishop.png");
                generateRect(j, i);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
                break;
                }
                case 'q':
            {
                pieces = isupper(a[i][j]) ? IMG_LoadTexture(renderer, "images/BlackQueen.png") : IMG_LoadTexture(renderer, "images/WhiteQueen.png");
                generateRect(j, i);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
                break;
                }
                case 'k':
            {
                pieces = isupper(a[i][j]) ? IMG_LoadTexture(renderer, "images/BlackKing.png") : IMG_LoadTexture(renderer, "images/WhiteKing.png");
                generateRect(j, i);
                SDL_RenderCopy(renderer, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
                break;
                }
            }
        }
        }
        SDL_RenderPresent(renderer);
        SDL_INIT_AUDIO;

}
void deadPiecePosition(int *x, int *y){
    if (*x > 6){
        (*y)++;
        *x = 0;
    }
    else{
        (*x)++;
    }
}
void printGraveYard(){
    SDL_RenderClear(rendererG);
    int i, x = 0, y = 0;
    SDL_RenderCopy(rendererG, yard, NULL, &grave_rect);
    for (i = 0; i < deadBlackPieces[0]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/BlackPawn.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadBlackPieces[1]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/BlackRook.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadBlackPieces[2]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/BlackKnight.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadBlackPieces[3]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/BlackBishop.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadBlackPieces[4]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/BlackQueen.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    x = 0; y = 2;
        for (i = 0; i < deadWhitePieces[0]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/WhitePawn.png");
              generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadWhitePieces[1]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/WhiteRook.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadWhitePieces[2]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/WhiteKnight.png");
               generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadWhitePieces[3]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/WhiteBishop.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    for (i = 0; i < deadWhitePieces[4]; i++)
    {
                pieces = IMG_LoadTexture(rendererG, "images/WhiteQueen.png");
                generateRect(x, y);
                deadPiecePosition(&x, &y);
                SDL_RenderCopy(rendererG, pieces, NULL, &draw_rect);
                SDL_DestroyTexture(pieces);
    }
    SDL_RenderPresent(rendererG);
}
void Promotion(){
    SDL_Window *promotion = SDL_CreateWindow("Promotion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256, 64 , SDL_WINDOW_SHOWN);
    SDL_Renderer *r = SDL_CreateRenderer(promotion, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *icon = IMG_Load("images/Icon.png");
    SDL_SetWindowIcon(promotion, icon);
    SDL_FreeSurface(icon);
    SDL_Texture *p;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderClear(r);
    for(int i = 0; i < 4; i++){
        switch(i){
            case 0:
                p = (!(turn%2)) ? IMG_LoadTexture(r, "images/WhiteQueen.png") : IMG_LoadTexture(r, "images/BlackQueen.png");
                generateRect(i,0);
                SDL_RenderCopy(r, p, NULL, &draw_rect);
                SDL_DestroyTexture(p);
                break;
            case 1:
                p = (!(turn%2)) ? IMG_LoadTexture(r, "images/WhiteBishop.png") : IMG_LoadTexture(r, "images/BlackBishop.png");
                generateRect(i,0);
                SDL_RenderCopy(r, p, NULL, &draw_rect);
                SDL_DestroyTexture(p);
                break;
            case 2:
                p = (!(turn%2)) ? IMG_LoadTexture(r, "images/WhiteRook.png") : IMG_LoadTexture(r, "images/BlackRook.png");
                generateRect(i,0);
                SDL_RenderCopy(r, p, NULL, &draw_rect);
                SDL_DestroyTexture(p);
                break;
            case 3:
                p = (!(turn%2)) ? IMG_LoadTexture(r, "images/WhiteKnight.png") : IMG_LoadTexture(r, "images/BlackKnight.png");
                generateRect(i,0);
                SDL_RenderCopy(r, p, NULL, &draw_rect);
                SDL_DestroyTexture(p);
                break;

        }
    }
    SDL_RenderPresent(r);
    SDL_Event event;
    SDL_PollEvent(&event);
    int flag = 0;
    while(!flag){
      while(event.type != SDL_MOUSEBUTTONDOWN){
        SDL_PollEvent(&event);
      }
      int x, y;
      SDL_GetMouseState(&x, &y);
      if(x >= 0 && x <=64 && event.motion.windowID == SDL_GetWindowID(promotion) ){
        moveInput[4] = (turn%2) ? 'Q' : 'q';
        flag = 1;
      }else if(x > 64 && x <= 128 && event.motion.windowID == SDL_GetWindowID(promotion) ){
        moveInput[4] = (turn%2) ? 'B' : 'b';
        flag = 1;
      }else if( x > 128 && x <= 192  && event.motion.windowID == SDL_GetWindowID(promotion) ){
        moveInput[4] = (turn%2) ? 'R' : 'r';
        flag = 1;
      }else if(x > 192 && x <= 256 && event.motion.windowID == SDL_GetWindowID(promotion) ){
        moveInput[4] = (turn%2) ? 'N' : 'n';
        flag = 1;
      }
        SDL_PollEvent(&event);
    }
    SDL_SetWindowGrab(promotion, SDL_FALSE);
    SDL_DestroyWindow(promotion);
    SDL_DestroyRenderer(r);
}
void handleEvents(){
    SDL_Event event;
    int flag = 0;
    while(!flag){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE && SDL_GetWindowID(window) == event.window.windowID) {
                quit = true;
                flag = 1;
                }
                if(event.window.event == SDL_WINDOWEVENT_CLOSE && SDL_GetWindowID(graveYard) == event.window.windowID) {
                    SDL_HideWindow(graveYard);
                }
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym== SDLK_z){
                    flag = undo(a);
                    if(flag){
                        turn++;
                    }
                if (fl == 1){
                    flag = undo(a);
                    if(flag){
                        turn++;
                    }
                }
                }
                if(event.key.keysym.sym == SDLK_x){
                    flag = redo(a);
                    if(flag){
                        turn++;
                    }
                if (fl == 1){
                    flag = redo(a);
                    if(flag){
                        turn++;
                    }
                }
                }
                if(event.key.keysym.sym == SDLK_s){
                    flag = save();
                }
                if(event.key.keysym.sym == SDLK_l){
                    flag = load();
                }
                if(event.key.keysym.sym == SDLK_m){
                    flagMute = !flagMute;
                }
                if(event.key.keysym.sym == SDLK_g){
                    SDL_ShowWindow(graveYard);
                    printGraveYard();
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x,&y);
                if(isupper(a[y/64][x/64]) == turn%2 && a[y/64][x/64] != '.' && a[y/64][x/64] != '-' &&  event.motion.windowID == SDL_GetWindowID(window) ){
                    moveInput[0] = x/64 + 'A';
                    moveInput[1] = y/64 + '1';
                    print();
                }
                if((isupper(a[y/64][x/64]) != turn%2 || a[y/64][x/64] == '.' || a[y/64][x/64] == '-') && ((x/64 + 'A') != moveInput[0] ||  (y/64 + '1') != moveInput[1]) && event.motion.windowID == SDL_GetWindowID(window) ){
                    moveInput[2] = x/64 + 'A';
                    moveInput[3] = y/64 + '1';
                    moveInput[4] = 0;
                    if((a[moveInput[1] - '1'][moveInput[0]-'A'] == 'p' && moveInput[3] == '1') || (a[moveInput[1] - '1'][moveInput[0]-'A'] == 'P' && moveInput[3] == '8' && event.motion.windowID == SDL_GetWindowID(window) )){
                        Promotion();
                    }
                    flag = doTurn(turn, moveInput);
                    if(flag){
                        turn++;
                    }
                }

                break;

        }
    }
    for(int i = 0; i < 5; i++){
        moveInput[i] = 0;
    }

}



int main( int argc, char * argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
     SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
     return 1;
    }
    int w, h;
    w = dm.w;
    h = dm.h;
    graveYard = SDL_CreateWindow("Grave Yard", w/2+256 ,h/2-128,MAX_WINDOWS_WIDTH,256,SDL_WINDOW_HIDDEN);
    rendererG = SDL_CreateRenderer(graveYard, -1, SDL_RENDERER_ACCELERATED);

    window = SDL_CreateWindow("Chess",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *icon = IMG_Load("images/Icon.png");
    SDL_SetWindowIcon(window, icon);
    SDL_SetWindowIcon(graveYard, icon);
    SDL_FreeSurface(icon);
    start = IMG_LoadTexture(renderer, "images/chessBack.jpg");
    cover = IMG_LoadTexture(renderer, "images/cover.jpg");
    yard = IMG_LoadTexture(rendererG, "images/graveYard.png");
    start_rect.x = 0;
    start_rect.y = 0;
    start_rect.h = MAX_WINDOWS_HEIGHT;
    start_rect.w = MAX_WINDOWS_WIDTH;
    grave_rect.x = 0;
    grave_rect.y = 0;
    grave_rect.h = 256;
    grave_rect.w = MAX_WINDOWS_WIDTH;
    SDL_RenderCopy(renderer, cover, NULL, &start_rect);
    SDL_RenderPresent(renderer);
    while(!fl && !quit)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_CLOSE && SDL_GetWindowID(window) == event.window.windowID){
                quit = true;
                }
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym== SDLK_1){
                    fl = 1;
                    break;
                }
                if(event.key.keysym.sym== SDLK_2){
                    fl = 2;
                    break;
                }
                else
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Wrong key","Please enter 1 or 2", NULL);
        }
    }
    while(!quit)
    {
        copyCheckBoard(a, chessBoard);
        print();
        int z, k;

        while(!(z =isCheckmate()) && !(k = isStalemate()) && !quit){
            int flag = 0;
            int f3 = 0;
            if(turn %2 == 1 && fl == 1){
                if(countAlive(a) <= 5){
                minimax(a, 6, 0, -9999, 9999, 6);
                }else if(countAlive(a) <= 10){
                    minimax(a, 5, 0, -9999, 9999, 5);
                }else{
                    minimax(a, 4, 0, -9999, 9999,4);

                }
                doMove(a, BestMove);
                turn++;
            }else{
            handleEvents();
            }
            print();
            if(!flagMute){
            Mix_Chunk *wave = NULL;
            Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
            wave = Mix_LoadWAV("hhh.wav");
            Mix_PlayChannel(-1, wave, 0);
            printGraveYard();
        }
    }
    if(z == 1){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Game","White Wins!",   NULL);

    }else if(z == 2){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Game","Black Wins!",   NULL);
    }else if (k == 6){
         SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Game","Stalemate!",   NULL);
    }
    quit = true;
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(graveYard);
    SDL_DestroyRenderer(rendererG);
    SDL_Quit();
    return 0;
}
