
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   
#include <time.h>    
#include "board.h"
#include "game.h"
#include "search.h"

// 获取玩家落子位置
int get_player_move(int board[N][N], int current_player, int *out_row, int *out_col) {
    int r = N / 2, c = N / 2; // 光标默认在正中间
    int key;
    
    while (1) {
        printboard_cursor(board, r, c);
        printf("\n>>> 当前轮到: %s 玩家\n", current_player == BLACK ? "黑棋 (X)" : "白棋 (O)");
        
        key = _getch(); // 读取键盘，不需要按回车

        // 处理方向键 (方向键返回两个字节)
        if (key == 224 || key == 0) {
            key = _getch();
            if (key == 72) { if (r > 0) r--; }      // 上
            else if (key == 80) { if (r < N-1) r++; } // 下
            else if (key == 75) { if (c > 0) c--; }   // 左
            else if (key == 77) { if (c < N-1) c++; } // 右
        } 
        // 处理 W A S D
        else if (key == 'w' || key == 'W') { if (r > 0) r--; }
        else if (key == 's' || key == 'S') { if (r < N-1) r++; }
        else if (key == 'a' || key == 'A') { if (c > 0) c--; }
        else if (key == 'd' || key == 'D') { if (c < N-1) c++; }
        // 处理空格 (落子)
        else if (key == 32) { 
            if (placestone(board, r, c, current_player)) {
                *out_row = r;
                *out_col = c;
                return 1; 
            }
        }
    }
}

void startgame(void){
    int board[N][N];
    initboard(board);

    int gameover = 0;
    int movecount = 0;
    int current_player = BLACK;
    
    while(!gameover){
        int row, col;
        get_player_move(board, current_player, &row, &col);
        movecount++;

        if (check(board, row, col, current_player)){
            printboard(board);
            printf("\n🎉 恭喜 %s 获胜!\n", current_player == BLACK ? "黑棋" : "白棋");
            gameover = 1;
        } else if(equal_game(board, row, col)){
            printboard(board);
            printf("\n🤝 平局,游戏结束\n");
            gameover = 1;
        } else {
            current_player = (current_player == BLACK) ? WHITE : BLACK;
        }
    }
}

void startAIGame(void){
    int board[N][N];
    initboard(board);

    int current_player = BLACK;
    int ai_player = WHITE;    
    int human_player = BLACK; 
    int depth = 3;

    int choice;
    // 先后手选择
    printf("\n请选择你的先后手 (1.执黑先手  2.执白后手): ");
    scanf("%d", &choice);
    while(getchar() != '\n');
    if (choice == 2){
        human_player = WHITE;
        ai_player = BLACK;
        current_player = BLACK;
    }
    
    // 难度选择
    printf("请选择 AI 难度 (1.简单(深度2)  2.普通(深度3)  3.困难(深度4)): ");
    scanf("%d", &choice);
    while(getchar() != '\n');
    if (choice == 1) depth = 2;
    else if (choice == 3) depth = 4;
    
    printf("\n设置完成即将开始游戏...\n按回车键继续...");
    getchar(); // 暂停

    int gameover = 0;

    // AI先手直接下中心
    if (ai_player == BLACK) {
        placestone(board, N/2, N/2, ai_player);
        current_player = human_player;
    }

    while(!gameover){
        if (current_player == human_player) {
            // --- 你的回合 ---
            int row, col;
            get_player_move(board, current_player, &row, &col);
            
            if (check(board, row, col, current_player)){
                printboard(board);
                printf("\n🎉 恭喜你，你战胜了 AI!\n");
                gameover = 1;
            } else if(equal_game(board, row, col)){
                printboard(board);
                printf("\n🤝 平局,游戏结束\n");
                gameover = 1;
            } else {
                current_player = ai_player;
            }
            
        } else {
            // --- AI 的回合 ---
            printboard(board);
            printf("\n🤖 AI 正在思考中 (深度 %d)...\n", depth);
            clock_t start_time = clock();
            
            Move aiMove = findbestmove(board, ai_player, human_player, depth);
            
            clock_t end_time = clock();
            double timespent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            
            placestone(board, aiMove.r, aiMove.c, current_player);
            
            if (check(board, aiMove.r, aiMove.c, current_player)){
                printboard(board);
                printf("\n💀 AI 获胜！你输了。\n");
                gameover = 1;
            } else if(equal_game(board, aiMove.r, aiMove.c)){
                printboard(board);
                printf("\n🤝 平局,游戏结束\n");
                gameover = 1;
            } else {
                current_player = human_player; 
            }
            
            
            printf("\n(系统提示: AI 刚刚下在了 %d %d,思考耗时 %.2f 秒)\n", aiMove.r, aiMove.c, timespent);
            printf("按任意键继续...");
            _getch(); 
        }
    }
}

void show_menu(void){
    printf("\n===== 五子棋游戏 =====\n");
    printf("1. 开始游戏 (人人对战)\n");
    printf("2. 开始游戏 (人机对战)\n");
    printf("3. 退出\n");
    printf("请选择 (1-3): ");
}