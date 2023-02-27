# simple-vim

> 20307130136林琰钧

## 1. 介绍

- 复旦大学2021秋数据结构pj
- 基于c++，设计一个简易vim编辑器
  - 该vim编辑器有三个界面，分别是欢迎界面、操作界面与结束界面
  - 在操作界面中有两种模式，分别是普通模式与操作模式
  - 可以通过键盘输入控制这两种模式的操作以及模式之间与界面之间的转换
  - 具体而言，普通模式具有移动光标、删除、撤销、重做、查找、打开文件、保存文件、切换到插入模式、退出等功能；插入模式有移动光标、插入、切换到普通模式等功能

## 2. 环境

- Windows系统
- vscode
- C++

## 3. 项目结构

``` plain
|_build .o文件的生成文件夹
|_file .txt文件的存放文件夹
|_include .h文件的存放文件夹
|_src .c文件的存放文件夹
Makefile 编译项目所需的文件
README.md 本文档
simple-vim.exe 可执行程序
```

## 4. 设计

- 数据结构设计
  - 文本以行为单位，每行储存在string里，所有string储存在vector中
  - 撤销与重做通过两个stack实现，每进行一次非重做非撤销操作都将历史push进撤销的stack中，每进行一次撤销操作都pop撤销的stack并push进重做的stack，每进行一次重做操作都pop重做的stack并push进撤销的stack
  - 文件流数据结构、光标操作、控制台窗口需要的句柄、智能指针等结构可以通过标准库直接调用
- 框架设计
  - 首先构建出了三个基本的界面
    - 考虑到有三种操作界面，这三个界面具有相似性，都有显示界面与处理输入的功能，因此先设计一个`Screen`父类，三种界面作为`Screen`的子类继承，记为`WelcomeScreen`，`EditorScreen`以及`GoodbyeScreen`。它们由于具有处理输入与显示界面的共同功能，因此将`Screen`作为虚基类，带有`HandleInput`与`Render`两个虚函数，其三个子类重写这两个操作。
    - 考虑通过多态实现上述三种界面的调用，因此通过智能指针来实现。由此，设计`Editor`类，储存一个调用窗口的智能指针`static std::shared_ptr<Screen> screen_`，并且具有运行程序`Run`，控制输入`HandleInput`，显示界面`Render`三个功能。其中，`Run`是一个死循环，不断调用`Render`以及`HandleInput`，`Render`与`HandleInput`分别调用`screen_`的`Render`与`HandleInput`，实现多态。
  - 然后构建`EditorScreen`的两种模式的操作
    - 首先建立历史操作的储存类`History`，其中带有撤销与重做的文本与光标位置的`stack`，共4个，为`stack<vector<string>> undo_txt_, redo_txt_;`以及`stack<COORD> undo_cur_, redo_cur_`。类中，有保留历史操作的`Save`函数，以及撤销、重做操作的`Undo`、`Redo`函数，以及是否能进行撤销、重做操作的判断函数`CanUndo`、`CanRedo`。
    - 考虑到这两种模式的操作具有相似性，比如都有光标的上下左右移动、都有文字的储存显示、历史记录的保留等，因此先设计一个`Txt`父类，两种模式作为`Txt`的子类继承，记为`NormalTxt`以及`InsertTxt`。它们由于具有处理输入与显示界面的共同功能，因此将`Txt`作为虚基类，带有`HandleInput`与`Render`两个虚函数，其两个子类重写这两个操作。同时，由于两种模式都有都有光标的上下左右移动，因此在`Txt`类中直接实现光标的上下左右移动操作的函数`MoveLeft`、`MoveDown`、`MoveUp`、`MoveRight`。同时由于两个子类都有文本显示、光标位置、历史记录，因此在`Txt`类中储存`vector<string> txt_`、`COORD cur_`、`History history_`三个数据。在`NormalTxt`类中，由于具有读写文件的操作，因此加入文件流数据`fstream file_`；在`InsertTxt`类中，没有多余的数据。
    - 考虑通过多态实现上述两种模式的调用，因此通过智能指针来实现。由此，在`EditorScreen`中储存一个调用不同模式的智能指针`static std::shared_ptr<Txt> text_`，实现多态。
  - 综上，便成功地封装出了若干类，类之间有继承关系，也有依赖关系，灵活多变、可读性强。其结果是，`main`函数中只需要实例化`Editor`类，并且调用`Run`函数，就可以运行这个Vim编辑器，简洁明了。

## 5. 运行

- 编译与启动程序

  - 进入主文件夹，创建`file`文件夹（simple-vim所有编辑的文件都在`file`文件夹下）
  
  - 在主文件夹打开bash命令行，输入`make`，即可生成`simple-vim.exe`，双击启动程序（注：`make clean`可以清除.o文件）

  - 注意
    - 不支持程序窗口大小的调整
    - 不支持文本的换行和换页

- 初始界面

  - 显示欢迎文字
  - 按任意键，进入默认模式Normal模式

- Normal模式

  - 窗口的左下角有一个`<Normal>`提示符，窗口由一个带有`Command`字样的横线分隔开来，横线以上是内容区，横下以下是命令区与操作显示区。
  - 命令
    - `:open filename`：读取文本文件filename并显示
    - `:w filename`：保存文本到文件filename，若不存在则新建，若已存在则直接覆盖
    - `:q`：退出编辑器
    - `x`：删除光标处字符
    - `u`：撤销上次操作
    - `r`：重做上次操作
    - `/pattern`：全文搜索pattern字符串
    - `h`, `j`, `k`, `l`：分别表示光标向左下上右移动
    - `i`：进入Insert模式

- Insert模式

  - 左下角有`<Insert>`的标记标明这是插入模式，以上均为文字区
  - 命令
    - `esc`：进入Normal模式