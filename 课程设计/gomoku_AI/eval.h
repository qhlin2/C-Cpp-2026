#ifndef EVAL_H
#define EVAL_H
#include "board.h"

int scorepoint(int board[N][N],int row,int col,int player);
int evaluatemove(int board[N][N],int r,int c,int aiplayer,int humanplayer);
int evaluateboard(int board[N][N],int aiplayer,int humanplayer);


#endif