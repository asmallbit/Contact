cmake_minimum_required(VERSION 3.19)
project(Contact)

#头文件路径
INCLUDE_DIRECTORIES("C:/msys64/mingw64/include")
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
        )

#生成静态库
add_library(DependFunctions ${source} ${header})

# 生成可执行文件
add_executable(Contact src/main.c)

#链接静态库
target_link_libraries(Contact DependFunctions)