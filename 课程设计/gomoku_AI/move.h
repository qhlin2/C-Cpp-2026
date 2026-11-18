#ifndef MOVE_H
#define MOVE_H
#include "board.h"

typedef struct{
    int r,c;
    int score;
}Move;
int generateMoves(int board[N][N],int aiplayer,int humanplayer,Move moves[],int maxmoves);

#endif