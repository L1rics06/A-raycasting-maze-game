#include <conio.h>
#include <cstdio>
#include <easyx.h>
#include <math.h>
#include <mmsystem.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>

#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "MSIMG32.LIB")

#ifndef _CONFIG_H
#define _CONFIG_H

// X Y 表示地图二维数组的X坐标和Y坐标，其中X向右为正，y向下为正
#define mapX 11
#define mapY 11
// WindowsX表示窗口横长像素，WindowsY表示窗口竖直长像素
#define WindowsX 768
#define WindowsY 768

//下面的定义与图片有关
IMAGE img_menu; //主菜单显示图片
IMAGE img_con; //通关图片

// 有关迷宫的宏
#define Wall 1
#define Road 0
#define Start 2
#define End 3
#define PI 3.141592653589793

//玩家的config
struct player_config {
  double x = WindowsX / (mapX + 2) * 1.5;
  double y = WindowsY / (mapY + 2) * 2.5; // 这两行其实是在设置人物初始位置
  double angle = 0;
  double radian; // 表示人物面朝角度(弧度制)
  char input;
  char name[20]; // 玩家名词和完成时间
  double time;
} player;


//以下变量都与时间相关，例如正计时，倒计时
char text_time[50];
char left_time[50];
time_t start_time ;
int totalltime=90; //倒计时计时时间
int seconds; //计时时间
int elapsed_time ;

int mode=60; //这个值是用来选择模式的

//以下变量与收集相关
int item=5;
int get_item=0;
char count_item[50];

// 存放图片的路径
char path1[100] = ".\\mostima.png"; 
char path2[100] = ".\\good.png";

//多线程初始化
pthread_t th; 

//音频文件路径
char path[100] = ".\\step.wav";  

//以下定义与变量与文件读写相关
#define MAX_NAME_LENGTH 50
#define MAX_PLAYERS 100
typedef struct {
    char name[MAX_NAME_LENGTH];
    int time;
} Player;
Player players[MAX_PLAYERS];
int numFromFile, totalPlayers;
FILE *file = fopen("players.txt", "a");
FILE *file2 = fopen("times.txt", "a");
char text_headcount[50];
char text_rank[50];


#endif

