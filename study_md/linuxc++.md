# linux c++

## 编译

#### 基本编译流程

1. 预处理
	* g++ filename -E -I includepath
2. 汇编
	* g++ filename -C
3. 生成目标文件
	* g++ filename -S
4. 链接
	1. 没有库文件的链接 g++ filename
	
	2. 静态库链接 g++ filename -I includepath <font style="color:red">-Lsrc(库文件路径)</font> -库名 		-o xx

####  静态库生成

1. 汇编,生成.o文件:g++ file -c -I includepath

2. 归档:ar rs 静态库名(一般以.a结尾) 上一条命令生成的.o文件

3. 链接: g++ filename -l(库文件名字--去掉lib和.a) -L(库文件路径) -I includepath -o target_name

#### 动态库生成

1. 生成动态库文件: g++ filename -I../include -fPIC -shared -o libxxx.so

2. 上述命令等价于
	* g++ filename -I include_path -c -fPIC
	* g++ -shared -o linxxx.so 上面生成的.o文件

3. 链接: g++ file_name -I include_path -L 动态库文件路径 -l(动态库文件的名字--去掉lib和.o后缀) -o target_name

4. 运行的时候需要指定LD_LIBRARY_PATH=动态库文件路径 ./可执行文件

## GDB调试

#### 常用GDB命令

1. 进入gdb命令行
	* help(h) 查看命令帮助
	* run(r) 重新开始运行文件(run-text:加载文本文件; run-bin:加载二进制文件)
	* start 单步执行,运行程序,停在第一行执行语句
	* list(1) 查看源代码(list-n,从第n行开始查看代码。list+ 函数名:查看具体函数)
	* set 设置变量的值
	* next(n) 单步调试(逐过程,函数直接执行)
	* step(s) 单步调试(逐语句：跳入之定义函数内部执行)
	* backtrace(bt) 查看函数的调用栈帧和层级关系
	* frame(f) 切换函数的栈帧
	* info(i) 查看函数内部局部变量的数值
	* finish 结束当前函数,返回到函数调用点
	* continue(c) 继续运行
	* print(p) 打印值及地址
	* quit(q) 退出
	* break num(b) 在某一行打断电
	* info breakpoints 查看当前所有断点
	* delete breakspoints num(d) 删除断点
	* display 追踪观察变量的值
	* undisplay 取消追踪
	* watch 被设置追踪观察点的变量发生变化是自动打印显示
	* i watch 显示观察点
	* enable breakpoints 启用断点
	* disable breakpoints 禁用断点
	* x 查看内存x/20xw 显示20个单元,16进制,4字节每单元
	* run argv[1] argv[2] 调试时命令行传参
	* set follow-fork-mode child MakeFile项目管理: 选择跟踪父子进程


## Cmake

#### 基本语法格式

1. 指令(参数1 参数2)
	* 参数使用括号括上
	* 参数之间是使用空格或者分号

2. 指令不区分大小写,参数和变量区分大小写

### 重要指令和CMake常用变量


#### 重要指令
1. cmake_minimum_required(VERSION versionNumber [FATAL_ERROR]) 指定CMake最低版本要求

2. project(工程名 [CXX] [C] [Java])  指定工程名,并且可指定工程支持的语言

3. set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]]) 显示的定义变量
	* example: set(SRC sayhello.cpp hello.cpp)定义SRC变量,其值为main.cpp hello.cpp

4. include_directories 向工程添加多个头文件的搜索路径(相当于g++ -I)
	* include_directories\(\[AFTER\|BEFORE\] \[SYSTEM\] dir1 dir2 dir3)

5. link_directories(dir1 dir2) 向工程添加多个库文件搜索路径(相当于g++ -L)

6. add_library 生成库文件
	* add_library(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] source1 source2.....(可以使用${前面用set定义的变量}))

7. add_compile_options 添加编译参数
	* add_compile_options()
	* add_compile_options(-w all -std=c++11 -O2)
8. add_executable 生成可执行文件
	* add_executable(exename source1 source2....)
	* add_executable(main main.cpp)

9. target_link_libraries 为目标文件添加需要链接的共享库
	* target_link_libraries(target library1 [debug | optimized] library 2)
	* target_link_libraries(main hello) 将hello动态库链接到可执行文件main

10. add_subdirectory 向当前工程添加存放源文件的子目录,并可以指定中间二进制和目标二进制存放位置
	* add_subdirectory(source_dir [binary_dir] [EXCULDE_FROM_ALL])
	* add_subdirectory(src) 添加src子目录,src中需要有一个CMakeLists.txt

11. aux_source_directory 发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表
	* aux_source_directory(dir 变量名字)
	* aux_source_directory(. SRC) 定义变量SRC,其值为当前目录下的所有源代码文件
	* add_executable(main ${SRC}) 编译SRC变量所代表的源代码文件,生成main可执行文件


#### 常用变量

1. CMAKE_C_FLAGS gcc编译选项

2. CMAKE_CXX_FLAGS g++编译选项
	* set(CMAKE_CXX_FLAGS "${CMAKE_C++_FLAGS} -std=c++11" )

3. CMAKE_BUILD_TYPE 编译类型
	* set(CMAKE_BUILD_TYPE Debug) 设定编译类型为debug,调试时需要选择debug
	* set(CMAKE_BUILD_TYPE Release) 设定编译类型为release,发布时选择

4. CMAKE_BINARY_DIR


### 编译工程

#### 项目结构及编译规则

1. CMake目录结构: 项目主目录存在一个CMakelists.txt

2. 两种方式设置编译规则
	* 包含源文件的子文件夹包含CMakeLists.txt,主目录的CMakeLists.txt通过add_subdirectory添加子目录
	* 包含源文件的子文件夹未包含CMakeLists.txt文件,子目录编译规则体现在主目录的CMakeLists.txt中

#### 编译流程

1. 手动编写CMakeLists.txt

2. 执行命令cmake PATH 生成Makefile(PATH是顶层CMakeLists.txt所在目录)

3. 执行make进行编译

#### 构建方式

1. 内部构件in-source build(不推荐)
	* 内部构建会在同级目录下产生一大堆中间文件，这些中间文件并不是我们最终所需要的，和工程源文件放在一起会显得杂乱无章

2. 外部构建out-of-source build(推荐)
	* 将编译输出文件与源文件放在不同目录中
		* 在当前目录下先创建build文件夹 mkdir build
		* 进入build文件夹 cd build
		* 编译上级目录的CMakeLists.txt,生成Makefile和其他文件 cmake
		* 执行make命令,生成target到build中


## 几点注意

1. 当用vscode调试的时候,出现了不按照自己行为的调试,查看cmake中的CMAKE_BUILD_TYPE是否设置成Debug,编译参数出现了了冲突(代码优化和 -g)去掉这俩参数,将CMAKE_BUILD_TYPE置为Debug
2. 在vscode中使用cmake一键调试的时候,需要在task.json中的cmake的args中加入-Bbuild  !! 注意这里-B后面没有空格