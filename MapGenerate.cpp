#include "Config.h"

// 两个地图的比例，由于是正方形地图正方形窗口，就只有一个rate(偷下懒)
int rate = WindowsX / (mapX + 2);

int pixelmap[WindowsX][WindowsY] = {0};
// 以二位数组表示的世界地图 1为墙壁 0为空地
int world_map[mapY + 2][mapX + 2];

//检查item的位置是否被占用
int check_line(int i){
  for (int j = 1; j < mapY+2; j++){
    if (world_map[i][j]==4||i==1) return 0;
  }
  return 1;
}

//随机放置item
int put_item(){
  int a=rand()%5+1;
  if (a==2) return 1;
  return 0;
}

//这两个函数是生成随机化迷宫的关键函数
void create(int x, int y) // 随机生成迷宫
{
  int c[4][2] = {0, 1, 1, 0, 0, -1, -1, 0}; // 四个方向
  int i, j, t;
  // 将方向打乱
  for (i = 0; i < 4; i++) {
    j = rand() % 4;
    t = c[i][0];
    c[i][0] = c[j][0];
    c[j][0] = t;
    t = c[i][1];
    c[i][1] = c[j][1];
    c[j][1] = t;
  }
  world_map[x][y] = Road;
  for (i = 0; i < 4; i++) {
    if (world_map[x + 2 * c[i][0]][y + 2 * c[i][1]] == Wall) {
      world_map[x + c[i][0]][y + c[i][1]] = Road;
      create(x + 2 * c[i][0], y + 2 * c[i][1]);
    }
  }
}

void initialize() {
  for (int i = 0; i <= mapY + 1; i++) {
    for (int j = 0; j <= mapX + 1; j++) {
      if (i == 0 || i == mapY + 1 || j == 0 || j == mapX + 1) // 初始化迷宫
      {
        world_map[i][j] = Road;
      } else
        world_map[i][j] = Wall;
    }
  }
  create(2 * (rand() % (mapY / 2) + 1),
         2 * (rand() % (mapX / 2) +
              1)); // 从随机一个点开始生成迷宫，该点行列都为偶数
  world_map[2][0] = Start;         
  world_map[2][1] = 0;         // 给定入口
  world_map[mapY - 1][mapX] = End; // 给定出口
  while (item>0){
    for (int i = 1; i < mapY ; i++) {
      for (int j = 1; j < mapX ; j++) {
        if (world_map[i][j]==0&&check_line(i)&&put_item()){
          world_map[i][j]=4;
          item--;
          if (item<=0) break;
        }
      }
    }  
  }
  printf("Here is your map\n");
  printf("1 stands for wall\n");
  printf("0 stands for nothing\n");
  printf("4 stands for barrier\n");
  printf("3 stands for exit\n");
  for (int i = 0; i < mapY + 2; i++) {
    for (int j = 0; j < mapX + 2; j++) {
      printf("%d ", world_map[i][j]);
    }
    printf("\n");
  }
}


/*{
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};*/

// 通过transform函数将地图转化成像素，从而便于射线距离的判断
// random函数是每一面墙都有不同的颜色以增加立体感，6 7则分别表示起点和终点
void transform() {
  for (int i = 0; i < (mapY + 2); i++) {
    for (int j = 0; j < (mapX + 2); j++) {

      if (world_map[i][j] == 1) {
        int random_color=rand()%5+1;       
        for (int q = rate * i; q < rate * (i + 1); q++) {
          for (int p = rate * j; p < rate * (j + 1); p++) {
            pixelmap[q][p] = random_color;
          }
        }
      }
      else if (world_map[i][j] == 0) {
        int random_color=0;       
        for (int q = rate * i; q < rate * (i + 1); q++) {
          for (int p = rate * j; p < rate * (j + 1); p++) {
            pixelmap[q][p] = random_color;
          }
        }
      }      
      else if (world_map[i][j] == 2) {
        int random_color=6;       
        for (int q = rate * i; q < rate * (i + 1); q++) {
          for (int p = rate * j; p < rate * (j + 1); p++) {
            pixelmap[q][p] = random_color;
          }
        }
      }
      else if (world_map[i][j] == 3) {
        int random_color=7;       
        for (int q = rate * i; q < rate * (i + 1); q++) {
          for (int p = rate * j; p < rate * (j + 1); p++) {
            pixelmap[q][p] = random_color;
          }
        }
      }
      else if (world_map[i][j] == 4) {
        int random_color=8;       
        for (int q = rate * i; q < rate * (i + 1); q++) {
          for (int p = rate * j; p < rate * (j + 1); p++) {
            pixelmap[q][p] = random_color;
          }
        }
      }
    }
  }
}
