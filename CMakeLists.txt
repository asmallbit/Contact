cmake_minimum_required(VERSION 3.19)
project(Contact)

# 设置为GBK编码
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")  #针对cpp的
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK")  #针对C

#头文件路径
INCLUDE_DIRECTORIES("C:/msys64/mingw64/include")        #标准库头文件,与自身编译器安装头文件路径有关
#INCLUDE_DIRECTORIES("CStandardLibrary/include")        #弃用
INCLUDE_DIRECTORIES("include")

# 源文件
set(source
        src/contact.c
        src/rest.c
        src/md5check.c
        )

#头文件
set(header
        include/contact.h
        include/rest.h
        include/md5check.h
        C:/msys64/mingw64/include       #c库头文件,根据自己机器适当调整
        #CStandardLibrary/include       #弃用
        )

#生成静态库
add_library(DependFunctions ${source} ${header})

# 生成可执行文件
add_executable(Contact src/main.c)

#链接静态库
target_link_libraries(Contact DependFunctions)