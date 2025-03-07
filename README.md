# 基于光线投射原理的伪3D迷宫游戏

    基于easyx图形库开发。
    大一上C语言结业项目之一，做这个的灵感来源于重返德军总部的伪3D，自己复现了下，原理是光线投射。
    迷宫的生成是随机的，每一次打开都会生成一个随机的迷宫。
    源文件还缺失一个mili.wav的音频（体积过大上传不了),所以直接打开可能会有声音上的出错。可以在config.h文件中对BGM文件进行修改。

  以下是对游戏的操作和基本信息
  
    You are Mostima,the keeper of the lock&keys.
    You are trapped in the maze.
    Break the white wall and leave here!
    The object of the game is to find the black wall to escape the maze,while you break the barria
    Press W/S to control role to move forward/back.And w/s can control main menu cursor.
    Press A/D to Control the rotational motion of the character.
    Press E to get position for now, which can make find the way.
    When you really can't finish the game, please press P.
    
  以下是对每个游戏文件的解释
    
    main.cpp:
    这是项目的入口文件，包含 main 函数。
    包含初始化函数 initialization，用于初始化图形界面、随机数种子、地图等。
    根据用户输入选择不同的模式（演示模式或游戏模式）。
    在游戏模式中，调用 EngineForGame 函数来运行游戏逻辑。
    在游戏结束时，根据结果调用 congratulation 或 pity 函数，并记录玩家信息。
    
    Config.h:
    包含项目所需的头文件和库。
    定义了游戏的各种宏、结构体和全局变量。
    包含与时间、模式、收集、图片路径、多线程、音频文件路径等相关的变量声明。
    
    EngineForGame.cpp:
    包含 EngineForGame 函数，负责游戏的主要逻辑。
    包含 Generation_Frame_3D 函数，用于生成伪3D画面。
    处理玩家输入、更新游戏状态、绘制游戏画面等。
    
    EngineForDev.cpp:
    是游戏演示模式的主题文件。
    包含一些二维的处理。
    
    misc.cpp:
    包含各种辅助函数，如 PlaySoundEffect（音效播放线程函数）、transparentimage（透明PNG图片函数）、message（信息显示函数）、menu（主菜单绘制函数）、congratulation（通关界面绘制函数）、pity（未通关界面绘制函数）等。
    包含与排行榜功能相关的函数，如 rank、infiles、datasFromFile、compare。
    
    players.txt 和 times.txt:
    用于存储玩家的名字和时间。
 
  
