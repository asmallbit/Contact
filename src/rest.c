//
// Created by jwhan on 2021/5/6.
//
#include "../include/rest.h"

//uint8_t转int
int uint8ToBin(uint8_t *handel, int length)
{
    int counter = 0;
    int result = 0;
    while (counter < length)
    {
        result = result * 10000 + handel[counter];
        counter++;
    }
    return result;
}

//显示菜单
void menu()
{
    printf("\n************电话簿************\n");
    printf("菜单:\n");
    printf("1.添加联系人\n2.查看现有联系人\n3.通过电话号码查询联系人信息\n4.通过姓名查询联系人信息\n");
    printf("5.通过地址查询联系人信息\n9.退出程序\n请输入您想选择的功能: ");
}

//scanf的安全替代,仅针对整形
void safetyScanfInt(int *in)
{
    int choice, flag = 0;
    while (flag == 0)
    {
        flag = scanf("%d", in);
        while ((choice = getchar()) != '\n' && choice != EOF)
            ; //清除缓存
        if (flag == 0)
        {
            printf("输入错误,请重新输入: ");
        }
    }
}

void safetyScanfString(char *str)
{
    char *flag = NULL;
    int len;
    while (flag == 0)
    {
        //flag = scanf("%s", str);
        //flag = gets(str);
        flag = fgets(str, MAXNUM-1, stdin);
        len = strlen(str);
        str[len-1] = '\0';
        //while ((choice = getchar()) != '\n' && choice != EOF)
        //; //清除缓存
        if (flag == 0)
        {
            printf("输入错误,请重新输入: ");
        }
    }
}

// 创建文件夹
void createFolder(char* folderName)
{
    // 文件夹不存在则创建文件夹
    if (_access(folderName, 0) == -1)
    {
        _mkdir(folderName);
    }
}
