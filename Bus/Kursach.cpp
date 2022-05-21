#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <locale.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <wincon.h>
#include"Header.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

const int MAX_SIZE = 20;
//char time = '30.05.2022';

struct Admin
{
	char login[MAX_SIZE];			//�����
	char password[MAX_SIZE];     //������
};

struct User
{
	char login[MAX_SIZE];			//�����
	char password[MAX_SIZE];     //������
};

struct Product
{
	char FIO[MAX_SIZE]; //������� ��� ��������
	char telephone[13]; //��� ������
	char name[MAX_SIZE];// �������� ��������
	char timeaccept[10];//����� ������
	char timeissue[10]; //����� ������
	float byn_price; //����
	char ready[1]; // ���������� 	

};

/*������� ��������� ������������ ������*/

Admin* adm = (Admin*)malloc(sizeof(Admin) * 2);
User* user = (User*)malloc(sizeof(User) * 10);
Product* prod = (Product*)malloc(sizeof(Product) * 10);

FILE* A;
FILE* U;
FILE* Orders;
FILE* Products;

/*������� ������ �� �����������*/

int sch = 0;
int count_of_enter_new = 0;
int a = 0;
int ver = 0;

static Product buf;
static Product tmp;
static User tmp1;
int lines_count = 0;
int lines_count2 = 0;

/*������, ��������� ��������� �� �����*/

void starline()
{
	printf("**************************************************************\n");
}

/*�������, ������� ������������ ���������� ����� � ����� � �������� � ��������*/

void file_s4et4ik_l()
{
	lines_count = 0;
	fopen_s(&U, "logusers.txt", "r");
	while (!feof(U))
	{
		if (fgetc(U) == '\n')
			lines_count++;
	}
	//lines_count++;
	fclose(U);
}

/*�������, ������� ������������ ���������� ����� � ����� � "�������" ����������*/

void file_s4et4ik_Bus2()
{
	lines_count2 = 0;
	fopen_s(&Products, "Products.txt", "r");
	if (Products == NULL) { printf("�� ������� ������� ����\n"); return; }
		while (!feof(Products))
	{
		if (fgetc(Products) == '\n')
			lines_count2++;
	}
	//lines_count2++;
	fclose(Products);
}

/*������� �������*/

int schu;

/*������� ��������*/

int check_price(float t)
{
	int y = (int)t;
	if (y >= 0) {
		t -= y;
		if (t >= 0 && t <= 0.99) return 1;
	}
	return 0;
}

int check_menu(int counter) {
	int n;
	while (1) {
		cin >> n;
		if (cin.fail() || cin.peek() != '\n' || n < 1 || n > counter) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "������������ ������. ����������, ���������� ��� ���.\n��� �����: ";
		}
		else
			return n;
	}
}
float check_for_price() 
{
	float n;
	while (1) 
	{
		scanf_s("%f", &n);
		if (cin.fail() || cin.peek() != '\n' || check_price(n) == 0) 
		{			
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "������������ ����. ����������, ���������� ��� ���.\n����� ����: ";
		}
		else
			return n;
	}
}
void check_for_string(char* str)
{
	char string[MAX_SIZE];
	int counter = 0;
	int flag;
	while (1)
	{
		flag = 0;
		gets_s(string);
		
		for (int i = 0; i < strlen(string); i++)
		{
			if (string[i] < 97 || string[i]>122)
			{
				cin.clear();
				flag = 1;
				cout << "������������ ����. ����������, ���������� ��� ���.\n��������� ������ ��������� ����� ������� ��������\n���������� �����: "; break;
			}
		}
		if (flag == 0) { strcpy(str, string); break; }
	}
}

void check_for_ready(char* str)
{
	cout << "+ ���� �����, - ���� �� �����";
	char ready[1];
	int counter = 0;
	int flag;
	while (1)
	{
		
		flag = 0;
		gets_s(ready);
			if (ready[0] != 43 || ready[0] != 45)
			{
				cin.clear();
				flag = 1;
				cout << "������������ ����. ����������, ���������� ��� ���.\n+ ���� �����, - ���� �� �����\n���������� �����: "; break;
			}
		if (flag == 0) { strcpy(str, ready); break; }
	}
}

void check_for_date(char* str)
{
	cout << "������� ���� � ������� DD.MM.YYYY ";
	char date[11];
	int counter = 0;
	int flag;
	int i;
	while (1)
	{
		flag = 0;
		gets_s(date);
			for (i = 0; i < strlen(date); i++)
			{
				if (i == 2 || i == 5) i++;
				if (date[i] < 48 || date[i] > 57)
				{
					cin.clear();
					flag = 1;
					cout << "������������ ����. ����������, ���������� ��� ���.\n������� ���� � ������� DD.MM.YYYY\n���������� �����: "; break;
				}
			}
			if (date[0] > 51 || date[3] > 49 || (date[4] > 50 && date[3] == 49))
				{
					cin.clear();
					flag = 1;
					cout << "������������ ����. ����������, ���������� ��� ���.\n������� ���� � ������� DD.MM.YYYY\n���������� �����: "; break;
				}
			if ((date[3] == 48 && date[4] == 50) && date[0] > 50)
				{
					cin.clear();
					flag = 1;
					cout << "������������ ����. ����������, ���������� ��� ���.\n������� ���� � ������� DD.MM.YYYY�\n���������� �����: "; break;
				}
			if (flag == 0) { strcpy(str, date); break; }
	}
}

void check_for_telephone(char* str)
{
	cout << "������� ����� �������� +375........... ";
	char number[14];
	int counter = 0;
	int flag;
	int i;
	while (1)
	{
		flag = 0;
		gets_s(number);
		if (number[0] != '+')
		{
			cin.clear();
			flag = 1;
			cout << "������� ����� �������� +375........... "; break;
		}
		for (i = 1; i < strlen(number); i++)
		{
			if (number[i] < '0' || number[i] > '9')
			{
				cin.clear();
				flag = 1;
				cout << "������� ����� �������� +375........... "; break;
			}
		}
		if (flag == 0) { strcpy(str, number); break; }
	}
}


/*���� ������ ������������*/



int user_menu()
{
	system("cls");
	int choise;
	printf("1) �������� ������\n");
	printf("2) ����� �� ����������\n");
	printf("3) ����� �� ���������\n");
	printf("4) ����������\n");
	printf("4) �������� ����\n");
	printf("6) ����� �� ���������\n");
	printf("7) ������� � ������� ��������\n");
	printf("��� �����: ");
	choise = check_menu(7);
	starline();
	return choise;
}

/*���� ������ ��������������*/

int admin_menu()
{
	system("cls");
	int choise;
	printf("1) ���� ������\n");
	printf("2) ����� ������\n");
	printf("3) ��������\n");
	printf("4) ����������\n");
	printf("5) ��������������\n");
	printf("6) �����\n");
	printf("7) ���������� c ������ ���������\n");
	printf("8) ���������� ������� �������\n");
	printf("9) ����� ������� �������\n");
	printf("10) �������������� ������� �������\n");
	printf("11) �������� ������� �������\n");
	printf("12) ������� � ������� ��������\n");
	printf("13) �������� ����\n");
	printf("14) �������\n");
	printf("15) ����� �� ���������\n");
	printf("��� �����: ");
	choise = check_menu(15);
	starline();
	system("cls");
	return choise;
}

/*����������, ����������� ��� �������, ��� ������� ����� ����������� ������*/

int help = 0;
int help1 = 0;

/*������� �����������*/

void verification()
{
	a = 0;

	system("cls");
	char p = '\0';
	fopen_s(&A, "logpass.txt", "r");
	fscanf(A, "%s", adm[0].login);
	fscanf(A, "%s", adm[0].password);

	fopen_s(&U, "logusers.txt", "r");
	for (int i = 0; i < schu; i++)
	{
		fscanf(U, "%s", user[i].login);
		fscanf(U, "%s", user[i].password);
	}
	fflush(stdin);
	while (a != 1 || a != 2)
	{
		if (ver == 0)
		{ 
		printf("������� Enter 3 ����, ��� ������ ����������� ");
		ver++;
		if (help == 1) getchar();
		gets_s(adm[1].login);
		int strlen = 0;
		int n = 0;
		while ((adm[1].password[n] = getch()) != '\r' && (n = n + 1))
		{
			printf("%c", '*');
			strlen++;
		}
		adm[1].password[strlen] = '\0';

		for (int i = 0; i < schu; i++)
		{
			if (strcmp(user[i].login, adm[1].login) == 0 && strcmp(user[i].password, adm[1].password) == 0)
			{
				help = 1;
				printf("���� �����������!\n");
				a = 2;
				break;
				break;
			}
		}
		if (strcmp(adm[0].login, adm[1].login) == 0 && strcmp(adm[0].password, adm[1].password) == 0)
		{
			help = 1;
			printf("���� �����������!\n");
			a = 1;
			break;
		}

		else if (a == 0)
		{
			help = 0;
			while (p != 13 && p != 27)
				p = _getch();
			switch (p)
			{
			case 13:p = '\0'; system("cls"); continue; break;
			case 27:fclose(A); return;
				continue;
			}
		}
		break;
		}
		else if (ver == 1)
		{
			if (help == 1) getchar();
		printf("������� �����: ");
		gets_s(adm[1].login);
		int strlen = 0;
		int n = 0;
		printf("������� ������: ");
		while ((adm[1].password[n] = getch()) != '\r' && (n = n + 1))
		{
			printf("%c", '*');
			strlen++;
		}
		adm[1].password[strlen] = '\0';
		system("CLS");

		for (int i = 0; i < schu; i++)
		{
			if (strcmp(user[i].login, adm[1].login) == 0 && strcmp(user[i].password, adm[1].password) == 0)
			{
				help = 1;
				printf("���� �����������!\n");
				a = 2;
				break;
				break;
			}
		}
		if (strcmp(adm[0].login, adm[1].login) == 0 && strcmp(adm[0].password, adm[1].password) == 0)
		{
			help = 1;
			printf("���� �����������!\n");
			a = 1;
			break;
		}

		else if (a == 0)
		{
			printf("\n�������� ����� ��� ������!\n");
			printf("\n1.������� Enter ����� ��������� ���� ��� Esc ����� ����� . . .\n");
			help = 0;
			while (p != 13 && p != 27)
				p = _getch();
			switch (p)
			{
			case 13:p = '\0'; system("cls"); continue; break;
			case 27:fclose(A); return;
				continue;
			}
		}
		break;	
		}
	}
	fclose(A);
	fclose(U);
}

/*������� ���������� ������� � ������� � ����*/

void file_l()
{
	fopen_s(&U, "logusers.txt", "w+t");
	for (int i = 0; i < schu; i++)
	{
		fprintf(U, "%s\n", user[i].login);
		fprintf(U, "%s\n", user[i].password);
	}
	fclose(U);
}

/*������� ���������� ������ ������������*/

void add_l()
{
	int flag = 0;
	int help3 = 0;
	if ((schu + 1) <= 10)
	{
		printf("������ %d\n", schu + 1);
		while (flag == 0)
		{
			int proverka = 0;
			printf("������� �����: ");
			if (help3 == 0)
			{
				gets_s(user[schu].login);
				gets_s(user[schu].login);
			}
			else gets_s(user[schu].login);
			printf("������� ������: ");
			gets_s(user[schu].password);

			for (int i = 0; i < schu; i++)
			{
				if (strcmp(user[i].login, user[schu].login) == 0)
				{
					printf("���� ����� ��� �����!\n������� ������ �����!\n\n"); proverka = 1; help3 = 1; break;
				}
			}
			if (proverka == 1) continue;
			else flag = 1;

			fflush(stdin);
			schu++;
			file_l();
			system("cls");
			printf("���������� ��������� �������!\n");
		}
	}
	else printf("������ �������� ��� �������\n");
}

/*������� ������ ������ ������������� � ��������� ����*/

void printf_table_l(struct User* array, int len)
{
	int i;
	if (schu == 0) printf("��� �������\n");

	printf("***********************************************\n");						
	for (i = 0; i < len; i++) {
		printf("* %-20s : %-20s *\n", "Login" ,user[i].login);
		printf("* %-20s : %-20s *\n", "Password", user[i].password);
		printf("* %-20s : %-20s *\n", "********************", "********************");
	}
	printf("______________________________________________\n");
}

/*������� ��������� ������ ������������*/

void change_log()
{
	int d;
	if (schu == 0) printf("��� �������\n");
	else
	{
		printf("������� ����� ������� ������ ��� ���������: ");
		d = check_menu(schu);
		system("cls");

		printf("������� ����� ������� ������: ");
		gets_s(user[d - 1].login);
		gets_s(user[d - 1].login);
		fflush(stdin);

		printf("������� ������: ");
		gets_s(user[d - 1].password);
		fflush(stdin);
		file_l();
		starline();
	}
}

/*������� �������� ������������*/

void del_log()
{
	int d, choise,res;
	if (schu == 0) printf("��� �������\n");
	else
	{
		printf("1) ������� ����������� ������\n");
		printf("2) ������� ��� ������\n");
		printf("3) �����\n");
		choise = check_menu(3);

		starline();

		if (choise == 1)
		{
			system("cls");
			printf("������� ����� ������ ��� ��������: ");
			d = check_menu(schu);
			printf("�� ����� ������ �������?\n");
			printf("1)��\n2)���\n");
			printf("��� �����: ");
			res = check_menu(2);
			system("cls");
			if (res == 1)
			{
				if (d <= 0 || d > schu)
				{
					printf("����� ������ �� ����������\n");
					return;
				}

				for (int i = (d - 1); i < schu; i++)
				{
					user[i] = user[i + 1];
				}
				schu--;
				file_l();
				puts("������ �������");
				starline();
			}
		}

		else if (choise == 2)
		{
			printf("�� ����� ������ �������?\n");
			printf("1)��\n2)���\n");
			printf("��� �����: ");
			res = check_menu(2);
			if (res == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					user[i] = tmp1;
				}
				schu = 0;
				file_l();
				puts("������ �������");
				puts("________________________________");
			}
		}

		else if (choise == 3)
		{
			return;
		}
		else
		{
			printf("�������� ��������\n");
		}
	}
}

/*������� ������ � ���� ��� ������������ � � ���� � "�������" ����������*/

void file_b()
{
	Orders = fopen("Orders.txt", "w+t");
	for (int i = 0; i < sch; i++)
	{
		fprintf(Orders, "������ %d:\n", i + 1);
		fprintf(Orders, "���:");
		fprintf(Orders, "%s\n", prod[i].FIO);
		fprintf(Orders, "�������:");
		fprintf(Orders, "%s\n", prod[i].telephone);
		fprintf(Orders, "��������:");
		fprintf(Orders, "%s\n", prod[i].name);
		fprintf(Orders, "����� ��������:");
		fprintf(Orders, "%s\n", prod[i].timeaccept);
		fprintf(Orders, "����� ������:");
		fprintf(Orders, "%s\n", prod[i].timeissue);
		fprintf(Orders, "����:");
		fprintf(Orders, "%.2f\n\n", prod[i].byn_price);
		fprintf(Orders, "����������:");
		fprintf(Orders, "%s\n", prod[i].ready);
	}
	fclose(Orders);

	Products = fopen("Products.txt", "w+t");
	for (int i = 0; i < sch; i++)
	{
		fprintf(Orders, "%s\n", prod[i].FIO);
		fprintf(Orders, "%s\n", prod[i].telephone);
		fprintf(Orders, "%s\n", prod[i].name);
		fprintf(Orders, "%s\n", prod[i].timeaccept);
		fprintf(Orders, "%s\n", prod[i].timeissue);
		fprintf(Orders, "%.2f\n", prod[i].byn_price);
		fprintf(Orders, "%s\n", prod[i].ready);
	}
	fclose(Products);
}

/*������� ���������� ������ �� �����*/

void file_read_b2()
{

	fopen_s(&Products, "Products.txt", "r");
		for (int i = 0; i < sch; i++)
		{
			fscanf(Products, "%s", prod[i].FIO);
			fscanf(Products, "%s", prod[i].telephone);
			fscanf(Products, "%s\n", prod[i].name);
			fscanf(Products, "%s", &prod[i].timeissue);
			fscanf(Products, "%s\n", &prod[i].timeaccept);
			fscanf(Products, "%f", &prod[i].byn_price);
			fscanf(Products, "%s", prod[i].ready);
	
		}
	fclose(Products);
}

/*������� ������ � ���� ��� ������ ������ ������*/

void file_find(int i, int count)
{
	Orders = fopen("Orders.txt", "a+t");
	
	if (count == 1)
	{
		fprintf(Orders, "������ %d ������������� ����� �� ��������� ���������\n", i + 1);
		fprintf(Orders, "���:");
		fprintf(Orders, "%s\n", prod[i].FIO);
		fprintf(Orders, "�������:");
		fprintf(Orders, "%s\n", prod[i].telephone);
		fprintf(Orders, "��������:");
		fprintf(Orders, "%s\n", prod[i].name);
		fprintf(Orders, "����� �����:");
		fprintf(Orders, "%s\n", prod[i].timeaccept);
		fprintf(Orders, "����� ������:");
		fprintf(Orders, "%s\n", prod[i].timeissue);
		fprintf(Orders, "����:");
		fprintf(Orders, "%.2f\n\n", prod[i].byn_price);
		fprintf(Orders, "����������:");
		fprintf(Orders, "%s\n", prod[i].ready);
	}
	else fprintf(Orders, "������ ������!\n");
	fclose(Orders);
}

/*������� ����� ������*/

void enter_new()
{
	if (sch != 0) count_of_enter_new = 1;
	if (count_of_enter_new != 0) { printf("��� ���������� ����� ������� �������������� ������� �4\n"); return; }
	int n;
	int i = 0;
	printf("������� ���������� �������� �������: ");
	n = check_menu(10);
	if (sch < n)
	{
		while (sch != n)
		{
			starline();
			printf("������ %d\n", sch + 1);

			printf("������� ���: ");
			check_for_string(prod[sch].FIO);
			check_for_string(prod[sch].FIO);
			fflush(stdin);

			printf("������� ����� ��������: ");
			check_for_telephone(prod[sch].telephone);
			fflush(stdin);

			printf("������� �������� ������: ");
			check_for_string(prod[sch].name);
			fflush(stdin);

			printf("������� ���� �����: ");
			check_for_date(prod[sch].timeaccept);

			printf("������� ���� ������: ");
			check_for_date(prod[sch].timeissue);

			printf("������� ����: ");
			prod[sch].byn_price = check_for_price();

			printf("������� ����������: ");
			check_for_ready(prod[sch].ready);
			fflush(stdin);
			
			count_of_enter_new = 1;
			sch++;
			starline();
		}
	}
	else printf("\n������� ������������ ���-�� �������\n");
	system("cls");
}

/*������� ������ ������ � ��������� ����*/

void print_table(struct Product* array, int len) 
{
	printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "���", "�������", "��������", "����� ��������", "����� ������", "����", "����������");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			for (int i = 0; i < len; i++) {
				printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			}
			printf("******************************************************************************************************************************************************************\n");
	system("pause");
}

/*������� �������� ������*/

void del()
{
	int d, choise,res;
	if (sch == 0) printf("��� �������\n");
	else
	{
		printf("1) ������� ����������� ������\n");
		printf("2) ������� ��� ������\n");
		printf("3) �����\n");
		choise = check_menu(3);

		starline();

		if (choise == 1)
		{
			printf("������� ����� ������ ��� ��������: ");
			d = check_menu(sch);
			while (d > sch || d<1)
			{
				printf("����� ������ �� ����������!\n���������� �����!\n����� ������ ��� ��������: ");
				scanf_s("%d", &d);
				if (scanf_s("%d", &d) != 1)
				{
					getchar();
					system("cls");
					cout << "�������� ���\n";
					return;
				}
			}
			system("cls");
			printf("�� ����� ������ �������?\n");
			printf("1)��\n2)���\n");
			printf("��� �����: ");
			res = check_menu(2);
			system("cls");
			if (res == 1)
			{
				if (d <= 0 || d > sch)
				{
					printf("����� ������ �� ����������\n");
					return;
				}

				for (int i = (d - 1); i < sch; i++)
				{
					prod[i] = prod[i + 1];
				}
				sch--;
				puts("������ �������!");
				starline();
			}
		}

		else if (choise == 2)
		{
			printf("�� ����� ������ �������?\n");
			printf("1)��\n2)���\n");
			printf("��� �����: ");
			res = check_menu(2);
			if (res == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					prod[i] = tmp;
				}
				sch = 0;
				puts("������ �������!");
				starline();
			}
		}

		else if (choise == 3)
		{
			return;
		}
		else
		{
			printf("�������� ��������!\n");
		}
	}
}

/*������� �������������� ������*/

void change()
{
	int d;
	if (sch == 0) printf("��� �������\n");
	else
	{
		printf("������� ����� ������ ��� ���������: ");
		d = check_menu(sch);
		system("cls");

		printf("������� ���: ");
		check_for_string(prod[sch].FIO);
		check_for_string(prod[sch].FIO);
		fflush(stdin);

		printf("������� ����� ��������: ");
		check_for_telephone(prod[sch].telephone);
		fflush(stdin);

		printf("������� �������� ������ : ");
		check_for_string(prod[sch].name);
		fflush(stdin);

		printf("������� ���� ����� \n ");
		check_for_date(prod[sch].timeaccept);
		fflush(stdin);

		printf("������� ���� ������ \n");
		check_for_date(prod[sch].timeissue);
		fflush(stdin);

		printf("������� ����: ");
		prod[sch].byn_price = check_for_price();

		printf("������� ����������: ");
		check_for_ready(prod[sch].ready);
		fflush(stdin);

		system("cls");
		printf("�������������� ��������� �������!\n");
	}
}

/*������� ���������� ����� ������*/

void add_more()
{
	int n;
	printf("������� ���������� ������� ��� ����������: ");
	n = check_menu(10);
	if ((sch + n) <= 10)
	{
		for (int i = 0; i < n; i++)
		{
			starline();
			printf("������ %d\n", sch + 1);

			printf("������� ���: ");
			check_for_string(prod[sch].FIO);
			check_for_string(prod[sch].FIO);
			fflush(stdin);

			printf("������� �������: ");
			check_for_telephone(prod[sch].telephone);
			fflush(stdin);

			printf("������� �������� ������: ");
			check_for_string(prod[sch].name);
			fflush(stdin);

			printf("������� ���� �����: ");
			check_for_date(prod[sch].timeaccept);
			fflush(stdin);

			printf("������� ���� ������: ");
			check_for_date(prod[sch].timeissue);
			fflush(stdin);

			printf("������� ����: ");
			prod[sch].byn_price = check_for_price();

			printf("������� ����������: ");
			check_for_ready(prod[sch].ready);
			fflush(stdin);

			sch++;
			starline();
		}
	system("cls");
	printf("���������� ��������� �������\n");
	}
	else printf("���������� �������� ������� �������\n");
}

/*������� ��� ������ �� ���������*/

int menu_find()
{
	setlocale(LC_ALL, "rus");
	int ch;
	printf("�������� �������� ��� ������: \n");
	printf("1) ���\n");
	printf("2) �������\n");
	printf("3) ����������\n");
	printf("4) �����\n");
	ch = check_menu(4);
	starline();
	system("cls");
	return ch;
}
void find_telephone(char* telef)
{
	int count=0;
	for (int i = 0; i < sch; i++)
	{
		if (_stricmp(telef, prod[i].telephone)==0)
		{
			printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "���", "�������", "��������", "����� ��������", "����� ������", "����", "����������");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			printf("******************************************************************************************************************************************************************\n");
			count = 1;
			file_find(i, count);
		}
	}
	
	if (count == 0) printf("�� ������� ������ �� ������� ���������\n");
}
void find_ready(char* read)
{
	int count = 0;
	for (int i = 0; i < sch; i++)
	{
		if (strcmp(read, prod[i].ready) == 0)
		{
			printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "���", "�������", "��������", "����� ��������", "����� ������", "����", "����������");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			printf("******************************************************************************************************************************************************************\n");
			count = 1;
			file_find(i, count);
		}
	}
	if (count == 0) printf("�� ������� ������ �� ������� ���������\n");
}
void find_FIO(char* FIO)
{
	int count = 0;
	for (int i = 0; i < sch; i++)
	{
		if (strcmp(FIO, prod[i].FIO) == 0)
		{
			printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "���", "�������", "��������", "����� ��������", "����� ������", "����", "����������");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			printf("******************************************************************************************************************************************************************\n");
			count = 1;
			file_find(i, count);
		}
	}
	if (count == 0) printf("�� ������� ������ �� ������� ���������\n");
}
void find()
{
	if (sch == 0) printf("��� �������\n");
	else
	{
		char FIO[20];
		char number[20];
		char ready[1];
		switch (menu_find())
		{
		case 1:	

			printf("������� ���: ");
			gets_s(FIO);
			gets_s(FIO);
			find_ready(FIO);
			break;

		case 2:
			
			printf("������� �������: ");
			gets_s(number);
			gets_s(number);
			find_telephone(number);
			break;

		case 3:
		
			printf("������� ����������: ");
			gets_s(ready);
			gets_s(ready);
			find_FIO(ready);
			break;
		case 4:
			
			break;
		default:puts("�������� ��������"); break;
		}
	}
}

/*������� ���������� �� ���������*/

int menu_sort()
{
	setlocale(LC_ALL, "rus");
	int ch;
	printf("�������� �������� ��� ����������: \n");
	printf("1) ����������\n");
	printf("2) ���������� ����\n");
	printf("3) ��������\n");
	printf("4) �����\n");
	ch = check_menu(4);
	starline();
	system("cls");
	return ch;
}

void sort_price_down()
{
	if (sch == 0) printf("��� �������\n");
	else
	{
		for (int k = 0; k < sch - 1; k++)
		{
			for (int j = k + 1; j < sch; j++)
			{
				if (prod[k].byn_price < prod[j].byn_price)
				{
				buf = prod[k];
				prod[k] = prod[j];
				prod[j] = buf;
				}
			}
		}
		starline();
		system("cls");
		printf("���� ����������� ���������� �� ������\n");
		starline();
	}
}

void sort_price_up()
{
	if (sch == 0) printf("��� �������\n");
	else
	{
		for (int k = 0; k < sch-1; k++)
		{
			for (int j = k + 1; j < sch; j++)
			{
				if (prod[k].byn_price > prod[j].byn_price)
				{
					buf = prod[k];
					prod[k] = prod[j];
					prod[j] = buf;
				}
			}
		}
		starline();
		system("cls");
		printf("���� ����������� ���������� �� ������\n");
		starline();
	}
}
void sort_ready()
{
	if (sch == 0) printf("��� �������\n");
	else
	{
		for (int k = 0; k < sch-1; k++)
		{
			for (int j = k + 1; j < sch; j++)
			{
				if (strcmp(prod[k].ready, prod[j].ready) > 0)
				{
					buf = prod[k];
					prod[k] = prod[j];
					prod[j] = buf;
				}
			}
		}
		starline();
		system("cls");
		printf("���� ����������� ���������� �� ����������\n");
		starline();
	}
}
void sort()
{
	if (sch == 0) printf("��� �������\n");
	else
	{
		switch (menu_sort())
		{
		case 1:
			sort_ready();
			break;

		case 2:
			sort_price_up();
			break;

		case 3:
			sort_price_down();
			break;
		
		case 4:
			break;

		default:puts("�������� ��������"); break;
		}
	}
}

/*������� ��� ������������ �����*/

int set_color()
{
	char p = '\0';
	printf("�������� ���� ���� � ������ �� ������������ ��������\n");
	printf("********************************************************************************************************\n");
	printf("* %24s  %-22s � %24s  %-22s *\n", "1", "", "2", "");
	printf("********************************************************************************************************\n");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "���", "׸����", "���", "������");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "�����", "�����", "�����", "������-�����");
	printf("********************************************************************************************************\n");
	printf("* %24s  %-22s � %24s  %-22s *\n", "3", "", "4", "");
	printf("********************************************************************************************************\n");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "���", "�����", "���", "������-�������");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "�����", "�����", "�����", "������-�������");
	printf("********************************************************************************************************\n");
	printf("\n ��� ����� : ");
	int i;
	while (1)
	{
		cin >> i;
		switch (i)
		{
		case 1:
			system("color 0F");
			system("cls");
			return 0;
		case 2:
			system("color 2E");
			system("cls");
			return 0;
		case 3:
			system("color 87");
			system("cls");
			return 0;
		case 4:
			system("color BC");
			//system("cls");
			break;
		default:
			cout << "������";
			break;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	system("color 87");
	file_s4et4ik_l();
	schu = lines_count / 2;
	file_s4et4ik_Bus2();
	sch = lines_count2 / 5;
	file_read_b2();
	verification();
	while (1)
	{
		if (a == 1)
		{
			switch (admin_menu())
			{
			case 1:
				system("cls");
				enter_new();
				file_b();
				break;

			case 2:
				system("cls");
				print_table(prod, sch);
				break;

			case 3:
				system("cls");
				del();
				file_b();
				break;

			case 4:
				system("cls");
				add_more();
				file_b();
				break;

			case 5:
				system("cls");
				change();
				file_b();
				break;

			case 6:
				system("cls");
				find();
				break;

			case 7:
				system("cls");
				sort();
				file_b();
				break;
			case 8:
				system("cls");
				add_l();
				break;

			case 9:
				system("cls");
				printf_table_l(user, schu);
				break;

			case 10:
				system("cls");
				change_log();
				break;

			case 11:
				system("cls");
				del_log();
				break;

			case 12:
				system("cls");
				verification();
				break;

			case 13:
				system("cls");
				set_color();
				break;

			case 14: 
				system("cls");
				break;

			case 15:
				system("cls");
				return 1;

			default:puts("�������� ��������"); break;
			}
		}
		else if (a == 2) //������������
		{
			switch (user_menu())
			{
			case 1:
				system("cls");
				print_table(prod, sch);
				break;
			case 3:
				system("cls");
				find();
				break;

			case 4:
				system("cls");
				set_color();
				break;

			case 5:
				system("cls");
				sort();
				file_b();
				break;

			case 6: 
				return 1;

			case 7:
				system("cls");
				verification();
				break;

			default:puts("�������� ��������"); break;
			}
		}
	}
}

