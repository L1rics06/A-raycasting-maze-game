/*Pay tribute to the legendary programmer John D. Carmack,
 without you there would be no 3D games today */
/*In the Pseudo 3D game, we will try our best to reproduce
Raycasting, which was used in Wolfenstein 3D*/

#include "EngineForGame.cpp" //EngineForDev.cpp includes EngineforGame.cpp

//初始化函数
void initialization(){
  initgraph(WindowsX, WindowsY); 
  srand((unsigned)time(NULL)); //用时间作为随机数种子
  initialize();transform(); //地图相关的初始化
  setfillcolor(WHITE);setlinecolor(WHITE); //画笔颜色初始化
  setbkmode(TRANSPARENT); //将文字显示转化成透明
  loadimage(&img_menu, _T(path1)); //载入图片   
  loadimage(&img_con, _T(path2)); 
  numFromFile = datasFromFile( players, MAX_PLAYERS);//读取排行榜的数据
}



int main() {
  int style;
  do{
  if (style == 3) message(2);
  message(1);
  scanf("%d", &style);}   // 1为2D视角的演示模式 2为正常模式 3为操作说明
  while (style==3);

  initialization();

  if (style == 1) { //演示模式
    EngineFovDev();
    if (checkwin() == 1) congratulation();

  } else if (style == 2) { //游戏模式
    PlaySound("Mili.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    menu();
    cleardevice();    
    EngineForGame();//进入EngineForGame.cpp
    if (checkwin() == 1) {
    while (_getch() != 27) 
    congratulation();
    closegraph();
    players[numFromFile].time=elapsed_time;
    printf("Please enter your name here to record:\n");
    scanf("%49s", players[numFromFile].name);
    infiles();
    }
    if (checkwin() == 2) pity();

  }
  return 0;
}
