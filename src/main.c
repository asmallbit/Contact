#include "../include/contact.h"
#include "../include/rest.h"
#include <stdio.h>
#define LISTNUM 30 //列表长度
//#define MAXNUM 90    //字符串的最大长度

//以下是临时文件地址
#define TEMPPHONEFILE "../contactData/tmp/phoneTemp.txt"
#define TEMPNAMEFILE "../contactData/tmp/nameTemp.txt"
#define TEMPADDRESSFILE "../contactData/tmp/addressTemp.txt"
//以下是真正的通讯录地址
#define TRUECONTACTFILE "../contactData/contact.txt"

int main()
{
    int flag = 0, contactNum;
    char *name, *phone, *address;
    Pbase baseName, basePhone, baseAddress;
    Pcontact contactName, contactPhone, contactAddress;
    Pcontact contact;
    contactPhone = createNullContact();
    contactAddress = createNullContact();
    contactName = createNullContact();
    baseName = createEmptyBasement(LISTNUM);
    basePhone = createEmptyBasement(LISTNUM);
    baseAddress = createEmptyBasement(LISTNUM);
    name = (char *)malloc(sizeof(char) * MAXNUM);
    phone = (char *)malloc(sizeof(char) * MAXNUM);
    address = (char *)malloc(sizeof(char) * MAXNUM);
    while (flag != 9)
    {
        menu();
        safetyScanfInt(&flag);
        if (flag == 1)
        {
            printf("请输入联系人的姓名: ");
            safetyScanfString(name);
            printf("请输入联系人的电话: ");
            safetyScanfString(phone);
            printf("请输入联系人的住址: ");
            safetyScanfString(address);
            if (addContact(baseName, basePhone, baseAddress, phone, name, address, TRUECONTACTFILE))
            {
                printf("添加成功!\n");
            }
        }
        //查看现有的联系人
        else if (flag == 2)
        {
            contactNum = showAllContact(TRUECONTACTFILE);
            if (contactNum == 0)
            {
                printf("您当前还没有存储联系人哦\n");
            }
            else
            {
                printf("当前总共存储了%d位联系人\n", contactNum);
            }
        }
        //查找  通过电话号
        else if (flag == 3)
        {
            //输入
            printf("请输入您要查找的联系人的电话号码: ");
            safetyScanfString(phone);
            //先从当前内存中存储的开始找
            if (searchContactPhone(basePhone, phone, contactPhone) == 1)
            {
                printf("查找成功!对应的信息为:\n");
                printf("姓名:%s\t电话号码:%s\t住址:%s\n", contactPhone->name, contactPhone->phone, contactPhone->address);
            }
            else if (searchContactPhone(basePhone, phone, contactPhone) == 0)
            {
                //转到文件中找
                searchContactPhoneFile(phone);
            }
            else
            {
                printf("写入文件失败,请检查你的磁盘是否出现问题\n");
            }
        }
        //查找  通过姓名
        else if (flag == 4)
        {
            //输入
            printf("请输入您要查找的联系人的姓名: ");
            safetyScanfString(name);
            //先从当前内存中存储的开始找
            if (searchContactName(baseName, name, contactName) == 1)
            {
                printf("查找成功!对应的信息为:\n");
                printf("姓名:%s\t电话号码:%s\t住址:%s\n", contactName->name, contactName->phone, contactName->address);
            }
            else if (searchContactName(baseName, name, contactName) == 0)
            {
                //转到文件中找
                searchContactNameFile(name);
            }
            else
            {
                printf("写入文件失败,请检查你的磁盘是否出现问题\n");
            }
        }
        //查找  通过地址
        else if (flag == 5)
        {
            //输入
            printf("请输入您要查找的联系人的住址: ");
            safetyScanfString(address);
            //先从当前内存中存储的开始找
            if (searchContactAddress(baseAddress, address, contactAddress) == 1)
            {
                printf("查找成功!对应的信息为:\n");
                printf("姓名:%s\t电话号码:%s\t住址:%s\n", contactAddress->name, contactAddress->phone, contactAddress->address);
            }
            else if (searchContactAddress(basePhone, phone, contactPhone) == 0)
            {
                //转到文件中找
                searchContactAddressFile(address);
            }
            else
            {
                printf("写入文件失败,请检查你的磁盘是否出现问题\n");
            }
        }
        //退出,进行释放指针等操作及询问用户是否保留电话簿
        else if (flag == 9)
        {
            //释放之前申请的空间
            freePbase(basePhone);
            freePbase(baseName);
            freePbase(baseAddress);
            free(name);
            free(address);
            free(phone);
        }
        else
        {
            printf("输入不合法,请检查你的输入\n");
        }
    }
    return 0;
}