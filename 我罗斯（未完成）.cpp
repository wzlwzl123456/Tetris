#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define FrameX  16  //��Ϸ�������Ͻǵ�X������
#define FrameY  4  //��Ϸ�������Ͻǵ�Y������
#define height  20 //��Ϸ���ڵĸ߶�
#define width   10//��Ϸ���ڵĿ�� 
#define StartX  1+width/2//����˹�������ĳ���λ�ú����� 
#define StartY  2//����˹�������ĳ���λ�������� 
int s[5][5] = { 0 };//����˹������������ 
int a[height + 2][width + 2] = { 0 };//����˹�����ӡ����
int flag_old = 0;	//��ǰ����˹������� 
int flag_next = 0;//��һ������˹������� 
int left = 1;	//1Ϊ�����ƣ�0Ϊ�������� 
int right = 1;//1Ϊ�����ƣ�0Ϊ��������
int down = 1;	//1Ϊ�����ƣ�0Ϊ��������
int trans = 1;//1Ϊ����ת��0Ϊ������ת 
int X = StartX;//���ķ��������
int Y = StartY;//���ķ���������
int Line = 0;	//���������� 
int Level = 1;//�ȼ�
int Score = 0;//����
/****************************************
 * ȷ����Ļ���λ��
 ****************************************/
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;//������
    pos.Y = y;//������
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/****************************************
* ������Ļ���
****************************************/
void HideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = 0; //���ؿ���̨���
    SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}
/****************************************
 * ���ɶ���˹����
 ****************************************/
void MakeTetris()
{
    int i = 0, j = 0;
    srand(time(NULL));
    if (flag_old == 0)flag_old = rand() % 19 + 1;
    else flag_old = flag_next;
    flag_next = rand() % 19 + 1;
    for (i = 0; i < 5; i++)for (j = 0; j < 5; j++)s[i][j] = 0;
    switch (flag_old)
    {
    case  1:s[1][1] = 1; s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; break;//��
    case  2:s[1][2] = 1; s[1][3] = 1; s[2][2] = 1; s[3][2] = 1; break;//������
    case  3:s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; s[3][3] = 1; break;
    case  4:s[1][2] = 1; s[2][2] = 1; s[3][1] = 1; s[3][2] = 1; break;
    case  5:s[1][2] = 1; s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; break;//  ��
    case  6:s[1][2] = 1; s[2][2] = 1; s[2][3] = 1; s[3][2] = 1; break;//������
    case  7:s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; s[3][2] = 1; break;//
    case  8:s[1][2] = 1; s[2][1] = 1; s[2][2] = 1; s[3][2] = 1; break;
    case  9:s[1][3] = 1; s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; break;//    ��
    case 10:s[1][2] = 1; s[2][2] = 1; s[3][2] = 1; s[3][3] = 1; break;//������
    case 11:s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; s[3][1] = 1; break;
    case 12:s[1][1] = 1; s[1][2] = 1; s[2][2] = 1; s[3][2] = 1; break;
    case 13:s[2][1] = 1; s[2][2] = 1; s[2][3] = 1; s[2][4] = 1; break;//��������
    case 14:s[1][2] = 1; s[2][2] = 1; s[3][2] = 1; s[4][2] = 1; break;
    case 15:s[1][1] = 1; s[1][2] = 1; s[2][2] = 1; s[2][3] = 1; break;//����
    case 16:s[1][3] = 1; s[2][2] = 1; s[2][3] = 1; s[3][2] = 1; break;//  ����
    case 17:s[1][2] = 1; s[1][3] = 1; s[2][1] = 1; s[2][2] = 1; break;//  ����
    case 18:s[1][1] = 1; s[2][1] = 1; s[2][2] = 1; s[3][2] = 1; break;//����
    case 19:s[2][2] = 1; s[2][3] = 1; s[3][2] = 1; s[3][3] = 1; break;//����
                                                                      //����
    default:break;
    }
}

/****************************************
 * ��ӡ������˹����
 ****************************************/
void PrintTetris()

{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++)
       for (j = 0; j < 5; j++)a[Y - 2 + i][X - 2 + j] = s[i][j];
    for (i = 1; i <= height; i++)
    {
        gotoxy(FrameX + 2, FrameY + i);
        for (j = 1; j <= width; j++)
            if (a[i][j])printf("��");
            else printf("  ");
    }
}

/****************************************
 * �ж϶���˹�����Ƿ���ƶ��ͱ���
 ****************************************/
void Judge_MoveAndTansform()
{
    switch (flag_old)
    {
    case  1:if (a[Y - 1][X - 2] == 0 && a[Y][X - 2] == 0)left = 1; else left = 0;
        if (a[Y - 1][X] == 0 && a[Y][X + 2] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X] == 0 && a[Y - 1][X + 1] == 0 && a[Y + 1][X] == 0)trans = 1; else trans = 0;
        break;
    case  2:if (a[Y - 1][X - 1] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 2] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 2][X] == 0 && a[Y][X + 1] == 0)down = 1; else down = 0;
        if (a[Y][X - 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case  3:if (a[Y][X - 2] == 0 && a[Y + 1][X] == 0)left = 1; else left = 0;
        if (a[Y][X + 2] == 0 && a[Y + 1][X + 2] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 2][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X] == 0 && a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0)trans = 1; else trans = 0;
        break;
    case  4:if (a[Y - 1][X - 1] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 2] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 2][X - 1] == 0 && a[Y + 2][X] == 0)down = 1; else down = 0;
        if (a[Y - 1][X - 1] == 0 && a[Y][X - 1] == 0 && a[Y][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case  5:if (a[Y - 1][X - 1] == 0 && a[Y][X - 2] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 2] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y + 1][X] == 0)trans = 1; else trans = 0;
        break;
    case  6:if (a[Y - 1][X - 1] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 2] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 2][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y][X - 1] == 0)trans = 1; else trans = 0;
        break;
    case  7:if (a[Y][X - 2] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y][X + 2] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 2][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X] == 0)trans = 1; else trans = 0;
        break;
    case  8:if (a[Y - 1][X - 1] == 0 && a[Y][X - 2] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 2][X] == 0)down = 1; else down = 0;
        if (a[Y][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case  9:if (a[Y][X - 2] == 0 && a[Y - 1][X] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 2] == 0 && a[Y][X + 2] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case 10:if (a[Y - 1][X - 1] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 2] == 0)right = 1; else right = 0;
        if (a[Y + 2][X] == 0 && a[Y + 2][X + 1] == 0)down = 1; else down = 0;
        if (a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0 && a[Y][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case 11:if (a[Y][X - 2] == 0 && a[Y + 1][X - 2] == 0)left = 1; else left = 0;
        if (a[Y][X + 2] == 0 && a[Y + 1][X] == 0)right = 1; else right = 0;
        if (a[Y + 2][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X - 1] == 0 && a[Y - 1][X] == 0 && a[Y + 1][X] == 0)trans = 1; else trans = 0;
        break;
    case 12:if (a[Y - 1][X - 2] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y][X - 1] == 0 && a[Y + 2][X] == 0)down = 1; else down = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X - 1] == 0 && a[Y][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case 13:if (a[Y][X - 2] == 0)left = 1; else left = 0;
        if (a[Y][X + 3] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0 && a[Y + 1][X + 2] == 0)down = 1; else down = 0;
        if (a[Y - 1][X] == 0 && a[Y + 1][X] == 0 && a[Y + 2][X] == 0)trans = 1; else trans = 0;
        break;
    case 14:if (a[Y - 1][X - 1] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0 && a[Y + 2][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0 && a[Y + 2][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 3][X] == 0)down = 1; else down = 0;
        if (a[Y][X - 1] == 0 && a[Y][X + 1] == 0 && a[Y][X + 2] == 0)trans = 1; else trans = 0;
        break;
    case 15:if (a[Y - 1][X - 2] == 0 && a[Y][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 2] == 0)right = 1; else right = 0;
        if (a[Y][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y + 1][X] == 0)trans = 1; else trans = 0;
        break;
    case 16:if (a[Y - 1][X] == 0 && a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 2] == 0 && a[Y][X + 2] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 2][X] == 0 && a[Y + 1][X + 1] == 0)down = 1; else down = 0;
        if (a[Y - 1][X - 1] == 0 && a[Y - 1][X] == 0)trans = 1; else trans = 0;
        break;
    case 17:if (a[Y - 1][X - 1] == 0 && a[Y][X - 2] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 2] == 0 && a[Y][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 1][X] == 0 && a[Y][X + 1] == 0)down = 1; else down = 0;
        if (a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case 18:if (a[Y - 1][X - 2] == 0 && a[Y][X - 2] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y - 1][X + 1] == 0 && a[Y][X + 1] == 0 && a[Y + 1][X + 1] == 0)right = 1; else right = 0;
        if (a[Y + 1][X - 1] == 0 && a[Y + 2][X] == 0)down = 1; else down = 0;
        if (a[Y - 1][X] == 0 && a[Y - 1][X + 1] == 0)trans = 1; else trans = 0;
        break;
    case 19:if (a[Y][X - 1] == 0 && a[Y + 1][X - 1] == 0)left = 1; else left = 0;
        if (a[Y][X + 2] == 0 && a[Y + 1][X + 2] == 0)right = 1; else right = 0;
        if (a[Y + 2][X] == 0 && a[Y + 2][X + 1] == 0)down = 1; else down = 0;
        trans = 0;
        break;
    default:break;
    }
}

int main()
{
	
}
