
#include "Config.h"
#include "MapGenerate.cpp"
#include "misc.cpp"

double ldistance;
double Temp_angle;
int itemcheck;
float step = 3; // 射线检测初始步长
double fx, next_fx;
double fy, next_fy;

// wallcheck是用来预测下一步玩家位置的，从而避免穿墙bug
int wallcheck;

// 用于在像素级检测是否为墙壁的函数
int check(double x, double y) {
  if (pixelmap[int(x)][int(y)] != 0) {
    return 1;
  }
  return 0;
}

// 射线函数，使用DDA算法绘制射线
void ray(double angle) {
  fx = player.x; // 初始化射线起点
  fy = player.y;

  player.angle =
      fmod(player.angle, 360.0);      // 保证 player.angle 在 [0, 360) 范围内
  player.radian = angle * PI / 180.0; // 转换角度为弧度

  double step_size = step; // 初始步长

  while (step_size > 0.1) { // 设置一个最小步长避免陷入死循环
    // 计算下一步位置
    next_fx = fx + cos(player.radian) * step_size;
    next_fy = fy + sin(player.radian) * step_size;
    // 判断当前像素是否是墙壁,逐步减小步长，以提高精度
    if (check(next_fy, next_fx)) {
      step_size = step_size / 2;
      continue;
    }
    // 如果没有碰到墙壁，继续推进射线
    fx = next_fx;
    fy = next_fy;
  }
  // 计算射线与起点的距离
  ldistance = sqrt((player.x - fx) * (player.x - fx) +
                   (player.y - fy) * (player.y - fy));
}

// 控制函数
void control(char input) {
  switch (input) {
  case 'a':
  case 'A':
    player.angle -= 1.5;
    break;
  case 'd':
  case 'D':
    player.angle += 1.5;
    break;
  case 'w':
  case 'W':
    wallcheck = world_map[(int)((player.y + sin(player.radian) * 15) / WindowsX *(mapX + 2))]
                        [(int)((player.x + cos(player.radian) * 15) / WindowsY * (mapY + 2))];
    if (wallcheck == 0 || wallcheck == 3||wallcheck == 4) {
      player.x += cos(player.radian) * 2.5;
      player.y += sin(player.radian) * 2.5;
    }
    break;
  case 's':
  case 'S':
    wallcheck = world_map[(int)((player.y - sin(player.radian) * 15) / WindowsX *(mapX + 2))]
                        [(int)((player.x - cos(player.radian) * 15) / WindowsY * (mapY + 2))];
    if (wallcheck == 0 || wallcheck == 3||wallcheck == 4) {
      player.x -= cos(player.radian) * 2.5;
      player.y -= sin(player.radian) * 2.5;
    }
    break;
    // 作弊码，方便调试
  case 'p':
  case 'P':
    player.x = WindowsX / (mapX + 2) * 10.5;
    player.y = WindowsY / (mapY + 2) * 10.5;
    break;
  case 'e':
  case 'E':
    printf("x=%.1f y=%.1f\n", player.x / (WindowsX / 13),
           player.y / (WindowsY / 13));
    break;
  case 'q':  
    for (int i = 0; i < mapY + 2; i++) {
      for (int j = 0; j < mapX + 2; j++) {
        printf("%d ", world_map[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    printf("x==%d y==%d\n",(int)(player.x / (WindowsX / 13)+0.2),(int)(player.y / (WindowsX / 13)+0.2));
    break;
  default:
    break;
  }
}

//用于检测是否收集item
void check_collect(){
  itemcheck = world_map[(int)(player.y / (WindowsX / 13) + 0.2)]
                       [(int)(player.x / (WindowsX / 13) + 0.2)];
  if (itemcheck == 4) {
    get_item++;
    world_map[(int)(player.y / (WindowsX / 13) + 0.2)]
             [(int)(player.x / (WindowsX / 13) + 0.2)] = 0;
    transform();
  }
  itemcheck = world_map[(int)(player.y / (WindowsX / 13) - 0.2)]
                       [(int)(player.x / (WindowsX / 13) - 0.2)];
  if (itemcheck == 4) {
    get_item++;
    world_map[(int)(player.y / (WindowsX / 13) - 0.2)]
             [(int)(player.x / (WindowsX / 13) - 0.2)] = 0;
    transform();
  }
}

// 检测通关条件
int checkwin() {
  int tempx = (int)(player.x / (WindowsX / 13));
  int tempy = (int)(player.y / (WindowsY / 13));
  if (tempx == 11 && tempy == 10 &&get_item>=5) return 1;
  if (totalltime-seconds<=0) return 2;
  return 0;
}

// 帧生成函数
void Generation_Frame_2D(int world_map[mapY + 2][mapX + 2]) {
  setfillcolor(WHITE);
  setlinecolor(WHITE);
  // 两个for循环绘制地图
  for (int i = 0; i < mapY + 2; i++) {
    for (int j = 0; j < mapX + 2; j++) {
      if (world_map[i][j] != 0) {
        if (world_map[i][j] != 1) {
          setfillcolor(GREEN);
          setlinecolor(GREEN);
        }
        fillrectangle(j * (WindowsX / (mapX + 2)), i * (WindowsY / (mapY + 2)),
                      (j + 1) * (WindowsX / (mapX + 2)),
                      (i + 1) * (WindowsY / (mapY + 2)));
        setfillcolor(WHITE);
        setlinecolor(WHITE);
      }
    }
  }
  setfillcolor(RED);
  setlinecolor(RED);
  fillcircle(player.x, player.y, 5);
  Temp_angle = player.angle;
  // 绘制射线
  for (float i = -24; i < 24; i += 0.1) {
    ray(player.angle + i);
    line(player.x, player.y, fx, fy);
  }
  player.radian = Temp_angle * PI / 180;
}

// 控制每一帧流程的函数
void EngineFovDev() {
  time_t start_time = time(NULL);
  while (player.input != 27 && checkwin() != 1) { // esc退出
    if (_kbhit()) {
      player.input = _getch(); // 获取按键
      control(player.input);
      cleardevice();
      Generation_Frame_2D(world_map);
      Sleep(10);
    }
    if (player.input != 27)
      player.input = 'f';
  }
  time_t end_time = time(NULL);
  int elapsed_time = difftime(end_time, start_time);
}


