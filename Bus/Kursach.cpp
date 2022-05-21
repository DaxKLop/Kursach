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
	char login[MAX_SIZE];			//логин
	char password[MAX_SIZE];     //пароль
};

struct User
{
	char login[MAX_SIZE];			//логин
	char password[MAX_SIZE];     //пароль
};

struct Product
{
	char FIO[MAX_SIZE]; //Фамилия Имя Отчество
	char telephone[13]; //Код заказа
	char name[MAX_SIZE];// Название продукта
	char timeaccept[10];//время приёмки
	char timeissue[10]; //время отдачи
	float byn_price; //цена
	char ready[1]; // готовнасть 	

};

/*Функции выделения динамической памяти*/

Admin* adm = (Admin*)malloc(sizeof(Admin) * 2);
User* user = (User*)malloc(sizeof(User) * 10);
Product* prod = (Product*)malloc(sizeof(Product) * 10);

FILE* A;
FILE* U;
FILE* Orders;
FILE* Products;

/*Счетчик данных об автовокзале*/

int sch = 0;
int count_of_enter_new = 0;
int a = 0;
int ver = 0;

static Product buf;
static Product tmp;
static User tmp1;
int lines_count = 0;
int lines_count2 = 0;

/*Фунция, выводящая звездочки на экран*/

void starline()
{
	printf("**************************************************************\n");
}

/*Функция, которая подсчитывает количество строк в файле с логинами и паролями*/

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

/*Функция, которая подсчитывает количество строк в файле с "чистыми" значениями*/

void file_s4et4ik_Bus2()
{
	lines_count2 = 0;
	fopen_s(&Products, "Products.txt", "r");
	if (Products == NULL) { printf("Не удалось создать файл\n"); return; }
		while (!feof(Products))
	{
		if (fgetc(Products) == '\n')
			lines_count2++;
	}
	//lines_count2++;
	fclose(Products);
}

/*Счетчик логинов*/

int schu;

/*Функции проверок*/

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
			cout << "Некорректные данные. Пожалуйста, попробуйте еще раз.\nВаш выбор: ";
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
			cout << "Некорректная цена. Пожалуйста, попробуйте еще раз.\nНовая цена: ";
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
				cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз.\nРазрешены только латинский буквы нижнего регистра\nПопробуйте снова: "; break;
			}
		}
		if (flag == 0) { strcpy(str, string); break; }
	}
}

void check_for_ready(char* str)
{
	cout << "+ если готов, - если не готов";
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
				cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз.\n+ если готов, - если не готов\nПопробуйте снова: "; break;
			}
		if (flag == 0) { strcpy(str, ready); break; }
	}
}

void check_for_date(char* str)
{
	cout << "Введите дату в формате DD.MM.YYYY ";
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
					cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз.\nВведите дату в формате DD.MM.YYYY\nПопробуйте снова: "; break;
				}
			}
			if (date[0] > 51 || date[3] > 49 || (date[4] > 50 && date[3] == 49))
				{
					cin.clear();
					flag = 1;
					cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз.\nВведите дату в формате DD.MM.YYYY\nПопробуйте снова: "; break;
				}
			if ((date[3] == 48 && date[4] == 50) && date[0] > 50)
				{
					cin.clear();
					flag = 1;
					cout << "Некорректный ввод. Пожалуйста, попробуйте еще раз.\nВведите дату в формате DD.MM.YYYYа\nПопробуйте снова: "; break;
				}
			if (flag == 0) { strcpy(str, date); break; }
	}
}

void check_for_telephone(char* str)
{
	cout << "Введите номер телефона +375........... ";
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
			cout << "Введите номер телефона +375........... "; break;
		}
		for (i = 1; i < strlen(number); i++)
		{
			if (number[i] < '0' || number[i] > '9')
			{
				cin.clear();
				flag = 1;
				cout << "Введите номер телефона +375........... "; break;
			}
		}
		if (flag == 0) { strcpy(str, number); break; }
	}
}


/*Меню выбора пользователя*/



int user_menu()
{
	system("cls");
	int choise;
	printf("1) Просмотр данных\n");
	printf("2) Вывод по готовности\n");
	printf("3) Поиск по параметру\n");
	printf("4) Сортировка\n");
	printf("4) Изменить цвет\n");
	printf("6) Выход из программы\n");
	printf("7) Переход к другому аккаунту\n");
	printf("Ваш выбор: ");
	choise = check_menu(7);
	starline();
	return choise;
}

/*Меню выбора администратора*/

int admin_menu()
{
	system("cls");
	int choise;
	printf("1) Ввод данных\n");
	printf("2) Вывод данных\n");
	printf("3) Удаление\n");
	printf("4) Добавление\n");
	printf("5) Редактирование\n");
	printf("6) Поиск\n");
	printf("7) Сортировка c учетом регистров\n");
	printf("8) Добавление учетных записей\n");
	printf("9) Вывод учетных записей\n");
	printf("10) Редактирование учетных записей\n");
	printf("11) Удаление учетных записей\n");
	printf("12) Переход к другому аккаунту\n");
	printf("13) Изменить цвет\n");
	printf("14) Очистка\n");
	printf("15) Выход из программы\n");
	printf("Ваш выбор: ");
	choise = check_menu(15);
	starline();
	system("cls");
	return choise;
}

/*Переменные, необходимые для условия, при котором будет считываться символ*/

int help = 0;
int help1 = 0;

/*Функция авторизации*/

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
		printf("Нажмите Enter 3 раза, для начала верификации ");
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
				printf("Вход осуществлен!\n");
				a = 2;
				break;
				break;
			}
		}
		if (strcmp(adm[0].login, adm[1].login) == 0 && strcmp(adm[0].password, adm[1].password) == 0)
		{
			help = 1;
			printf("Вход осуществлен!\n");
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
		printf("Введите логин: ");
		gets_s(adm[1].login);
		int strlen = 0;
		int n = 0;
		printf("Введите пароль: ");
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
				printf("Вход осуществлен!\n");
				a = 2;
				break;
				break;
			}
		}
		if (strcmp(adm[0].login, adm[1].login) == 0 && strcmp(adm[0].password, adm[1].password) == 0)
		{
			help = 1;
			printf("Вход осуществлен!\n");
			a = 1;
			break;
		}

		else if (a == 0)
		{
			printf("\nНеверный логин или пароль!\n");
			printf("\n1.Нажмите Enter чтобы повторить ввод или Esc чтобы выйти . . .\n");
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

/*Функция добавления логинов и паролей в файл*/

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

/*Функиця добавления нового пользователя*/

void add_l()
{
	int flag = 0;
	int help3 = 0;
	if ((schu + 1) <= 10)
	{
		printf("Запись %d\n", schu + 1);
		while (flag == 0)
		{
			int proverka = 0;
			printf("Введите логин: ");
			if (help3 == 0)
			{
				gets_s(user[schu].login);
				gets_s(user[schu].login);
			}
			else gets_s(user[schu].login);
			printf("Введите пароль: ");
			gets_s(user[schu].password);

			for (int i = 0; i < schu; i++)
			{
				if (strcmp(user[i].login, user[schu].login) == 0)
				{
					printf("Этот логин уже занят!\nВведите другой логин!\n\n"); proverka = 1; help3 = 1; break;
				}
			}
			if (proverka == 1) continue;
			else flag = 1;

			fflush(stdin);
			schu++;
			file_l();
			system("cls");
			printf("Добавление произошло успешно!\n");
		}
	}
	else printf("Нельзя добавить ещё записей\n");
}

/*Функция вывода данных пользователей в табличном виде*/

void printf_table_l(struct User* array, int len)
{
	int i;
	if (schu == 0) printf("Нет записей\n");

	printf("***********************************************\n");						
	for (i = 0; i < len; i++) {
		printf("* %-20s : %-20s *\n", "Login" ,user[i].login);
		printf("* %-20s : %-20s *\n", "Password", user[i].password);
		printf("* %-20s : %-20s *\n", "********************", "********************");
	}
	printf("______________________________________________\n");
}

/*Функция изменения данных пользователя*/

void change_log()
{
	int d;
	if (schu == 0) printf("Нет записей\n");
	else
	{
		printf("Введите номер учетной записи для изменения: ");
		d = check_menu(schu);
		system("cls");

		printf("Введите логин учетной записи: ");
		gets_s(user[d - 1].login);
		gets_s(user[d - 1].login);
		fflush(stdin);

		printf("Введите пароль: ");
		gets_s(user[d - 1].password);
		fflush(stdin);
		file_l();
		starline();
	}
}

/*Функция удаления пользователя*/

void del_log()
{
	int d, choise,res;
	if (schu == 0) printf("Нет записей\n");
	else
	{
		printf("1) Удалить определённую запись\n");
		printf("2) Удалить все записи\n");
		printf("3) Выход\n");
		choise = check_menu(3);

		starline();

		if (choise == 1)
		{
			system("cls");
			printf("Введите номер записи для удаления: ");
			d = check_menu(schu);
			printf("Вы точно хотите удалить?\n");
			printf("1)Да\n2)Нет\n");
			printf("Ваш выбор: ");
			res = check_menu(2);
			system("cls");
			if (res == 1)
			{
				if (d <= 0 || d > schu)
				{
					printf("Такой записи не существует\n");
					return;
				}

				for (int i = (d - 1); i < schu; i++)
				{
					user[i] = user[i + 1];
				}
				schu--;
				file_l();
				puts("Запись удалена");
				starline();
			}
		}

		else if (choise == 2)
		{
			printf("Вы точно хотите удалить?\n");
			printf("1)Да\n2)Нет\n");
			printf("Ваш выбор: ");
			res = check_menu(2);
			if (res == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					user[i] = tmp1;
				}
				schu = 0;
				file_l();
				puts("Записи удалены");
				puts("________________________________");
			}
		}

		else if (choise == 3)
		{
			return;
		}
		else
		{
			printf("Неверное значение\n");
		}
	}
}

/*Функция записи в файл для пользователя и в файл с "чистыми" значениями*/

void file_b()
{
	Orders = fopen("Orders.txt", "w+t");
	for (int i = 0; i < sch; i++)
	{
		fprintf(Orders, "Запись %d:\n", i + 1);
		fprintf(Orders, "ФИО:");
		fprintf(Orders, "%s\n", prod[i].FIO);
		fprintf(Orders, "телефон:");
		fprintf(Orders, "%s\n", prod[i].telephone);
		fprintf(Orders, "Название:");
		fprintf(Orders, "%s\n", prod[i].name);
		fprintf(Orders, "Время принятия:");
		fprintf(Orders, "%s\n", prod[i].timeaccept);
		fprintf(Orders, "Время отдачи:");
		fprintf(Orders, "%s\n", prod[i].timeissue);
		fprintf(Orders, "Цена:");
		fprintf(Orders, "%.2f\n\n", prod[i].byn_price);
		fprintf(Orders, "Готовность:");
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

/*Функция считывания данных из файла*/

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

/*Функция записи в файл при выборе пункта поиска*/

void file_find(int i, int count)
{
	Orders = fopen("Orders.txt", "a+t");
	
	if (count == 1)
	{
		fprintf(Orders, "Запись %d удовлетворяет поиск по заданному параметру\n", i + 1);
		fprintf(Orders, "ФИО:");
		fprintf(Orders, "%s\n", prod[i].FIO);
		fprintf(Orders, "телефон:");
		fprintf(Orders, "%s\n", prod[i].telephone);
		fprintf(Orders, "Название:");
		fprintf(Orders, "%s\n", prod[i].name);
		fprintf(Orders, "Время приёма:");
		fprintf(Orders, "%s\n", prod[i].timeaccept);
		fprintf(Orders, "Время отдачи:");
		fprintf(Orders, "%s\n", prod[i].timeissue);
		fprintf(Orders, "Цена:");
		fprintf(Orders, "%.2f\n\n", prod[i].byn_price);
		fprintf(Orders, "Готовность:");
		fprintf(Orders, "%s\n", prod[i].ready);
	}
	else fprintf(Orders, "Ошибка поиска!\n");
	fclose(Orders);
}

/*Функция ввода данных*/

void enter_new()
{
	if (sch != 0) count_of_enter_new = 1;
	if (count_of_enter_new != 0) { printf("Для добавления новых записей воспользуйтесь пунктов №4\n"); return; }
	int n;
	int i = 0;
	printf("Введите количество желаемых записей: ");
	n = check_menu(10);
	if (sch < n)
	{
		while (sch != n)
		{
			starline();
			printf("Запись %d\n", sch + 1);

			printf("Введите ФИО: ");
			check_for_string(prod[sch].FIO);
			check_for_string(prod[sch].FIO);
			fflush(stdin);

			printf("Введите номер телефона: ");
			check_for_telephone(prod[sch].telephone);
			fflush(stdin);

			printf("Введите название товара: ");
			check_for_string(prod[sch].name);
			fflush(stdin);

			printf("Введите дату приёма: ");
			check_for_date(prod[sch].timeaccept);

			printf("Введите дату выдачи: ");
			check_for_date(prod[sch].timeissue);

			printf("Введите цену: ");
			prod[sch].byn_price = check_for_price();

			printf("Введите готовность: ");
			check_for_ready(prod[sch].ready);
			fflush(stdin);
			
			count_of_enter_new = 1;
			sch++;
			starline();
		}
	}
	else printf("\nВведено максимальное кол-во записей\n");
	system("cls");
}

/*Функция вывода данных в табличном виде*/

void print_table(struct Product* array, int len) 
{
	printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "ФИО", "Телефон", "Название", "Время принятия", "Время выдачи", "Цена", "Готовность");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			for (int i = 0; i < len; i++) {
				printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			}
			printf("******************************************************************************************************************************************************************\n");
	system("pause");
}

/*Функция удаления данных*/

void del()
{
	int d, choise,res;
	if (sch == 0) printf("Нет записей\n");
	else
	{
		printf("1) Удалить определённую запись\n");
		printf("2) Удалить все записи\n");
		printf("3) Выход\n");
		choise = check_menu(3);

		starline();

		if (choise == 1)
		{
			printf("Введите номер записи для удаления: ");
			d = check_menu(sch);
			while (d > sch || d<1)
			{
				printf("Такой записи не существует!\nПопробуйте снова!\nНомер записи для удаления: ");
				scanf_s("%d", &d);
				if (scanf_s("%d", &d) != 1)
				{
					getchar();
					system("cls");
					cout << "Неверный тип\n";
					return;
				}
			}
			system("cls");
			printf("Вы точно хотите удалить?\n");
			printf("1)Да\n2)Нет\n");
			printf("Ваш выбор: ");
			res = check_menu(2);
			system("cls");
			if (res == 1)
			{
				if (d <= 0 || d > sch)
				{
					printf("Такой записи не существует\n");
					return;
				}

				for (int i = (d - 1); i < sch; i++)
				{
					prod[i] = prod[i + 1];
				}
				sch--;
				puts("Запись удалена!");
				starline();
			}
		}

		else if (choise == 2)
		{
			printf("Вы точно хотите удалить?\n");
			printf("1)Да\n2)Нет\n");
			printf("Ваш выбор: ");
			res = check_menu(2);
			if (res == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					prod[i] = tmp;
				}
				sch = 0;
				puts("Записи удалены!");
				starline();
			}
		}

		else if (choise == 3)
		{
			return;
		}
		else
		{
			printf("Неверное значение!\n");
		}
	}
}

/*Функция редактирования данных*/

void change()
{
	int d;
	if (sch == 0) printf("Нет записей\n");
	else
	{
		printf("Введите номер записи для изменения: ");
		d = check_menu(sch);
		system("cls");

		printf("Введите ФИО: ");
		check_for_string(prod[sch].FIO);
		check_for_string(prod[sch].FIO);
		fflush(stdin);

		printf("Введите номер телефона: ");
		check_for_telephone(prod[sch].telephone);
		fflush(stdin);

		printf("Введите название товара : ");
		check_for_string(prod[sch].name);
		fflush(stdin);

		printf("Введите дату приёма \n ");
		check_for_date(prod[sch].timeaccept);
		fflush(stdin);

		printf("Введите дату выдачи \n");
		check_for_date(prod[sch].timeissue);
		fflush(stdin);

		printf("Введите цену: ");
		prod[sch].byn_price = check_for_price();

		printf("Введите готовность: ");
		check_for_ready(prod[sch].ready);
		fflush(stdin);

		system("cls");
		printf("Редактирвоание произошло успешно!\n");
	}
}

/*Функция добавление новых данных*/

void add_more()
{
	int n;
	printf("Введите количество записей для добавления: ");
	n = check_menu(10);
	if ((sch + n) <= 10)
	{
		for (int i = 0; i < n; i++)
		{
			starline();
			printf("Запись %d\n", sch + 1);

			printf("Введите ФИО: ");
			check_for_string(prod[sch].FIO);
			check_for_string(prod[sch].FIO);
			fflush(stdin);

			printf("Введите телефон: ");
			check_for_telephone(prod[sch].telephone);
			fflush(stdin);

			printf("Введите название товара: ");
			check_for_string(prod[sch].name);
			fflush(stdin);

			printf("Введите дату приёма: ");
			check_for_date(prod[sch].timeaccept);
			fflush(stdin);

			printf("Введите дату выдачи: ");
			check_for_date(prod[sch].timeissue);
			fflush(stdin);

			printf("Введите цену: ");
			prod[sch].byn_price = check_for_price();

			printf("Введите готовность: ");
			check_for_ready(prod[sch].ready);
			fflush(stdin);

			sch++;
			starline();
		}
	system("cls");
	printf("Добавление произошло успешно\n");
	}
	else printf("Невозможно добавить столько записей\n");
}

/*Функции для поиска по параметру*/

int menu_find()
{
	setlocale(LC_ALL, "rus");
	int ch;
	printf("Выберете параметр для поиска: \n");
	printf("1) ФИО\n");
	printf("2) Телефон\n");
	printf("3) Готовность\n");
	printf("4) Назад\n");
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
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "ФИО", "Телефон", "Название", "Время принятия", "Время выдачи", "Цена", "Готовность");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			printf("******************************************************************************************************************************************************************\n");
			count = 1;
			file_find(i, count);
		}
	}
	
	if (count == 0) printf("Не найдено данных по данному параметру\n");
}
void find_ready(char* read)
{
	int count = 0;
	for (int i = 0; i < sch; i++)
	{
		if (strcmp(read, prod[i].ready) == 0)
		{
			printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "ФИО", "Телефон", "Название", "Время принятия", "Время выдачи", "Цена", "Готовность");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			printf("******************************************************************************************************************************************************************\n");
			count = 1;
			file_find(i, count);
		}
	}
	if (count == 0) printf("Не найдено данных по данному параметру\n");
}
void find_FIO(char* FIO)
{
	int count = 0;
	for (int i = 0; i < sch; i++)
	{
		if (strcmp(FIO, prod[i].FIO) == 0)
		{
			printf("******************************************************************************************************************************************************************\n");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "ФИО", "Телефон", "Название", "Время принятия", "Время выдачи", "Цена", "Готовность");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************", "*******************");
			printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20.2f | %-20s |\n", prod[i].FIO, prod[i].telephone, prod[i].name, prod[i].timeaccept, prod[i].timeissue, prod[i].byn_price, prod[i].ready);
			printf("******************************************************************************************************************************************************************\n");
			count = 1;
			file_find(i, count);
		}
	}
	if (count == 0) printf("Не найдено данных по данному параметру\n");
}
void find()
{
	if (sch == 0) printf("Нет записей\n");
	else
	{
		char FIO[20];
		char number[20];
		char ready[1];
		switch (menu_find())
		{
		case 1:	

			printf("Введите ФИО: ");
			gets_s(FIO);
			gets_s(FIO);
			find_ready(FIO);
			break;

		case 2:
			
			printf("Введите телефон: ");
			gets_s(number);
			gets_s(number);
			find_telephone(number);
			break;

		case 3:
		
			printf("Введите готовность: ");
			gets_s(ready);
			gets_s(ready);
			find_FIO(ready);
			break;
		case 4:
			
			break;
		default:puts("Неверное значение"); break;
		}
	}
}

/*Функции сортировки по параметру*/

int menu_sort()
{
	setlocale(LC_ALL, "rus");
	int ch;
	printf("Выберете параметр для сортировки: \n");
	printf("1) Готовность\n");
	printf("2) Возрастане цены\n");
	printf("3) Убывание\n");
	printf("4) Назад\n");
	ch = check_menu(4);
	starline();
	system("cls");
	return ch;
}

void sort_price_down()
{
	if (sch == 0) printf("Нет записей\n");
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
		printf("Была произведена сортировка по пункту\n");
		starline();
	}
}

void sort_price_up()
{
	if (sch == 0) printf("Нет записей\n");
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
		printf("Была произведена сортировка по пункту\n");
		starline();
	}
}
void sort_ready()
{
	if (sch == 0) printf("Нет записей\n");
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
		printf("Была произведена сортировка по готовности\n");
		starline();
	}
}
void sort()
{
	if (sch == 0) printf("Нет записей\n");
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

		default:puts("Неверное значение"); break;
		}
	}
}

/*Функция для установления цвета*/

int set_color()
{
	char p = '\0';
	printf("Выберите цвет фона и текста из предложенных шаблонов\n");
	printf("********************************************************************************************************\n");
	printf("* %24s  %-22s № %24s  %-22s *\n", "1", "", "2", "");
	printf("********************************************************************************************************\n");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "Фон", "Чёрный", "Фон", "Зелёный");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "Текст", "Белый", "Текст", "Светло-жёлтый");
	printf("********************************************************************************************************\n");
	printf("* %24s  %-22s № %24s  %-22s *\n", "3", "", "4", "");
	printf("********************************************************************************************************\n");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "Фон", "Серый", "Фон", "Светло-голубой");
	printf("* %-22s : %-23s * %-22s : %-23s *\n", "Текст", "Белый", "Текст", "Светло-красный");
	printf("********************************************************************************************************\n");
	printf("\n Ваш выбор : ");
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
			cout << "Ошибка";
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

			default:puts("Неверное значение"); break;
			}
		}
		else if (a == 2) //пользователь
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

			default:puts("Неверное значение"); break;
			}
		}
	}
}

