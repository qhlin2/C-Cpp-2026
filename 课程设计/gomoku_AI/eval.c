#include<stdio.h>
#include"eval.h"
int getscoreindirection(int board[N][N],int r,int c,int dr,int dc,int player){
    // 1. 以 (r,c) 为中心，提取出长度为 9 的一维数组
    // 0=空位，1=自己，2=对手或墙壁
    int line[9];
    for(int i=-4;i<=4;i++){
        int nr=r+i*dr;
        int nc=c+i*dc;
        if(nr<0||nr>=N||nc<0||nc>=N) line[i+4]=2;
        else if(board[nr][nc]==player) line[i+4]=1;
        else if(board[nr][nc]==EMPTY) line[i+4]=0;
        else line[i+4]=2;
    }
    
    int max_score=0;
    // 滑窗遍历
    for(int i=0;i<=4;i++){
        int self_count=0;
        int empty_count=0;
        for(int j=0;j<5;j++){
            if(line[i+j]==1) self_count++;
            else if(line[i+j]==0) empty_count++;
        }
        
        // 如果窗口里有自己的棋子且没有对手的棋子
        if(self_count>0&&self_count+empty_count==5){
            // 检查是否存在直连（连续3个或2个）
            int is_straight_3=0;
            int is_straight_2=0;
            for(int j=0;j<=2;j++){
                if(line[i+j]==1&&line[i+j+1]==1&&line[i+j+2]==1) is_straight_3=1;
                if(line[i+j]==1&&line[i+j+1]==1) is_straight_2=1;
            }
            
            int score=0;
            // 评估权重
            if(self_count==5) return 1000000; // 五连
            
            if(self_count==4){
                if(line[i]==0&&line[i+4]==0) score=100000; // 活四
                else score=10000; // 冲四 / 跳冲四
            }else if(self_count==3){
                if(line[i]==0&&line[i+4]==0){
                    if(is_straight_3) score=8000; // 直连活三
                    else score=3000; // 跳活三
                }else{
                    if(is_straight_3) score=1000; // 直连眠三
                    else score=300; // 跳眠三
                }
            }else if(self_count==2){
                if(line[i]==0&&line[i+4]==0){
                    if(is_straight_2) score=500; // 直连活二
                    else score=200; // 跳活二
                }else{
                    if(is_straight_2) score=100; // 直连眠二
                    else score=50; // 跳眠二
                }
            }else if(self_count==1){
                score=10; // 单子
            }
            
            if(score>max_score) max_score=score;
        }
    }
    return max_score;
}
    
int scorepoint(int board[N][N], int r, int c, int player) {
    int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    int totalScore = 0;

    for (int i = 0; i < 4; i++) {
        totalScore += getscoreindirection(board, r, c, dirs[i][0], dirs[i][1], player);
    }
    return totalScore;
}
//单点局面评估

int evaluateboard(int board[N][N], int aiplayer, int humanplayer) {
    int total_ai = 0;
    int total_human = 0;
    
    // 遍历整个棋盘的空位，看这些空位对双方的威胁有多大
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == EMPTY) {
                // 如果 AI 下这里，得分多少
                int s_ai = scorepoint(board, i, j, aiplayer);
                // 如果人类下这里，得分多少
                int s_human = scorepoint(board, i, j, humanplayer);
                
                // 取双方的威胁值累加
                total_ai += s_ai;
                total_human += s_human;
            }
        }
    }
    // AI 总分 - 人类总分
    return total_ai - total_human;
}
int evaluatemove(int board[N][N], int r, int c, int aiplayer, int humanplayer) {
    int aiscore = scorepoint(board, r, c, aiplayer);
    int humanescore = scorepoint(board, r, c, humanplayer);

    
    if (humanescore >= 1000000) return 90000000; 
    if (aiscore >= 1000000) return 95000000; 
    if (humanescore >= 100000) return 85000000;
    
    
    if (humanescore >= 10000) {
        if (aiscore >= 3000) return 80000000;
        return 75000000;                      
    }
    
    if (aiscore >= 100000) return 70000000; 
    if (aiscore >= 10000) return 60000000;  
    
    
    if (humanescore >= 3000) {
        if (aiscore >= 3000) return 55000000; 
        return 50000000;                      
    }
    
    if (aiscore >= 3000) return 45000000;

    return aiscore + (int)(humanescore * 1.2);
}