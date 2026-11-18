#include<stdio.h>
#include"board.h"
#include"game.h"


int main(void){
    int choice;
    while(1){
        show_menu();
        if(scanf("%d",&choice)!=1){
            printf("输入错误，请重新选择！\n");
            while(getchar() != '\n');
            continue;
        }
        if(choice==1){
            startgame();
        }else if (choice==2){
            startAIGame();
        }else if(choice==3){
            printf("感谢游玩,再见！\n");
            break;
        }else{
            printf("无效的选择，请重新输入。\n");
        }

    }
    return 0;


}










