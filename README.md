## qt工具箱

### ### 一.基本内容

#### 1.各种内置宏的作用

Q_DISABLE_COPY: 禁止复制，防止浅拷贝

注：

1.Pimpl(pointer to implementation) - 编译器封装

### 二.配置连接数据库

#### 1.配置Sql模块

```markdown
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
target_link_libraries(toolkit PRIVATE Qt6::Sql)
```

#### 2.测试代码

```c++
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("10.199.245.227");
    db.setDatabaseName("python_codegen");
    db.setUserName("xxxxxx");
    db.setPassword("xxxxxx");
    bool ok = db.open();
```

注：

1.问题1

QSqlDatabase: QMYSQL driver not loaded
QSqlDatabase: available drivers: QSQLITE QODBC QPSQL

解决方案：[SQL Database Drivers | Qt SQL 6.3.2](https://doc.qt.io/qt-6/sql-driver.html)

2.问题2

'"cmake"' 不是内部或外部命令，也不是可运行的程序或批处理文件。

windows下安装cmake:

[Download | CMake](https://cmake.org/download/)

找不到make: D:\normal\cmake\bin

3.问题3

CMake Error: CMake was unable to find a build program corresponding to "Ninja".

解决方案：add Ninja to system path

D:\dev\qt\Tools\Ninja

4.问题4

No CMAKE_CXX_COMPILER could be found.

需要配置环境变量：D:\dev\qt\Tools\mingw1120_64\bin

安装visual studio code

4.安装命令

```batch
mkdir build-sqldrivers
cd build-sqldrivers

D:\dev\qt\6.3.1\mingw_64\bin\qt-cmake.bat 
 -G Ninja D:\dev\qt\6.3.1\Src\qtbase\src\plugins\sqldrivers 
 -DCMAKE_INSTALL_PREFIX=D:\dev\qt\6.3.1\mingw_64
 -DMySQL_INCLUDE_DIR="D:\normal\mysql\location\include"
 -DMySQL_LIBRARY="D:\normal\mysql\location\lib\libmysql.lib"

cmake --build .
cmake --install .
```

5.问题5

QSqlDatabase: QMYSQL driver not loaded
QSqlDatabase: available drivers: QSQLITE QMARIADB QMYSQL QODBC QPSQL

复制libmysql.dll到mingw_64/bin目录下即可

### 三.测试框架

**Qt支持四种测试框架，分别是QTest,QtQuickTest,Google Test, Boost Test**

```markdown
gtest中断言的宏可以分为两类：一类是ASSERT宏，另一类就是EXPECT宏了。
1、ASSERT_系列：如果当前点检测失败则退出当前函数
2、EXPECT_系列：如果当前点检测失败则继续往下执行
如果你对自动输出的错误信息不满意的话，也是可以通过operator<<能够在失败的时候打印
日志，将一些自定义的信息
```
