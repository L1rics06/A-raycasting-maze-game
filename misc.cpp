#include "Config.h"


//这些函数与排行榜功能相关
void rank();
void infiles();
int datasFromFile(Player players[], int maxPlayers);
int compare(const void *a, const void *b);

//音效播放线程函数
void * PlaySoundEffect(void *a){
    char command[100];
    sprintf(command, "open \"%s\" type waveaudio alias sfx",path );
    while (1){
        if(player.input=='w'||player.input=='s') {
            mciSendString(command, NULL, 0, NULL); 
            mciSendString("play sfx", NULL, 0, NULL);
            Sleep(1000);  
        }
        mciSendString("close sfx", NULL, 0, NULL);             
    }
    return NULL;
}

//透明PNG图片的函数
void transparentimage(int x,int y,IMAGE img){
	IMAGE img1;
	DWORD *d1;
	img1=img;
	d1=GetImageBuffer(&img1);
	float h,s,l;
	for(int i=0;i<img1.getheight()*img1.getwidth();i++){
		RGBtoHSL(BGR(d1[i]),&h,&s,&l);
		if(l<0.03){
			d1[i]=BGR(WHITE);
		}
		if(d1[i]!=BGR(WHITE)){
			d1[i]=0;
		}
	}
	putimage(x,y,&img1,SRCAND);
	putimage(x,y,&img,SRCPAINT);

}

//储存信息的函数
void message(int a){
  if(a==1){
    printf("Enter '1' to start Dev mode,which will display the 2D theory of this game.\n");
    printf("Enter '2' to start game mode.\n");
    printf("Enter '3' to get game informations.\n");
    printf("Press ESC to exit game.\n");
    for (int i = 0; i < 40; i++) printf("-");
    printf("\n");
  }else if(a==2){
    printf("You are Mostima,the keeper of the lock&keys.\n");
    printf("You are trapped in the maze.\nBreak the white wall and leave here!\n");
    printf("The object of the game is to find the black wall to escape the maze,while you break the barria\n");
    printf("Press W/S to control role to move forward/back.And w/s can control main menu cursor.\n");
    printf("Press A/D to Control the rotational motion of the character.\n");
    printf("Press E to get position for now, which can make find the way.\n");
    printf("When you really can't finish the game, please press P.\n");
    for (int i = 0; i < 40; i++) printf("-");
    printf("\n");
  }
}

//主菜单的绘制 模式的选择
void menu() {
  char input='f';
  settextcolor(WHITE);setfillcolor(WHITE);setlinecolor(WHITE);
  settextstyle(40, 0, _T("Microsoft YaHei"));
  while (mode!=0){
    while (_getch() != 13){
        cleardevice();
        transparentimage(100,50, img_menu);
        outtextxy(WindowsX * 1 / 2-300, WindowsY * 1 / 3, _T("Pseudo 3D random maze"));
        outtextxy(WindowsX * 1 / 4-100, WindowsY * 2 / 3, _T("Start"));
        outtextxy(WindowsX * 2 / 4-100, WindowsY * 2 / 3, _T("Rank"));
        outtextxy(WindowsX * 3 / 4-100, WindowsY * 2 / 3, _T("Exit"));
        outtextxy(WindowsX * 1 / 2-300, WindowsY * 4 / 5, _T("Press A/D and Enter to choose"));
        input = _getch(); // 获取按键
        if (input=='a'||input=='A') mode--;
        else if(input=='d'||input=='D') mode++;
        mode=mode%3;
        if(mode==0){
          fillrectangle(WindowsX * 1 / 4-10,WindowsY * 2 / 3+5,WindowsX * 1 / 4-5,WindowsY * 2 / 3);  
        }
        else if(mode==1){
          fillrectangle(WindowsX * 2 / 4-10,WindowsY * 2 / 3+5,WindowsX * 2 / 4-5,WindowsY * 2 / 3);  
        }
        else if(mode==2){
          fillrectangle(WindowsX * 3 / 4-10,WindowsY * 2 / 3+5,WindowsX * 3 / 4-5,WindowsY * 2 / 3);  
        }
        input='f';
    } 
    if (mode==2) exit(0);
    if (mode==1) rank(); 
  }
}

//排行榜的绘制
void rank(){
    cleardevice();
    sprintf(text_headcount,"Headcount: %d",numFromFile);
    settextcolor(WHITE);setfillcolor(WHITE);setlinecolor(WHITE);
    settextstyle(40, 0, _T("Microsoft YaHei"));
    outtextxy(50,50,_T(text_headcount));
    outtextxy(50,100,_T("Ranking list:"));
    for (int i = 0; i < numFromFile; i++){
        sprintf(text_rank,"%d. %s - %ds",i+1,players[i].name, players[i].time);
        outtextxy(100,150+i*50,_T(text_rank));
    }
    outtextxy(300,600,_T("Press ESC to return"));
}

//开场界面的绘制
void open() {
  settextcolor(WHITE);setfillcolor(WHITE);setlinecolor(WHITE);
  settextstyle(40, 0, _T("Microsoft YaHei"));
  outtextxy((WindowsX -textwidth(_T("You are Mostima,the keeper of the lock&keys"))) /2,
            (WindowsY -textheight(_T("You are Mostima,the keeper of the lock&keys"))) /2 -50,
            _T("You are Mostima,the keeper of the lock&keys"));
  outtextxy((WindowsX - textwidth(_T("You re trapped in the maze."))) / 2,
            (WindowsY - textheight(_T("You re trapped in the maze."))) / 2,
            _T("You re trapped in the maze."));
  outtextxy((WindowsX - textwidth(_T("Break the white wall and leave here!"))) / 2,
            (WindowsY - textheight(_T("Break the white wall and leave here!"))) / 2 + 50,
            _T("Break the white wall and leave here!"));
  outtextxy((WindowsX - textwidth(_T("Press any key......"))) / 2,
            (WindowsY - textheight(_T("Press any key......"))) / 2 + 100,
            _T("Press any key......"));
}

// 通关界面绘制
void congratulation() {
  setbkcolor(RGB(135, 206, 250));
  cleardevice();
  settextcolor(WHITE);
  putimage(150,500, &img_con);
  settextstyle(40, 0, _T("Microsoft YaHei"));
  outtextxy(
      (WindowsX - textwidth(_T("Congratulations on clearing the level!"))) / 2,
      (WindowsY - textheight(_T("Congratulations on clearing the level!"))) /2 -50,
              _T("Congratulations on clearing the level!"));
  outtextxy((WindowsX - textwidth(_T("Press ESC to exit..."))) / 2,
            (WindowsY - textheight(_T("Press ESC to exit..."))) / 2 + 50,
            _T("Press ESC to exit..."));
  outtextxy(125, 200, text_time);
}

//绘制没有通关的函数
void pity(){
  setbkcolor(RGB(135, 206, 250));
  cleardevice();
  settextcolor(WHITE);
  settextstyle(40, 0, _T("Microsoft YaHei"));
  outtextxy(
      (WindowsX - textwidth(_T("What a pity!!!You runned out your time"))) / 2,
      (WindowsY - textheight(_T("What a pity!!!You runned out your time"))) /2 -50,
              _T("What a pity!!!You runned out your time"));
  outtextxy((WindowsX - textwidth(_T("Press ESC to exit..."))) / 2,
            (WindowsY - textheight(_T("Press ESC to exit..."))) / 2 + 50,
            _T("Press ESC to exit..."));
  while (_getch() != 27);
  closegraph();
}

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerA->time - playerB->time;
}

// 从文件中读取玩家数据
int datasFromFile(Player players[], int maxPlayers) {
    FILE *file = fopen("./players.txt", "a+");
    FILE *file2 = fopen("./times.txt", "a+");
    if (!file) {
        perror("File open fail.");
        return -1;
    }
    if (!file2) {
        perror("File open fail.");
        return -1;
    }
    Player player;
    int count = 0;
    while (1) {
        if (count >= maxPlayers) {
            break;
        }
        if ((fscanf(file, "%49s\n", player.name)==1)&&(fscanf(file2, "%d", &player.time)) == 1) {
            players[count++] = player; // 存储读取的玩家数据
        } else {
            break;
        }
    }
    fclose(file);
    fclose(file2);
    return count; // 返回读取的玩家数量
}

// 打开文件
void infiles() {
    file = fopen("./players.txt", "a"); // "a" 表示追加模式，如果文件不存在则创建
    file2 = fopen("./times.txt", "a");
    // 写入新输入的玩家数据
    fprintf(file, "%s\n", players[numFromFile].name);
    fprintf(file2, "%d\n", players[numFromFile].time); 
    fclose(file);
    fclose(file2);
    totalPlayers = 1 + numFromFile; // 新输入的玩家加上文件中读取的玩家数量
    // 对玩家分数进行排序
    qsort(players, totalPlayers, sizeof(Player), compare);
}