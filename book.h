#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;
typedef struct book //ͼ��
{
	char title[100];  //����
	char isbn[100];  //���
	char author[100];  //����
	char publisher[100];  //������
	char publishtime[100];//��������
	int value;  //����
	int cnt; //�鼮����
	struct book* next;  //��һ���鼮
}Book;




