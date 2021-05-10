#ifndef CONTACT_H
#define CONTACT_H
#include "md5check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# ifndef LISTNUM
# define LISTNUM 30 //表的规格是20
# endif
# ifndef MAXWORDSINALION
# define MAXWORDSINALION 300 //每行可容纳的最大字符串长度
# endif
# ifndef MAXNUM
# define MAXNUM 100 //每个选项(姓名,电话号码等)容许的最大输入
# endif
#define MAXWORDSOFMD5TRANS 2

//以下是临时文件地址
# ifndef TEMPPHONEFILE
# define TEMPPHONEFILE "../contactData/tmp/phoneTemp.txt"
# endif
# ifndef TEMPNAMEFILE
# define TEMPNAMEFILE "../contactData/tmp/nameTemp.txt"
# endif
# ifndef TEMPADDRESSFILE
# define TEMPADDRESSFILE "../contactData/tmp/addressTemp.txt"
# endif
//以下是真正的通讯录地址
# ifndef TRUECONTACTFILE
# define TRUECONTACTFILE "../contactData/contact.txt"
# endif

struct contact;
typedef struct contact *Pcontact;
struct contact
{
    char *name, *address, *phone;
    Pcontact next;
};

struct base;
typedef struct base *Pbase;
struct base
{
    Pcontact tail;
    Pbase next;
};

//创建一个空的表
Pbase createEmptyBasement(int size);
//创建一个空的联系人
Pcontact createNullContact();
//寻找新建的联系人应该插入的位置(通过电话号码确定)
int positionPhone(Pcontact p);
//寻找新建的联系人应该插入的位置(通过姓名确定)
int positionName(Pcontact p);
//寻找新建的联系人应该插入的位置(通过住址确定)
int positionAddress(Pcontact p);
//添加联系人并写入外存的文件中
int addContact(Pbase pName, Pbase pPhone, Pbase pAddress, char *phone, char *name, char *address, char *file);
//散列关键码存入链表
int pushContact(Pbase p, int pos, Pcontact new);
//查找联系人(姓名),数据在内存中存在时使用
int searchContactName(Pbase p, char *name, Pcontact store);
//查找联系人(手机号),数据在内存中时使用
int searchContactPhone(Pbase p, char *phone, Pcontact store);
//查找联系人(地址),数据在内存中时使用
int searchContactAddress(Pbase p, char *address, Pcontact store);
//查找联系人(姓名),数据仅存在于文件中时使用
int searchContactNameFile(char *name);
//查找联系人(手机号),数据在存在于文件中时使用
int searchContactPhoneFile(char *phone);
//查找联系人(手机号),数据仅存在于文件时使用
int searchContactAddressFile(char *address);
//显示当前的所有联系人并返回联系人数量,从写入的文件中读入
int showAllContact(char *file);
//后续处理,释放指针
void freePbase(Pbase p);
//模糊查找,寻找一切符合条件的选项(删除)
// int searchContactAll(Pcontact p, );

#endif //CONTACT_CONTACT_H
