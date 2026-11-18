#ifndef BOARD_H
#define BOARD_H

#define N 15
#define EMPTY 0
#define BLACK 1
#define WHITE 2

void initboard(int board[N][N]);
void printboard(int board[N][N]);
int placestone(int board[N][N],int row,int col,int player);
int check(int board[N][N],int r,int c,int player);
int equal_game(int board[N][N],int row,int col);
void printboard_cursor(int board[N][N], int cr, int cc);

#endif