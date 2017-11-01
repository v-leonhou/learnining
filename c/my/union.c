#include "stdio.h"

struct info {
    char name[20];
    int num;
    char sex;
    char profession;
    union{
        float score;
        char course[20];
    }sc;
};

void procet()
{
    int i;
    struct info my[2];

    printf("请输入信息:\n");
    printf("姓名 编号 性别(f/m) 职业(t/s) 属性:\n");
    for(i=0;i<2;i++)
    {
        scanf("%s %d %c %c",my[i].name,&my[i].num,&my[i].sex,&my[i].profession);
        if( my[i].profession == 's')
        {
            scanf("%f",&my[i].sc.score);
        }
        else {
            scanf("%s",my[i].sc.course);
        }
        // fflush(stdin);
    }

    printf("\n\n输出学生信息:\n");
    for(i=0;i<2;i++)
    {
        if(my[i].profession == 's')
        {
            printf("%s %d %c %c %f\n",my[i].name,my[i].num,my[i].sex,my[i].profession,my[i].sc.score);
        }
        else {
            printf("%s %d %c %c %s\n",my[i].name,my[i].num,my[i].sex,my[i].profession,my[i].sc.course);
        }

    }
}

int main()
{
    union hello{
        int a;
        char name[10];
    }test;
    test.a = 120000;
    printf("test的大小为%ld\n",sizeof(test));
    printf("test成员a的值%d ,name的值%c你好 \n\n",test.a,test.name[1]);


}
