#ifndef CONTACT_REST_H
#define CONTACT_REST_H
#include <stdint-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <direct.h>

# ifndef MAXNUM
# define MAXNUM 100
# endif

//uint8_t转int
int uint8ToBin(uint8_t *handel, int length);
//主菜单界面
void menu();
//处理输入 整形,相比scanf添加了清除缓存功能
void safetyScanfInt(int *in);
//处理输入 字符串
void safetyScanfString(char *name);
//创建文件夹
void createFolder(char* folderName);

#endif //CONTACT_REST_H
