# Eigen

## 1	源码安装

​	**见**[CSDN](https://blog.csdn.net/yuan0061/article/details/83002229?ops_request_misc=&request_id=&biz_id=102&utm_term=EIGEN%E5%AE%89%E8%A3%85&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-83002229.142^v3^pc_search_result_control_group,143^v4^register&spm=1018.2226.3001.4187),安装位置在`usr/local/include` 和 `/usr/include`,使用时添加头文件 `#include<Eigen/Eigen.h>` 

## 2	内置类型

```c++
Eigen通过tyepdef定义了许多内置类型，不过底层仍然是Eigen::Matrix,如下所示：
    //初始化为0   //Matrix3d实质上是Eigen::Matrix<double, 3, 3> 
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero(): 
        
    //如果不确定矩阵大小，可以使用动态大小的矩阵
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic; 
                                                 
    //与上类似，表示任意大小的元素类型为double的矩阵变量
	Eigen::MatrixXd matrix_xd;   
                                                  
    //表示任意大小的元素类型为float的矩阵变量
 	Eigen::MatrixXf matrix_xf; 
                                                         
    //Vector3d实质上是Eigen::Matrix<double, 3, 1>   三行一列
	Eigen::Vector3d v_3d;

```

## 3	使用

- **加减乘除跟数字操作一样**

- **赋值操作**

  ```c++
  matrix_33<<1,2,3,4,5,6,7,8,9;
  或 matrix_33(0,0)=1;
  ```

- **矩阵操作**

  ```c++
  cout << matrix_33.transpose() << endl;    //转置
  cout << matrix_33.sum() << endl;          //各元素和
  cout << matrix_33.trace() << endl;        //迹
  cout << matrix_33 * 10 << endl;           //数乘
  cout << matrix_33.inverse() << endl;      //逆
  cout << matrix_33.determinant() << endl;  //行列式
  cout << matrix_33.adjoint() << endl;      //伴随
  cout << matrix_33.cwiseAbs() << endl;     //绝对值
  cout << matrix_33.maxCoeff() << endl;     //求最大系数
  ```

- **求解Ax=b**

  ```c++
  // 求解Ax=b ; Vector2d => Matrix<double,2, 1>
  Eigen::Vector2d C = A.colPivHouseholderQr().solve(b); 
  
  cwiseAbs()求绝对值
  maxcoff()求最大系数
  ```

- **单位矩阵**

  ```c++
  Eigen::MatrixXd::Identity(4, 4)  
  or
  Eigen::Matrix<double ,4,4> A;
  A.setIdentity(4, 4);
  ```

  

# GCC编译器

## 1	cpp文件编译过程

```bash
1 预处理-Pre-Processing           		//.i文件
    # -E 选项指示编译器仅对输入文件进行预处理
    g++  -E  test.cpp  -o  test.i    

2 编译-Compiling                   	// .s文件
    # -S 编译选项告诉 g++ 在为 C++ 代码产生了汇编语言文件后停止编译
    #  g++ 产生的汇编语言文件的缺省扩展名是 .s 
    g++  -S  test.i  -o   test.s

3 汇编-Assembling                   	// .o文件
    # -c 选项告诉 g++ 仅把源代码编译为机器语言的目标代码
    # 缺省时 g++ 建立的目标代码文件有一个 .o 的扩展名。
    g++  -c  test.s  -o  test.o

4 链接-Linking                       	// bin文件
    # -o 编译选项来为将产生的可执行文件用指定的文件名
    g++  test.o  -o  test
```

## 2	g++重要编译参数

```bash
1	-g	编译带调试信息的可执行文件
    # -g 选项告诉 GCC 产生能被 GNU 调试器GDB使用的调试信息，以调试程序。

    # 产生带调试信息的可执行文件test
    g++ -g test.cpp

2	-O[n]	优化源代码
    ## 所谓优化，例如省略掉代码中从未使用过的变量、直接将常量表达式用结果值代替等等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率。

    # -O 选项告诉g++对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。-O2 选项告诉 g++ 产生尽可能小和尽可能快的代码。 如-O2，-O3，-On（n 常为0–3）
    # -O 同时减小代码的长度和执行时间，其效果等价于-O1
    # -O0 表示不做优化
    # -O1 为默认优化
    # -O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等。
    # -O3 则包括循环展开和其他一些与处理特性相关的优化工作。
    # 选项将使编译的速度比使用 -O 时慢， 但通常产生的代码执行速度会更快。

    # 使用 -O2优化源代码，并输出可执行文件
    g++ -O2 test.cpp
    
3	-l  和  -L     指定库文件  |  指定库文件路径
    # -l参数(小写)就是用来指定程序要链接的库，-l参数紧接着就是库名
    # 在/lib和/usr/lib和/usr/local/lib里的库直接用-l参数就能链接

    # 链接glog库
    g++ -lglog test.cpp

    # 如果库文件没放在上面三个目录里，需要使用-L参数(大写)指定库文件所在目录
    # -L参数跟着的是库文件所在的目录名

    # 链接mytest库，libmytest.so在/home/bing/mytestlibfolder目录下
    g++ -L/home/bing/mytestlibfolder -lmytest test.cpp
    
4	-I    指定头文件搜索目录
    # -I 
    # /usr/include目录一般不用指定，gcc知道去那里找，但是如果头文件不在/usr/icnclude里我们就要用-I参数指定了，
    # 比如头文件放在/myinclude目录里，那编译命令行就要加上-I/myinclude 参数了，如果不加你会得到一个”xxxx.h: No such file or directory”的错误。
    #-I参数可以用相对路径，比如头文件在当前 目录，可以用-I.来指定。上面我们提到的–cflags参数就是用来生成-I参数的。

    g++ -I/myinclude test.cpp	
    
5	-Wall    打印警告信息
	# 打印出gcc提供的警告信息(例如：变量定义了未使用，初始化列表的顺序跟定义的成员变量顺序不一致等等)
	g++ -Wall test.cpp

6	-w    关闭警告信息
	# 关闭所有警告信息
	g++ -w test.cpp

7	-std=c++11    设置编译标准
    # 使用 c++11 标准编译 test.cpp
    g++ -std=c++11 test.cpp


8	-o     指定输出文件名
    # 指定即将产生的文件名

    # 指定输出可执行文件名为test
    g++ test.cpp -o test
    
9	-D     定义宏
    # 在使用gcc/g++编译的时候定义宏

    # 常用场景：
    # -DDEBUG 定义DEBUG宏，可能文件中有DEBUG宏部分的相关信息，用个DDEBUG来选择开启或关闭DEBUG
    例子：
    // -Dname 定义宏name,默认定义内容为字符串“1”
     #include <stdio.h>

     int main()
     {
         #ifdef DEBUG
            printf("DEBUG LOG\n");
         #endif
            printf("in\n");
    }

    // 1. 在编译的时候，使用gcc -DDEBUG main.cpp
    // 2. ifdef代码可以被执行
```



------

# GDB调试器

## 1	使用

```bash
## 以下命令后括号内为命令的简化使用，比如run（r），直接输入命令 r 就代表命令run
$(gdb)help(h)        # 查看命令帮助，具体命令查询在gdb中输入help + 命令 

$(gdb)run(r)         # 重新开始运行文件（run-text：加载文本文件，run-bin：加载二进制文件）

$(gdb)start          # 单步执行，运行程序，停在第一行执行语句

$(gdb)list(l)        # 查看原代码（list-n,从第n行开始查看代码。list+ 函数名：查看具体函数）

$(gdb)set            # 设置变量的值

$(gdb)next(n)        # 单步调试（逐过程，函数直接执行）

$(gdb)step(s)        # 单步调试（逐语句：跳入自定义函数内部执行）

$(gdb)backtrace(bt)  # 查看函数的调用的栈帧和层级关系

$(gdb)frame(f)       # 切换函数的栈帧

$(gdb)info(i)        # 查看函数内部局部变量的数值

$(gdb)finish         # 结束当前函数，返回到函数调用点

$(gdb)continue(c)    # 继续运行

$(gdb)print(p)       # 打印值及地址

$(gdb)quit(q)        # 退出gdb

$(gdb)break+num(b)                 # 在第num行设置断点

$(gdb)info breakpoints             # 查看当前设置的所有断点

$(gdb)delete breakpoints num(d)    # 删除第num个断点

$(gdb)display                      # 追踪查看具体变量值

$(gdb)undisplay                    # 取消追踪观察变量

$(gdb)watch                        # 被设置观察点的变量发生修改时，打印显示

$(gdb)i watch                      # 显示观察点

$(gdb)enable breakpoints           # 启用断点

$(gdb)disable breakpoints          # 禁用断点

$(gdb)x                            # 查看内存x/20xw 显示20个单元，16进制，4字节每单元

$(gdb)run argv[1] argv[2]          # 调试时命令行传参

$(gdb)set follow-fork-mode child   # Makefile项目管理：选择跟踪父子进程（fork()）

```

> Tips:
>
> ​	1.编译程序时需要加上-g，之后才能用gdb进行调试：gcc -g main.c -o main
>
> ​	2.回车键：重复上一命令



------

# CMake

## 1	语法特性

- **基本语法格式**

  - 参数之间使用**空格**或**分号**分开

- **指令是大小写无关的，参数和变量是与大小写有关**

  ```bash
  set(HELLO hello.cpp)
  add_executable(hello main.cpp hello.cpp)
  ADD_EXECUTABLE(hello main.cpp ${HELLO})  #HELLO与set建立的HELLO大小写要一致
  ```

- **变量使用${}方式取值，但是在 IF 控制语句中是直接使用变量名**

## 2	重要指令和CMake常用变量

### 2.1	重要指令

- **cmake_minimum_required** **- 指定CMake的最小版本要求**

  ```bash
  # CMake最小版本要求为2.8.3
  cmake_minimum_required(VERSION 2.8.3)
  ```

- - 语法：**cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])**

- **project** **- 定义工程名称，并可指定工程支持的语言** 

  ```bash
  # 指定工程名为HELLOWORLD
  project(HELLOWORLD)
  ```

- - 语法：**project(projectname [CXX] [C] [Java])**

- **set** **- 显式的定义变量** 

  ```bash
  # 定义SRC变量，其值为main.cpp hello.cpp
  set(SRC sayhello.cpp hello.cpp)
  ```

- - 语法：**set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])**

- **include_directories - 向工程添加多个特定的头文件搜索路径** --->相当于指定g++编译器的-I参数

  ```bash
  # 将/usr/include/myincludefolder 和 ./include 添加到头文件搜索路径
  include_directories(/usr/include/myincludefolder ./include)
  ```

- - 语法：**include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2 …)**

- **link_directories** **- 向工程添加多个特定的库文件搜索路径** --->相当于指定g++编译器的-L参数

  ```bash
  # 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径
  link_directories(/usr/lib/mylibfolder ./lib)
  ```

- - 语法：link_directories(dir1 dir2 …) 

- **add_library** **- 生成库文件**

  ```bash
  # 通过变量 SRC 生成 libhello.so 共享库
  # SHARED生成动态库、STATIC生成静态库
  add_library(hello SHARED ${SRC})
  ```

- - 语法：**add_library(libname [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 source2 … sourceN)**

- **add_compile_options** - 添加编译参数

  ```bash
  # 添加编译参数 -Wall -std=c++11
  add_compile_options(-Wall -std=c++11 -O2)
  ```

- - 语法：**add_compile_options()**

- **add_executable** **- 生成可执行文件**

  ```bash
  # 编译main.cpp生成可执行文件main
  add_executable(main main.cpp)
  ```

- - 语法：**add_library(exename source1 source2 … sourceN)**

- **target_link_libraries** - 为 target 添加需要链接的共享库  --->相同于指定g++编译器-l参数

  ```bash
  # 将hello动态库文件链接到可执行文件main
  target_link_libraries(main hello) #可以写成libhello.so 或者直接用 hello
  ```

- - 语法：**target_link_libraries(target library1library2…)**

- **add_subdirectory - 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置**

  ```bash
  # 添加src子目录，src中需有一个CMakeLists.txt
  add_subdirectory(src)
  ```

- - 语法：**add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])**

- **aux_source_directory - 发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表**

  ```bash
  # 定义SRC变量，其值为当前目录下所有的源代码文件
  aux_source_directory(. SRC)
  # 编译SRC变量所代表的源代码文件，生成main可执行文件
  add_executable(main ${SRC})
  ```

- - 语法：**aux_source_directory(dir VARIABLE)**

### 2.2	CMake重用变量

- **CMAKE_C_FLAGS  gcc编译选项**

  **CMAKE_CXX_FLAGS  g++编译选项**

  ```bash
  # 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  ```

  **CMAKE_BUILD_TYPE  编译类型(Debug, Release)**

  ```bash
  # 设定编译类型为debug，调试时需要选择debug
  set(CMAKE_BUILD_TYPE Debug) 
  # 设定编译类型为release，发布时需要选择release
  set(CMAKE_BUILD_TYPE Release) 
  ```

  **CMAKE_BINARY_DIR**

  **PROJECT_BINARY_DIR**

  **<projectname>__BINARY_DIR**

- 1. 这三个变量指代的内容是一致的。
  2. 如果是 in source build，指的就是工程顶层目录。
  3. 如果是 out-of-source 编译,指的是工程编译发生的目录。
  4. PROJECT_BINARY_DIR 运行`cmake`命令的目录，即工程编译发生的路径。

- **CMAKE_SOURCE_DIR**

  **PROJECT_SOURCE_DIR**
  **<projectname>__SOURCE_DIR**

- 1. 这三个变量指代的内容是一致的,不论采用何种编译方式,都是工程顶层目录。
  2. 也就是在 in source build时,他跟 CMAKE_BINARY_DIR 等变量一致。
  3. PROJECT_SOURCE_DIR 最近一个`CMakeLists.txt`文件所在的文件夹路径。。

------

- **CMAKE_C_COMPILER：指定C编译器**

- **CMAKE_CXX_COMPILER：指定C++编译器**

  ```bash
  set(CMAKE_CXX_COMPLIER 14)
  ```

- **EXECUTABLE_OUTPUT_PATH：可执行文件输出的存放路径**

  ```bash
  #指定可执行文件的输出目录，输出到bin下面  
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
  ```

- **CMAKE_LIBRARY_OUTPUT_DIRECTORY：库文件输出的存放路径**

> Tips:
>
> EXECUTABLE_OUTPUT_PATH/LIBRARY_OUTPUT_PATH
>
> 上述两个参数已经被CMAKE_RUNTIME_OUTPUT_DIRECTORY`和`CMAKE_LIBRARY_OUTPUT_DIRECTORY替代

## 3	CMake编译工程

CMake目录结构：项目主目录存在一个CMakeLists.txt文件

**两种方式设置编译规则**：

1. 包含源文件的子文件夹包含CMakeLists.txt文件，主目录的CMakeLists.txt通过add_subdirectory添加子目录即可；
2. 包含源文件的子文件夹未包含CMakeLists.txt文件，子目录编译规则体现在主目录的CMakeLists.txt中；

## 4	sample

源码在routing_planning/学习笔记/cmake_test_file下

- **目录结构**

  ```bash
  next@pc:~/routing_planning/学习笔记/cmake_test_file$ tree .
  .
  ├── bin
  ├── build
  ├── CMakeLists.txt
  ├── include
  │   ├── Gun.hpp
  │   └── solider.hpp
  ├── lib
  ├── math
  │   ├── CMakeLists.txt
  │   ├── myMath.cpp
  │   └── myMath.hpp
  ├── pc_complies.sh
  └── src
      ├── Gun.cpp
      ├── main.cpp
      └── solider.cpp
      
  
  #在math中添加了一个计算前n项计算方法
  #pc_complies.sh为编写的自动编译的脚本
  ```

- **子目录的CMakeLists.txt**

  ```bash
  aux_source_directory(. DIR_LIB_SRCS)
  
  # 生成链接库,默认生成的是静态库
  # STATIC生成静态库、SHARED生成动态库或共享库
  add_library(MathFunctions_so SHARED ${DIR_LIB_SRCS})
  add_library(MathFunctions_o STATIC ${DIR_LIB_SRCS})
  ```

- **主目录CMakeLists.txt**

  ```bash
  cmake_minimum_required(VERSION 3.0.0)
  project(CMAKE_TEST VERSION 0.1.0)
  
  # 设置CMAKE编译选项 c++14标准、o2优化、显示warning
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
  # 设置c++版本
  # set(CMAKE_CXX_STANDARD 14)
  
  # 设置编译版本 bebug / relese
  SET(CMAKE_BUILD_TYPE Debug)
  # SET(CMAKE_BUILD_TYPE Release)
  
  # -fPIC 作用于编译阶段，告诉编译器产生与位置无关代码(Position-Independent Code)，
  # 则产生的代码中，没有绝对地址，全部使用相对地址，故而代码可以被加载器加载到内存的任意位置，
  # 都可以正确的执行。这正是共享库所要求的，共享库被加载时，在内存的位置不是固定的。
  # add_compile_options(-fPIC)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON) #与上面被注释的作用相同，下面这种比较标准
  
  #设置可执行文件输出路径 注意要放在靠前的位置提前设置
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)
  # 设置静态链接库输出路径
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
  # 设置动态链接库输出路径
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
  
  # 添加math子目录，注意子文件要放在总CMakeLists.txt的上面，不然链接不到
  add_subdirectory(math)
  
  # include_directories 设置包含的目录
  # PROJECT_SOURCE_DIR 工程的根目录
  include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/math
  )
  
  # aux_source_directory 搜索所有的cpp文件
  # 在当前src目录下搜索所有的cpp文件，并储存在变量DIR_SRCS中
  aux_source_directory(./src DIR_SRCS)
  
  # 编译可执行文件
  add_executable(CMAKE_TEST ${DIR_SRCS})
  
  # 指定链接动态库或静态库 
  target_link_libraries(CMAKE_TEST MathFunctions_so) #在math中生成的链接库
  # target_link_libraries(CMAKE_TEST ${PROJECT_SOURCE_DIR}/lib/libMathFunctions.so)
  
  # 指定工程需要用到的一些库
  #find_package(PkgConfig)
  #添加需要链接的库文件目录
  # link_directories(
  # /usr/lib64/
  # ${GTK_LIBRARY_DIRS}
  # )
  ```


------

# GoogleTest

## 1	源码编译安装

```bash
1.下载源码
	https://github.com/google/googletest/
2.CMake安装编译
	cd googletest
	mkdir build && cd build
	cmake .. && make -j4
	make install
	
#GTest库文件安装在/usr/local/lib/目录，头文件安装在/usr/local/include/目录
```

## 2	使用

- **断言含义**

  - gtest 使用一系列断言的宏来检查值是否符合预期，主要分为两类：ASSERT 和 EXPECT。区别在于 ASSERT 不通过的时候会认为是一个 fatal 的错误，退出当前函数（只是函数）。而 EXPECT 失败的话会继续运行当前函数，所以对于函数内几个失败可以同时报告出来。通常我们用 EXPECT 级别的断言就好，除非你认为当前检查点失败后函数的后续检查没有意义

  - `<<`要提供自定义失败消息，只需使用运算符或一系列此类运算符将其流式传输到宏中 。请参阅以下示例，使用`ASSERT_EQ`and`EXPECT_EQ`宏来验证值相等

    ```c++
    ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";
    
    for (int i = 0; i < x.size(); ++i) {
      EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    }
    ```

    

- **基础断言**

| Fatal assertion         | Nonfatal assertion      | Verifies           |
| ----------------------- | ----------------------- | ------------------ |
| ASSERT_TRUE(condition)  | EXPECT_TRUE(condition)  | condition is true  |
| ASSERT_FALSE(condition) | EXPECT_FALSE(condition) | condition is false |

- **数值比较**

| Fatal assertion                 | Nonfatal assertion              | Verifies           |
| ------------------------------- | ------------------------------- | ------------------ |
| `ASSERT_EQ(`*val1*`,`*val2*`);` | `EXPECT_EQ(`*val1*`,`*val2*`);` | *val1* `==` *val2* |
| `ASSERT_NE(`*val1*`,`*val2*`);` | `EXPECT_NE(`*val1*`,`*val2*`);` | *val1* `!=` *val2* |
| `ASSERT_LT(`*val1*`,`*val2*`);` | `EXPECT_LT(`*val1*`,`*val2*`);` | *val1* `<` *val2*  |
| `ASSERT_LE(`*val1*`,`*val2*`);` | `EXPECT_LE(`*val1*`,`*val2*`);` | *val1* `<=` *val2* |
| `ASSERT_GT(`*val1*`,`*val2*`);` | `EXPECT_GT(`*val1*`,`*val2*`);` | *val1* `>` *val2*  |
| `ASSERT_GE(`*val1*`,`*val2*`);` | `EXPECT_GE(`*val1*`,`*val2*`);` | *val1* `>=` *val2* |

- **字符串比较**

| Fatal assertion                        | Nonfatal assertion                     | Verifies                                                     |
| -------------------------------------- | -------------------------------------- | ------------------------------------------------------------ |
| `ASSERT_STREQ(`*str1*`,`*str2*`);`     | `EXPECT_STREQ(`*str1*`,`_str_2`);`     | the two C strings have the same content                      |
| `ASSERT_STRNE(`*str1*`,`*str2*`);`     | `EXPECT_STRNE(`*str1*`,`*str2*`);`     | the two C strings have different content                     |
| `ASSERT_STRCASEEQ(`*str1*`,`*str2*`);` | `EXPECT_STRCASEEQ(`*str1*`,`*str2*`);` | the two C strings have the same content, ignoring case(忽略大小写) |
| `ASSERT_STRCASENE(`*str1*`,`*str2*`);` | `EXPECT_STRCASENE(`*str1*`,`*str2*`);` | the two C strings have different content, ignoring case(忽略大小写) |

## 3 sample

- demo1见routing_planning/Notes/GoogleTest/demo1

```c++
#include <gtest/gtest.h>

int add(int a ,int b){
  return a+b;
}
//一个 test_case_name 对应一个函数的测试用例，test_name 可以对应这个测试用例下的某个场景的测试集。
//这两个名字可以任意取，但应该是有意义的，而且不能包含下划线 _
TEST(testCase , test0){
  EXPECT_EQ(add(8,11),19);
}

TEST(testCase1 , test0){
  EXPECT_EQ(add(7,11),18);
}

int main(){
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

结果：
[==========] Running 2 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from testCase
[ RUN      ] testCase.test0
[       OK ] testCase.test0 (0 ms)
[----------] 1 test from testCase (0 ms total)

[----------] 1 test from testCase1
[ RUN      ] testCase1.test0
[       OK ] testCase1.test0 (0 ms)
[----------] 1 test from testCase1 (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 2 tests.
```

- demo2较复杂直接见代码routing_planning/Notes/GoogleTest/demo2
- [http://google.github.io/googletest/primer.html](http://google.github.io/googletest/primer.html)中还提供了测试夹具(对多个测试使用相同的数据配置)、调用测试等案例.



------

# Docker

# ROS 2

## 1	ROS 1的弊端

- **多机器人系统**：没有构建多机器人系统的标准
  - 因为ros1不支持多master的概念
- **跨平台**：无法适用于windows、RTOS等系统
- **实时性**：缺少实时性方面的设计
  - 在毫秒级的实时性要求下，`ros1`底层的那套`TCP/UDP`通讯无法满足要求
- **网络连接**：需要良好的网络环境保证数据的完整性
  - WiFi不好或者数据量大的时候下会出现丢包情况（因为tcp/udp把ros的一些特性也封装进去了）
- **产品化**：从科学研究到消费产品的过渡欠佳
  - 通常得维护两套代码
- **项目管理**：无法胜任完整生命周期下项目管理
  - 缺乏一些自动化测试等工具

## 2	ROS 2的设计思想

- **架构的颠覆**
  - ros1的架构下，所有节点需要使用Master进行管理
  - ros2使用基于DDS的Discovery机制，去掉了Master这一机制
- **API的重新设计**
  - ros1中大部分代码都基于2009.2月设计的API(无法满足现在的很多语言新特性)
  - ros2重新设计了用户API,但使用方法类似
    - ROS 2广泛使用C ++ 11。而ROS 1的核心主要使用C ++ 03，在其API并没有使用C++ 11功能
    - ROS 2的Python版本至少为3.5，ROS 1的Python版本为2.7
- **编译系统升级**
  - ros1使用rosbuild、catkin管理项目(项目多了后，会出现各种报错)
  - ros2使用升级版的ament、colcon(基于CMake改进的编译机制) 
- **ros2的优点**
  - 支持多机器人系统(DDS的使用)
  - 铲除原型与产品之间的鸿沟
  - 支持微控制器(主要指MCU)
  - 支持实时控制(DDS的使用 )
  - 跨系统平台支持

## 3	ROS 1 和 ROS 2 的区别

![img](https://img-blog.csdnimg.cn/20191202220328111.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3R1emlhYWE=,size_16,color_FFFFFF,t_70)

|           | OS                        | 通讯          | 节点模型          | 进程          |
| :-------- | :------------------------ | :------------ | :---------------- | :------------ |
| **ROS 1** | linux                     | TCPROS/UDPROS | publish/subscribe | Nodelet       |
| **ROS 2** | linux、Windows、MAC、RTOS | DDS           | discovery         | Intra-process |

![image-20220404102101394](/home/next/.config/Typora/typora-user-images/image-20220404102101394.png)

- rclc的添加主要是ros2要适用于MCU的开发
- ros2中多了一个ros2的Middleware API是为了适配不同的操作系统以及不同的DDS提供商

## 4	DDS(data distribution service数据分发服务)

​    DDS信息发布中间件是一种轻便的、能够提供实时信息传送的中间件技术。DDS中间件是一个软件层，从操作系统、网络传输和底层数据格式的细节中抽象出应用。相同的概念和api提供给不同的编成语言，使得应用在不同的操作系统、编成语言和处理体系架构之间交换信息。底层细节包括数据传输格式、发现、连接、可靠性和、协议、Qos策略等由中间件来管理。

  DDS采用发布/订阅体系架构，以数据为中心，提供丰富的Qos服务质量策略。

## 5	ROS 2安装

```bash
1. 设置编码
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

2.设置软件源
sudo apt update && sudo apt install curl gnupg2 lsb-release
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
 
sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'

3.安装ROS2
sudo apt update
sudo apt install ros-foxy-desktop

4.设置环境变量
source /opt/ros/foxy/setup.bash
  如果有安装ROS1，会提示一个警告

5.安装自动补全工具
sudo apt install python3-argcomplete
 
跑几个例程测试一下：   先运行一个talker：
source /opt/ros/foxy/setup.bash
ros2 run demo_nodes_cpp talker
 
再运行一个Listener
source /opt/ros/foxy/setup.bash
ros2 run demo_nodes_py listener

6.删除
如果哪一天不喜欢了，还可以这样删除：
sudo apt remove ros-foxy-* 


参考连接：https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html
参考连接：https://www.guyuehome.com/10226
```

> 设置软件源可能出现如下问题：
>
> ​	curl: (7) Failed to connect to raw.githubusercontent.com port 443: Connection refused
>
> 解决：
>
> ​	修改hosts解决此问题的办法，不用科学上网。
>
> ​	在[https://www.ipaddress.com/](http://link.zhihu.com/?target=https%3A//www.ipaddress.com/)查询[http://raw.githubusercontent.com](http://link.zhihu.com/?target=http%3A//raw.githubusercontent.com)的真实IP 199.232.28.133 。
>
> ​	修改hosts，添加如下内容：
>
> ​	sudo gedit /etc/hosts
>
> ​	加入这一行：199.232.28.133 raw.githubusercontent.com

## 6	ROS 2使用

### 1	ros1、ros2命令对比

- terminal 命令

  ```bash
  #相当于把ros1里面的命令分开
  rosrun 	--> ros2 run
  rosnode --> ros2 node
  roslaunch --> ros2 launch
  rosparam --> ros2 param
  rospkg 	--> ros2 pkg
  rosservice --> ros2 service 
  rossrv 	--> ros2 srv
  rostopic --> ros2 topic
  rosaction --> ros2 action
  ```

- bashrc存入

  ```bash
  #ros1
  echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc 
  #ros2
  echo "source ~/colcon_ws/install/setup.bash" >> ~/.bashrc
  ```

- 编译

  ```bash
  catkin_make --> colcon build
  #ros1
  catkin_make -DCATKIN_WHITELIST_PACKAGES="" 
  #ros2
  colcon build --packages-select  PACKAGE_NAME
  ```



### 2	功能包创建 & 编译 & 运行

#### 创建功能包 

```bash
mkdir -p dev_src/src
cd ~/dev_src/src

#创建功能包语法
ros2 pkg create --build-type ament_cmake <package_name>

#创建功能包
ros2 pkg create --build-type ament_cmake --node-name my_node my_package --dependencies rclcpp std_msgs (这一步顺便完成了cpp文件的创建)


 --dependencies 参数会将后边的依赖自动添加到package.xml和CMakeLists.txt中
 
将会产生如下文件：
my_package/
├── CMakeLists.txt
├── include
│   └── my_package
├── package.xml
└── src
    └── my_node.cpp
```

#### 编译功能包

```bash
将目录退回到dev_src目录下
运行 colcon build 
这个命令会编译工作空间中的所有功能包

如果只想编译某一个包的话，可以这样：
colcon build --packages-select my_package
```

#### 设置环境变量

```bash
打开一个新的终端，运行下工作空间的环境变量，这样才能让该终端找到新创建的包：
. install/setup.bash
 接下来就可以在该终端中运行新建的功能包
```

#### 运行功能包中的节点

```bash
接着上述 设置环境变量的步骤 运行
ros2 run my_package my_node
```

#### 自定义cpp文件需要修改package.xml和CMakeLists.txt

```bash
/*****************************************************/
package.xml
#后序如果要设置依赖项
需要添加依赖项，放到ament_cmake下边：
<depend>rclcpp</depend>
<depend>std_msgs</depend>


/*****************************************************/
CMakeLists.txt
#设置编译规则
接下来打开CMakeLists.txt文件，在find_package语句下，新加入两行：
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

#然后再设置具体的编译规则
add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

#最后还要设置安装的规则，这样ros2 run命令才找的到执行文件
install(TARGETS
  talker
  DESTINATION
  lib/${PROJECT_NAME})
```



## 7	ROS_DOMAIN_ID

如果在局域网的多台电脑中使用ROS2，默认的通信机制会自动建立各机器分布式通信框架，也就是不同电脑之间已经可以通信了，如果你不希望多台电脑之间产生连接，可以设置不同的组网ID，相同ID的电脑之间可以通信，不同ID的电脑之间无法通信。  

**临时端口**

默认情况下，Linux 内核使用端口 32768-60999 作为临时端口。这意味着域 ID 0-101 和 215-232 可以安全使用，而不会与临时端口冲突。临时端口范围可在 Linux 中通过在`/proc/sys/net/ipv4/ip_local_port_range`. 如果使用自定义临时端口范围，则可能必须相应调整上述数字。

**参与者限制**

对于计算机上运行的每个 ROS 2 进程，都会创建一个 DDS“参与者”。由于每个 DDS 参与者占用计算机上的两个端口，因此在一台计算机上运行 120 多个 ROS 2 进程可能会溢出到其他域 ID 或临时端口。

**Linux**

```
export ROS_DOMAIN_ID=<your_domain_id>
echo "export ROS_DOMAIN_ID=<your_domain_id>" >> ~/.bashrc
```