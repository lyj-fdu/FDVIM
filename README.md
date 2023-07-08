# FDVIM

> 20307130136林琰钧

[TOC]

# 1. 项目概述

复旦大学2021秋数据结构pj

## 1.1. 功能

- 基于c++，设计一个简易vim编辑器，名为FDVIM
- 该vim编辑器有三个界面，分别是欢迎界面、操作界面与结束界面
- 在操作界面中有两种模式，分别是普通模式与操作模式
  - 普通模式具有移动光标、删除、撤销、重做、查找、打开文件、保存文件、切换到插入模式、退出等功能
  - 插入模式有移动光标、插入、切换到普通模式等功能
- 可以通过键盘输入控制这两种模式的操作以及模式之间与界面之间的转换

## 1.2. 运行效果

- 从左到右分别是欢迎、操作、结束页面

  ![run](assets/img/run.png)

# 2. 部署

## 2.1. 项目结构

```plain
.
│  .gitignore
│  build.bat
│  CMakeLists.txt
│  LICENSE
│  main.cpp
│  README.md
│
├─assets
│  │  1.txt
│  │  2.txt
│  │  3.txt
│  │
│  └─img
│          edit.png
│          goodbye.png
│          run.png
│          UML.drawio
│          UML.png
│          welcome.png
│
├─include
│  ├─Editor
│  │      Editor.h
│  │
│  ├─Screen
│  │      EditScreen.h
│  │      GoodbyeScreen.h
│  │      Screen.h
│  │      WelcomeScreen.h
│  │
│  ├─Txt
│  │      InsertTxt.h
│  │      NormalTxt.h
│  │      Txt.h
│  │
│  └─Util
│          Cursor.h
│          History.h
│
└─lib
    │  CMakeLists.txt
    │
    ├─Editor
    │      CMakeLists.txt
    │      Editor.cpp
    │
    ├─Screen
    │      CMakeLists.txt
    │      EditScreen.cpp
    │      GoodbyeScreen.cpp
    │      Screen.cpp
    │      WelcomeScreen.cpp
    │
    ├─Txt
    │      CMakeLists.txt
    │      InsertTxt.cpp
    │      NormalTxt.cpp
    │      Txt.cpp
    │
    └─Util
            CMakeLists.txt
            Cursor.cpp
            History.cpp
```

## 2.2. 环境配置

- Windows系统
- cmd终端
- CMake（3.20以上版本，且带有MinGW Makefiles）

## 2.3. 编译运行

- 运行`build.bat`，即可在`build`文件夹下找到`fdvim.exe`，双击即可启动程序

# 3. 操作指南

- 注意
  - 不支持程序窗口大小的调整
  - 不支持文本的换行和换页
  - 所有fdvim所编辑的文件都存放在`assets`文件夹内

## 3.1. 欢迎界面

- 显示欢迎文字
- 按任意键进入操作界面（默认为Normal模式）

## 3.2. 操作界面

- Normal模式
  - 窗口左下角有`<Normal>`提示符，该行是命令与提示操作区，上方是文本内容区
  - 命令
    - `:open filename`：读取文本文件filename并显示，若不存在则新建，若已存在则直接打开；filename为`assets`文件夹下的文件名，例如`1.txt`
    - `:w filename`：保存文本到文件filename，若不存在则新建，若已存在则直接覆盖
    - `:q`：退出编辑器
    - `x`：删除光标处字符
    - `u`：撤销上次操作
    - `r`：重做上次操作
    - `/pattern`：从光标处开始全字匹配pattern字符串
    - `h`, `j`, `k`, `l`：分别表示光标向左下上右移动
    - `i`：进入Insert模式
- Insert模式
  - 窗口左下角有`<Insert>`提示符，该行是提示操作区，上方是文本内容区
  - 输入`esc`进入Normal模式
  - 其他输入均会在光标处将内容添加入文本

## 3.3. 结束界面

- 显示再见文字
- 按任意键退出程序

# 4. 设计

![UML](assets/img/UML.png)

## 4.1. 数据结构设计

- 文本以行为单位，每行储存在string里，所有string储存在vector中
- 撤销与重做通过两个stack实现，每进行一次非重做非撤销操作都将历史push进撤销的stack中，每进行一次撤销操作都pop撤销的stack并push进重做的stack，每进行一次重做操作都pop重做的stack并push进撤销的stack
- 文件流数据结构、控制台窗口需要的句柄、智能指针等结构可以通过标准库直接调用
- 光标操作封装为一个单例模式的工具类`Cursor`

## 4.2. 框架设计

- 首先构建出了三个基本的界面
  - 考虑到有三种操作界面，这三个界面具有相似性，都有显示界面与处理输入的功能，因此先设计一个`Screen`父类，三种界面作为`Screen`的子类继承，记为`WelcomeScreen`，`EditScreen`以及`GoodbyeScreen`。它们由于具有处理输入与显示界面的共同功能，因此将`Screen`作为虚基类，带有`handleInput`与`render`两个虚函数，其三个子类重写这两个操作。
  - 考虑通过多态实现上述三种界面的调用，因此通过智能指针来实现。由此，设计`Editor`类，储存一个调用窗口的智能指针`static std::shared_ptr<Screen> screen`，并且具有运行程序`run`，控制输入`handleInput`，显示界面`render`三个功能。其中，`run`是一个死循环，不断调用`render`以及`handleInput`，`render`与`handleInput`分别调用`screen`的`render`与`handleInput`，实现多态。
- 然后构建`EditScreen`的两种模式的操作
  - 首先建立历史操作的储存类`History`，其中带有撤销与重做的文本与光标位置的`stack`，共4个，为`stack<vector<string>> undo_txt, redo_txt;`以及`stack<COORD> undo_cur, redo_cur`。类中，有保留历史操作的`save`函数，以及撤销、重做操作的`undo`、`redo`函数，以及是否能进行撤销、重做操作的判断函数`canUndo`、`canRedo`。
  - 考虑到这两种模式的操作具有相似性，比如都有文字的储存显示、历史记录的保留等，因此先设计一个`Txt`父类，两种模式作为`Txt`的子类继承，记为`NormalTxt`以及`InsertTxt`。它们由于具有处理输入与显示界面的共同功能，因此将`Txt`作为虚基类，带有`handleInput`与`render`两个虚函数，其两个子类重写这两个操作。由于两个子类都有文本显示、光标位置、历史记录，因此在`Txt`类中储存`vector<string> txt`、`COORD cur`、`History history`三个数据。在`NormalTxt`类中，由于具有读写文件的操作，因此加入文件流数据`fstream file`；在`InsertTxt`类中，没有多余的数据。
  - 考虑通过多态实现上述两种模式的调用，因此通过智能指针来实现。由此，在`EditScreen`中储存一个调用不同模式的智能指针`static std::shared_ptr<Txt> text`，实现多态。
- 综上，便成功地封装出了若干类，类之间有继承关系，也有依赖关系，灵活多变、可读性强。其结果是，`main`函数中只需要实例化`Editor`类，并且调用`run`函数，就可以运行这个Vim编辑器，简洁明了。