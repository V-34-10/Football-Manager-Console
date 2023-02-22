system("chcp 1251");
// Íåîáõ³äí³ á³áë³îòåêè
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
struct player // ñòðóêòóðà äàíèõ - ãðàâåöü
{	
	char first_second_name_player[20]; // Ï.². ãðàâöÿ
	time_t date_of_birth; // Äàòà íàðîäæåííÿ 
	char sex[5]; // ñòàòü ãðàâöÿ (ââîäèòüñÿ ç êëàâ³àòóðè «æ» – æ³íî÷à, «÷» – ÷îëîâ³÷à).
	char nationality[15]; // ãðîìàäÿíñòâî
	char role[4]; // Àìïëóà(îáèðàºòüñÿ ç³ ñïèñêó : ÂÐ – âîðîòàð, ËÏ – ë³âèé ï³âçàõèñíèê, ÖÔ – öåíòð ôîðâàðä)
	size_t kol_games; // KG – ê³ëüê³ñòü ïðîâåäåíèõ ³ãîð 
	size_t kod; // Êîä ãðàâöÿ
};

struct team // ñòðóêòóðà äàíèõ - êîìàíäà
{
	char country[15]; // êðà¿íà
	char team_p[15]; // êîìàíäà ãðàâöÿ
	size_t transfer_cost; // Òðàíñôåðíà âàðò³ñòü ôóòáîë³ñòà 
	char contract[10]; // Òåðì³í êîíòðàêòó (îáèðàºòüñÿ ç³ ñïèñêó: 1 ð³ê, 2 ðîêè, 3 ðîêè).
	size_t kod; // Êîä ãðàâöÿ
};

// ôóíêö³ÿ çàãðóçî÷íîãî ³íäèêàòîðà
void progress_bar(int percents) 
{
	int half = percents / 2;
	printf("\r\t\t\t\t\t[");
	for (int i = 0; i < half; ++i) putc('#', stdout);
	for (int i = 0; i < 50 - half; ++i) putc(' ', stdout);
	printf("] %3d %%", percents);
	fflush(stdout);
}

// ôóíêö³ÿ ëîêàë³çàö³¿
void _ukr() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

// Ïðîòîòèïè ôóíêö³é
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

// øàáëîíè äëÿ ïåðåâ³ðêè ââåäåíèõ äàíèõ
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

// Äâà ôàéëè: file - ôàéë Êîìàíäà, file_1 - ôàéë Ãðàâö³
FILE* file;
FILE* file_1;

int main()
{
	
	_ukr();
	system("color F4");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n ");
	_ukr(); cout << "\t\t\t\t\t Äîáðî ïîæàëîâàòü äî îáë³êó äàíèõ ôóòáîë³ñò³â FIFA! " << endl;
	for (int i = 0; i <= 100; ++i) {
		progress_bar(i);
		Sleep(50);
	}
	Sleep(3500);
	MENU();
	return 0;
}

// ôóíêö³ÿ íà íàÿâí³ñòü ³äåíòè÷íîãî çàïèñó â ôàéë³ - Êîìàíäè
bool proverka_zapusy_file(team data)
{
	team data1;
	fopen_s(&file, "player.dat", "rb");
	while (fread(&data1, sizeof(team), 1, file))
	{
		if (data.kod == data1.kod)
		{
			fclose(file);
			cout << "\t\tÂâåäåíèé çàïèñ ³ñíóº â ôàéë³!" << endl;
			return true;
		}
	};
	fclose(file);
	return false;
}

// ôóíêö³ÿ - ïàóçà
void system_pause()
{
	cout << endl << "\t\tÄëÿ ïðîäîâæåíÿ íàòèñí³òü áóäü-ÿêó êëàâ³øó...";
	_getch();
}

// ôóíêö³ÿ ãîëîâíîãî ìåíþ
void MENU()
{
	int n, * pn = &n;
	do
	{
		system("cls");
		system("color F6");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\t\t\tÃîëîâíå ìåíþ\n";
		_ukr(); cout << endl << "\t1. Ôàéë 'Êîìàíäà'\n";
		_ukr(); cout << endl << "\t2. Ôàéë 'Ãðàâö³'\n";
		_ukr(); cout << endl << "\t0. Âèõ³ä ç ïðîãðàìè";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tÂàø âèáið - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_2, regular_2))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 2!!!";
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
		_ukr(); cout << endl << "\t\t\t\t\t\tÄî ïîáà÷åííÿ!!! ";
		_ukr(); cout << endl << "\t\t\t\tÄÿêóþ çà âèêîðèñòàííÿ îáë³êó äàíèõ ôóòáîë³ñò³â FIFA!";
	}
}

// ôóíêö³ÿ ìåíþ ôàéëà - Êîìàíäè
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
		_ukr(); cout << endl << "\t\t\t\t\t\tÃîëîâíå ìåíþ ôàéëà 'Êîìàíäà'\n";
		_ukr(); cout << endl << "\t1. Ñòâîðåííÿ íîâîãî ôàéëó\n";
		_ukr(); cout << endl << "\t2. Ïåðåãëÿä ³ñíóþ÷îãî ôàéëó\n";
		_ukr(); cout << endl << "\t3. Äîäàâàííÿ äàíèõ ó ôàéë\n";
		_ukr(); cout << endl << "\t4. Ðåäàãóâàííÿ çàïèñ³â (ÿê ö³ëêîì, òàê ³ çà îêðåìèìè ïîëÿìè)\n";
		_ukr(); cout << endl << "\t5. Âèäàëåííÿ çàïèñ³â (çà ¹ ï/ï)\n";
		_ukr(); cout << endl << "\t6. Ñîðòóâàííÿ ³íôîðìàö³¿ (çà äâîìà îçíàêàìè: çà âàðò³ñòþ òà çà êðà¿íîþ)\n";
		_ukr(); cout << endl << "\t7. Âèêîíàííÿ çàïèò³â\n";
		_ukr(); cout << endl << "\t0. Ïîâåðíåííÿ äî ïîïåðåäíüîãî ìåíþ";
		
		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tÂàø âèáið - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_7, regular_7))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 7 !!!";
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
				_ukr(); cout << endl << "\n\t\tÏîìèëêà. Ñòâîð³òü ôàéë!";
			}
			else
			{

				if ((fread(&data, sizeof(team), 1, file)) == NULL)
				{
					_ukr(); cout << endl << "\n\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\n\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
			}
			else fclose(file); 
			menu_edit_element();
			
			break;
		case 5:
			system("cls");

			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
			}
			else
			{
				fclose(file);
				_ukr(); cout << endl << "\n\tÔàéë äî âèäàëåííÿ çàïèñ³â:\n\n";
				review_file();
				system_pause();
				if (del_element() == true)
				{
					system("cls");
					_ukr(); cout << endl << "\n\tÔàéë ï³ñëÿ âèäàëåííÿ çàïèñ³â:\n";
					review_file();
				}
				else {
					_ukr(); cout << endl << "\n\t\tÔàéë íå çì³íèâñÿ!";
				}
			}

			system_pause();
			break;
		case 6:
			system("cls");

			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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

// ôóíêö³ÿ ìåíþ çàïèò³â
int menu()
{
	team data;
	int n, * pn = &n;
	do {
		system("color F0");
		system("cls");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\tÌåíþ çàïèò³â\n\n";
		_ukr(); cout << endl << "\t1. Ï³äðàõóâàòè ê³ëüê³ñòü ãðàâö³â, ÿê³ çíàõîäÿòüñÿ ó îñíîâíîìó ôàéë³,";
		_ukr(); cout << endl << "\tïî êîæí³é ñòàò³\n";
		_ukr(); cout << endl << "\t2. Âèâåäåííÿ äàíèõ ïðî ãðàâö³â, ó ÿêèõ òåðì³í êîíòðàêòó äîð³âíþº";
		_ukr(); cout << endl << "\tçíà÷åííþ ââåäåíîìó ç êëàâ³àòóðè\n";
		_ukr(); cout << endl << "\t3. Âèâåäåííÿ äàíèõ ïðî âñ³õ ãðàâö³â, ãðîìàäÿíñòâî ÿêèõ áóëî îáðàíî";
		_ukr(); cout << endl << "\têîðèñòóâà÷åì\n";
		_ukr(); cout << endl << "\t4. Ï³äðàõóâàòè çàãàëüíó âàðò³ñòü ïî êîæíîìó ãðàâöþ,";
		_ukr(); cout << endl << "\tó ÿêîãî º êîíòðàêò\n";
		_ukr(); cout << endl << "\t5. Çíàéòè, äå ïðàöþº ãðàâåöü/ãðàâö³,";
		_ukr(); cout << endl << "\tçà ìàêñèìàëüíîþ ê³ëüê³ñòþ ³ãîð\n";
		_ukr(); cout << endl << "\t0. Ïîâåðíåííÿ äî ïîïåðåäíüîãî ìåíþ";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tÂàø âèáið - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_5, regular_5))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 5 !!!";
			}
		} while (!flag);

		switch (*pn)
		{
		case 1:
			system("cls");
			fopen_s(&file, "player.dat", "rb");
			if ((fread(&data, sizeof(team), 1, file)) == NULL)
			{
				_ukr(); cout << endl << "\n\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\n\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\n\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\n\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\n\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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

// ôóíêö³ÿ çàïèòó - ï³äðàõóíîê ê³ëüêîñò³ ïî ñòàò³
void kol_sex_file_1()
{
	player data;
	size_t kol_sex_m(0), kol_sex_w(0);
	_ukr(); cout << endl << "\t\tÐåçóëüòàòè âàøîãî çàïèòó: \n\n";
	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1))
	{
		if (strcmp(data.sex, "×") == 0) kol_sex_m++;
		if (strcmp(data.sex, "Æ") == 0) kol_sex_w++;
	};
	_ukr(); cout << "\t\tÊ³ëüê³ñòü ãðàâö³â ÷îëîâ³÷î¿ ñòàò³ -> " << kol_sex_m << endl;
	_ukr(); cout << "\t\tÊ³ëüê³ñòü ãðàâö³â æ³íî÷î¿ ñòàò³ -> " << kol_sex_w << endl;
	fclose(file_1);
}

// ôóíêö³ÿ çàïèòó - çíàõîäæåííÿ ïî êîíòðàêòó
void contract_file()
{
	team data;
	player data1;
	int choice;
	bool flag = false;
	char contr[10];

	cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "\t\tÎáåð³òü òåðì³í êîíòðàêòó, çà ÿêèì íåîáõ³äíî çíàéòè çàïèñ - ";
	cout << endl << "\t\t1. 1 ð³ê\n\t\t2. 2 ðîêè\n\t\t3. 3 ðîêè";

	string _ñhoice;
	
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\t\tÂàø âèáið - ";
		getline(cin, _ñhoice);
		if (regex_match(_ñhoice.c_str(), result_3, regular_3))
		{
			flag1 = true;
			choice = atoi(_ñhoice.c_str());

			if (choice == 1) strcpy_s(contr, "1");
			else if (choice == 2) strcpy_s(contr, "2");
			else strcpy_s(contr, "3");
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!";
		}

	} while (!flag1);

	system("cls");
	_ukr(); cout << endl << "\t\tÐåçóëüòàòè âàøîãî çàïèòó: \n\n";
	cout << endl;

	cout << "\t\t";
	for (size_t i = 0; i <= 96; i++) cout << "-";
	_ukr(); cout << "\n\t\t| Êîä |" << "         Ï.².      |" << " Äàòà íàðîäæåííÿ |" << " Ñòàòü |"
		<< " KG |" << "  Êîìàíäà  |" << " Àìïëóà |" << "   Ãðîìàäÿíñòâî  |" << endl;
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
	for (size_t i = 0; i <= 96; i++) cout << "-"; /// ê³íåöü òàáëèö³
	if (flag == false)
	{
		system("cls");
		cout << "\n\t\tÍåîáõ³äí³ çàïèñè íå çíàéäåíî!" << endl;
	}
}

// ôóíêö³ÿ çàïèòó - çíàõîäæåííÿ ïî ãðîìàäÿíñòâó
void nationality_file_1()
{
	player data;
	team data1;
	int choice;
	bool flag = false;
	char national[15];

	cin.ignore(cin.rdbuf()->in_avail());
	cout << endl << "\t\tÎáåð³òü ãðîìàäÿíñòâî, çà ÿêèì íåîáõ³äíî çíàéòè çàïèñ - ";
	cout << endl << "\t\t1. Óêðà¿íà\n\t\t2. Àðãåíòèíà\n\t\t3. ²ñïàí³ÿ";

	string _ñhoice;
	
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << endl << "\t\tÂàø âèáið - ";
		getline(cin, _ñhoice);
		if (regex_match(_ñhoice.c_str(), result_3, regular_3))
		{
			flag1 = true;
			choice = atoi(_ñhoice.c_str());

			if (choice == 1) strcpy_s(national, "Óêðà¿íà");
			else if (choice == 2) strcpy_s(national, "Àðãåíòèíà");
			else strcpy_s(national, "²ñïàí³ÿ");
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!";
		}

	} while (!flag1);

	system("cls");
	_ukr(); cout << endl << "\t\tÐåçóëüòàòè âàøîãî çàïèòó: \n\n";
	cout << endl;

	cout << "\t\t";
	for (size_t i = 0; i <= 98; i++) cout << "-";
	_ukr(); cout << "\n\t\t| Êîä |" << "         Ï.².      |" << "  Êðà¿íà  |" 
				<< "  Êîìàíäà  |" << " Àìïëóà |" << " Âàðò³ñòü(ìëí.ºâðî) |"
		<< " Òåðì³í êîíòðàêòó |" << endl;
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
	for (size_t i = 0; i <= 98; i++) cout << "-"; /// ê³íåöü òàáëèö³
	if (flag == false)
	{
		system("cls");
		cout << "\n\t\tÍåîáõ³äí³ çàïèñè íå çíàéäåíî!" << endl;
	}
}

// ôóíêö³ÿ çàïèòó - ï³äðàõóíêó çàãàëüíî¿ âàðòîñò³ ïî ãðàâöþ
void total_cost_file_1()
{
	player data;
	team data1;
	size_t total_transfer_cost;

	_ukr(); cout << endl << "\t\tÐåçóëüòàò âàøîãî çàïèòó: \n\n\t\t";
	for (size_t i = 0; i <= 118; i++) cout << "-";
	_ukr(); cout << "\n\t\t| Êîä |" << "         Ï.².      |" << " Àìïëóà |";
	_ukr(); cout << "  Êðà¿íà  |" << "  Êîìàíäà  |" << " Âàðò³ñòü(ìëí.ºâðî) |" 
		<< " Òåðì³í êîíòðàêòó |" <<  " Çàãàëüíà âàðò³ñòü |" << endl;
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
	for (size_t i = 0; i <= 118; i++) cout << "-"; /// ê³íåöü òàáëèö³
}

// ôóíêö³ÿ çàïèòó - çíàõîäæåííÿ äå ïðàöþº ãðàâåöü
void max_kol_games_file_1()
{
	player data;
	team data1;
	size_t num(0), max = 0;
	bool flag = 0, flag1 = 0;

	_ukr(); cout << endl << "\t\tÐåçóëüòàò âàøîãî çàïèòó: \n\t\t";
	for (size_t i = 0; i <= 49; i++) cout << "-";
	_ukr(); cout << "\n\t\t| ¹ |" << "         Ï.².         |" << " MAX |";
	_ukr(); cout << "    Êîìàíäà    |" << endl;
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
		_ukr(); cout << endl << "\t\tÐåçóëüòàò âàøîãî çàïèòó: \n\t\t";
		_ukr(); cout << endl << "\t\tÃðàâåöü ç ìàêñèìàëüíîþ ê³ëüê³ñòþ ³ãîð - " << max
			 << " ,íå ïðàöþº â æîäí³é ç êîìàíä!";
	}
	if (flag == 1)
	{
		cout << "\n\t\t";
		for (size_t i = 0; i <= 49; i++) cout << "-"; /// ê³íåöü òàáëèö³
	}
}

// ôóíêö³ÿ ïåðåãëÿäó ôàéëà Êîìàíäè
void review_file()
{
	int num = 0;
	team data;
	_table(); //// çàãîëîâîê òàáëèö³
	cap_table();  //// øàïêà òàáëèö³
	
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
	for (size_t i = 0; i <= 82; i++) cout << "-"; /// ê³íåöü òàáëèö³
}

// ôóíêö³ÿ çàãîëîâêó òàáëèö³ - Êîìàíäè
void _table()
{
	team data;
	size_t total_kol(0), kol_ukrain(0), kol_argentin(0), kol_spania(0);
	_ukr(); cout << "\t\t\t\t\tÎáë³ê äàíèõ ôóòáîë³ñò³â FIFA!" << endl;

	fopen_s(&file, "player.dat", "rb");
	while (fread(&data, sizeof(team), 1, file))
	{
		total_kol++;
		if (strcmp(data.country, "Óêðà¿íà") == 0) kol_ukrain++;
		if (strcmp(data.country, "Àðãåíòèíà") == 0) kol_argentin++;
		if (strcmp(data.country, "²ñïàí³ÿ") == 0) kol_spania++;
	};
	_ukr(); cout << "\n\tÊîðîòêà ³íôîðìàö³ÿ ôàéëà: \n\n";
	_ukr(); cout << "\tÊ³ëüê³ñòü çàïèñ³â â ôàéë³ -> " << total_kol << endl;
	_ukr(); cout << "\tÊ³ëüê³ñòü óêðà¿íö³â â ôàéë³ -> " << kol_ukrain << endl;
	_ukr(); cout << "\tÊ³ëüê³ñòü àðãåíòèíö³â â ôàéë³ -> " << kol_argentin << endl;
	_ukr(); cout << "\tÊ³ëüê³ñòü ³ñïàíö³â â ôàéë³ -> " << kol_spania << endl;
	fclose(file);
}

// ôóíêö³ÿ øàïêè òàáëèö³ - Êîìàíäè
void cap_table() 
{
	for (size_t i = 0; i <= 82; i++) cout << "-";
	_ukr(); cout << "\n| ¹ ï/ï |" << "  Êðà¿íà  |" << "    Êîìàíäà    |";
	_ukr(); cout << "  Âàðò³ñòü(ìëí.ºâðî) |" << " Òåðì³í êîíòðàêòó |" << " Êîä |" << endl;
	for (size_t i = 0; i <= 82; i++) cout << "-";
}

// ôóíêö³ÿ ñòâîðåííÿ íîâîãî ôàéëà Êîìàíäè
void new_file()
{
	const char file_new[] = "player.dat";
	fopen_s(&file, file_new, "rb");
	if (!file)
	{
		_ukr(); cout << "\t\tÑòâîðþºìî íîâèé ôàéë." << endl;
		fopen_s(&file, file_new, "wb");
		_ukr(); cout << "\t\tÔàéë óñï³øíî ñòâîðíåíî!" << endl;
		system_pause();
	}
	else
	{
		_ukr(); cout << "\t\t²ñíóº ôàéë ç ïåâíèìè äàíèìè!" << endl;
		system_pause();
	}
	fclose(file);
}

// ôóíêö³ÿ âèäàëåííÿ çàïèñ³â ç ôàéëà Êîìàíäè
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
		_ukr(); cout << endl << "\n\tÂâåä³òü íîìåð çàïèñó (¹ ï/ï), ÿêèé íåîáõ³äíî âèäàëèòè - ";
		getline(cin, _n_del);
		if (regex_match(_n_del.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_del = atoi(_n_del.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
		}

	} while (!flag1);


	if (n_del > total_kol)
	{
		_ukr(); cout << endl << "\t\tÏîìèëêà. Ââåäåíèé íîìåð çàïèñó ïåðåâèùóº ê³ëüê³ñòü çàïèñ³â â ôàéë³!";
		_ukr(); cout << endl << "\t\tÊ³ëüê³ñòü çàïèñ³â â ôàéë³ -> " << total_kol << ".";
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

// ôóíêö³ÿ ïåðåâ³ðêè êîäó ãðàâöÿ ïðè ðåäàãóâàíí³
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

// ôóíêö³ÿ ðåäàãóâàííÿ - ö³ëêîì
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
		_ukr(); cout << endl << "\t\tÂâåä³òü íîìåð çàïèñó (¹ ï/ï), ÿêèé íåîáõ³äíî ðåäàãóâàòè - ";
		getline(cin, _n_edit);
		if (regex_match(_n_edit.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_edit = atoi(_n_edit.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
		}

	} while (!flag1);

	if (n_edit > total_kol)
	{
		_ukr(); cout << endl << "\t\tÏîìèëêà. Ââåäåíèé íîìåð çàïèñó ïåðåâèùóº ê³ëüê³ñòü çàïèñ³â â ôàéë³!";
		_ukr(); cout << endl << "\t\tÊ³ëüê³ñòü çàïèñ³â â ôàéë³ -> " << total_kol << ".";
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
		for (size_t i = 0; i <= 82; i++) cout << "-"; /// ê³íåöü òàáëèö³

		fclose(file);

		_ukr(); cout << endl << "\t\tÂè öåé çàïèñ õîò³ëè â³äðåäàãóâàòè ? Ò/Y(òàê)/Í/N(í³) - ";
		cin >> var;
		cin.ignore(cin.rdbuf()->in_avail());
		if (var == 'Ò' || var == 'ò' || var == 'Y' || var == 'y')
		{
			int choice;
			_ukr(); cout << endl << "\t\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³!" << endl;

			string _ñhoice;
			bool flag2 = 0;
			_ukr(); cout << endl << "\t\tÎáåð³òü êðà¿íó ç³ ñïèñêó: ";
			_ukr(); cout << endl << "\t\t1. Óêðà¿íà\n\t\t2. Àðãåíòèíà\n\t\t3. ²ñïàí³ÿ";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice);
				if (regex_match(_ñhoice.c_str(), result_3, regular_3))
				{
					flag2 = true;
					choice = atoi(_ñhoice.c_str());

					if (choice == 1) strcpy_s(data.country, "Óêðà¿íà");
					else if (choice == 2) strcpy_s(data.country, "Àðãåíòèíà");
					else strcpy_s(data.country, "²ñïàí³ÿ");
				}
				else
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!";
				}

			} while (!flag2);

			string _team;
			regex regular3("([ª-ß¥º-ÿ´]{4,13})");
			cmatch result3;
			bool flag3 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü íàçâó êîìàíäè â³ä 4 äî 13 ñèìâîë³â (Íàïðèêëàä: Øàõòàð): ";
				getline(cin, _team);
				if (regex_match(_team.c_str(), result3, regular3))
				{
					flag3 = 1;
					_ukr(); cout << endl << "\t\tÂàøà íàçâà êîìàíäè âèãëÿäàº òàê - ÔÊ " << _team;
					strcpy_s(data.team_p, _team.c_str());
				}
				else
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà! Ôîðìàò ââåäåííÿ ìàº áóòè òàêèì: 'Øàõòàð' !!";
				}
			} while (!flag3);

			string _transfer_cost;
			bool flag4 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü òðàíñôåðíó âàðò³ñòü ôóòáîë³ñòà (â ìëí.ºâðî â³ä 1 äî 400): ";
				getline(cin, _transfer_cost);
				if (regex_match(_transfer_cost.c_str(), result_three_digit, regular_three_digit))
				{
					 
					if (atoi(_transfer_cost.c_str()) < 1 || atoi(_transfer_cost.c_str()) > 400) {
						_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 400!";
					}
					else {
						flag4 = true;
						data.transfer_cost = atoi(_transfer_cost.c_str());
					}
				}
				else 
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 400!";
				}
			} while (!flag4);

			string _ñhoice1;
			bool flag5 = 0;
			cout << endl << "\t\tÎáåð³òü òåðì³í êîíòðàêòó  ç³ ñïèñêó: ";
			cout << endl << "\t\t1. 1 ð³ê\n\t\t2. 2 ðîêè\n\t\t3. 3 ðîêè";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice1);
				if (regex_match(_ñhoice1.c_str(), result_3, regular_3))
				{
					flag5 = true;
					choice = atoi(_ñhoice1.c_str());

					if (choice == 1) strcpy_s(data.contract, "1");
					else if (choice == 2) strcpy_s(data.contract, "2");
					else strcpy_s(data.contract, "3");
				}
				else
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!";
				}

			} while (!flag5);

			string _ñhoice2;
			bool flag6 = 0;
			
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü êîä ãðàâöÿ (0 - íà ïðîäàæ³): ";
				getline(cin, _ñhoice2);
				if (regex_match(_ñhoice2.c_str(), result_three_digit, regular_three_digit))
				{
					flag6 = true;
					data.kod = atoi(_ñhoice2.c_str());
					if (proverka_kod_zapus_file(data) == false)
					{
						flag6 = 0;
						_ukr(); cout << endl << "\t\tÏîìèëêà. Íå â³ðíå ðåäàãóâàííÿ êîäó, òàêîãî ãðàâöÿ ç âåäåííèì êîäîì - íå ³ñíóº!";
					}
				}
				else
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
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
			if (var == 'Í' || var == 'í' || var == 'N' || var == 'n')
			{
				_ukr(); cout << endl << "\t\tÑïðîáóéòå ñïî÷àòêó!" << endl;
			}
			else _ukr(); cout << endl << "\t\tÏîìèëêà!!!";

			return false;
		}
	}
	
}

// ôóíêö³ÿ ðåäàãóâàííÿ çà îêðåìèìè ïîëÿìè
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
		_ukr(); cout << endl << "\t\tÂâåä³òü íîìåð çàïèñó (¹ ï/ï), ÿêèé íåîáõ³äíî ðåäàãóâàòè - ";
		getline(cin, _n_edit);
		if (regex_match(_n_edit.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_edit = atoi(_n_edit.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
		}

	} while (!flag1);

	if (n_edit > total_kol)
	{
		_ukr(); cout << endl << "\t\tÏîìèëêà. Ââåäåíèé íîìåð çàïèñó ïåðåâèùóº ê³ëüê³ñòü çàïèñ³â â ôàéë³!";
		_ukr(); cout << endl << "\t\tÊ³ëüê³ñòü çàïèñ³â â ôàéë³ -> " << total_kol << ".";
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
		for (size_t i = 0; i <= 82; i++) cout << "-"; /// ê³íåöü òàáëèö³
		fclose(file);

		_ukr(); cout << endl << "\t\tÂè öåé çàïèñ õîò³ëè â³äðåäàãóâàòè ? Ò/Y(òàê)/Í/N(í³) - ";
		cin >> var;
		cin.ignore();
		if (var == 'Ò' || var == 'ò' || var == 'Y' || var == 'y')
		{
			do
			{
				system("cls");
				_ukr(); cout << endl << "\tÏîëÿ ÿê³ âè ìîæåòå â³äðåäàãóâàòè:\n";
				_ukr(); cout << endl << "\t1. Êðà¿íà\n";
				_ukr(); cout << endl << "\t2. Êîìàíäà\n";
				_ukr(); cout << endl << "\t3. Âàðò³ñòü â ìëí.ºâðî\n";
				_ukr(); cout << endl << "\t4. Òåðì³í êîíòðàêòó\n";
				_ukr(); cout << endl << "\t5. Êîä ãðàâöÿ\n";
				_ukr(); cout << endl << "\t0. Ïîâåðíåííÿ íàçàä";

				string _n;
				bool flag2 = 0;
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\n\tÂàø âèáið - ";
					getline(cin, _n);
					if (regex_match(_n.c_str(), result_5, regular_5))
					{
						flag2 = true;
						*pn = atoi(_n.c_str());
					}
					else
					{
						_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 0 äî 5!";
					}

				} while (!flag2);

				string _ñhoice;
				bool flag3 = 0;

				string _team;
				regex regular4("([ª-ß¥º-ÿ´]{4,13})");
				cmatch result4;
				bool flag4 = 0;

				string _ñhoice1;
				bool flag5 = 0;

				string _ñhoice2;
				bool flag6 = 0;

				string _transfer_cost;
				bool flag7 = 0;

				switch (*pn)
				{
				case 1:
					system("cls");

					_ukr(); cout << endl << "\t\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

					_ukr(); cout << endl << "\t\tÎáåð³òü êðà¿íó ç³ ñïèñêó: ";
					_ukr(); cout << endl << "\t\t1. Óêðà¿íà\n\t\t2. Àðãåíòèíà\n\t\t3. ²ñïàí³ÿ";
					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tÂàø âèáið - ";
						getline(cin, _ñhoice);
						if (regex_match(_ñhoice.c_str(), result_3, regular_3))
						{
							flag3 = true;
							choice = atoi(_ñhoice.c_str());

							if (choice == 1) strcpy_s(data.country, "Óêðà¿íà");
							else if (choice == 2) strcpy_s(data.country, "Àðãåíòèíà");
							else strcpy_s(data.country, "²ñïàí³ÿ");
						}
						else
						{
							_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!";
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

					_ukr(); cout << endl << "\t\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;
					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tÂåä³òü íàçâó êîìàíäè íå á³ëüøå 13 ñèìâîë³â (Íàïðèêëàä: Øàõòàð): ";
						getline(cin, _team);
						if (regex_match(_team.c_str(), result4, regular4))
						{
							flag4 = 1;
							_ukr(); cout << endl << "\t\tÂàøà íàçâà êîìàíäè âèãëÿäàº òàê - ÔÊ " << _team;
							strcpy_s(data.team_p, _team.c_str());

						}
						else
						{
							_ukr(); cout << endl << "\t\tÏîìèëêà! Ôîðìàò ââåäåííÿ ìàº áóòè òàêèì: 'Øàõòàð' !!";
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
						_ukr(); cout << endl << "\t\tÂåä³òü òðàíñôåðíó âàðò³ñòü ôóòáîë³ñòà (â ìëí.ºâðî â³ä 1 äî 400): ";
						getline(cin, _transfer_cost);
						if (regex_match(_transfer_cost.c_str(), result_three_digit, regular_three_digit))
						{

							if (atoi(_transfer_cost.c_str()) < 1 || atoi(_transfer_cost.c_str()) > 400) {
								_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 400!";
							}
							else {
								flag7 = true;
								data.transfer_cost = atoi(_transfer_cost.c_str());
							}
						}
						else
						{
							_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 400!";
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

					_ukr(); cout << endl << "\t\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

					cout << endl << "\t\tÎáåð³òü òåðì³í êîíòðàêòó  ç³ ñïèñêó: ";
					cout << endl << "\t\t1. 1 ð³ê\n\t\t2. 2 ðîêè\n\t\t3. 3 ðîêè";
					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tÂàø âèáið - ";
						getline(cin, _ñhoice1);
						if (regex_match(_ñhoice1.c_str(), result_3, regular_3))
						{
							flag5 = true;
							choice = atoi(_ñhoice1.c_str());

							if (choice == 1) strcpy_s(data.contract, "1");
							else if (choice == 2) strcpy_s(data.contract, "2");
							else strcpy_s(data.contract, "3");
						}
						else
						{
							_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!";
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

					_ukr(); cout << endl << "\t\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

					do {
						cin.ignore(cin.rdbuf()->in_avail());
						_ukr(); cout << endl << "\t\tÂåä³òü êîä ãðàâöÿ (0 - íà ïðîäàæ³): ";
						getline(cin, _ñhoice2);
						if (regex_match(_ñhoice2.c_str(), result_three_digit, regular_three_digit))
						{
							flag6 = true;
							data.kod = atoi(_ñhoice2.c_str());
							if (proverka_kod_zapus_file(data) == false)
							{
								flag6 = 0;
								_ukr(); cout << endl << "\t\tÏîìèëêà. Íå â³ðíå ðåäàãóâàííÿ êîäó, òàêîãî ãðàâöÿ ç âåäåííèì êîäîì - íå ³ñíóº!";
							}
						}
						else
						{
							_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
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
			if (var == 'Í' || var == 'í' || var == 'N' || var == 'n')
			{
				_ukr(); cout << endl << "\t\tÑïðîáóéòå ñïî÷àòêó!" << endl;
			}
			else {
				_ukr(); cout << endl << "\t\tÏîìèëêà!!!";
			}
			return false;
		}
	}
}

// ôóíêö³ÿ ìåíþ ðåäàãóâàííÿ
int menu_edit_element()
{
	int n, * pn = &n;
	do
	{
		system("color F2");
		_ukr(); cout << endl << "\tÐåäàãóâàííÿ ìîæå âèêîíóâàòèñÿ äâîìà ìåòîäàìè: \n";
		_ukr(); cout << endl << "\t1. Ö³ëêîì\n";
		_ukr(); cout << endl << "\t2. Çà îêðåìèìè ïîëÿìè\n";
		_ukr(); cout << endl << "\t0. Ñêàñóâàííÿ ðåäàãóâàííÿ";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tÂàø âèáið - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_2, regular_2))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 2 !!!";
			}
		} while (!flag);

		switch (*pn)
		{
		case 1:
			system("cls");
			if (full_edit_element() == true)
			{
				system("cls");
				_ukr(); cout << endl << "\tÏ³ñëÿ ðåäàãóâàííÿ äàíí³ âèãëÿäàþòü íàñòóïíèì ÷èíîì:\n";
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
				_ukr(); cout << endl << "\tÏ³ñëÿ ðåäàãóâàííÿ äàíí³ âèãëÿäàþòü íàñòóïíèì ÷èíîì:\n";
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
		_ukr(); cout << endl << "\tÐåäàãóâàííÿ çàïèñ³â ñêàñîâàíî." << endl;
		system_pause();
	}
}

// ôóíêö³ÿ ìåíþ ñîðòóâàííÿ
int menu_sort()
{
	int n, * pn = &n;
	do
	{
		system("cls");
		system("color F2");
		_ukr(); cout << endl << "\tÑîðòóâàííÿ ìîæå âèêîíóâàòèñÿ äâîìà ìåòîäàìè: \n";
		_ukr(); cout << endl << "\t1. Â³äñîðòóâàòè çà âàðò³ñòþ\n";
		_ukr(); cout << endl << "\t2. Â³äñîðòóâàòè çà êðà¿íîþ\n";
		_ukr(); cout << endl << "\t0. Ïîâåðíåííÿ äî ïîïåðåäíüîãî ìåíþ";

		string _n;
		
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tÂàø âèáið - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_2, regular_2))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 2 !!!";
			}
		} while (!flag);
		
		switch (*pn)
		{
		case 1:
			system("cls");
			_ukr(); cout << endl << "\tÔàéë äî ñîðòóâàííÿ çàïèñ³â.\n";
			review_file();
			system_pause();
			system("cls");
			_ukr(); cout << endl << "\tÔàéë ï³ñëÿ ñîðòóâàííÿ çàïèñ³â.\n";
			sort_transfer_cost();
			review_file();
			system_pause();
			break;
		case 2:
			system("cls");
			_ukr(); cout << endl << "\tÔàéë äî ñîðòóâàííÿ çàïèñ³â.\n";
			review_file();
			system_pause();
			system("cls");
			_ukr(); cout << endl << "\tÔàéë ï³ñëÿ ñîðòóâàííÿ çàïèñ³â.\n";
			sort_country();
			review_file();
			system_pause();
			break;
		case 0:
			return 0;
		}
	} while (*pn != 0);
}

// ôóíêö³ÿ ñîðòóâàííÿ çà òðàíñôåðíîþ âàðò³ñòþ
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

// ôóíêö³ÿ ñîðòóâàííÿ çà êðà¿íîþ
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

// ôóíêö³ÿ ââåäåííÿ äàòè
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
		_ukr(); cout << "\n\t\tÂâåä³òü äåíü - ";
		getline(cin, _day);
		if (regex_match(_day.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_day.c_str()) < 1 || atoi(_day.c_str()) > 31) {
				_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 31!";
			}
			else {
				flag = true;
				day = atoi(_day.c_str());
				t_data.tm_mday = day;
			}
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 31!";
		}
	} while (!flag);

	string _mon;
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\n\t\tÂâåä³òü ì³ñÿöü - ";
		getline(cin, _mon);
		if (regex_match(_mon.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_mon.c_str()) < 1 || atoi(_mon.c_str()) > 12) {
				_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 12!";
			}
			else {
				flag1 = true;
				mon = atoi(_mon.c_str());
				t_data.tm_mon = mon - 1;
			}
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 12!";
		}
	} while (!flag1);

	string _year;
	
	bool flag2 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\n\t\tÂâåä³òü ð³ê - ";
		getline(cin, _year);
		if (regex_match(_year.c_str(), result_four_digit, regular_four_digit))
		{
			flag2 = true;
			year = atoi(_year.c_str());
			t_data.tm_year = year - 1900;
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà, ð³ê â ôîðìàò³ - 1972 !";
		}
	} while (!flag2);

	data = mktime(&t_data);
	return data;
}

// ôóíêö³ÿ äîäàâàííÿ çàïèñ³â â ôàéë Êîìàíäè
void add_data()
{
	team data;
	int n, * pn = &n;
	bool flag6 = 0;
	_ukr(); cout << endl << "\t\t\t\t\t\tÄîäàâàííÿ íîâèõ çàïèñ³â ó ôàéë:\n" << endl;

	string _pn;
	bool flag1 = 0;
	
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\t\tÂåä³òü ê³ëüê³ñòü íîâèõ çàïèñ³â àáî 0 äëÿ ñêàñóâàííÿ (íå á³ëüøå 15): ";
		getline(cin, _pn);
		if (regex_match(_pn.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_pn.c_str()) < 1 || atoi(_pn.c_str()) > 15) {
				_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 15!" << endl;
			}
			else {
				flag1 = true;
				*pn = atoi(_pn.c_str());
			}
		}
		else
		{
			_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!" << endl;
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
			cout << endl << "\t\tÂåäåííÿ " << i + 1 << " çàïèñó (çàãàëîì " << *pn << "):" << endl;

			string _ñhoice;
			bool flag2 = 0;

			_ukr(); cout << endl << "\t\tÎáåð³òü êðà¿íó ç³ ñïèñêó: ";
			_ukr(); cout << endl << "\t\t1. Óêðà¿íà\n\t\t2. Àðãåíòèíà\n\t\t3. ²ñïàí³ÿ";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice);
				if (regex_match(_ñhoice.c_str(), result_3, regular_3))
				{
					flag2 = true;
					choice = atoi(_ñhoice.c_str());

					if (choice == 1) strcpy_s(data.country, "Óêðà¿íà");
					else if (choice == 2) strcpy_s(data.country, "Àðãåíòèíà");
					else strcpy_s(data.country, "²ñïàí³ÿ");
				}
				else
				{
					_ukr(); cout << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!" << endl;
				}

			} while (!flag2);

			string _team;
			regex regular("([ª-ß¥º-ÿ´]{4,13})");
			cmatch result;
			bool flag = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü íàçâó êîìàíäè íå á³ëüøå 13 ñèìâîë³â (Íàïðèêëàä: Øàõòàð): "; 
				getline(cin, _team);
				if (regex_match(_team.c_str(), result, regular))
				{
					flag = 1;
					_ukr(); cout << endl << "\t\tÂàøà íàçâà êîìàíäè âèãëÿäàº òàê - ÔÊ " << _team;
					 strcpy_s(data.team_p, _team.c_str());
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà! Ôîðìàò ââåäåííÿ ìàº áóòè òàêèì: 'Øàõòàð' !!" << endl;
				}
			} while (!flag);

			string _transfer_cost;
			bool flag3 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü òðàíñôåðíó âàðò³ñòü ôóòáîë³ñòà (â ìëí.ºâðî â³ä 1 äî 400): ";
				getline(cin, _transfer_cost);
				if (regex_match(_transfer_cost.c_str(), result_three_digit, regular_three_digit))
				{

					if (atoi(_transfer_cost.c_str()) < 1 || atoi(_transfer_cost.c_str()) > 400) {
						_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 400!" << endl;
					}
					else {
						flag3 = true;
						data.transfer_cost = atoi(_transfer_cost.c_str());
					}
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 400!" << endl;
				}
			} while (!flag3);

			string _ñhoice1;
			bool flag4 = 0;

			_ukr();
			cout << endl << "\t\tÎáåð³òü òåðì³í êîíòðàêòó  ç³ ñïèñêó: ";
			cout << endl << "\t\t1. 1 ð³ê\n\t\t2. 2 ðîêè\n\t\t3. 3 ðîêè";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice1);
				if (regex_match(_ñhoice1.c_str(), result_3, regular_3))
				{
					flag4 = true;
					choice = atoi(_ñhoice1.c_str());

					if (choice == 1) strcpy_s(data.contract, "1");
					else if (choice == 2) strcpy_s(data.contract, "2");
					else strcpy_s(data.contract, "3");
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!" << endl;
				}

			} while (!flag4);

			string _ñhoice2;
			bool flag5 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü êîä ãðàâöÿ (0 - íà ïðîäàæ³): ";
				getline(cin, _ñhoice2);
				if (regex_match(_ñhoice2.c_str(), result_three_digit, regular_three_digit))
				{
					flag5 = true;
					data.kod = atoi(_ñhoice2.c_str());
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!" << endl;
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
			cout << endl << "\t\tÄîäàíà òàêà ê³ëüê³ñòü çàïèñ³â - " << *pn << " !";
		}
	}
	else
	{
		_ukr(); cout << endl << "\t\tÄîäàâàííÿ íîâèõ çàïèñ³â ó ôàéë ñêàñîâàíî.";
	}
	cout << endl << endl << endl;
}

// ôóíêö³ÿ ìåíþ ôàéëà Ãðàâö³
int menu_file_1()
{
	int n, * pn = &n;
	player data;
	do {
		system("color F5");
		system("cls");
		cout << "\n\n\n\n\n\n";
		_ukr(); cout << endl << "\t\t\t\tÃîëîâíå ìåíþ ôàéëà 'Ãðàâö³'\n\n";
		_ukr(); cout << endl << "\t1. Ñòâîðåííÿ íîâîãî ôàéëó\n";
		_ukr(); cout << endl << "\t2. Ïåðåãëÿä ³ñíóþ÷îãî ôàéëó\n";
		_ukr(); cout << endl << "\t3. Äîäàâàííÿ äàíèõ ó ôàéë\n";
		_ukr(); cout << endl << "\t4. Ðåäàãóâàííÿ äàíèõ çà êîäîì çàïèñó\n";
		_ukr(); cout << endl << "\t5. Âèäàëåííÿ çàïèñ³â çà êîäîì çàïèñó\n";
		_ukr(); cout << endl << "\t0. Ïîâåðíåííÿ äî ïîïåðåäíüîãî ìåíþ";

		string _n;
		bool flag = 0;
		do {
			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\n\tÂàø âèáið - ";
			getline(cin, _n);
			if (regex_match(_n.c_str(), result_5, regular_5))
			{
				flag = 1;
				*pn = atoi(_n.c_str());
			}
			else
			{
				_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 5 !!!";
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
				_ukr(); cout << endl << "\t\tÏîìèëêà. Ñòâîð³òü ôàéë!";
			}
			else
			{
				if ((fread(&data, sizeof(player), 1, file_1)) == NULL)
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\t\tÏîìèëêà. Ñòâîð³òü ôàéë!";
			}
			else
			{
				if ((fread(&data, sizeof(player), 1, file_1)) == NULL)
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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
				_ukr(); cout << endl << "\t\tÏîìèëêà. Ñòâîð³òü ôàéë!";
			}
			else
			{
				if ((fread(&data, sizeof(player), 1, file_1)) == NULL)
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà. Ôàéë ïîðîæí³é!";
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

// ôóíêö³ÿ ñòâîðåííÿ íîâîãî ôàéëà Ãðàâö³
void new_file_1()
{
	const char file_new[] = "player_1.dat";
	fopen_s(&file_1, file_new, "rb");
	if (!file_1)
	{
		_ukr(); cout << "\t\tÑòâîðþºìî íîâèé ôàéë." << endl;
		fopen_s(&file_1, file_new, "wb");
		_ukr(); cout << "\t\tÔàéë óñï³øíî ñòâîðíåíî!" << endl;
		system_pause();
	}
	else
	{
		_ukr(); cout << "\t\t²ñíóº ôàéë ç ïåâíèìè äàíèìè!" << endl;
		system_pause();
	}
	fclose(file_1);
}

// ôóíêö³ÿ ïåðåãëÿäó ôàéëà Ãðàâö³
void review_file_1()
{
	player data;
	int num(0);
	table_cap_table();  //// øàïêà òà çàãîëîâîê òàáëèö³
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
	for (size_t i = 0; i <= 81; i++) cout << "-";  /// ê³íåöü òàáëèö³
}

// ôóíêö³ÿ øàïêè òàáëèö³ - Ãðàâö³
void table_cap_table()
{
	player data;
	size_t total_kol(0), kol_role_vr(0), kol_role_lp(0), kol_role_cf(0);
	_ukr(); cout << "\t\t\t\t\tÄåòàëüíà ³íôîðìàö³ÿ ïðî ãðàâö³â FIFA!" << endl;

	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data, sizeof(player), 1, file_1))
	{
		total_kol++;
		if (strcmp(data.role, "ÂÐ") == 0) kol_role_vr++;
		if (strcmp(data.role, "ËÏ") == 0) kol_role_lp++;
		if (strcmp(data.role, "ÖÔ") == 0) kol_role_cf++;
	};
	_ukr(); cout << "\n\tÊîðîòêà ³íôîðìàö³ÿ ôàéëà: \n\n";
	_ukr(); cout << "\tÊ³ëüê³ñòü çàïèñ³â â ôàéë³ -> " << total_kol << endl;
	_ukr(); cout << "\tÊ³ëüê³ñòü àìïëóà 'ÂÐ' -> " << kol_role_vr << endl;
	_ukr(); cout << "\tÊ³ëüê³ñòü àìïëóà 'ËÏ' -> " << kol_role_lp << endl;
	_ukr(); cout << "\tÊ³ëüê³ñòü àìïëóà 'ÖÔ' -> " << kol_role_cf << endl;
	fclose(file_1);

	cout << "\n";
	for (size_t i = 0; i <= 81; i++) cout << "-";
	_ukr(); cout << "\n| Êîä |" << "         Ï.².      |" << " Äàòà íàðîäæåííÿ |";
	_ukr(); cout << " Ñòàòü |" << " Ãðîìàäÿíñòâî |" << " Àìïëóà |" << " KG |" << endl;
	for (size_t i = 0; i <= 81; i++) cout << "-";
}

// ôóíêö³ÿ íà íàÿâí³ñòü ³äåíòè÷íîãî çàïèñó â ôàéë³ - Ãðàâö³
bool proverka_zapusy_file_1(player data)
{
	player data1;
	fopen_s(&file_1, "player_1.dat", "rb");
	while (fread(&data1, sizeof(player), 1, file_1))
	{
		if (data.kod == data1.kod)
		{
			fclose(file_1);
			cout << "\t\tÂâåäåíèé çàïèñ ³ñíóº â ôàéë³!" << endl;
			return true;
		}
	};
	fclose(file_1);
	return false;
}

// ôóíêö³ÿ äîäàâàííÿ çàïèñ³â â ôàéë Ãðàâö³
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

	_ukr(); cout << endl << "\t\t\t\t\t\tÄîäàâàííÿ íîâèõ çàïèñ³â ó ôàéë 'Ãðàâö³' :\n" << endl;
	cin.ignore(cin.rdbuf()->in_avail());

	string _pn;
	bool flag1 = 0;
	do {
		cin.ignore(cin.rdbuf()->in_avail());
		_ukr(); cout << "\t\tÂåä³òü ê³ëüê³ñòü íîâèõ çàïèñ³â àáî 0 äëÿ ñêàñóâàííÿ (íå á³ëüøå 15): ";
		getline(cin, _pn);
		if (regex_match(_pn.c_str(), result_two_digit, regular_two_digit))
		{
			if (atoi(_pn.c_str()) < 1 || atoi(_pn.c_str()) > 15) {
				_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 15!" << endl;
			}
			else {
				flag1 = true;
				*pn = atoi(_pn.c_str());
			}
		}
		else
		{
			_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!" << endl;
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
			cout << endl << "\t\tÂåäåííÿ " << i + 1 << " çàïèñó (çàãàëîì " << *pn << "):" << endl;
			
			++num;
			
			string name_player;
			regex regular("([ª-ß¥º-ÿ´]+?)( )([ª-ß¥º-ÿ´]+?)");
			cmatch result;
			bool flag = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂåä³òü ïð³çâèùå òà ³ì'ÿ ãðàâöÿ (Íàïðèêëàä: ßðìîëåíêî Àíäð³é): "; 
				getline(cin, name_player);  
				if (regex_match(name_player.c_str(), result, regular))
				{
					flag = 1;
					cout << "\t\tÂàøå ïð³çâèùå òà ³ì'ÿ ãðàâöÿ âèãëÿäàº òàê - " << name_player;
					strcpy_s(data.first_second_name_player, name_player.c_str());
				}
				else
				{
					cout << "\t\tÏîìèëêà! Ôîðìàò ââåäåííÿ ìàº áóòè òàêèì: 'ßðìîëåíêî Àíäð³é' !!";
				}
			} while (!flag);

			cin.ignore(cin.rdbuf()->in_avail());
			_ukr(); cout << endl << "\t\tÂåä³òü äàòó íàðîäæåííÿ ôóòáîë³ñòà:" << endl;
			data.date_of_birth = vvod_data_of_birth();

			string _ñhoice;
			bool flag2 = 0;
			_ukr();
			cout << endl << "\n\t\tÎáåð³òü ñòàòü ãðàâöÿ: ";
			cout << endl << "\t\t1. 'æ' – æ³íî÷à\n\t\t2. '÷' – ÷îëîâ³÷à";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice);
				if (regex_match(_ñhoice.c_str(), result_2, regular_2))
				{
					flag2 = true;
					choice = atoi(_ñhoice.c_str());

					if (choice == 1) strcpy_s(data.sex, "Æ");
					else strcpy_s(data.sex, "×");
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 2!" << endl;
				}

			} while (!flag2);

			string _ñhoice1;
			bool flag3 = 0;
			cout << endl << "\n\t\tÎáåð³òü ãðîìàäÿíñòâî ç³ ñïèñêó: ";
			cout << endl << "\t\t1. Óêðà¿íà\n\t\t2. Àðãåíòèíà\n\t\t3. ²ñïàí³ÿ";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice1);
				if (regex_match(_ñhoice1.c_str(), result_3, regular_3))
				{
					flag3 = true;
					choice = atoi(_ñhoice1.c_str());

					if (choice == 1) strcpy_s(data.nationality, "Óêðà¿íà");
					else if (choice == 2) strcpy_s(data.nationality, "Àðãåíòèíà");
					else strcpy_s(data.nationality, "²ñïàí³ÿ");
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!" << endl;
				}

			} while (!flag3);

			string _ñhoice2;
			bool flag4 = 0;
			cout << endl << "\n\t\tÎáåð³òü àìïëóà ç³ ñïèñêó: ";
			cout << endl << "\t\t1. ÂÐ – âîðîòàð\n\t\t2. ËÏ – ë³âèé ï³âçàõèñíèê\n\t\t3. ÖÔ – öåíòð ôîðâàðä";
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\t\tÂàø âèáið - ";
				getline(cin, _ñhoice2);
				if (regex_match(_ñhoice2.c_str(), result_3, regular_3))
				{
					flag4 = true;
					choice = atoi(_ñhoice2.c_str());

					if (choice == 1) strcpy_s(data.role, "ÂÐ");
					else if (choice == 2) strcpy_s(data.role, "ËÏ");
					else strcpy_s(data.role, "ÖÔ");
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!" << endl;
				}

			} while (!flag4);

			string _kol_games;
			bool flag5 = 0;

			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\n\t\tÂåä³òü ê³ëüê³ñòü ïðîâåäåíèõ ³ãîð (KG)  ôóòáîë³ñòà (â³ä 1 äî 150): ";
				getline(cin, _kol_games);
				if (regex_match(_kol_games.c_str(), result_three_digit, regular_three_digit))
				{

					if (atoi(_kol_games.c_str()) < 1 || atoi(_kol_games.c_str()) > 150) {
						_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 150!" << endl;
					}
					else {
						flag5 = true;
						data.kol_games = atoi(_kol_games.c_str());
					}
				}
				else
				{
					_ukr(); cout  << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 150!" << endl;
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
			cout << endl << "\t\tÄîäàíà òàêà ê³ëüê³ñòü çàïèñ³â - " << *pn << " !";
		}
	}
	else
	{
		_ukr(); cout << endl << "\t\tÄîäàâàííÿ íîâèõ çàïèñ³â ó ôàéë ñêàñîâàíî.";
	}
	cout << endl << endl << endl;
}

// ôóíêö³ÿ ðåäàãóâàííÿ ôàéëà Ãðàâö³
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
		_ukr(); cout << endl << "\n\tÂâåä³òü êîä çàïèñó, ÿêèé íåîáõ³äíî ðåäàãóâàòè - ";
		getline(cin, _n_edit);
		if (regex_match(_n_edit.c_str(), result_three_digit, regular_three_digit))
		{
			flag = true;
			n_edit = atoi(_n_edit.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
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
		cout << "\t\tÏîìèëêà. Ââåäåíîãî êîäó íå ³ñíóº!" << endl;
		return 0;
	}

	system("cls");
	fseek(file_1, num1 * sizeof(player), SEEK_SET);

	fread(&data, sizeof(player), 1, file_1);
	cout << "\n";
	for (size_t i = 0; i <= 83; i++) cout << "-";
	_ukr(); cout << "\n| Êîä |" << "         Ï.².      |" << " Äàòà íàðîäæåííÿ |";
	_ukr(); cout << " Ñòàòü |" << "  Ãðîìàäÿíñòâî  |" << " Àìïëóà |" << " KG |" << endl;
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
	for (size_t i = 0; i <= 83; i++) cout << "-";  /// ê³íåöü òàáëèö³

	fclose(file_1);

	_ukr(); cout << endl << "\n\tÂè öåé çàïèñ õîò³ëè â³äðåäàãóâàòè ? Ò/Y(òàê)/Í/N(í³) - ";
	cin >> var;
	cin.ignore();
	if (var == 'Ò' || var == 'ò' || var == 'Y' || var == 'y')
	{
		do
		{
			system("cls");
			_ukr(); cout << endl << "\tÏîëÿ ÿê³ âè ìîæåòå â³äðåäàãóâàòè:\n";
			_ukr(); cout << endl << "\t1. Ï.².\n";
			_ukr(); cout << endl << "\t2. Äàòà íàðîäæåííÿ\n";
			_ukr(); cout << endl << "\t3. Ñòàòü\n";
			_ukr(); cout << endl << "\t4. Ãðîìàäÿíñòâî\n";
			_ukr(); cout << endl << "\t5. Àìïëóà\n";
			_ukr(); cout << endl << "\t6. KG - ê³ëüê³ñòü ïðîâåäåíèõ ³ãîð\n";
			_ukr(); cout << endl << "\t0. Ïîâåðíåííÿ äî ïîïåðåäíüîãî ìåíþ";

			string _n;
			bool flag0 = 0;
			do {
				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\n\tÂàø âèáið - ";
				getline(cin, _n);
				if (regex_match(_n.c_str(), result_6, regular_6))
				{
					flag0 = 1;
					*pn = atoi(_n.c_str());
				}
				else
				{
					_ukr(); cout << endl << "\t\tÏîìèëêà! Ââåäåííÿ ìàº áóòè öèôðîâèì ³ í³ÿêèì ³íøèì, ÷èñëà â³ä 0 äî 6 !!!";
				}
			} while (!flag0);

			string name_player;
			regex regular1("([ª-ß¥º-ÿ´]+?)( )([ª-ß¥º-ÿ´]+?)");
			cmatch result1;
			bool flag1 = 0;

			string _ñhoice;
			bool flag2 = 0;

			string _ñhoice1;
			bool flag3 = 0;

			string _kol_games;
			bool flag4 = 0;

			switch (*pn)
			{
			case 1:
				system("cls");

				_ukr(); cout << endl << "\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\n\tÂåä³òü ïð³çâèùå òà ³ì'ÿ ãðàâöÿ (Íàïðèêëàä: ßðìîëåíêî Àíäð³é): ";
					getline(cin, name_player);
					if (regex_match(name_player.c_str(), result1, regular1))
					{
						flag1 = 1;
						cout << "\n\tÂàøå ïð³çâèùå òà ³ì'ÿ ãðàâöÿ âèãëÿäàº òàê - " << name_player;
						strcpy_s(data.first_second_name_player, name_player.c_str());
					}
					else
					{
						cout << "\n\tÏîìèëêà! Ôîðìàò ââåäåííÿ ìàº áóòè òàêèì: 'ßðìîëåíêî Àíäð³é' !!";
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

				_ukr(); cout << endl << "\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

				cin.ignore(cin.rdbuf()->in_avail());
				_ukr(); cout << endl << "\n\tÂåä³òü äàòó íàðîäæåííÿ ôóòáîë³ñòà: ";
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
				cout << endl << "\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

				cout << endl << "\n\t\tÎáåð³òü ñòàòü ãðàâöÿ: ";
				cout << endl << "\t\t1. 'æ' – æ³íî÷à\n\t\t2. '÷' – ÷îëîâ³÷à";
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\t\tÂàø âèáið - ";
					getline(cin, _ñhoice);
					if (regex_match(_ñhoice.c_str(), result_2, regular_2))
					{
						flag2 = true;
						choice = atoi(_ñhoice.c_str());

						if (choice == 1) strcpy_s(data.sex, "Æ");
						else strcpy_s(data.sex, "×");
					}
					else
					{
						_ukr(); cout << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 2!" << endl;
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
				cout << endl << "\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

				cout << endl << "\n\t\tÎáåð³òü ãðîìàäÿíñòâî ç³ ñïèñêó: ";
				cout << endl << "\t\t1. Óêðà¿íà\n\t\t2. Àðãåíòèíà\n\t\t3. ²ñïàí³ÿ";
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\t\tÂàø âèáið - ";
					getline(cin, _ñhoice1);
					if (regex_match(_ñhoice1.c_str(), result_3, regular_3))
					{
						flag3 = true;
						choice = atoi(_ñhoice1.c_str());

						if (choice == 1) strcpy_s(data.nationality, "Óêðà¿íà");
						else if (choice == 2) strcpy_s(data.nationality, "Àðãåíòèíà");
						else strcpy_s(data.nationality, "²ñïàí³ÿ");
					}
					else
					{
						_ukr(); cout << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!" << endl;
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
				cout << endl << "\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

				cout << endl << "\n\t\tÎáåð³òü àìïëóà ç³ ñïèñêó: ";
				cout << endl << "\t\t1. ÂÐ – âîðîòàð\n\t\t2. ËÏ – ë³âèé ï³âçàõèñíèê\n\t\t3. ÖÔ – öåíòð ôîðâàðä";
				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\t\tÂàø âèáið - ";
					getline(cin, _ñhoice1);
					if (regex_match(_ñhoice1.c_str(), result_3, regular_3))
					{
						flag3 = true;
						choice = atoi(_ñhoice1.c_str());

						if (choice == 1) strcpy_s(data.role, "ÂÐ");
						else if (choice == 2) strcpy_s(data.role, "ËÏ");
						else strcpy_s(data.role, "ÖÔ");
					}
					else
					{
						_ukr(); cout << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 3!" << endl;
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
				cout << endl << "\t\tËþáèé êîðèñòóâà÷ó, ââîäèìî íîâ³ äàíí³ äàííîãî ïîëÿ!" << endl;

				do {
					cin.ignore(cin.rdbuf()->in_avail());
					_ukr(); cout << endl << "\n\t\tÂåä³òü ê³ëüê³ñòü ïðîâåäåíèõ ³ãîð (KG)  ôóòáîë³ñòà (â³ä 1 äî 150): ";
					getline(cin, _kol_games);
					if (regex_match(_kol_games.c_str(), result_three_digit, regular_three_digit))
					{

						if (atoi(_kol_games.c_str()) < 1 || atoi(_kol_games.c_str()) > 150) {
							_ukr(); cout << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè ÷èñëà â³ä 1 äî 150!" << endl;
						}
						else {
							flag4 = true;
							data.kol_games = atoi(_kol_games.c_str());
						}
					}
					else
					{
						_ukr(); cout << "\n\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà â³ä 1 äî 150!" << endl;
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
		if (var == 'Í' || var == 'í' || var == 'N' || var == 'n')
		{
			_ukr(); cout << endl << "\n\tÑïðîáóéòå ñïî÷àòêó!" << endl;
		}
		else {
			_ukr(); cout << endl << "\n\tÏîìèëêà!!!";
		}
		return 0;
	}
}

// ôóíêö³ÿ âèäàëåííÿ çàïèñ³â ç ôàéëà Ãðàâö³
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
		_ukr(); cout << endl << "\n\tÂâåä³òü êîä ãðàâöÿ, ÿêèé íåîáõ³äíî âèäàëèòè - ";
		getline(cin, _n_del);

		if (regex_match(_n_del.c_str(), result_three_digit, regular_three_digit))
		{
			flag1 = true;
			n_del = atoi(_n_del.c_str());
		}
		else
		{
			_ukr(); cout << endl << "\t\tÏîìèëêà. Âè ìàºòå ìîæëèâ³ñòü âèêîðèñòîâóâàòè Ò²ËÜÊÈ ÷èñëà!";
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
		cout << endl << "\t\tÏîìèëêà. Ââåäåíîãî êîäó íå ³ñíóº!" << endl;
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
