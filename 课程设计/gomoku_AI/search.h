#ifndef SEARCH_H
#define SEARCH_H

#include"board.h"
#include"move.h"

Move findbestmove(int board[N][N],int aiplayer,int humanplayer,int depth);
#endif