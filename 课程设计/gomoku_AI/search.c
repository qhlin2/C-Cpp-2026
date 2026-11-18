#include<stdio.h>
#include"search.h"
#include"eval.h"


#define INF 100000000
//AI 的已知最小值（因为 AI 在求最大，所以它当前找到的值就是它能保证的最小值，即α

//人类的已知最大值（因为人类在求最小，所以它当前压到的值就是它能允许的最大值，即β
int minimax(int board[N][N],int depth,int isMAX,int aiplayer,int humanplayer,int alpha,int beta){
    if (depth==0)return evaluateboard(board,aiplayer,humanplayer);
    Move moves[50];
    int count=generateMoves(board,aiplayer,humanplayer,moves,20);
    if (count==0)return evaluateboard(board,aiplayer,humanplayer);
    //ai希望最大值
    if (isMAX){
        int bestscore=-INF;

        for(int i=0;i<count;i++){
            int r =moves[i].r,c=moves[i].c;
            board[r][c]=aiplayer;
            if (check(board, r, c, aiplayer)) {
                board[r][c] = EMPTY;
                return 1000000+depth; // 减 depth 是为了让人类选最快赢的步
            }
            int score=minimax(board,depth-1,0,aiplayer,humanplayer,alpha,beta);
            board[r][c]=EMPTY;

            if(score>bestscore){
                bestscore=score;
            }
            if(alpha<bestscore){
                alpha=bestscore;
            }
            if(alpha>=beta){
                break;
            }
        }
        return bestscore;
    }else{//人类希望最小值
        int bestscore=INF;
        for(int i=0;i<count;i++){
            int r =moves[i].r,c=moves[i].c;
            board[r][c]=humanplayer;
            if (check(board, r, c, humanplayer)) {
                board[r][c] = EMPTY;
                return -1000000-depth; 
            }
            int score=minimax(board,depth-1,1,aiplayer,humanplayer,alpha,beta);
            board[r][c]=EMPTY;
            if(score<bestscore){
                bestscore=score;
            }
            if(beta>bestscore){
                beta=bestscore;
            }
            if (alpha>=beta){
                break;
            }
        }
        return bestscore;
    }
}
Move findbestmove(int board[N][N],int aiplayer,int humanplayer,int depth){
     Move moves[50];
    int count=generateMoves(board,aiplayer,humanplayer,moves,50);
    Move bestmove=moves[0];
    int bestscore=-INF;
    int alpha=-INF;
    int beta=INF;

    for(int i=0;i<count;i++){
        int r =moves[i].r,c=moves[i].c;
        board[r][c]=aiplayer;
        if (check(board, r, c, aiplayer)) {
            board[r][c] = EMPTY;
            return moves[i]; 
        }
        int score=minimax(board,depth-1,0,aiplayer,humanplayer,alpha,beta);
        board[r][c]=EMPTY;
        if(score>bestscore){
            bestscore=score;
            bestmove=moves[i];
        }
        if(bestscore>alpha){
            alpha=bestscore;
        }
    }
    return bestmove;
}








