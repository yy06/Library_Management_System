#include"book.h"

struct node //�û������鼮
{
	int borrow_amount, max_amount; //�����鼮������ ��������
	double tax;  //����ʱ���շѱ���
	time_t borrow_time[10], return_time[10];  //�衢��ʱ��
	Book borrowBook[10];  //ÿλ����10���鼮
};

typedef struct user //�û�
{
	char user_name[30];  //�û���
	char password[30];  //����
	char ID[30]; //��Ч֤������
	int admin;  //�Ƿ����Ա
	struct node user_book;  //�û������鼮
	struct user* next;  //��һλ�û�
}User;

Book* book_head;  //ͼ��ͷָ��
int book_amount;  //ͼ��������
User* user_head;  //�û�ͷָ��
User* g_UserAdmin;  //��������Ա�˺�
int user_amount;  //�û�������
void welcomePage();  //��ӭҳ��
void manual();  //ʹ���ֲ�
void mainMenu();  //���˵�
void userRegister();  //�û�ע��
void userLogin();  //�û���¼
void adminLogin();  //����Ա��½
void userMenu(User*);  //�û��˵�
void userChange(User*);  //�����û���Ϣ
int deleteUser(User*);  //ɾ���˺�
void borrowBook(User*);  //���Ĺ���
void returnBook(User*);  //�������
void history(User*);  //��ʷ�������
void adminIniti();  //��������Ա�˺ų�ʼ��/**<  */
User* serchUsername(char*);  //�����û���
void adminMenu(User*);  //����Ա�˵�
void queryUser();  //�û���Ϣ��ѯ
void adminUser();  //�����û���Ϣ
void allHistory(); //�鿴�û�ͼ����Ĺ黹���
User* serchUserByOrder();  //����������û�
void setAdmin(User*);  //���ù���Ա
void addBook();  //����ͼ����Ϣ
void changeBook() ; //�޸�ͼ����Ϣ
void deleteBook();  //ɾ��ͼ����Ϣ
void browseBook();  //ͼ�����
void searchBook();
void searchTitle();   //����������
void searchAuthor();       // �����߲���
void searchIsbn();         //����Ų���
void searchPublisher();     //�����������
void creatUserList(char*, char*, char*);  //�����û�����
void creatBookList(char*, char*, char*, char*, int);  //����ͼ������
void userIniti(User*);  //�û�ͼ������ʼ��
void load();  //���ļ��м�������
void save();  //�������ݵ��ļ�


void welcomePage()  //��ӭҳ��
{
	load();
	while (1)
	{
	    puts("+---------------------------------------------+");
		puts("|            ��ӭʹ��ͼ�����ϵͳ!            |");
		puts("|---------------------------------------------|");
		puts("|                 [1]����ϵͳ                 |");
		puts("|                 [2]ʹ���ֲ�                 |");
		puts("|                 [0]�˳�ϵͳ                 |");
		puts("+---------------------------------------------+");
        puts("�������ֺ�س���");

		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: mainMenu(); break; // ����ϵͳ
		case 2: manual(); system("pause"); system("cls"); break; //ʹ���ֲ�
		case 0: return ; //�˳�ϵͳ
		default: puts("ָ�����,����������!");
		system("cls"); break;
		}
	}
}
void manual() //ʹ���ֲ�
{
	puts("��ϵͳΪͼ����Ĺ���ϵͳ");
	puts("[*] ����Ա����");
	puts("[1] ���,�޸�ɾ��ͼ����Ϣ");
	puts("[2] ��ѯͼ��");
	puts("[3] �����û�");
	puts("[4] ��ѯ�����û��������");

	puts("[*] �û�����");
	puts("[1] ��ѯͼ��");
	puts("[2] ����ͼ��");
	puts("[3] �黹ͼ��");

}
void mainMenu()  //���˵�
{
	while (1)
	{
        puts("+---------------------------------------------+");
		puts("|                    ���˵�                   |");
        puts("|---------------------------------------------|");
		puts("|                [1] �û�ע��                 |");
		puts("|                [2] �û���½                 |");
		puts("|                [3] ����Ա��½               |");
		puts("|                [0] ���ػ�ӭҳ��             |");
        puts("+---------------------------------------------+");
        puts("�������ֺ�س���");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
        //�û�ע��
		case 1: userRegister(); break;
		//�û���¼
		case 2: userLogin();  break;
		//����Ա��¼
		case 3: adminLogin();  break;
		//���ص���ӭ����
		case 0: return;
		default: puts("ָ�����,����������!");
		system("cls"); break;
		}
	}
}
void userRegister()  //�û�ע��
{
	char name[30];
	puts("������ע����û���");
	scanf("%s", name);
	User* account;

    //�����û�
	while (account = serchUsername(name), account != NULL)
	{
		puts("���û����Ѵ���,���������룡");
		scanf("%s", name);
	}

	puts("����������(������25����ĸ)");
	char password[30];
	scanf("%s", password);

	puts("������֤������");
	char ID[30];
	scanf("%s", ID);
	//�����û�������
	creatUserList(name, password, ID);
	puts("ע��ɹ���");
	//�û�������1
	++user_amount;
	system("cls");
}

void userLogin()  //�û���¼
{
	char name[30];
	puts("�������û���");
	scanf("%s", name);
	User* account;
	//�����û�,����Ϊ��˵���û�������
	while (account = serchUsername(name), account == NULL)
	{
		system("cls");
		puts("���û��������ڣ���ע������µ�½�˺ţ�\n");
		system("pause");
		return ;

	}

	puts("�����������˺�����");
	scanf("%s", name);

	if (strcmp(account->password, name))
	{
		puts("�������,�����µ�½��\n");
		return ;
	}
    //��¼�ɹ���ת���û��˵�
	puts("��¼�ɹ�!");
	system("cls");
	userMenu(account);
}



void adminLogin()  //����Ա��½
{
	char name[30];
	puts("����������˺�");
	scanf("%s", name);
	User* account;
	while (account = serchUsername(name), account == NULL)
	{
		system("cls");
		puts("���û���������,�����µ�½�˺ţ�");
        system("pause");
		return ;

	}
    //�ж�Ȩ��
	if (!account->admin)
	{
		system("cls");
		puts("���˺��޹���Ȩ��!");
		system("pause");
		return;
	}

	puts("����������˺ŵ�����");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		system("cls");
		puts("�������,�����µ�½��");
		system("pause");
        return;
	}
	//��¼�ɹ������������
	puts("��¼�ɹ���");
	system("cls");
	adminMenu(account);
}



void creatUserList(char* name, char* password, char* ID)  //�����û�����
{

	User* np = user_head;

	while (np->next)
        np = np->next;

	User* tp = (User*)malloc(sizeof(User));
	strcpy(tp->user_name, name); // ��ֵ
	strcpy(tp->password, password);
	strcpy(tp->ID, ID);
	tp->admin = 0;
	tp->next = NULL;

    //��ʼ���û�
	userIniti(tp);

	np->next = tp;

	save(); //���浽�ļ�
}

void creatBookList(char* title, char* isbn, char* author, char* publisher,char* publishtime,int value, int cnt)  //����ͼ������
{
	Book* np =  book_head;
	while (np->next) np = np->next;
	Book* tb = (Book*)malloc(sizeof(Book));
	strcpy(tb->title, title);
	strcpy(tb->isbn, isbn);
	strcpy(tb->author, author);
	strcpy(tb->publisher, publisher);
	strcpy(tb->publishtime, publishtime);
	tb->value = value;
	tb->cnt = cnt;
	tb->next = NULL;
	np->next = tb;
	save();
}
void userIniti(User* account)  //�û�ͼ������ʼ��
{
	account->user_book.borrow_amount = 0;
	account->user_book.max_amount = 10;
	account->user_book.tax = 1.0;
	memset(account->user_book.borrow_time, 0, sizeof(account->user_book.borrow_time));
	memset(account->user_book.return_time, 0, sizeof(account->user_book.return_time));
	memset(account->user_book.borrowBook, 0, sizeof(account->user_book.borrowBook));
}

void load()  //���ļ��м�������
{
	book_head = (Book*)malloc(sizeof(Book));
	book_head->next = NULL;
	book_amount = 0;

	FILE* fp2;
	fp2 = fopen("book.bin", "rb");
	if (fp2 == NULL)
	{

            puts("���ļ�ʧ��!");
            fclose(fp2);
            return ;

	}
	else
	{
		Book* bp =  book_head;
		Book* tp = (Book*)malloc(sizeof(Book));
		while (fread(tp, sizeof(Book), 1, fp2))
		{
			bp->next = tp;
			++book_amount;
			tp = tp->next;
			tp = (Book*)malloc(sizeof(Book));
			bp = bp->next;
		}
		fclose(fp2);
	}

	user_head = (User*)malloc(sizeof(User));
	user_head->next = NULL;
	user_amount = 0;

	FILE* fp1;
	fp1 = fopen("user.bin", "rb");
	if (fp1 == NULL)
	{
		adminIniti(); return;
	}
	User* np =  user_head;
	User* temp = (User*)malloc(sizeof(User));

	while (fread(temp, sizeof(User), 1, fp1))
	{
		np->next = temp;
		++user_amount;
		temp = temp->next;
		temp = (User*)malloc(sizeof(User));
		np = np->next;
	}
	g_UserAdmin = user_head->next;
	fclose(fp1);
}

void save()  //�������ݵ��ļ�
{
	FILE* fp = fopen("user.bin", "wb");
	User* temp = user_head->next;
	while (temp)
	{
		fwrite(temp, sizeof(User), 1, fp);
		temp = temp->next;
	}
	fclose(fp);

	fp = fopen("book.bin", "wb");
	Book* tb = book_head->next;
	while (tb)
	{
		fwrite(tb, sizeof(Book), 1, fp);
		tb = tb->next;
	}
	fclose(fp);
}

void userMenu(User* account)  //�û��˵�
{
	while (1)
	{

      printf("        ��ӭ�û�%12s��¼!\n", account->user_name);
		puts("+-----------------------------------------------+");
		puts("|                [1] ͼ�����                   |");
		puts("|                [2] ͼ�����                   |");
		puts("|                [3] ��ʷ����                   |");
		puts("|                [4] ���Ĺ���                   |");
		puts("|                [5] �������                   |");
		puts("|                [6] �޸��˺�                   |");
		puts("|                [7] ɾ���˺�                   |");
		puts("|                [0] �˳���½                   |");
		puts("+-----------------------------------------------+");
		 puts("�������ֺ�س���");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: browseBook(); system("pause"); system("cls"); break;
		case 2: searchBook(); system("pause"); system("cls"); break;
		case 3: history(account); system("pause"); system("cls"); break;
		case 4: borrowBook(account); break;
		case 5: returnBook(account); break;
		case 6: userChange(account);  break;
		case 7: if (deleteUser(account))
		{
			printf("���˺��ѱ�ɾ��,�����µ�½��\n");
			system("cls");
			return; //���ص����˵�
		}
		else break;
		case 0: printf("�˺ŵǳ��ɹ�!\n");
		system("cls"); return;
		default: printf("ָ�����,���������룡\n");
		system("cls"); break;
		}
	}
}

void userChange(User* account)  //�����û���Ϣ
{
	printf("���޸��û���%s\t �����ڿ��Ը������ĸ�����Ϣ!\n", account->user_name);
	char Name[30];
	printf("�������µ��û���(������25����ĸ)��\n");
	scanf("%s", Name);
	strcpy(account->user_name, Name);
	printf("������������������(������25����ĸ)��\n");
	char password[30];
	scanf("%s", password);
	strcpy(account->password, password);
	printf("�û�%s\t�˺��������޸ģ�\n", account->user_name);
	printf("����������������Ч֤������(������25����ĸ)��\n");
	char ID[30];
	scanf("%s", ID);
	strcpy(account->ID, ID);
	printf("�û�%s\t��Ч֤���������޸ģ�\n", account->user_name);
	save();
	printf("�û�%s\t������Ϣ�޸ĳɹ������ڷ�����һ����...\n", account->user_name);
	system("cls");
}

int deleteUser(User* account)  //ɾ���˺�
{
	if (!strcmp(account->user_name, g_UserAdmin->user_name))
	{
		printf("�û�%sӵ�����Ȩ�ޣ�ɾ��ʧ��\n", g_UserAdmin->user_name);
		system("cls"); return 0;
	}
	printf("�Ƿ���Ҫɾ���˺�%s��\n", account->user_name);
	puts("[1] ��");
	puts("[0] ��");
	puts("�������ֺ�س���");
	int op;  scanf("%d", &op);
	if (op == 1)
	{
		if (account->user_book.borrow_amount)
		{
			printf("ɾ��ʧ�ܣ����û���%d��ͼ��δ�黹�����ȹ黹������ͼ�飡\n", account->user_book.borrow_amount);
		}
		else
		{
			User* tp = (User*)malloc(sizeof(User));
			tp = user_head;
			User* np = (User*)malloc(sizeof(User));
			np = user_head->next;
			while (np)
			{
				if (!strcmp(np->user_name, account->user_name))
				{
					tp->next = np->next;
					free(np); --user_amount;
					save();
					printf("�˺���ɾ���ɹ���\n");
					system("pause"); system("cls");
					return 1;
				}
				tp = np;
				np = np->next;
			}
		}
	}
	else if (!op) printf("��ȡ�����β�����\n");
	else printf("����ѡ��������������룡���ڷ�����һ��...\n");
	system("pause"); system("cls"); return 0;
}

void borrowBook(User* account)  //���Ĺ���
{
	printf("�û�%s:������������Ч���֤������\n", account->user_name);
	char ID[30]; scanf("%s", ID); system("cls");
	while (strcmp(account->ID, ID))
	{
		system("cls");
		puts("���֤�����벻ƥ��,���������룡");
		scanf("%s", ID);
	}
	while (1)
	{
		int ans = account->user_book.borrow_amount, Max = account->user_book.max_amount;
		if (ans == Max)
		{
			printf("�û�%s:����ͼ������ %d �����Ѵ����� %d �������ȹ黹����ͼ�飡\n", account->user_name, ans, Max);
			system("pause"); system("cls"); return;
		}
		browseBook();
		puts("��������ĵ��鼮���(���� 0 �˳�)");
		int cnt; scanf("%d", &cnt);
		if (cnt == 0)
		{
			puts("�˳��ɹ���"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt < 0)
		{
			puts("�������!");
		}
		else
		{
			puts("��������ĵ�ʱ��(����ʱ�䲻�ܴ��ڵ���180)");
			int day; scanf("%d", &day);
			if (day > 180 || day <= 0)
				puts("����ʱ�����!");
			else
			{
				Book* tb = (Book*)malloc(sizeof(Book));
				tb = book_head->next;
				for (int i = 1; i < cnt; ++i)
					tb = tb->next;
				tb->cnt--;
				account->user_book.borrowBook[ans] = *tb;
				account->user_book.borrow_time[ans] = time(NULL);
				account->user_book.return_time[ans] = time(NULL) + day * 3600 * 24;
				++account->user_book.borrow_amount;
				save();
				printf("�û�%s:����ͼ�顶%s���ɹ���\n", account->user_name, tb->title);
			}
		}
		system("pause"); system("cls");
	}
}

void returnBook(User * account)  //�������
{

	while (1)
	{
		history(account);
		if (!account->user_book.borrow_amount)
		{
			system("pause"); system("cls"); return;
		}
		printf("����������Ҫ�黹���鼮��ţ�����-1���˳�����ϵͳ����\n");
		int cnt = 0; scanf("%d", &cnt); system("cls");
		if (cnt == -1)
		{
			printf("�����˳�����ϵͳ�����Ժ�...\n");
			system("pause"); system("cls"); return;
		}
		if (cnt > account->user_book.borrow_amount || cnt < 0)
		{
			printf("����ȷ���������鼮��ţ�\n");
		}
		else
		{
			int i = 0;
			for (--cnt; i < cnt; ++i);
			Book* tb = (Book*)malloc(sizeof(Book));
				tb = book_head->next;
				for (int i = 1; i < cnt; ++i)
					tb = tb->next;
			tb->cnt++;
			char title[100];
			strcpy(title, account->user_book.borrowBook[i].title);
			time_t t = time(NULL);
			printf("*************************************************\n");
			printf("�涨����ʱ��:%s", ctime(&account->user_book.return_time[i]));
			printf("��ǰʱ��:%s", ctime(&t));
			t -= account->user_book.return_time[i];


			if (t > 0)
			{
				double cost = t / 3600.0 / 24 * account->user_book.tax;
				printf("������δ��ָ�������ڹ黹��%s��,����Ҫ֧��ΥԼ��%.2lfԪ\n", title, cost);
			}
			else printf("�鼮��%s������δ����ʱ�䣬����֧��ΥԼ��\n", title);


			for (; i < account->user_book.borrow_amount; ++i)
			{
				account->user_book.borrowBook[i] = account->user_book.borrowBook[i + 1];
				account->user_book.borrow_time[i] = account->user_book.borrow_time[i + 1];
				account->user_book.return_time[i] = account->user_book.return_time[i + 1];
			}
			--account->user_book.borrow_amount;
			save();
			printf("�鼮��%s���黹�ɹ���\n", title);
		}
		system("pause"); system("cls");
	}
}

void history(User * account)  //��ʷ�������
{
	int n = account->user_book.borrow_amount;
	puts("############################################################");
	printf("�û�%s:\n", account->user_name);
	if (!n)
	{
		puts("�����鼮�ڽ��ļ�¼��"); return;
	}
	puts("�����鼮���");
	for (int i = 0; i < n; ++i)
	{
		struct node t = account->user_book;
		time_t nt = time(NULL) - t.return_time[i];
		double cost = 0.0;
		if (nt > 0) cost = t.tax * (nt / 3600.0 / 24);
		printf("[%d]\n", i + 1);
		printf("����:��%s��\n", t.borrowBook[i].title);
		printf("��������:%s", ctime(&t.borrow_time[i]));
		printf("�涨��������:%s", ctime(&t.return_time[i]));
		if (nt > 0) printf("�Ƿ�ʱ:��\n");
		else printf("  �Ƿ�ʱ:��\n");
		printf("���ķ���:%.2lf\n", cost);
	}
}

void adminIniti()  //��������Ա�˺ų�ʼ��
{
	FILE* fp = fopen("user.bin", "wb");
	if (fp == NULL)
	{
		printf("����ԱȨ�޳�ʼ��ʧ�ܣ�\n"); exit(0);
	}
	g_UserAdmin = (User*)malloc(sizeof(User));
	strcpy(g_UserAdmin->user_name, "admin");
	strcpy(g_UserAdmin->password, "admin");
	strcpy(g_UserAdmin->ID, "1999");
	g_UserAdmin->admin = 1;
	g_UserAdmin->next = NULL;
	userIniti(g_UserAdmin);
	user_head->next = g_UserAdmin;
	user_amount = 1;
	save();
	fclose(fp);
}

User* serchUsername(char* name)  //�����û���
{
	User* np = user_head->next;
	while (np)
	{
		if (!strcmp(np->user_name, name)) return np;
		np = np->next;
	}
	return NULL;
}

void adminMenu(User * account)  //����Ա�˵�
{
	while (1)
	{

       printf("        ��ӭ����Ա%12s��¼\n", account->user_name);
        puts("+-----------------------------------------------+");
		puts("|                [1] ����ͼ��                   |");
		puts("|                [2] �޸�ͼ��                   |");
		puts("|                [3] ɾ��ͼ��                   |");
		puts("|                [4] ͼ�����                   |");
		puts("|                [5] ͼ�����                   |");
		puts("|                [6] �����û�                   |");
		puts("|                [0] �˳���½                   |");
        puts("+-----------------------------------------------+");
        puts("�������ֺ�س���");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: addBook(); break;
		case 2: changeBook(); break;
		case 3: deleteBook(); break;
		case 4: browseBook(); system("pause"); system("cls"); break;
		case 5: searchBook(); break;
		case 6: adminUser(); break;
		case 0: printf("�˳��ɹ�!\n"); system("pause"); system("cls"); return;
		default: printf("ָ�����,���������룡\n"); system("pause"); system("cls"); break;
		}
	}
}

void queryUser()  //�û���Ϣ��ѯ
{
	int cnt = 1;
	User* np = (User*)malloc(sizeof(User));
	np = user_head->next;
	printf("|���\t\t|�˺�\t\t       |����\t\t      |֤������\t\t\t |�Ƿ����Ա|\n");
	puts("|---------------------------------------------------------------------------------------------------|");
	while (np)
	{
		printf("|%d\t\t|%-22s|%-22s|%-26s|", cnt, np->user_name, np->password, np->ID);
		if (np->admin) puts(" ��       |");
		else puts(" ��       |");
		np = np->next;
		++cnt;

	}
	puts("+---------------------------------------------------------------------------------------------------+");
}

void adminUser()  //�����û���Ϣ
{
	while (1)
	{
		puts("+-----------------------------------------------+");
		puts("|                  �������                     |");
		puts("|-----------------------------------------------|");
		puts("|            [1] �鿴�û�������Ϣ               |");
		puts("|            [2] �޸��û�������Ϣ               |");
		puts("|            [3] ɾ���û��˺�                   |");
		puts("|            [4] �鿴�û�ͼ����Ĺ黹���       |");
		puts("|            [5] ���ù���ԱȨ��                 |");
		puts("|            [0] �����ܹ������                 |");
		puts("+-----------------------------------------------+");
		User* np = (User*)malloc(sizeof(User));
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: queryUser(); system("pause"); system("cls"); break;
		case 2: if (np = serchUserByOrder(), np != NULL) userChange(np);
				else
		{
			system("cls");
		}
				break;
		case 3:if (np = serchUserByOrder(), np != NULL)
		{
			int admin = np->admin;
			if (deleteUser(np) && admin)
				puts("���˺��ѱ�ɾ��,�����µ�½!");
			system("pause"); system("cls");
			return;
		}
			   else
		{
			system("pause"); system("cls");
		}
			   break;
		case 4: allHistory(); break;
		case 5: if (np = serchUserByOrder(), np != NULL) setAdmin(np);
				else
		{
			system("cls");
		}
				break;
		case 0: puts("�˳��ɹ�!"); system("pause"); system("cls"); return;
		default: puts("ָ��������������룡"); system("pause"); system("cls"); break;
		}
	}
}

void allHistory() //�鿴�û�ͼ����Ĺ黹���
{
	while (1)
	{
	    puts("+---------------------------------------------------------------------------------------------------+");
        puts("|                                      ͼ����Ĺ黹��ѯϵͳ                                         |");
		puts("+---------------------------------------------------------------------------------------------------+");
		User* account  = serchUserByOrder();
		if (account)
		{
			history(account);
			puts("���ĳɹ�!");
			system("pause"); system("cls"); return;
		}
		system("cls");
	}
}




User* serchUserByOrder()  //����������û�
{
	queryUser();
	puts("��������������û����");
	int cnt; scanf("%d", &cnt); system("cls");
	if (cnt > user_amount || cnt <= 0)
		puts("�������!");
	else
	{
		User* tb =  user_head->next;
		for (int i = 1; i < cnt; ++i)
			tb = tb->next;
		return tb;
	}
	return NULL;
}

void setAdmin(User * account)  //���ù���Ա
{

	if (!strcmp(account->user_name, g_UserAdmin->user_name))
	{
		printf("�û�%sӵ����߹���Ȩ��,�޸�ʧ��!", g_UserAdmin->user_name);
		system("cls"); return;
	}
	printf("�Ƿ�ȷ�Ͻ��û�%s����Ϊ����Ա��\n", account->user_name);

	puts("[0] ȡ������ԱȨ��");
	puts("[1] ����Ϊ����Ա");
    puts("�������ֺ�س���");

	int op; scanf("%d", &op);
	if (op == 1)
	{
		account->admin = op;
		printf("�û�%s\t����ԱȨ�����óɹ���\n", account->user_name);
	}
	else if (op == 0)
	{
		account->admin = op;
		printf("�û�%s\t����ԱȨ���ѱ�ȡ����\n", account->user_name);
	}
	else
	{
		puts("����ʧ��,�밴Ҫ������");
	}

	save();
	system("cls");
}


void addBook()  //����ͼ����Ϣ
{
	char title[100], isbn[100], author[100], publisher[100], publishtime[100];
	int value,cnt;
	puts("��������Ҫ��ӵ��鼮����");
	scanf("%s", title);
	puts("��������Ҫ��ӵ��鼮���");
	scanf("%s", isbn);
	puts("��������Ҫ��ӵ��鼮����");
	scanf("%s", author);
	puts("��������Ҫ��ӵ��������");
	scanf("%s", publisher);
	puts("��������Ҫ��ӵ����������");
	scanf("%s", publishtime);
	puts("��������Ҫ��ӵ�ͼ�鵥��");
	scanf("%d", &value);
	puts("��������Ҫ��ӵ��鼮����");
	scanf("%d", &cnt);
	++book_amount;
	creatBookList(title, isbn, author, publisher, publishtime, value, cnt);
	printf("����鼮��%s���ɹ�", title);
	system("pause"); system("cls");
}
void changeBook()  //�޸�ͼ����Ϣ
{
	while(1)
	{
		browseBook();
		puts("��������޸ĵ��鼮���(����0�˳�)");
		int cnt; scanf("%d", &cnt);
		if (cnt == 0)
		{
			puts("�˳��ɹ���"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt < 0)
		{
			puts("�������!");
		}
		else
		{
			Book* tb = (Book*)malloc(sizeof(Book));
			tb = book_head->next;
			int dd=1;
			while (tb)
			{
				if(dd==cnt)
				{
					char title[100], isbn[100], author[100], publisher[100],publishtime[100];
					int value,cnt;
					puts("�������޸ĺ���鼮����");
					scanf("%s", title);
					puts("�������޸ĺ�ļ����");
					scanf("%s", isbn);
					puts("�������޸ĺ���鼮����");
					scanf("%s", author);
					puts("�������޸ĺ�ĳ�����");
					scanf("%s", publisher);
					puts("�������޸ĺ�ĳ�������");
					scanf("%s", publishtime);
					puts("�������޸ĺ��ͼ�鵥��");
					scanf("%d", &value);
					puts("�������޸ĺ���鼮����");
					scanf("%d", &cnt);
					strcpy(tb->title,title);
					strcpy(tb->isbn,isbn);
					strcpy(tb->author,author);
					strcpy(tb->publisher,publisher);
					strcpy(tb->publishtime,publishtime);
					tb->value=value;
					tb->cnt=cnt;
					break;
				}
				tb = tb->next; ++dd;
			}
		}
		system("pause"); system("cls");
	}
}
void deleteBook()  //ɾ��ͼ����Ϣ
{
	while (1)
	{
		browseBook();
		printf("�������ɾ�����鼮���(����0�˳�)\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == 0)
		{
			puts("�˳��ɹ�!"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt < 0)
		{
			puts("�������!");
		}
		else
		{
			Book* tb = book_head;
			Book* np =  book_head->next;
			for (int i = 1; i < cnt; ++i)
			{
				np = tb;
				tb = tb->next;
			}
			np->next = tb->next;
			free(tb);
			--book_amount; //������1
			save();
			puts("ɾ���ɹ���");
		}
		system("pause"); system("cls");
	}
}

void browseBook()  //ͼ�����
{
	int cnt = 1;
	if (!book_amount)
	{
		printf("����ͼ������!\n");
		return;
	}
	Book* tb = book_head->next;
	puts("ͼ����������");
 	puts("+--------------------------------------------------------------------------------+");
    puts("|���|    ����    |    ���    |    ����    |   ������   |   ��������  |����|����|");
    puts("+--------------------------------------------------------------------------------+");
	while (tb)
	{
		printf("|%4d|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", cnt, tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		tb = tb->next; ++cnt;
	}
}
void searchBook()//ͼ�����
{   while(1)
	{
        puts("+-------------------------------------+");
        puts("|               ����ͼ��              |");
        puts("|-------------------------------------|");
		puts("|          [1] ����������             |");
		puts("|          [2] �����߲���             |");
		puts("|          [3] ����Ų���             |");
		puts("|          [4] �����������           |");
		puts("|          [0] ���ػ�ӭҳ��           |");
		puts("+-------------------------------------+");
        puts("�������ֺ�س���");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
			case 1: searchTitle(); system("pause"); system("cls"); break;
			case 2: searchAuthor(); system("pause"); system("cls"); break;
			case 3: searchIsbn();  system("pause"); system("cls"); break;
			case 4: searchPublisher(); system("pause"); system("cls"); break;
			case 0: system("pause"); system("cls"); return ;
			default: printf("�����ָ����������룡\n");
			system("cls"); break;
		}
	}
}
void searchTitle()   //����������
{

	Book* tb = book_head->next;
	puts("�������������");
	char name[100];
	scanf("%s",name);
    puts("+--------------------------------------------------------------------------+");
    puts("|    ����    |    ���    |    ����    |   ������   |  ��������  |����|����|");
    puts("+--------------------------------------------------------------------------+");
	while (tb)
	{
		if(strcmp(tb->title,name)==0)
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}

		tb = tb->next;
	}
}
void searchAuthor()       // �����߲���
{
	Book* tb = book_head->next;
	puts("������ͼ������");
	char name[100];
	scanf("%s",name);
    puts("+--------------------------------------------------------------------------+");
    puts("|    ����    |    ���    |    ����    |   ������   |  ��������  |����|����|");
    puts("+--------------------------------------------------------------------------+");
	while (tb)
	{
		if(strcmp(tb->author,name)==0)
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}
		tb = tb->next;
	}

}
void searchIsbn()         //����Ų���
{
	Book* tb = book_head->next;
	puts("������������");
	char name[100];
	scanf("%s",name);
    puts("+--------------------------------------------------------------------------+");
    puts("|    ����    |    ���    |    ����    |   ������   |  ��������  |����|����|");
    puts("+--------------------------------------------------------------------------+");
	while (tb)
	{
		if(strcmp(tb->isbn,name)==0)
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}
		tb = tb->next;
	}
}
void searchPublisher()     //�����������
{
	Book* tb =  book_head->next; //��Ԫ���
	puts("���������������");
	char name[100];
	scanf("%s",name);
	puts("+--------------------------------------------------------------------------+");
    puts("|    ����    |    ���    |    ����    |   ������   |  ��������  |����|����|");
    puts("+--------------------------------------------------------------------------+");


	while (tb)
	{
		if(strcmp(tb->publisher,name)==0) //�Ƚϳ�����
		{
			printf("|%12s|%12s|%12s|%12s|%12s|%4d|%4d|\n", tb->title, tb->isbn,
			tb->author, tb->publisher,tb->publishtime,tb->value, tb->cnt);
		}

		tb = tb->next;
	}
}

