#include <stdio.h>
#include <string.h>
#define MAX_STU 100   // 最多学生数

typedef struct {
    int id;         //学号
    char name[20];  // 姓名
    float score;    // 成绩
} Student;

Student stu[MAX_STU];
int count = 0;  // 当前学生数量

void menu();
void add();
void search();
void modify();
void del();
void sort();
void average();
void loadFromTxt();
void saveToTxt();

  int main(void)
{
    loadFromTxt();
    int choice;
    while (1)
    {
        menu();
        printf("请输入功能选择：");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: add(); break;
            case 2: search(); break;
            case 3: modify(); break;
            case 4: del(); break;
            case 5: sort(); break;
            case 6: average(); break;
            case 0:
                printf("退出系统！\n");
                return 0;
            default: printf("输入错误，请重新选择！\n");
        }
    }
    return 0;
}

void menu()
{
    printf("\n===== 学生成绩管理系统 =====\n");
    printf("1. 录入学生信息\n");
    printf("2. 查询学生信息\n");
    printf("3. 修改学生成绩\n");
    printf("4. 删除学生信息\n");
    printf("5. 按成绩降序排序\n");
    printf("6. 统计平均分\n");
    printf("0. 退出系统\n");
    printf("============================\n");
}

void add()
{
    if (count >= MAX_STU)
    {
        printf("人数已满，无法添加！\n");
        return;
    }
    printf("请输入学号 姓名 成绩：");
    scanf("%d %s %f", &stu[count].id, stu[count].name, &stu[count].score);
    count++;
    printf("添加成功！\n");
    saveToTxt();
}

void search()
{
    int id, i, flag = 0;
    printf("请输入要查询的学号：");
    scanf("%d", &id);
    for (i = 0; i < count; i++)
    {
        if (stu[i].id == id)
        {
            printf("查到：学号:%d 姓名:%s 成绩:%.2f\n", stu[i].id, stu[i].name, stu[i].score);
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("未找到该学生！\n");
}

void modify()
{
    int id, i, flag = 0;
    float newScore;
    printf("请输入要修改的学号：");
    scanf("%d", &id);
    for (i = 0; i < count; i++)
    {
        if (stu[i].id == id)
        {
            printf("原信息：学号:%d 姓名:%s 成绩:%.2f\n", stu[i].id, stu[i].name, stu[i].score);
            printf("输入新成绩：");
            scanf("%f", &newScore);
            stu[i].score = newScore;
            printf("修改成功！\n");
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("未找到该学生！\n");
    if(flag) saveToTxt();
}

void del()
{
    int id, i, j, flag = 0;
    printf("请输入要删除的学号：");
    scanf("%d", &id);
    for (i = 0; i < count; i++)
    {
        if (stu[i].id == id)
        {
            for (j = i; j < count - 1; j++)
            {
                stu[j] = stu[j+1];
            }
            count--;
            printf("删除成功！\n");
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("未找到该学生！\n");
    if(flag) saveToTxt();
}

void sort()
{
    int i, j;
    Student temp;
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            if (stu[j].score < stu[j+1].score)
            {
                temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
    printf("===== 排序结果（成绩降序）=====\n");
    for (i = 0; i < count; i++)
    {
        printf("%d\t%s\t%.2f\n", stu[i].id, stu[i].name, stu[i].score);
    }
    saveToTxt();
}

void average()
{
    int i;
    float sum = 0, avg;
    if (count == 0)
    {
        printf("暂无学生数据！\n");
        return;
    }
    for (i = 0; i < count; i++)
    {
        sum += stu[i].score;
    }
    avg = sum / count;
    printf("学生总数：%d，总分：%.2f，平均分：%.2f\n", count, sum, avg);
}

void saveToTxt()
{
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        printf("?? 文件打开失败，无法保存！\n");
        return;
    }
    fprintf(fp, "%d\n", count);
    for(int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %.2f\n", stu[i].id, stu[i].name, stu[i].score);
    }
    fclose(fp);
    printf("? 数据已保存到 student.txt\n");
}

void loadFromTxt() {
      FILE *fp = fopen("student.txt", "r");
      if (fp == NULL) {
          printf("? 没有找到student.txt，新建文件\n");
          count=0;
          return;
      }
      if (fscanf(fp, "%d", &count) != 1) {
          count=0;
          fclose(fp);
          return;
      }
      if (count<0) count=0;
      if (count>MAX_STU) count=MAX_STU;
      for(int i = 0; i < count; i++)
      {
          fscanf(fp, "%d %s %f\n", &stu[i].id, &stu[i].name, &stu[i].score);
      }
      fclose(fp);
}