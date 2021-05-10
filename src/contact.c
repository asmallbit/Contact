//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "UnreachableCode"
#include "../include/contact.h"

//创建外层链表中的一个空元素
int insertElement(Pbase p)
{
    Pbase new;
    while (p->next != NULL)
    {
        p = p->next;
    }
    new = (Pbase)malloc(sizeof(struct base));
    if (new != NULL)
    {
        new->next = NULL;
        new->tail = NULL;
        p->next = new;
        return 1;
    }
    return 0;
}

//创建一个空的表
Pbase createEmptyBasement(int size)
{
    int counter = 0;
    Pbase new, temp; //op做new的前驱
    new = (Pbase)malloc(sizeof(struct base));
    if (new == NULL)
    {
        return NULL;
    }
    new->next = NULL;
    new->tail = NULL;
    while (counter < size - 1)
    {
        if (!insertElement(new))
        {
            break;
        }
        counter++;
    }
    if (counter == size - 1)
    {
        return new;
    }
    else
    {
        while (counter >= 0)
        {
            temp = new->next;
            free(new);
            new = temp;
            counter--;
        }
        printf("Out of space!\n");
        return NULL;
    }
}

//创建空的联系人
Pcontact createNullContact()
{
    Pcontact new;
    new = (Pcontact)malloc(sizeof(struct contact));
    if (new != NULL)
    {
        new->address = (char *)malloc(sizeof(char) * MAXNUM);
        if (new->address == NULL)
        {
            printf("Out of space!\n");
            free(new);
            return NULL;
        }
        new->name = (char *)malloc(sizeof(char) * MAXNUM);
        if (new->name == NULL)
        {
            printf("Out of space!\n");
            free(new->address);
            free(new);
            return NULL;
        }
        new->phone = (char *)malloc(sizeof(char) * MAXNUM);
        if (new->phone == NULL)
        {
            printf("Out of space!\n");
            free(new->address);
            free(new->name);
            free(new);
            return NULL;
        }
        new->next = NULL;
        return new;
    }
    printf("Out of space!\n");
    return NULL;
}

//寻找联系人应该存放的位置(针对电话号码)
int positionPhone(Pcontact p)
{
    uint8_t element[16];
    int store;
    FILE *fp;
    fp = fopen(TEMPPHONEFILE, "w+");
    fputs(p->phone, fp);
    fclose(fp);
    if (MD5(TEMPPHONEFILE, element))
    {
        store = uint8ToBin(element, MAXWORDSOFMD5TRANS);
        return store % LISTNUM;
    }
    else
    {
        printf("抱歉,文件处理出现异常,请重启本程序\n");
        return -1;
    }
}

//寻找新建的联系人应该插入的位置(通过姓名确定)
int positionName(Pcontact p)
{
    uint8_t element[16];
    int store;
    FILE *fp;
    fp = fopen(TEMPNAMEFILE, "w+");
    fputs(p->name, fp);
    fclose(fp);
    if (MD5(TEMPNAMEFILE, element))
    {
        store = uint8ToBin(element, MAXWORDSOFMD5TRANS);
        return store % LISTNUM;
    }
    else
    {
        printf("抱歉,文件处理出现异常,请重启本程序\n");
        return -1;
    }
}

//寻找新建的联系人应该插入的位置(通过住址确定)
int positionAddress(Pcontact p)
{
    uint8_t element[16];
    int store;
    FILE *fp;
    fp = fopen(TEMPADDRESSFILE, "w+");
    fputs(p->address, fp);
    fclose(fp);
    if (MD5(TEMPADDRESSFILE, element))
    {
        store = uint8ToBin(element, MAXWORDSOFMD5TRANS);
        return store % LISTNUM;
    }
    else
    {
        printf("抱歉,文件处理出现异常,请重启本程序\n");
        return -1;
    }
}

//散列关键码存入链表
int pushContact(Pbase p, int pos, Pcontact new)
{
    int counter = 1;
    Pcontact temp;
    while (counter < pos)
    {
        p = p->next;
        counter++;
    }
    temp = p->tail;
    //假如元素后面没有后继
    if (temp == NULL)
    {
        p->tail = new;
        return 1;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new;
    return 1;
}

//创建联系人        因为要创建3个链表,所以难免显得比较啰嗦
int addContact(Pbase pName, Pbase pPhone, Pbase pAddress, char *phone, char *name, char *address, char *file)
{
    Pcontact new1, new2, new3;
    int posName, posPhone, posAddress, stringLen;
    char *aline;
    aline = (char *)malloc(sizeof(char) * (MAXWORDSINALION + 1));
    new1 = createNullContact();
    new2 = createNullContact();
    new3 = createNullContact();
    if (new1 == NULL || new2 == NULL || new3 == NULL)
    {
        return 0;
    }
    //开始复制
    strcpy(new1->name, name);
    strcpy(new1->phone, phone);
    strcpy(new1->address, address);
    strcpy(new2->name, name);
    strcpy(new2->phone, phone);
    strcpy(new2->address, address);
    strcpy(new3->name, name);
    strcpy(new3->phone, phone);
    strcpy(new3->address, address);
    //建立三个链表,每个链表均为散列排列
    //先找到元素对应的特征值
    posName = positionName(new1);
    posPhone = positionPhone(new1);
    posAddress = positionAddress(new1);
    //开始添加到链表并写入到文件
    pushContact(pName, posName, new1);
    pushContact(pPhone, posPhone, new2);
    pushContact(pAddress, posAddress, new3);
    //存入文件中,首先对写入的字符串进行处理
    aline[0] = '\0';
    strcat(aline, name);
    stringLen = strlen(aline);
    aline[stringLen] = '\t';
    aline[stringLen + 1] = '\0';
    strcat(aline, phone);
    stringLen = strlen(aline);
    aline[stringLen] = '\t';
    aline[stringLen + 1] = '\0';
    strcat(aline, address);
    stringLen = strlen(aline);
    aline[stringLen] = '\n';
    aline[stringLen + 1] = '\0';
    //开始处理写入文件
    FILE *fp;
    fp = fopen(file, "a+");
    fputs(aline, fp);
    fclose(fp);
    return 1;
}

//查找联系人根据手机号码
//查找联系人(手机号)
int searchContactPhone(Pbase p, char *phone, Pcontact store)
{
    int pos, partMD5, counter = 1;
    FILE *fp;
    Pcontact temp;
    uint8_t result[16];
    fp = fopen(TEMPPHONEFILE, "w+");
    if (fputs(phone, fp) != EOF)
    {
        fclose(fp);
        if (MD5(TEMPPHONEFILE, result))
        {
            partMD5 = uint8ToBin(result, MAXWORDSOFMD5TRANS);
            //定位对应的位置
            pos = partMD5 % LISTNUM;
            while (counter < pos)
            {
                p = p->next;
                counter++;
            }
        }
        temp = p->tail;
        while (temp != NULL)
        {
            if (!strcmp(temp->phone, phone))
            {
                fclose(fp);
                //store = temp;
                strcpy(store->address, temp->address);
                strcpy(store->name, temp->name);
                strcpy(store->phone, temp->phone);
                return 1;
            }
            temp = temp->next;
        }
        fclose(fp);
        store = NULL;
        return 0;
    }
    else
    {
        store = NULL;
        return -1;
    }
}

//查找联系人(姓名)
int searchContactName(Pbase p, char *name, Pcontact store)
{
    int pos, partMD5, counter = 1;
    FILE *fp;
    Pcontact temp;
    uint8_t result[16];
    fp = fopen(TEMPNAMEFILE, "w+");
    if (fputs(name, fp) != EOF)
    {
        fclose(fp);
        if (MD5(TEMPNAMEFILE, result))
        {
            partMD5 = uint8ToBin(result, MAXWORDSOFMD5TRANS);
            //查找对应的位置
            pos = partMD5 % LISTNUM;
            while (counter < pos)
            {
                p = p->next;
                counter++;
            }
        }
        temp = p->tail;
        while (temp != NULL)
        {
            if (!strcmp(temp->name, name))
            {
                fclose(fp);
                //store = temp;
                strcpy(store->address, temp->address);
                strcpy(store->name, temp->name);
                strcpy(store->phone, temp->phone);
                return 1;
            }
            temp = temp->next;
        }
        fclose(fp);
        store = NULL;
        return 0;
    }
    else
    {
        store = NULL;
        return -1;
    }
}

//查找联系人(地址)
int searchContactAddress(Pbase p, char *address, Pcontact store)
{
    int pos, partMD5, counter = 1;
    FILE *fp;
    Pcontact temp;
    uint8_t result[16];
    fp = fopen(TEMPADDRESSFILE, "w+");
    if (fputs(address, fp) != EOF)
    {
        fclose(fp);
        if (MD5(TEMPADDRESSFILE, result))
        {
            partMD5 = uint8ToBin(result, MAXWORDSOFMD5TRANS);
            //定位对应的位置
            pos = partMD5 % LISTNUM;
            while (counter < pos)
            {
                p = p->next;
                counter++;
            }
        }
        temp = p->tail;
        while (temp != NULL)
        {
            if (!strcmp(temp->address, address))
            {
                fclose(fp);
                //store = temp;
                strcpy(store->address, temp->address);
                strcpy(store->name, temp->name);
                strcpy(store->phone, temp->phone);
                return 1;
            }
            temp = temp->next;
        }
        fclose(fp);
        store = NULL;
        return 0;
    }
    else
    {
        store = NULL;
        return -1;
    }
}

//显示当前的所有联系人
int showAllContact(char *file)
{
    char buffer[MAXWORDSINALION], *flag;
    int counter = 0;
    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL)
    {
        //printf("文件不存在!\n");
        return 0;
    }
    flag = fgets(buffer, MAXWORDSINALION, (FILE *)fp);
    printf("姓名\t电话号码\t住址\n");
    while (flag != NULL)
    {
        printf("%s", buffer);
        flag = fgets(buffer, MAXWORDSINALION, fp);
        counter++;
    }
    fclose(fp);
    return counter;
}

//查找联系人(姓名),数据仅存在于文件中时使用
int searchContactNameFile(char *name)
{
    char buff[MAXNUM], *p, *strStore, *flag;
    FILE *fp;
    strStore = (char *)malloc(sizeof(char) * MAXNUM);
    fp = fopen(TRUECONTACTFILE, "r");
    while (1)
    {
        flag = fgets(buff, MAXNUM, fp);
        if (flag == NULL)
        {
            fclose(fp);
            free(strStore);
            printf("抱歉,没有找的关于 %s 的信息\n", name);
            return 0;
        }
        //存储提取的信息
        strcpy(strStore, buff);
        //分割获取的字符
        p = strtok(buff, "\t");
        if (!strcmp(p, name))
        {
            printf("找到符合条件的联系人:\n");
            printf("姓名\t电话号码\t住址\n");
            printf("%s\n", strStore);
            fclose(fp);
            free(strStore);
            return 1;
        }
    }
}

//查找联系人(手机号),数据在存在于文件中时使用
int searchContactPhoneFile(char *phone)
{
    char buff[MAXNUM], *p, *strStore, *flag;
    FILE *fp;
    strStore = (char *)malloc(sizeof(char) * MAXNUM);
    fp = fopen(TRUECONTACTFILE, "r");
    while (1)
    {
        flag = fgets(buff, MAXNUM, fp);
        if (flag == NULL)
        {
            fclose(fp);
            free(strStore);
            printf("抱歉,没有找到手机号为 %s 的信息\n", phone);
            return 0;
        }
        strcpy(strStore, buff);
        //分割获取的字符
        p = strtok(buff, "\t");
        p = strtok(NULL, "\t");
        if (strcmp(p, phone) == 0)
        {
            printf("找到符合条件的联系人:\n");
            printf("姓名\t电话号码\t住址\n");
            printf("%s\n", strStore);
            fclose(fp);
            free(strStore);
            return 1;
        }
    }
}

//查找联系人(地址),数据仅存在于文件时使用
int searchContactAddressFile(char *address)
{
    char buff[MAXNUM], *p, *strStore, *flag;
    FILE *fp;
    strStore = (char *)malloc(sizeof(char) * MAXNUM);
    //可能有待改进,可以进入file参数
    fp = fopen(TRUECONTACTFILE, "r");
    while (1)
    {
        flag = fgets(buff, MAXNUM, fp);
        if (flag == NULL)
        {
            fclose(fp);
            free(strStore);
            printf("抱歉,没有找到住址为 %s 的信息\n", address);
            return 0;
        }
        strcpy(strStore, buff);
        //分割获取的字符
        p = strtok(buff, "\t");
        p = strtok(NULL, "\t");
        p = strtok(NULL, "\t");
        if (!strcmp(address, p))
        {
            printf("找到符合条件的联系人:\n");
            printf("姓名\t电话号码\t住址\n");
            printf("%s\n", strStore);
            fclose(fp);
            free(strStore);
            return 1;
        }
    }
}

//释放指针
void freePbase(Pbase p)
{
    Pbase tempBase;
    Pcontact contact, tempContact;
    //把之前申请的空间全部释放
    while (p != NULL)
    {
        tempBase = p->next;
        contact = p->tail;
        while (contact != NULL)
        {
            tempContact = contact->next;
            free(contact);
            contact = tempContact;
        }
        free(p);
        p = tempBase;
    }
}