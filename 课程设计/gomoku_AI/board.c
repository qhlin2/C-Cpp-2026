#include <stdio.h>
#include "board.h"
#include <stdlib.h> 

void initboard(int board[N][N]){
    for(int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            board[i][j]=EMPTY;
        }
    }
}
//空：.白:O 黑：X  
void printboard(int board[N][N]) {
    system("cls"); 
    
    printf("   ");
    for (int j = 0; j < N; j++) {
        printf("%2d", j); // 占两个字符宽度对齐
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        // 打印行号（0-14）
        printf("%2d ", i);
        
        for (int j = 0; j < N; j++) {
            if (board[i][j] == EMPTY) printf(" .");
            else if (board[i][j] == BLACK) printf(" \033[31mX\033[0m"); // 红色 X
            else if (board[i][j] == WHITE) printf(" \033[34mO\033[0m"); // 蓝色 O
        }
        printf("\n");
    }
    printf("\n");
}

int placestone(int board[N][N] ,int row,int col,int player){
    if(row<0||row>=N||col<0||col>=N){
        return 0;
    }
    //越界
    if(board[row][col]!=EMPTY){
        return 0;  
    }
    //已有子
    board[row][col]=player;
    return 1;
    //成功落子
}

int check(int board[N][N],int r,int c,int player){
    int dir[4][2]={{0,1},{1,0},{1,1},{1,-1}};
    for(int i=0;i<4;i++){
        int count=1;
        int dr=dir[i][0],dc=dir[i][1];
        int nr=r+dr,nc=c+dc;
        while (nr>=0&&nr<=N&&nc>=0&&nc<=N&&board[nr][nc]==player){
            count++;
            nr+=dr;
            nc+=dc;
        }
        dr=-dir[i][0],dc=-dir[i][1];
        nr=r+dr,nc=c+dc;
        while (nr>=0&&nr<=N&&nc>=0&&nc<=N&&board[nr][nc]==player){
            count++;
            nr+=dr;
            nc+=dc;
        }
        if(count>=5){
            return 1;
            //赢了
        }

    }
    return 0;
}

int equal_game(int board[N][N],int row,int col){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(board[i][j]==EMPTY){
                return 0;
            }
        }
    }
    return 1;
}

void printboard_cursor(int board[N][N], int cr, int cc) {
    system("cls");
    printf("【操作提示】使用 W/A/S/D 或 方向键 移动光标，按 空格键 落子\n\n");

    // 打印列号
    printf("   ");
    for (int j = 0; j < N; j++) printf("%2d", j);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%2d ", i); // 打印行号
        for (int j = 0; j < N; j++) {
            
            if (i == cr && j == cc) {
                if (board[i][j] == EMPTY) printf("[\033[32m.\033[0m]"); // 绿 空位
                else if (board[i][j] == BLACK) printf("[\033[31mX\033[0m]"); // 红 黑子
                else printf("[\033[34mO\033[0m]"); // 蓝 白子
            } else {
                // 普通位置
                if (board[i][j] == EMPTY) printf(" .");
                else if (board[i][j] == BLACK) printf(" \033[31mX\033[0m");
                else printf(" \033[34mO\033[0m");
            }
        }
        printf("\n");
    }
}