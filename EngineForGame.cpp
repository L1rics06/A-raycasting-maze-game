#include "EngineForDev.cpp"


int cell;//线条顶端位置
int Floor;//线条底部位置
int color;//线条颜色
float L;//距离决定灰度
//以上参数伪3D绘制函数

// 90s倒计时函数
void countdown() {
  time_t current_time;
  time(&current_time);
  seconds=difftime(current_time, start_time);
  sprintf(left_time, "Time left: %dS",totalltime-seconds);
}

//记数item并转换成字符串
void countitem(){
  sprintf(count_item,"The barrier has been broken: %d/5",get_item);
}

// 天空地面绘制
void sky_ground() {
  setfillcolor(CYAN);
  fillrectangle(0, 0, WindowsX, WindowsY / 2);
  setfillcolor(BROWN);
  fillrectangle(0, WindowsY / 2, WindowsX, WindowsY);
}

// 在pixelmap中得到每个像素点的颜色值
void get_color() {
  color = pixelmap[(int)(fy + sin(player.radian) * 2)]
                  [(int)(fx + cos(player.radian) * 2)];
}

// 将墙壁颜色转换为响应的颜色值,并且根据distance来确定灰度
void rectangle_color() {
  L = 0.4 / 150 * ldistance + 0.2;
  get_color();
  switch (color) {
  case 1:
    setfillcolor(HSLtoRGB(120, 1, L));
    setlinecolor(HSLtoRGB(120, 1, L));
    break;
  case 2:
    setfillcolor(HSLtoRGB(60, 1, L));
    setlinecolor(HSLtoRGB(60, 1, L));
    break;
  case 3:
    setfillcolor(HSLtoRGB(0, 1, L));
    setlinecolor(HSLtoRGB(0, 1, L));
    break;
  case 4:
    setfillcolor(HSLtoRGB(300, 1, L));
    setlinecolor(HSLtoRGB(300, 1, L));
    break;
  case 5:
    setfillcolor(HSLtoRGB(240, 1, L));
    setlinecolor(HSLtoRGB(240, 1, L));
    break;
  case 6:
    setfillcolor(BLUE);
    setlinecolor(BLUE);
    break;
  case 7:
    setfillcolor(BLACK);
    setlinecolor(BLACK);
    break;
  case 8:
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    break;
  default:
    break;
  }
}

// 伪3D画面的生成，根据反比例函数确定线条长度
void Generation_Frame_3D(int world_map[mapY + 2][mapX + 2]) {
  sky_ground();
  Temp_angle = player.angle;
  countdown();countitem();
  check_collect();
  outtextxy(75, 75, left_time); //倒计时时间
  outtextxy(75, 125, count_item);//统计打破结界数量
  //下面的就是绘制画面的函数
  for (float i = -20; i < 20; i += 0.1) {
    ray(player.angle + i);
    rectangle_color();
    cell = (double)WindowsY / 2 - (double)WindowsY / ldistance * 4;
    Floor = (double)WindowsY - cell;
    fillrectangle((i + 20) * 19.2, cell, (i + 20) * 19.2 + 2, Floor);
  }
  player.radian = Temp_angle * PI / 180;
}

// 此文件的“main“函数
void EngineForGame() {
  while (_kbhit()==0) open(); //开场剧情介绍
  start_time = time(NULL);
  pthread_create(&th,NULL,PlaySoundEffect,NULL);// 多线程解决音效播放方案
  while (player.input != 27 && checkwin() == 0) { // esc退出
      check_collect();
      if (_kbhit()) {
      player.input = _getch(); // 获取按键
        control(player.input);
        cleardevice();
        Generation_Frame_3D(world_map);
        Sleep(20);
      if (player.input != 27)
        player.input = 'f';
      }else{                  // eles分支是为了实时更新时间
        cleardevice();
        Generation_Frame_3D(world_map);
        Sleep(20);
      }
  }

  //下面是来计算总时间的变量
  time_t end_time = time(NULL);
  elapsed_time = difftime(end_time, start_time);
  sprintf(text_time, "Your game completion time is %dS",elapsed_time);
}