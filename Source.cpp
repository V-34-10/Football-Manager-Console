// Необхідні бібліотеки
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <ctime>
#include <Windows.h>
#include <string>
#include <regex>
#include <conio.h>

using namespace std;
struct player // структура даних - гравець
{	
	char first_second_name_player[20]; // П.І. гравця
	time_t date_of_birth; // Дата народження 
	char sex[5]; // стать гравця (вводиться з клавіатури «ж» – жіноча, «ч» – чоловіча).
	char nationality[15]; // громадянство
	char role[4]; // Амплуа(обирається зі списку : ВР – воротар, ЛП – лівий півзахисник, ЦФ – центр форвард)
	size_t kol_games; // KG – кількість проведених ігор 
	size_t kod; // Код гравця
};

struct team // структура даних - команда
{
	char country[15]; // країна
	char team_p[15]; // команда гравця
	size_t transfer_cost; // Трансферна вартість футболіста 
	char contract[10]; // Термін контракту (обирається зі списку: 1 рік, 2 роки, 3 роки).
	size_t kod; // Код гравця
};

// функція загрузочного індикатора
void progress_bar(int percents) 
{
	int half = percents / 2;
	printf("\r\t\t\t\t\t[");
	for (int i = 0; i < half; ++i) putc('#', stdout);
	for (int i = 0; i < 50 - half; ++i) putc(' ', stdout);
	printf("] %3d %%", percents);
	fflush(stdout);
}

// функція локалізації
void _ukr() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

// Прототипи функцій
void MENU();
int Menu();
int menu();
int menu_file_1();
int menu_edit_element();
int menu_sort();

void system_pause();

void review_file();
void review_file_1();

void add_data();
void add_data_file_1();
time_t vvod_data_of_birth();

void new_file();
void new_file_1();

void _table();
void cap_table();
void table_cap_table();

void kol_sex_file_1();
void contract_file();
void nationality_file_1();
void total_cost_file_1();
void max_kol_games_file_1();

bool del_element();
void del_kod_file_1();

bool full_edit_element();
bool not_full_edit_element();
int edit_kod_file_1();

void sort_transfer_cost();
void sort_country();

bool proverka_zapusy_file(team data);
bool proverka_zapusy_file_1(player data);
bool proverka_kod_zapus_file(team data);

// шаблони для перевірки введених даних
regex regular_2("([0-2])");
cmatch result_2;
regex regular_3("([1-3])");
cmatch result_3;
regex regular_5("([0-5])");
cmatch result_5;
regex regular_6("([0-6])");
cmatch result_6;
regex regular_7("([0-7])");
cmatch result_7;
regex regular_three_digit("[0-9]+([0-9]+[0-9])?");
cmatch result_three_digit;
regex regular_two_digit("[0-9]+([0-9])?");
cmatch result_two_digit;
regex regular_four_digit("[0-9]+[0-9]+[0-9]+[0-9]");
cmatch result_four_digit;

// Два файли: file - файл Команда, file_1 - файл Гравці
FILE* file;
FILE* file_1;

int main()
{
	
	_ukr();
	system("color F4");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n ");
	_ukr(); cout << "\t\t\t\t\t Добро пожаловать до обліку даних футболістів FIFA! " << endl;
	for (int i = 0; i <= 100; ++i) {
		progress_bar(i);
		Sleep(50);
	}
	Sleep(3500);
	MENU();
	return 0;
}

// функція на наявність ідентичного запису в файлі - Команди
bool proverka_zapusy_file(team data)
{
	team data1;
	fopen_s(&file, "player.dat", "rb");
	while (fread(&data1, sizeof(team), 1, file))
	{
		if (data.kod == data1.kod)
		{
			fclose(file);
			cout << "\t\tВведений запис існує в файлі!" << endl;
			return true;
		}
	};
	fclose(file);
	return false;
}

// функція - пауза
void system_pause()
{
	cout << endl << "\t\tДля продовженя натисніть будь-яку клавішу...";
	_getch();
}

// функція головного меню
void MENU()
{
	int n, * pn = &n;
	do
	{
		system("cls");
		system("color F6");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\t\t\tГоловне меню\n";
		_ukr(); cout << endl << "\t1. Файл 'Команда'\n";
		_ukr(); cout << endl << "\t2. Файл 'Гравці'\n";
		_ukr(); cout << endl << "\t0. Вихід з програми";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tВаш вибiр - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_2, regular_2))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 2!!!";
			}
		} while (!flag);

		switch (*pn)
		{
		case 1:
			system("cls");
			Menu();
			system_pause();
			break;
		case 2:
			system("cls");
			menu_file_1();
			system_pause();
			break;
		}
	} while (*pn != 0);
	if (*pn == 0)
	{
		system("cls");
		system("color F4");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\t\t\tДо побачення!!! ";
		_ukr(); cout << endl << "\t\t\t\tДякую за використання обліку даних футболістів FIFA!";
	}
}

// функція меню файла - Команди
int Menu()
{
	int n, * pn = &n;
	int num = 0;
	team data;
	do
	{
		system("color F9");
		system("cls"); 
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\t\t\tГоловне меню файла 'Команда'\n";
		_ukr(); cout << endl << "\t1. Створення нового файлу\n";
		_ukr(); cout << endl << "\t2. Перегляд існуючого файлу\n";
		_ukr(); cout << endl << "\t3. Додавання даних у файл\n";
		_ukr(); cout << endl << "\t4. Редагування записів (як цілком, так і за окремими полями)\n";
		_ukr(); cout << endl << "\t5. Видалення записів (за № п/п)\n";
		_ukr(); cout << endl << "\t6. Сортування інформації (за двома ознаками: за вартістю та за країною)\n";
		_ukr(); cout << endl << "\t7. Виконання запитів\n";
		_ukr(); cout << endl << "\t0. Повернення до попереднього меню";
		
		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tВаш вибiр - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_7, regular_7))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 7 !!!";
			}
		} while (!flag);

		switch (*pn)
		{
		case 1:
			system("cls");
			new_file();
			break;
		case 2:
		{
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if (!file) {
				_ukr(); cout << endl << "\n\t\tПомилка. Створіть файл!";
			}
			else
			{

				if ((fread(&data, sizeof(team), 1, file)) == NULL)
				{
					_ukr(); cout << endl << "\n\t\tПомилка. Файл порожній!";
					fclose(file);
				}
				else
				{
					fclose(file);
					review_file();
				}
			}
			system_pause();
			break;
		}
		case 3:
			system("cls");
			add_data();
			system_pause();
			break;
		case 4:
			system("cls");
			
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\t\tПомилка. Файл порожній!";
			}
			else fclose(file); 
			menu_edit_element();
			
			break;
		case 5:
			system("cls");

			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\t\tПомилка. Файл порожній!";
			}
			else
			{
				fclose(file);
				_ukr(); cout << endl << "\n\tФайл до видалення записів:\n\n";
				review_file();
				system_pause();
				if (del_element() == true)
				{
					system("cls");
					_ukr(); cout << endl << "\n\tФайл після видалення записів:\n";
					review_file();
				}
				else {
					_ukr(); cout << endl << "\n\t\tФайл не змінився!";
				}
			}

			system_pause();
			break;
		case 6:
			system("cls");

			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\t\tПомилка. Файл порожній!";
			}
			else fclose(file);
			menu_sort();
			
			system_pause();
			break;
		case 7:
			system("cls");
			menu();
			system_pause();
			break;
		case 0:
			return 0;
		}
	} while (*pn != 0);
}

// функція меню запитів
int menu()
{
	team data;
	int n, * pn = &n;
	do {
		system("color F0");
		system("cls");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\tМеню запитів\n\n";
		_ukr(); cout << endl << "\t1. Підрахувати кількість гравців, які знаходяться у основному файлі,";
		_ukr(); cout << endl << "\tпо кожній статі\n";
		_ukr(); cout << endl << "\t2. Виведення даних про гравців, у яких термін контракту дорівнює";
		_ukr(); cout << endl << "\tзначенню введеному з клавіатури\n";
		_ukr(); cout << endl << "\t3. Виведення даних про всіх гравців, громадянство яких було обрано";
		_ukr(); cout << endl << "\tкористувачем\n";
		_ukr(); cout << endl << "\t4. Підрахувати загальну вартість по кожному гравцю,";
		_ukr(); cout << endl << "\tу якого є контракт\n";
		_ukr(); cout << endl << "\t5. Знайти, де працює гравець/гравці,";
		_ukr(); cout << endl << "\tза максимальною кількістю ігор\n";
		_ukr(); cout << endl << "\t0. Повернення до попереднього меню";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tВаш вибiр - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_5, regular_5))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 5 !!!";
			}
		} while (!flag);

		switch (*pn)
		{
		case 1:
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\tПомилка. Файл порожній!";
			}
			else fclose(file);
			kol_sex_file_1();
			system_pause();
			break;
		case 2:
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\tПомилка. Файл порожній!";
			}
			else fclose(file);
			contract_file();
			system_pause();
			break;
		case 3:
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\tПомилка. Файл порожній!";
			}
			else fclose(file);
			nationality_file_1();
			system_pause();
			break;
		case 4:
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\tПомилка. Файл порожній!";
			}
			else fclose(file);
			total_cost_file_1();
			system_pause();
			break;
		case 5:
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\tПомилка. Файл порожній!";
			}
			else fclose(file);
			max_kol_games_file_1();
			system_pause();
			break;
		case 0:
			return 0;
		}
	} while (*pn != 0);
}

// функція запиту - підрахунок кількості по статі
void kol_sex_file_1()
{
	player data;
	size_t kol_sex_m(0), kol_sex_w(0);
	_ukr(); cout << endl << "\t\tРезультати вашого запиту: \n\n";
	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1))
	{
		if (strcmp(data.sex, "Ч") == 0) kol_sex_m++;
		if (strcmp(data.sex, "Ж") == 0) kol_sex_w++;
	};
	_ukr(); cout << "\t\tКількість гравців чоловічої статі -> " << kol_sex_m << endl;
	_ukr(); cout << "\t\tКількість гравців жіночої статі -> " << kol_sex_w << endl;
	fclose(file_1);
}

// функція запиту - знаходження по контракту
void contract_file()
{
	team data;
	player data1;
	int choice;
	bool flag = false;
	char contr[10];

	cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "\t\tОберіть термін контракту, за яким необхідно знайти запис - ";
	cout << endl << "\t\t1. 1 рік\n\t\t2. 2 роки\n\t\t3. 3 роки";

	string _сhoice;
	
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\t\tВаш вибiр - ";
		getline(cin, _сhoice);
		if (regex_match(_сhoice.c_str(), result_3, regular_3))
		{
			flag1 = true;
			choice = atoi(_сhoice.c_str());

			if (choice == 1) strcpy_s(contr, "1");
			else if (choice == 2) strcpy_s(contr, "2");
			else strcpy_s(contr, "3");
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!";
		}

	} while (!flag1);

	system("cls");
	_ukr(); cout << endl << "\t\tРезультати вашого запиту: \n\n";
	cout << endl;

	cout << "\t\t";
	for (size_t i = 0; i <= 96; i++) cout << "-";
	_ukr(); cout << "\n\t\t| Код |" << "         П.І.      |" << " Дата народження |" << " Стать |"
		<< " KG |" << "  Команда  |" << " Амплуа |" << "   Громадянство  |" << endl;
	cout << "\t\t";
	for (size_t i = 0; i <= 96; i++) cout << "-";

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data1, sizeof(player), 1, file_1) == 1)
	{

		fopen_s(&file, "player.dat", "rb");
		while (fread(&data, sizeof(team), 1, file) == 1)
		{
			if (data1.kod == data.kod) {
				if (strcmp(contr, data.contract) == 0)
				{
					flag = true;
					struct tm t_data;
					cout << endl << "\t\t|" << right << setw(3) << data1.kod << setw(3);
					cout << '|' << left << setw(19) << data1.first_second_name_player;
					localtime_s(&t_data, &(data1.date_of_birth));
					char full_data_of_birth[10];
					strftime(full_data_of_birth, 10, "%x", &t_data);
					cout << '|' << right << setw(13) << full_data_of_birth << setw(5);
					cout << '|' << right << setw(4) << data1.sex << setw(4);
					cout << '|' << right << setw(3) << data1.kol_games << setw(2);
					cout << '|' << left << setw(11) << data.team_p;
					cout << '|' << right << setw(5) << data1.role << setw(4);
					cout << '|' << left << setw(17) << data1.nationality << '|';
				}
			}

		}
		fclose(file);
	}
	fclose(file_1);
	cout << "\n\t\t";
	for (size_t i = 0; i <= 96; i++) cout << "-"; /// кінець таблиці
	if (flag == false)
	{
		system("cls");
		cout << "\n\t\tНеобхідні записи не знайдено!" << endl;
	}
}

// функція запиту - знаходження по громадянству
void nationality_file_1()
{
	player data;
	team data1;
	int choice;
	bool flag = false;
	char national[15];

	cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "\t\tОберіть громадянство, за яким необхідно знайти запис - ";
	cout << endl << "\t\t1. Україна\n\t\t2. Аргентина\n\t\t3. Іспанія";

	string _сhoice;
	
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\t\tВаш вибiр - ";
		getline(cin, _сhoice);
		if (regex_match(_сhoice.c_str(), result_3, regular_3))
		{
			flag1 = true;
			choice = atoi(_сhoice.c_str());

			if (choice == 1) strcpy_s(national, "Україна");
			else if (choice == 2) strcpy_s(national, "Аргентина");
			else strcpy_s(national, "Іспанія");
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!";
		}

	} while (!flag1);

	system("cls");
	_ukr(); cout << endl << "\t\tРезультати вашого запиту: \n\n";
	cout << endl;

	cout << "\t\t";
	for (size_t i = 0; i <= 98; i++) cout << "-";
	_ukr(); cout << "\n\t\t| Код |" << "         П.І.      |" << "  Країна  |" 
				<< "  Команда  |" << " Амплуа |" << " Вартість(млн.євро) |"
		<< " Термін контракту |" << endl;
	cout << "\t\t";
	for (size_t i = 0; i <= 98; i++) cout << "-";

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1) == 1)
	{

		fopen_s(&file, "player.dat", "rb");
		while (fread(&data1, sizeof(team), 1, file) == 1)
		{
			if (data.kod == data1.kod) {
				if (strcmp(national, data.nationality) == 0)
				{
					flag = true;
					cout << endl << "\t\t|" << right << setw(3) << data1.kod << setw(3);
					cout << '|' << left << setw(19) << data.first_second_name_player;
					cout << '|' << left << setw(10) << data1.country;
					cout << '|' << left << setw(11) << data1.team_p;
					cout << '|' << right << setw(5) << data.role << setw(4);
					cout << '|' << right << setw(11) << data1.transfer_cost << setw(10);
					cout << '|' << right << setw(10) << data1.contract << setw(9) << '|';
				}
			}
			
		}
		fclose(file);
	}
	fclose(file_1);
	cout << "\n\t\t";
	for (size_t i = 0; i <= 98; i++) cout << "-"; /// кінець таблиці
	if (flag == false)
	{
		system("cls");
		cout << "\n\t\tНеобхідні записи не знайдено!" << endl;
	}
}

// функція запиту - підрахунку загальної вартості по гравцю
void total_cost_file_1()
{
	player data;
	team data1;
	size_t total_transfer_cost;

	_ukr(); cout << endl << "\t\tРезультат вашого запиту: \n\n\t\t";
	for (size_t i = 0; i <= 118; i++) cout << "-";
	_ukr(); cout << "\n\t\t| Код |" << "         П.І.      |" << " Амплуа |";
	_ukr(); cout << "  Країна  |" << "  Команда  |" << " Вартість(млн.євро) |" 
		<< " Термін контракту |" <<  " Загальна вартість |" << endl;
	cout << "\t\t";
	for (size_t i = 0; i <= 118; i++) cout << "-";

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1) == 1)
	{
		
		fopen_s(&file, "player.dat", "rb");
		while (fread(&data1, sizeof(team), 1, file) == 1)
		{
			if (data.kod == data1.kod)
			{
				cout << endl << "\t\t|" << right << setw(3) << data1.kod << setw(3);
				cout << '|' << left << setw(19) << data.first_second_name_player;
				cout << '|' << right << setw(5) << data.role << setw(4);
				cout << '|' << left << setw(10) << data1.country;
				cout << '|' << left << setw(11) << data1.team_p << setw(5);
				cout << '|' << right << setw(8) << data1.transfer_cost << setw(9);
				cout << '|' << right << setw(10) << data1.contract << setw(9);
				total_transfer_cost = data1.transfer_cost * atoi(data1.contract);
				cout << '|' << right << setw(10) << total_transfer_cost << setw(10) << '|';
			}
		}
		fclose(file);
	}
	fclose(file_1);
	cout << "\n\t\t";
	for (size_t i = 0; i <= 118; i++) cout << "-"; /// кінець таблиці
}

// функція запиту - знаходження де працює гравець
void max_kol_games_file_1()
{
	player data;
	team data1;
	size_t num(0), max = 0;
	bool flag = 0, flag1 = 0;

	_ukr(); cout << endl << "\t\tРезультат вашого запиту: \n\t\t";
	for (size_t i = 0; i <= 49; i++) cout << "-";
	_ukr(); cout << "\n\t\t| № |" << "         П.І.         |" << " MAX |";
	_ukr(); cout << "    Команда    |" << endl;
	cout << "\t\t";
	for (size_t i = 0; i <= 49; i++) cout << "-";
	fopen_s(&file_1, "player_1.dat", "rb");
	fread(&data, sizeof(player), 1, file_1);
	max = data.kol_games;
	while (fread(&data, sizeof(player), 1, file_1) == 1)
	{
		if (data.kol_games > max)
		{
			max = data.kol_games;
		}
	}
	fclose(file_1);

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1) == 1)
	{
		if (data.kol_games == max)
		{
			fopen_s(&file, "player.dat", "rb");
			while (fread(&data1, sizeof(team), 1, file) == 1)
			{
				if (data1.kod == data.kod)
				{
					flag = flag1 = 1;
					cout << endl << "\t\t|" << right << setw(2) << ++num << setw(2);
					cout << "|" << left << setw(22)  << data.first_second_name_player << setw(3);
					cout << "|" << right << max;
					cout << "|" << left << setw(15) << data1.team_p << setw(5) << "|";
				}
			}
			fclose(file);
		}
	}
	fclose(file_1);
	if (flag1 == 0)
	{
		system("cls");
		_ukr(); cout << endl << "\t\tРезультат вашого запиту: \n\t\t";
		_ukr(); cout << endl << "\t\tГравець з максимальною кількістю ігор - " << max
			 << " ,не працює в жодній з команд!";
	}
	if (flag == 1)
	{
		cout << "\n\t\t";
		for (size_t i = 0; i <= 49; i++) cout << "-"; /// кінець таблиці
	}
}

// функція перегляду файла Команди
void review_file()
{
	int num = 0;
	team data;
	_table(); //// заголовок таблиці
	cap_table();  //// шапка таблиці
	
	fopen_s(&file, "player.dat", "rb");
	while (fread(&data, sizeof(team), 1, file))
	{
		cout << endl << '|' << right << setw(4) << ++num << setw(4);
		cout << '|'   << left << setw(10) << data.country;
		cout << '|' << left << setw(15)  << data.team_p;
		cout << '|' << right << setw(12) << data.transfer_cost << setw(10);
		cout << '|' << right << setw(10) << data.contract << setw(9);
		cout << '|' << right << setw(3) << data.kod << setw(3) << '|';
	}
	fclose(file);
	cout << "\n";
	for (size_t i = 0; i <= 82; i++) cout << "-"; /// кінець таблиці
}

// функція заголовку таблиці - Команди
void _table()
{
	team data;
	size_t total_kol(0), kol_ukrain(0), kol_argentin(0), kol_spania(0);
	_ukr(); cout << "\t\t\t\t\tОблік даних футболістів FIFA!" << endl;

	fopen_s(&file, "player.dat", "rb");
	while (fread(&data, sizeof(team), 1, file))
	{
		total_kol++;
		if (strcmp(data.country, "Україна") == 0) kol_ukrain++;
		if (strcmp(data.country, "Аргентина") == 0) kol_argentin++;
		if (strcmp(data.country, "Іспанія") == 0) kol_spania++;
	};
	_ukr(); cout << "\n\tКоротка інформація файла: \n\n";
	_ukr(); cout << "\tКількість записів в файлі -> " << total_kol << endl;
	_ukr(); cout << "\tКількість українців в файлі -> " << kol_ukrain << endl;
	_ukr(); cout << "\tКількість аргентинців в файлі -> " << kol_argentin << endl;
	_ukr(); cout << "\tКількість іспанців в файлі -> " << kol_spania << endl;
	fclose(file);
}

// функція шапки таблиці - Команди
void cap_table() 
{
	for (size_t i = 0; i <= 82; i++) cout << "-";
	_ukr(); cout << "\n| № п/п |" << "  Країна  |" << "    Команда    |";
	_ukr(); cout << "  Вартість(млн.євро) |" << " Термін контракту |" << " Код |" << endl;
	for (size_t i = 0; i <= 82; i++) cout << "-";
}

// функція створення нового файла Команди
void new_file()
{
	const char file_new[] = "player.dat";
	fopen_s(&file, file_new, "rb");
	if (!file)
	{
		_ukr(); cout << "\t\tСтворюємо новий файл." << endl;
		fopen_s(&file, file_new, "wb");
		_ukr(); cout << "\t\tФайл успішно створнено!" << endl;
		system_pause();
	}
	else
	{
		_ukr(); cout << "\t\tІснує файл з певними даними!" << endl;
		system_pause();
	}
	fclose(file);
}

// функція видалення записів з файла Команди
bool del_element()
{
	team data;
	size_t num = 0, n_del;
	FILE* filehelply;
	size_t total_kol(0);

	fopen_s(&file, "player.dat", "rb");
	while (fread(&data, sizeof(team), 1, file))
	{
		total_kol++;
	};
	fclose(file);

	string _n_del;
	
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\n\tВведіть номер запису (№ п/п), який необхідно видалити - ";
		getline(cin, _n_del);
		if (regex_match(_n_del.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_del = atoi(_n_del.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
		}

	} while (!flag1);


	if (n_del > total_kol)
	{
		_ukr(); cout << endl << "\t\tПомилка. Введений номер запису перевищує кількість записів в файлі!";
		_ukr(); cout << endl << "\t\tКількість записів в файлі -> " << total_kol << ".";
		return false;
	}
	else
	{
		fopen_s(&file, "player.dat", "rb");
		fopen_s(&filehelply, "player_helply.dat", "w+b");
		while (fread(&data, sizeof(team), 1, file) == 1)
		{
			num++;
			if (num != n_del)
			{
				fwrite(&data, sizeof(team), 1, filehelply);
			}
		}
		fclose(file);
		fclose(filehelply);
		remove("player.dat");
		rename("player_helply.dat", "player.dat");
		return true;
	}
}

// функція перевірки коду гравця при редагуванні
bool proverka_kod_zapus_file(team data)
{
	player data1;
	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data1, sizeof(player), 1, file_1))
	{
		if (data.kod == data1.kod)
		{
			fclose(file_1);
			return true;
		}
	};
	fclose(file_1);
	return false;
}

// функція редагування - цілком
bool full_edit_element()
{
	team data;
	size_t num = 0, n_edit;
	char var;
	size_t total_kol(0);

	fopen_s(&file, "player.dat", "rb");
	while (fread(&data, sizeof(team), 1, file))
	{
		total_kol++;
	};
	fclose(file);

	string _n_edit;
	bool flag1 = 0;
	do {
		review_file();
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\t\tВведіть номер запису (№ п/п), який необхідно редагувати - ";
		getline(cin, _n_edit);
		if (regex_match(_n_edit.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_edit = atoi(_n_edit.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
		}

	} while (!flag1);

	if (n_edit > total_kol)
	{
		_ukr(); cout << endl << "\t\tПомилка. Введений номер запису перевищує кількість записів в файлі!";
		_ukr(); cout << endl << "\t\tКількість записів в файлі -> " << total_kol << ".";
		return false;
	}
	else {
		fopen_s(&file, "player.dat", "rb");
		cout << endl;
		fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);

		fread(&data, sizeof(team), 1, file);

		cap_table();

		cout << endl << '|' << right << setw(4) << ++num << setw(4);
		cout << '|' << left << setw(10) << data.country;
		cout << '|' << left << setw(15) << data.team_p;
		cout << '|' << right << setw(12) << data.transfer_cost << setw(10);
		cout << '|' << right << setw(10) << data.contract << setw(9);
		cout << '|' << right << setw(3) << data.kod << setw(3) << '|';

		cout << "\n";
		for (size_t i = 0; i <= 82; i++) cout << "-"; /// кінець таблиці

		fclose(file);

		_ukr(); cout << endl << "\t\tВи цей запис хотіли відредагувати ? Т/Y(так)/Н/N(ні) - ";
		cin >> var;
		cin.ignore(cin.rdbuf()->in_avail());
		if (var == 'Т' || var == 'т' || var == 'Y' || var == 'y')
		{
			int choice;
			_ukr(); cout << endl << "\t\t\tЛюбий користувачу, вводимо нові данні!" << endl;

			string _сhoice;
			bool flag2 = 0;
			_ukr(); cout << endl << "\t\tОберіть країну зі списку: ";
			_ukr(); cout << endl << "\t\t1. Україна\n\t\t2. Аргентина\n\t\t3. Іспанія";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice);
				if (regex_match(_сhoice.c_str(), result_3, regular_3))
				{
					flag2 = true;
					choice = atoi(_сhoice.c_str());

					if (choice == 1) strcpy_s(data.country, "Україна");
					else if (choice == 2) strcpy_s(data.country, "Аргентина");
					else strcpy_s(data.country, "Іспанія");
				}
				else
				{
					_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!";
				}

			} while (!flag2);

			string _team;
			regex regular3("([Є-ЯҐє-яґ]{4,13})");
			cmatch result3;
			bool flag3 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть назву команди від 4 до 13 символів (Наприклад: Шахтар): ";
				getline(cin, _team);
				if (regex_match(_team.c_str(), result3, regular3))
				{
					flag3 = 1;
					_ukr(); cout << endl << "\t\tВаша назва команди виглядає так - ФК " << _team;
					strcpy_s(data.team_p, _team.c_str());
				}
				else
				{
					_ukr(); cout << endl << "\t\tПомилка! Формат введення має бути таким: 'Шахтар' !!";
				}
			} while (!flag3);

			string _transfer_cost;
			bool flag4 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть трансферну вартість футболіста (в млн.євро від 1 до 400): ";
				getline(cin, _transfer_cost);
				if (regex_match(_transfer_cost.c_str(), result_three_digit, regular_three_digit))
				{
					 
					if (atoi(_transfer_cost.c_str()) < 1 || atoi(_transfer_cost.c_str()) > 400) {
						_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 400!";
					}
					else {
						flag4 = true;
						data.transfer_cost = atoi(_transfer_cost.c_str());
					}
				}
				else 
				{
					_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 400!";
				}
			} while (!flag4);

			string _сhoice1;
			bool flag5 = 0;
			cout << endl << "\t\tОберіть термін контракту  зі списку: ";
			cout << endl << "\t\t1. 1 рік\n\t\t2. 2 роки\n\t\t3. 3 роки";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice1);
				if (regex_match(_сhoice1.c_str(), result_3, regular_3))
				{
					flag5 = true;
					choice = atoi(_сhoice1.c_str());

					if (choice == 1) strcpy_s(data.contract, "1");
					else if (choice == 2) strcpy_s(data.contract, "2");
					else strcpy_s(data.contract, "3");
				}
				else
				{
					_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!";
				}

			} while (!flag5);

			string _сhoice2;
			bool flag6 = 0;
			
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть код гравця (0 - на продажі): ";
				getline(cin, _сhoice2);
				if (regex_match(_сhoice2.c_str(), result_three_digit, regular_three_digit))
				{
					flag6 = true;
					data.kod = atoi(_сhoice2.c_str());
					if (proverka_kod_zapus_file(data) == false)
					{
						flag6 = 0;
						_ukr(); cout << endl << "\t\tПомилка. Не вірне редагування коду, такого гравця з веденним кодом - не існує!";
					}
				}
				else
				{
					_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
				}
			} while (!flag6);

			if (proverka_zapusy_file(data) == false)
			{
				fopen_s(&file, "player.dat", "r+b");
				fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);
				fwrite(&data, sizeof(team), 1, file);
				fclose(file);
				return true;
			}
		}
		else
		{
			if (var == 'Н' || var == 'н' || var == 'N' || var == 'n')
			{
				_ukr(); cout << endl << "\t\tСпробуйте спочатку!" << endl;
			}
			else _ukr(); cout << endl << "\t\tПомилка!!!";

			return false;
		}
	}
	
}

// функція редагування за окремими полями
bool not_full_edit_element()
{
	team data;
	size_t num = 0, n_edit, total_kol(0);
	char var;
	int n, * pn = &n;
	int choice;

	fopen_s(&file, "player.dat", "rb");
	while (fread(&data, sizeof(team), 1, file))
	{
		total_kol++;
	};
	fclose(file);
	
	string _n_edit;
	bool flag1 = 0;
	do {
		review_file();
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\t\tВведіть номер запису (№ п/п), який необхідно редагувати - ";
		getline(cin, _n_edit);
		if (regex_match(_n_edit.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_edit = atoi(_n_edit.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
		}

	} while (!flag1);

	if (n_edit > total_kol)
	{
		_ukr(); cout << endl << "\t\tПомилка. Введений номер запису перевищує кількість записів в файлі!";
		_ukr(); cout << endl << "\t\tКількість записів в файлі -> " << total_kol << ".";
		return false;
	}
	else {
		fopen_s(&file, "player.dat", "rb");
		cout << endl;
		fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);

		fread(&data, sizeof(team), 1, file);

		cap_table();

		cout << endl << '|' << right << setw(4) << ++num << setw(4);
		cout << '|' << left << setw(10) << data.country;
		cout << '|' << left << setw(15) << data.team_p;
		cout << '|' << right << setw(12) << data.transfer_cost << setw(10);
		cout << '|' << right << setw(10) << data.contract << setw(9);
		cout << '|' << right << setw(3) << data.kod << setw(3) << '|';

		cout << "\n";
		for (size_t i = 0; i <= 82; i++) cout << "-"; /// кінець таблиці
		fclose(file);

		_ukr(); cout << endl << "\t\tВи цей запис хотіли відредагувати ? Т/Y(так)/Н/N(ні) - ";
		cin >> var;
		cin.ignore();
		if (var == 'Т' || var == 'т' || var == 'Y' || var == 'y')
		{
			do
			{
				system("cls");
				_ukr(); cout << endl << "\tПоля які ви можете відредагувати:\n";
				_ukr(); cout << endl << "\t1. Країна\n";
				_ukr(); cout << endl << "\t2. Команда\n";
				_ukr(); cout << endl << "\t3. Вартість в млн.євро\n";
				_ukr(); cout << endl << "\t4. Термін контракту\n";
				_ukr(); cout << endl << "\t5. Код гравця\n";
				_ukr(); cout << endl << "\t0. Повернення назад";

				string _n;
				bool flag2 = 0;
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\n\tВаш вибiр - ";
					getline(cin, _n);
					if (regex_match(_n.c_str(), result_5, regular_5))
					{
						flag2 = true;
						*pn = atoi(_n.c_str());
					}
					else
					{
						_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 0 до 5!";
					}

				} while (!flag2);

				string _сhoice;
				bool flag3 = 0;

				string _team;
				regex regular4("([Є-ЯҐє-яґ]{4,13})");
				cmatch result4;
				bool flag4 = 0;

				string _сhoice1;
				bool flag5 = 0;

				string _сhoice2;
				bool flag6 = 0;

				string _transfer_cost;
				bool flag7 = 0;

				switch (*pn)
				{
				case 1:
					system("cls");

					_ukr(); cout << endl << "\t\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

					_ukr(); cout << endl << "\t\tОберіть країну зі списку: ";
					_ukr(); cout << endl << "\t\t1. Україна\n\t\t2. Аргентина\n\t\t3. Іспанія";
					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tВаш вибiр - ";
						getline(cin, _сhoice);
						if (regex_match(_сhoice.c_str(), result_3, regular_3))
						{
							flag3 = true;
							choice = atoi(_сhoice.c_str());

							if (choice == 1) strcpy_s(data.country, "Україна");
							else if (choice == 2) strcpy_s(data.country, "Аргентина");
							else strcpy_s(data.country, "Іспанія");
						}
						else
						{
							_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!";
						}

					} while (!flag3);

					fopen_s(&file, "player.dat", "r+b");
					fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);
					fwrite(&data, sizeof(team), 1, file);
					fclose(file);

					
					system_pause();
					return true;
					break;
				case 2:
					system("cls");

					_ukr(); cout << endl << "\t\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;
					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tВедіть назву команди не більше 13 символів (Наприклад: Шахтар): ";
						getline(cin, _team);
						if (regex_match(_team.c_str(), result4, regular4))
						{
							flag4 = 1;
							_ukr(); cout << endl << "\t\tВаша назва команди виглядає так - ФК " << _team;
							strcpy_s(data.team_p, _team.c_str());

						}
						else
						{
							_ukr(); cout << endl << "\t\tПомилка! Формат введення має бути таким: 'Шахтар' !!";
						}
					} while (!flag4);

					fopen_s(&file, "player.dat", "r+b");
					fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);
					fwrite(&data, sizeof(team), 1, file);
					fclose(file);

					
					system_pause();
					return true;
					break;
				case 3:
					system("cls");

					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tВедіть трансферну вартість футболіста (в млн.євро від 1 до 400): ";
						getline(cin, _transfer_cost);
						if (regex_match(_transfer_cost.c_str(), result_three_digit, regular_three_digit))
						{

							if (atoi(_transfer_cost.c_str()) < 1 || atoi(_transfer_cost.c_str()) > 400) {
								_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 400!";
							}
							else {
								flag7 = true;
								data.transfer_cost = atoi(_transfer_cost.c_str());
							}
						}
						else
						{
							_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 400!";
						}
					} while (!flag7);

					fopen_s(&file, "player.dat", "r+b");
					fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);
					fwrite(&data, sizeof(team), 1, file);
					fclose(file);

					system_pause();
					return true;
					break;
				case 4:
					system("cls");

					_ukr(); cout << endl << "\t\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

					cout << endl << "\t\tОберіть термін контракту  зі списку: ";
					cout << endl << "\t\t1. 1 рік\n\t\t2. 2 роки\n\t\t3. 3 роки";
					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tВаш вибiр - ";
						getline(cin, _сhoice1);
						if (regex_match(_сhoice1.c_str(), result_3, regular_3))
						{
							flag5 = true;
							choice = atoi(_сhoice1.c_str());

							if (choice == 1) strcpy_s(data.contract, "1");
							else if (choice == 2) strcpy_s(data.contract, "2");
							else strcpy_s(data.contract, "3");
						}
						else
						{
							_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!";
						}

					} while (!flag5);

					fopen_s(&file, "player.dat", "r+b");
					fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);
					fwrite(&data, sizeof(team), 1, file);
					fclose(file);

					system_pause();
					return true;
					break;
				case 5:
					system("cls");

					_ukr(); cout << endl << "\t\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tВедіть код гравця (0 - на продажі): ";
						getline(cin, _сhoice2);
						if (regex_match(_сhoice2.c_str(), result_three_digit, regular_three_digit))
						{
							flag6 = true;
							data.kod = atoi(_сhoice2.c_str());
							if (proverka_kod_zapus_file(data) == false)
							{
								flag6 = 0;
								_ukr(); cout << endl << "\t\tПомилка. Не вірне редагування коду, такого гравця з веденним кодом - не існує!";
							}
						}
						else
						{
							_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
						}
					} while (!flag6);

					fopen_s(&file, "player.dat", "r+b");
					fseek(file, (n_edit - 1) * sizeof(team), SEEK_SET);
					fwrite(&data, sizeof(team), 1, file);
					fclose(file);

					system_pause();
					return true;
					break;
				case 0:
					return 0;
				}
			} while (*pn != 0);
		}
		else
		{
			if (var == 'Н' || var == 'н' || var == 'N' || var == 'n')
			{
				_ukr(); cout << endl << "\t\tСпробуйте спочатку!" << endl;
			}
			else {
				_ukr(); cout << endl << "\t\tПомилка!!!";
			}
			return false;
		}
	}
}

// функція меню редагування
int menu_edit_element()
{
	int n, * pn = &n;
	do
	{
		system("color F2");
		_ukr(); cout << endl << "\tРедагування може виконуватися двома методами: \n";
		_ukr(); cout << endl << "\t1. Цілком\n";
		_ukr(); cout << endl << "\t2. За окремими полями\n";
		_ukr(); cout << endl << "\t0. Скасування редагування";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tВаш вибiр - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_2, regular_2))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 2 !!!";
			}
		} while (!flag);

		switch (*pn)
		{
		case 1:
			system("cls");
			if (full_edit_element() == true)
			{
				system("cls");
				_ukr(); cout << endl << "\tПісля редагування данні виглядають наступним чином:\n";
				review_file();
			}
			
			system_pause();
			return 0;
			break;
		case 2:
			system("cls");
			if (not_full_edit_element() == true)
			{
				system("cls");
				_ukr(); cout << endl << "\tПісля редагування данні виглядають наступним чином:\n";
				review_file();
			}
			
			system_pause();
			return 0;
			break;
		}
	} while (*pn != 0);
	if (*pn == 0)
	{
		system("cls");
		_ukr(); cout << endl << "\tРедагування записів скасовано." << endl;
		system_pause();
	}
}

// функція меню сортування
int menu_sort()
{
	int n, * pn = &n;
	do
	{
		system("cls");
		system("color F2");
		_ukr(); cout << endl << "\tСортування може виконуватися двома методами: \n";
		_ukr(); cout << endl << "\t1. Відсортувати за вартістю\n";
		_ukr(); cout << endl << "\t2. Відсортувати за країною\n";
		_ukr(); cout << endl << "\t0. Повернення до попереднього меню";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tВаш вибiр - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_2, regular_2))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 2 !!!";
			}
		} while (!flag);
		
		switch (*pn)
		{
		case 1:
			system("cls");
			_ukr(); cout << endl << "\tФайл до сортування записів.\n";
			review_file();
			system_pause();
			system("cls");
			_ukr(); cout << endl << "\tФайл після сортування записів.\n";
			sort_transfer_cost();
			review_file();
			system_pause();
			break;
		case 2:
			system("cls");
			_ukr(); cout << endl << "\tФайл до сортування записів.\n";
			review_file();
			system_pause();
			system("cls");
			_ukr(); cout << endl << "\tФайл після сортування записів.\n";
			sort_country();
			review_file();
			system_pause();
			break;
		case 0:
			return 0;
		}
	} while (*pn != 0);
}

// функція сортування за трансферною вартістю
void sort_transfer_cost()
{
	team data, data1;
	int k = 1, n;
	fopen_s(&file, "player.dat", "r+b");
	while (k)
	{
		k = 0; n = 1;
		fread(&data, sizeof(team), 1, file);
		while (fread(&data1, sizeof(team), 1, file) == 1)
		{
			n++;
			if (data.transfer_cost > data1.transfer_cost)
			{
				fseek(file, (n - 2) * sizeof(team), SEEK_SET);
				fwrite(&data1, sizeof(team), 1, file);
				fseek(file, (n - 1) * sizeof(team), SEEK_SET);
				fwrite(&data, sizeof(team), 1, file);
				k = 1;
			}
			else data = data1;
			fseek(file, n * sizeof(team), SEEK_SET);
		}
		rewind(file);
	}
	fclose(file);
}

// функція сортування за країною
void sort_country()
{
	setlocale(LC_ALL, "ukrainian");
	team data, data1;
	int k = 1, n;
	fopen_s(&file, "player.dat", "r+b");
	while (k)
	{
		k = 0; n = 1;
		fread(&data, sizeof(team), 1, file);
		while (fread(&data1, sizeof(team), 1, file) == 1)
		{
			n++;
			if (strcoll(data.country, data1.country) > 0)
			{
				fseek(file, (n - 2) * sizeof(team), SEEK_SET);
				fwrite(&data1, sizeof(team), 1, file);
				fseek(file, (n - 1) * sizeof(team), SEEK_SET);
				fwrite(&data, sizeof(team), 1, file);
				k = 1;
			}
			else data = data1;
			fseek(file, n * sizeof(team), SEEK_SET);
		}
		rewind(file);
	}
	fclose(file);
	_ukr();
}

// функція введення дати
time_t vvod_data_of_birth()
{
	int day, mon, year;
	time_t data;
	struct tm t_data;
	data = time(NULL);
	localtime_s(&t_data, &data);

	string _day;
	
	bool flag = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\n\t\tВведіть день - ";
		getline(cin, _day);
		if (regex_match(_day.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_day.c_str()) < 1 || atoi(_day.c_str()) > 31) {
				_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 31!";
			}
			else {
				flag = true;
				day = atoi(_day.c_str());
				t_data.tm_mday = day;
			}
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 31!";
		}
	} while (!flag);

	string _mon;
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\n\t\tВведіть місяць - ";
		getline(cin, _mon);
		if (regex_match(_mon.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_mon.c_str()) < 1 || atoi(_mon.c_str()) > 12) {
				_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 12!";
			}
			else {
				flag1 = true;
				mon = atoi(_mon.c_str());
				t_data.tm_mon = mon - 1;
			}
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 12!";
		}
	} while (!flag1);

	string _year;
	
	bool flag2 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\n\t\tВведіть рік - ";
		getline(cin, _year);
		if (regex_match(_year.c_str(), result_four_digit, regular_four_digit))
		{
			flag2 = true;
			year = atoi(_year.c_str());
			t_data.tm_year = year - 1900;
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа, рік в форматі - 1972 !";
		}
	} while (!flag2);

	data = mktime(&t_data);
	return data;
}

// функція додавання записів в файл Команди
void add_data()
{
	team data;
	int n, * pn = &n;
	bool flag6 = 0;
	_ukr(); cout << endl << "\t\t\t\t\t\tДодавання нових записів у файл:\n" << endl;

	string _pn;
	bool flag1 = 0;
	
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\t\tВедіть кількість нових записів або 0 для скасування (не більше 15): ";
		getline(cin, _pn);
		if (regex_match(_pn.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_pn.c_str()) < 1 || atoi(_pn.c_str()) > 15) {
				_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 15!" << endl;
			}
			else {
				flag1 = true;
				*pn = atoi(_pn.c_str());
			}
		}
		else
		{
			_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!" << endl;
		}

	} while (!flag1);


	if (*pn != 0)
	{
		for (int i = 0; i < *pn; i++)
		{
			system("cls");
			_ukr();
			int choice;
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "\t\tВедення " << i + 1 << " запису (загалом " << *pn << "):" << endl;

			string _сhoice;
			bool flag2 = 0;

			_ukr(); cout << endl << "\t\tОберіть країну зі списку: ";
			_ukr(); cout << endl << "\t\t1. Україна\n\t\t2. Аргентина\n\t\t3. Іспанія";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice);
				if (regex_match(_сhoice.c_str(), result_3, regular_3))
				{
					flag2 = true;
					choice = atoi(_сhoice.c_str());

					if (choice == 1) strcpy_s(data.country, "Україна");
					else if (choice == 2) strcpy_s(data.country, "Аргентина");
					else strcpy_s(data.country, "Іспанія");
				}
				else
				{
					_ukr(); cout << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!" << endl;
				}

			} while (!flag2);

			string _team;
			regex regular("([Є-ЯҐє-яґ]{4,13})");
			cmatch result;
			bool flag = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть назву команди не більше 13 символів (Наприклад: Шахтар): "; 
				getline(cin, _team);
				if (regex_match(_team.c_str(), result, regular))
				{
					flag = 1;
					_ukr(); cout << endl << "\t\tВаша назва команди виглядає так - ФК " << _team;
					 strcpy_s(data.team_p, _team.c_str());
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка! Формат введення має бути таким: 'Шахтар' !!" << endl;
				}
			} while (!flag);

			string _transfer_cost;
			bool flag3 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть трансферну вартість футболіста (в млн.євро від 1 до 400): ";
				getline(cin, _transfer_cost);
				if (regex_match(_transfer_cost.c_str(), result_three_digit, regular_three_digit))
				{

					if (atoi(_transfer_cost.c_str()) < 1 || atoi(_transfer_cost.c_str()) > 400) {
						_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 400!" << endl;
					}
					else {
						flag3 = true;
						data.transfer_cost = atoi(_transfer_cost.c_str());
					}
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 400!" << endl;
				}
			} while (!flag3);

			string _сhoice1;
			bool flag4 = 0;

			_ukr();
			cout << endl << "\t\tОберіть термін контракту  зі списку: ";
			cout << endl << "\t\t1. 1 рік\n\t\t2. 2 роки\n\t\t3. 3 роки";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice1);
				if (regex_match(_сhoice1.c_str(), result_3, regular_3))
				{
					flag4 = true;
					choice = atoi(_сhoice1.c_str());

					if (choice == 1) strcpy_s(data.contract, "1");
					else if (choice == 2) strcpy_s(data.contract, "2");
					else strcpy_s(data.contract, "3");
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!" << endl;
				}

			} while (!flag4);

			string _сhoice2;
			bool flag5 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть код гравця (0 - на продажі): ";
				getline(cin, _сhoice2);
				if (regex_match(_сhoice2.c_str(), result_three_digit, regular_three_digit))
				{
					flag5 = true;
					data.kod = atoi(_сhoice2.c_str());
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!" << endl;
				}
			} while (!flag5);

			
			
			if (proverka_zapusy_file(data) == false)
			{
				flag6 = 1;
				fopen_s(&file, "player.dat", "a+b");
				fwrite(&data, sizeof(team), 1, file);
				fclose(file);
			}

		}
		if (flag6 == 1)
		{
			_ukr();
			cout << endl << "\t\tДодана така кількість записів - " << *pn << " !";
		}
	}
	else
	{
		_ukr(); cout << endl << "\t\tДодавання нових записів у файл скасовано.";
	}
	cout << endl << endl << endl;
}

// функція меню файла Гравці
int menu_file_1()
{
	int n, * pn = &n;
	player data;
	do {
		system("color F5");
		system("cls");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\tГоловне меню файла 'Гравці'\n\n";
		_ukr(); cout << endl << "\t1. Створення нового файлу\n";
		_ukr(); cout << endl << "\t2. Перегляд існуючого файлу\n";
		_ukr(); cout << endl << "\t3. Додавання даних у файл\n";
		_ukr(); cout << endl << "\t4. Редагування даних за кодом запису\n";
		_ukr(); cout << endl << "\t5. Видалення записів за кодом запису\n";
		_ukr(); cout << endl << "\t0. Повернення до попереднього меню";

		string _n;
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tВаш вибiр - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_5, regular_5))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 5 !!!";
			}
		} while (!flag);
		
		switch (*pn)
		{
		case 1:
			system("cls");
			new_file_1();
			break;
		case 2:
			system("cls");

			fopen_s(&file_1, "player_1.dat", "rb");
			if (!file_1) {
				_ukr(); cout << endl << "\t\tПомилка. Створіть файл!";
			}
			else
			{
				if ((fread(&data, sizeof(player), 1, file_1)) == NULL)
				{
					_ukr(); cout << endl << "\t\tПомилка. Файл порожній!";
					fclose(file_1);
				}
				else
				{
					fclose(file_1);
					review_file_1();
				}
			}

			system_pause();
			break;
		case 3:
			system("cls");
			add_data_file_1();
			system_pause();
			break;
		case 4:
			system("cls");

			fopen_s(&file_1, "player_1.dat", "rb");
			if (!file_1) {
				_ukr(); cout << endl << "\t\tПомилка. Створіть файл!";
			}
			else
			{
				if ((fread(&data, sizeof(player), 1, file_1)) == NULL)
				{
					_ukr(); cout << endl << "\t\tПомилка. Файл порожній!";
					fclose(file_1);
				}
				else
				{
					fclose(file_1);
					edit_kod_file_1();
				}
			}

			system_pause();
			break;
		case 5:
			system("cls");

			fopen_s(&file_1, "player_1.dat", "rb");
			if (!file_1) {
				_ukr(); cout << endl << "\t\tПомилка. Створіть файл!";
			}
			else
			{
				if ((fread(&data, sizeof(player), 1, file_1)) == NULL)
				{
					_ukr(); cout << endl << "\t\tПомилка. Файл порожній!";
					fclose(file_1);
				}
				else
				{
					fclose(file_1);
					del_kod_file_1();
				}
			}

			system_pause();
			break;
		case 0:
			return 0;
		}
	} while (*pn != 0);
}

// функція створення нового файла Гравці
void new_file_1()
{
	const char file_new[] = "player_1.dat";
	fopen_s(&file_1, file_new, "rb");
	if (!file_1)
	{
		_ukr(); cout << "\t\tСтворюємо новий файл." << endl;
		fopen_s(&file_1, file_new, "wb");
		_ukr(); cout << "\t\tФайл успішно створнено!" << endl;
		system_pause();
	}
	else
	{
		_ukr(); cout << "\t\tІснує файл з певними даними!" << endl;
		system_pause();
	}
	fclose(file_1);
}

// функція перегляду файла Гравці
void review_file_1()
{
	player data;
	int num(0);
	table_cap_table();  //// шапка та заголовок таблиці
	fopen_s(&file_1, "player_1.dat", "rb");	
	while (fread(&data, sizeof(player), 1, file_1))
	{
		struct tm t_data;
		cout << endl << '|' << right << setw(3) << data.kod << setw(3);

		cout << '|' << left << setw(19) << data.first_second_name_player << setw(4);
		localtime_s(&t_data, &(data.date_of_birth));
		char full_data_of_birth[10];
		strftime(full_data_of_birth, 10, "%x", &t_data);
		cout << '|' << right << setw(9) << full_data_of_birth << setw(6);
		cout << '|' << right << setw(4) << data.sex << setw(4);
		cout << '|' << left << setw(14) << data.nationality;
		cout << '|' << right << setw(5) << data.role << setw(4);
		cout << '|' << right << setw(3) << data.kol_games <<  setw(2) << '|';
	}
	fclose(file_1);
	cout << "\n";
	for (size_t i = 0; i <= 81; i++) cout << "-";  /// кінець таблиці
}

// функція шапки таблиці - Гравці
void table_cap_table()
{
	player data;
	size_t total_kol(0), kol_role_vr(0), kol_role_lp(0), kol_role_cf(0);
	_ukr(); cout << "\t\t\t\t\tДетальна інформація про гравців FIFA!" << endl;

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1))
	{
		total_kol++;
		if (strcmp(data.role, "ВР") == 0) kol_role_vr++;
		if (strcmp(data.role, "ЛП") == 0) kol_role_lp++;
		if (strcmp(data.role, "ЦФ") == 0) kol_role_cf++;
	};
	_ukr(); cout << "\n\tКоротка інформація файла: \n\n";
	_ukr(); cout << "\tКількість записів в файлі -> " << total_kol << endl;
	_ukr(); cout << "\tКількість амплуа 'ВР' -> " << kol_role_vr << endl;
	_ukr(); cout << "\tКількість амплуа 'ЛП' -> " << kol_role_lp << endl;
	_ukr(); cout << "\tКількість амплуа 'ЦФ' -> " << kol_role_cf << endl;
	fclose(file_1);

	cout << "\n";
	for (size_t i = 0; i <= 81; i++) cout << "-";
	_ukr(); cout << "\n| Код |" << "         П.І.      |" << " Дата народження |";
	_ukr(); cout << " Стать |" << " Громадянство |" << " Амплуа |" << " KG |" << endl;
	for (size_t i = 0; i <= 81; i++) cout << "-";
}

// функція на наявність ідентичного запису в файлі - Гравці
bool proverka_zapusy_file_1(player data)
{
	player data1;
	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data1, sizeof(player), 1, file_1))
	{
		if (data.kod == data1.kod)
		{
			fclose(file_1);
			cout << "\t\tВведений запис існує в файлі!" << endl;
			return true;
		}
	};
	fclose(file_1);
	return false;
}

// функція додавання записів в файл Гравці
void add_data_file_1()
{
	player data;
	int num(0);
	int n, * pn = &n;
	bool flag6 = 0;

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1))
	{
		num = data.kod;
	}
	fclose(file_1); 

	_ukr(); cout << endl << "\t\t\t\t\t\tДодавання нових записів у файл 'Гравці' :\n" << endl;
	cin.ignore(cin.rdbuf()->in_avail());

	string _pn;
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\t\tВедіть кількість нових записів або 0 для скасування (не більше 15): ";
		getline(cin, _pn);
		if (regex_match(_pn.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_pn.c_str()) < 1 || atoi(_pn.c_str()) > 15) {
				_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 15!" << endl;
			}
			else {
				flag1 = true;
				*pn = atoi(_pn.c_str());
			}
		}
		else
		{
			_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!" << endl;
		}

	} while (!flag1);

	if (*pn != 0)
	{
		for (int i = 0; i < *pn; i++)
		{
			system("cls");
			_ukr();
			int choice = 0;
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "\t\tВедення " << i + 1 << " запису (загалом " << *pn << "):" << endl;
			
			++num;
			
			string name_player;
			regex regular("([Є-ЯҐє-яґ]+?)( )([Є-ЯҐє-яґ]+?)");
			cmatch result;
			bool flag = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВедіть прізвище та ім'я гравця (Наприклад: Ярмоленко Андрій): "; 
				getline(cin, name_player);  
				if (regex_match(name_player.c_str(), result, regular))
				{
					flag = 1;
					cout << "\t\tВаше прізвище та ім'я гравця виглядає так - " << name_player;
					strcpy_s(data.first_second_name_player, name_player.c_str());
				}
				else
				{
					cout << "\t\tПомилка! Формат введення має бути таким: 'Ярмоленко Андрій' !!";
				}
			} while (!flag);

			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\t\tВедіть дату народження футболіста:" << endl;
			data.date_of_birth = vvod_data_of_birth();

			string _сhoice;
			bool flag2 = 0;
			_ukr();
			cout << endl << "\n\t\tОберіть стать гравця: ";
			cout << endl << "\t\t1. 'ж' – жіноча\n\t\t2. 'ч' – чоловіча";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice);
				if (regex_match(_сhoice.c_str(), result_2, regular_2))
				{
					flag2 = true;
					choice = atoi(_сhoice.c_str());

					if (choice == 1) strcpy_s(data.sex, "Ж");
					else strcpy_s(data.sex, "Ч");
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 2!" << endl;
				}

			} while (!flag2);

			string _сhoice1;
			bool flag3 = 0;
			cout << endl << "\n\t\tОберіть громадянство зі списку: ";
			cout << endl << "\t\t1. Україна\n\t\t2. Аргентина\n\t\t3. Іспанія";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice1);
				if (regex_match(_сhoice1.c_str(), result_3, regular_3))
				{
					flag3 = true;
					choice = atoi(_сhoice1.c_str());

					if (choice == 1) strcpy_s(data.nationality, "Україна");
					else if (choice == 2) strcpy_s(data.nationality, "Аргентина");
					else strcpy_s(data.nationality, "Іспанія");
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!" << endl;
				}

			} while (!flag3);

			string _сhoice2;
			bool flag4 = 0;
			cout << endl << "\n\t\tОберіть амплуа зі списку: ";
			cout << endl << "\t\t1. ВР – воротар\n\t\t2. ЛП – лівий півзахисник\n\t\t3. ЦФ – центр форвард";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tВаш вибiр - ";
				getline(cin, _сhoice2);
				if (regex_match(_сhoice2.c_str(), result_3, regular_3))
				{
					flag4 = true;
					choice = atoi(_сhoice2.c_str());

					if (choice == 1) strcpy_s(data.role, "ВР");
					else if (choice == 2) strcpy_s(data.role, "ЛП");
					else strcpy_s(data.role, "ЦФ");
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!" << endl;
				}

			} while (!flag4);

			string _kol_games;
			bool flag5 = 0;

			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\n\t\tВедіть кількість проведених ігор (KG)  футболіста (від 1 до 150): ";
				getline(cin, _kol_games);
				if (regex_match(_kol_games.c_str(), result_three_digit, regular_three_digit))
				{

					if (atoi(_kol_games.c_str()) < 1 || atoi(_kol_games.c_str()) > 150) {
						_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 150!" << endl;
					}
					else {
						flag5 = true;
						data.kol_games = atoi(_kol_games.c_str());
					}
				}
				else
				{
					_ukr(); cout  << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 150!" << endl;
				}
			} while (!flag5);

			data.kod = num;
			
			if (proverka_zapusy_file_1(data) == false)
			{
				flag6 = 1;
				fopen_s(&file_1, "player_1.dat", "a+b");
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);
			}
		}
		if (flag6 == 1)
		{
			_ukr();
			cout << endl << "\t\tДодана така кількість записів - " << *pn << " !";
		}
	}
	else
	{
		_ukr(); cout << endl << "\t\tДодавання нових записів у файл скасовано.";
	}
	cout << endl << endl << endl;
}

// функція редагування файла Гравці
int edit_kod_file_1()
{
	player data;
	size_t num = 0, n_edit;
	char var;
	int n, * pn = &n;
	int choice;

	string _n_edit;
	bool flag = 0;
	do {
		cout << endl;
		review_file_1();
		cout << endl;
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\n\tВведіть код запису, який необхідно редагувати - ";
		getline(cin, _n_edit);
		if (regex_match(_n_edit.c_str(), result_three_digit, regular_three_digit))
		{
			flag = true;
			n_edit = atoi(_n_edit.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
		}

	} while (!flag);

	size_t num1 = 0, temp = 0;
	bool flag1 = 0;
	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1))
	{
		if (data.kod != n_edit)
		{
			num1++;
		}
		else
		{
			temp = data.kod;
			break;
		}
	};
	if (temp == 0)
	{
		_ukr();
		cout << "\t\tПомилка. Введеного коду не існує!" << endl;
		return 0;
	}

	system("cls");
	fseek(file_1, num1 * sizeof(player), SEEK_SET);

	fread(&data, sizeof(player), 1, file_1);
	cout << "\n";
	for (size_t i = 0; i <= 83; i++) cout << "-";
	_ukr(); cout << "\n| Код |" << "         П.І.      |" << " Дата народження |";
	_ukr(); cout << " Стать |" << "  Громадянство  |" << " Амплуа |" << " KG |" << endl;
	for (size_t i = 0; i <= 83; i++) cout << "-";

	struct tm t_data;
	cout << endl << '|' << setw(3) << data.kod << setw(3);
	cout << '|' << left << setw(19) << data.first_second_name_player << setw(4);
	localtime_s(&t_data, &(data.date_of_birth));
	char full_data_of_birth[10];
	strftime(full_data_of_birth, 10, "%x", &t_data);
	cout << '|' << right << setw(9) << full_data_of_birth << setw(6);
	cout << '|' << right << setw(4) << data.sex << setw(4);
	cout << '|' << left << setw(16) << data.nationality;
	cout << '|' << right << setw(5) << data.role << setw(4);
	cout << '|' << right << setw(3) << data.kol_games << setw(2) << '|';

	cout << "\n";
	for (size_t i = 0; i <= 83; i++) cout << "-";  /// кінець таблиці

	fclose(file_1);

	_ukr(); cout << endl << "\n\tВи цей запис хотіли відредагувати ? Т/Y(так)/Н/N(ні) - ";
	cin >> var;
	cin.ignore();
	if (var == 'Т' || var == 'т' || var == 'Y' || var == 'y')
	{
		do
		{
			system("cls");
			_ukr(); cout << endl << "\tПоля які ви можете відредагувати:\n";
			_ukr(); cout << endl << "\t1. П.І.\n";
			_ukr(); cout << endl << "\t2. Дата народження\n";
			_ukr(); cout << endl << "\t3. Стать\n";
			_ukr(); cout << endl << "\t4. Громадянство\n";
			_ukr(); cout << endl << "\t5. Амплуа\n";
			_ukr(); cout << endl << "\t6. KG - кількість проведених ігор\n";
			_ukr(); cout << endl << "\t0. Повернення до попереднього меню";

			string _n;
			bool flag0 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\n\tВаш вибiр - ";
				getline(cin, _n);
				if (regex_match(_n.c_str(), result_6, regular_6))
				{
					flag0 = 1;
					*pn = atoi(_n.c_str());
				}
				else
				{
					_ukr(); cout << endl << "\t\tПомилка! Введення має бути цифровим і ніяким іншим, числа від 0 до 6 !!!";
				}
			} while (!flag0);

			string name_player;
			regex regular1("([Є-ЯҐє-яґ]+?)( )([Є-ЯҐє-яґ]+?)");
			cmatch result1;
			bool flag1 = 0;

			string _сhoice;
			bool flag2 = 0;

			string _сhoice1;
			bool flag3 = 0;

			string _kol_games;
			bool flag4 = 0;

			switch (*pn)
			{
			case 1:
				system("cls");

				_ukr(); cout << endl << "\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\n\tВедіть прізвище та ім'я гравця (Наприклад: Ярмоленко Андрій): ";
					getline(cin, name_player);
					if (regex_match(name_player.c_str(), result1, regular1))
					{
						flag1 = 1;
						cout << "\n\tВаше прізвище та ім'я гравця виглядає так - " << name_player;
						strcpy_s(data.first_second_name_player, name_player.c_str());
					}
					else
					{
						cout << "\n\tПомилка! Формат введення має бути таким: 'Ярмоленко Андрій' !!";
					}
				} while (!flag1);

				fopen_s(&file_1, "player_1.dat", "r+b");
				fseek(file_1, num1 * sizeof(player), SEEK_SET);
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);

				system_pause();
				break;
			case 2:
				system("cls");

				_ukr(); cout << endl << "\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\n\tВедіть дату народження футболіста: ";
				data.date_of_birth = vvod_data_of_birth();

				fopen_s(&file_1, "player_1.dat", "r+b");
				fseek(file_1, num1 * sizeof(player), SEEK_SET);
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);

				system_pause();
				break;
			case 3:
				system("cls");

				_ukr();
				cout << endl << "\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

				cout << endl << "\n\t\tОберіть стать гравця: ";
				cout << endl << "\t\t1. 'ж' – жіноча\n\t\t2. 'ч' – чоловіча";
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\t\tВаш вибiр - ";
					getline(cin, _сhoice);
					if (regex_match(_сhoice.c_str(), result_2, regular_2))
					{
						flag2 = true;
						choice = atoi(_сhoice.c_str());

						if (choice == 1) strcpy_s(data.sex, "Ж");
						else strcpy_s(data.sex, "Ч");
					}
					else
					{
						_ukr(); cout << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 2!" << endl;
					}

				} while (!flag2);

				fopen_s(&file_1, "player_1.dat", "r+b");
				fseek(file_1, num1 * sizeof(player), SEEK_SET);
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);

				system_pause();
				break;
			case 4:
				system("cls");

				_ukr();
				cout << endl << "\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

				cout << endl << "\n\t\tОберіть громадянство зі списку: ";
				cout << endl << "\t\t1. Україна\n\t\t2. Аргентина\n\t\t3. Іспанія";
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\t\tВаш вибiр - ";
					getline(cin, _сhoice1);
					if (regex_match(_сhoice1.c_str(), result_3, regular_3))
					{
						flag3 = true;
						choice = atoi(_сhoice1.c_str());

						if (choice == 1) strcpy_s(data.nationality, "Україна");
						else if (choice == 2) strcpy_s(data.nationality, "Аргентина");
						else strcpy_s(data.nationality, "Іспанія");
					}
					else
					{
						_ukr(); cout << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!" << endl;
					}

				} while (!flag3);

				fopen_s(&file_1, "player_1.dat", "r+b");
				fseek(file_1, num1 * sizeof(player), SEEK_SET);
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);

				system_pause();
				break;
			case 5:
				system("cls");

				_ukr();
				cout << endl << "\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

				cout << endl << "\n\t\tОберіть амплуа зі списку: ";
				cout << endl << "\t\t1. ВР – воротар\n\t\t2. ЛП – лівий півзахисник\n\t\t3. ЦФ – центр форвард";
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\t\tВаш вибiр - ";
					getline(cin, _сhoice1);
					if (regex_match(_сhoice1.c_str(), result_3, regular_3))
					{
						flag3 = true;
						choice = atoi(_сhoice1.c_str());

						if (choice == 1) strcpy_s(data.role, "ВР");
						else if (choice == 2) strcpy_s(data.role, "ЛП");
						else strcpy_s(data.role, "ЦФ");
					}
					else
					{
						_ukr(); cout << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 3!" << endl;
					}

				} while (!flag3);

				fopen_s(&file_1, "player_1.dat", "r+b");
				fseek(file_1, num1 * sizeof(player), SEEK_SET);
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);

				system_pause();
				break;
			case 6:
				system("cls");

				_ukr();
				cout << endl << "\t\tЛюбий користувачу, вводимо нові данні данного поля!" << endl;

				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\n\t\tВедіть кількість проведених ігор (KG)  футболіста (від 1 до 150): ";
					getline(cin, _kol_games);
					if (regex_match(_kol_games.c_str(), result_three_digit, regular_three_digit))
					{

						if (atoi(_kol_games.c_str()) < 1 || atoi(_kol_games.c_str()) > 150) {
							_ukr(); cout << "\n\t\tПомилка. Ви маєте можливість використовувати числа від 1 до 150!" << endl;
						}
						else {
							flag4 = true;
							data.kol_games = atoi(_kol_games.c_str());
						}
					}
					else
					{
						_ukr(); cout << "\n\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа від 1 до 150!" << endl;
					}
				} while (!flag4);

				fopen_s(&file_1, "player_1.dat", "r+b");
				fseek(file_1, num1 * sizeof(player), SEEK_SET);
				fwrite(&data, sizeof(player), 1, file_1);
				fclose(file_1);

				system_pause();
				break;
			case 0:
				return 0;
			}
		} while (*pn != 0);
	}
	else
	{
		if (var == 'Н' || var == 'н' || var == 'N' || var == 'n')
		{
			_ukr(); cout << endl << "\n\tСпробуйте спочатку!" << endl;
		}
		else {
			_ukr(); cout << endl << "\n\tПомилка!!!";
		}
		return 0;
	}
}

// функція видалення записів з файла Гравці
void del_kod_file_1()
{
	player data;
	team data1;
	size_t num = 0, n_del;
	FILE* filehelply_1;
	size_t total_kol(0);

	string _n_del;
	bool flag1 = 0;
	do {
		review_file_1();
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\n\tВведіть код гравця, який необхідно видалити - ";
		getline(cin, _n_del);

		if (regex_match(_n_del.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_del = atoi(_n_del.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tПомилка. Ви маєте можливість використовувати ТІЛЬКИ числа!";
		}

	} while (!flag1);


	fopen_s(&file_1, "player_1.dat", "rb");
	fopen_s(&filehelply_1, "player_helply_1.dat", "w+b");
	size_t temp = 0;

	while (fread(&data, sizeof(player), 1, file_1) == 1)
	{
		if (data.kod != n_del)
		{
			fwrite(&data, sizeof(player), 1, filehelply_1);
		}
		else
		{
			temp = data.kod;
		}
	}
	if (temp == 0)
	{
		_ukr();
		cout << endl << "\t\tПомилка. Введеного коду не існує!" << endl;
	}
	fclose(file_1);
	fclose(filehelply_1);
	remove("player_1.dat");
	rename("player_helply_1.dat", "player_1.dat");

	fopen_s(&file, "player.dat", "r+b");
	size_t num1 = 0;

	while (fread(&data1, sizeof(team), 1, file) == 1)
	{
		num1++;
		if (data1.kod == temp)
		{
			data1.kod = 0;
			fseek(file, (num1 - 1) * sizeof(team), SEEK_SET);
			fwrite(&data1, sizeof(team), 1, file);
			break;
		}
	}
	fclose(file);
}