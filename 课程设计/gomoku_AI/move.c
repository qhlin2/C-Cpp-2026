#include"move.h"
#include "eval.h"

int hasnear(int board[N][N],int r,int c){
    for (int i=-2;i<=2;i++){
        for (int j=-2;j<=2;j++){
            if(i==0 &&j==0) continue;
            int nr=r+i,nc=c+j;
            if(nr>=0 && nr<N && nc>=0 && nc<N &&board[nr][nc]!=EMPTY){
                return 1;
            }    
        }
    }
    return 0;
}
int generateMoves(int board[N][N],int aiplayer,int humanplayer,Move moves[],int maxmoves){
    int count=0;
    //第一步
    int hasStone=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if (board[i][j]!=EMPTY){
                hasStone=1;
            }
        }
    }
    if(!hasStone){
        moves[0].r=N/2;
        moves[0].c=N/2;
        moves[0].score=0;
        return 1;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if (board[i][j]==EMPTY && hasnear(board,i,j)){
                moves[count].r=i;
                moves[count].c=j;
                moves[count].score=evaluatemove(board,i,j,aiplayer,humanplayer);
                count++;
                if (count>=50) break;
            }
        }
        if(count>=50) break;
    }
    for(int i=0;i<count-1;i++){
        for (int j=0;j<count-i-1;j++){
            if(moves[j].score<moves[j+1].score){
                Move temp=moves[j];
                moves[j]=moves[j+1];
                moves[j+1]=temp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        int tr = moves[i].r, tc = moves[i].c;
        board[tr][tc] = humanplayer;
        if (check(board, tr, tc, humanplayer)) {
            // 如果人类下这里能赢，给这个点加上无法超越的高分
            moves[i].score = 99999999;
        }
        board[tr][tc] = EMPTY;
    }

    // 重新排一次序，让刚加了分的绝杀点跑到最前面
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (moves[j].score < moves[j + 1].score) {
                Move temp = moves[j];
                moves[j] = moves[j + 1];
                moves[j + 1] = temp;
            }
        }
    }

    return (count > maxmoves) ? maxmoves : count;
    
}