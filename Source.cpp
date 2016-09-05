#include <iostream> 
#include <windows.h>
#include <string> 
#include <conio.h>
#include <time.h>
#include <thread>
#include <cmath>
#include "Center.h"
#include "Stage.h"
#include "StartScreen.h"
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//https://www.youtube.com/watch?v=nAFCtZF92UY //
static string STAGE[31] =
{ "1++++++++++++21++++++++++++2",
"-~~~~~~~~~~~~--~~~~~~~~~~~~-",
"-~1++2~1+++2~--~1+++2~1++2~-",
"-C-XX-~-XXX-~--~-XXX-~-XX-C-",
"-~4++3~4+++3~43~4+++3~4++3~-",
"-~~~~~~~~~~~~~~~~~~~~~~~~~~-",
"-~1++2~12~1++++++2~12~1++2~-",
"-~4++3~--~4++21++3~--~4++3~-",
"-~~~~~~--~~~~--~~~~--~~~~~~-",
"4++++2~-4++2~--~1++3-~1++++3",
"XXXXX-~-1++3~43~4++2-~-XXXXX",
"XXXXX-~--~~~~~~~~~~--~-XXXXX",
"XXXXX-~--~1++GG++2~--~-XXXXX",
"+++++3~43~-XXXXXX-~43~4+++++",
"XXXXXX~~~~-XXXXXX-~~~~XXXXXX",
"+++++2~12~-XXXXXX-~12~1+++++",
"XXXXX-~--~4++++++3~--~-XXXXX",
"XXXXX-~--~~~~~~~~~~--~-XXXXX",
"XXXXX-~--~1++++++2~--~-XXXXX",
"1++++3~43~4++21++3~43~4++++2",
"-~~~~~~~~~~~~--~~~~~~~~~~~~-",
"-~1++2~1+++2~--~1+++2~1++2~-",
"-~4+2-~4+++3~43~4+++3~-1+3~-",
"-C~~--~~~~~~~~~~~~~~~~--~~C-",
"4+2~--~12~1++++++2~12~--~1+3",
"1+3~43~--~4++21++3~--~43~4+2",
"-~~~~~~--~~~~--~~~~--~~~~~~-",
"-~1++++34++2~--~1++34++++2~-",
"-~4++++++++3~43~4++++++++3~-",
"-~~~~~~~~~~~~~~~~~~~~~~~~~~-",
"4++++++++++++++++++++++++++3" };



int lives = 3;
long double HIGHSCORE = 0;
int pelletTimer = 35;
bool Hacks = false;
char lastmove = 'd';
COORD Pac;

void title()
{
	while (true)
	{
		SetConsoleTitle("PAC-MAN       ");
		Sleep(400);
		SetConsoleTitle("PAC-MAN <.....");
		Sleep(400);
		SetConsoleTitle("PAC-MAN  <....");
		Sleep(400);
		SetConsoleTitle("PAC-MAN   <...");
		Sleep(400);
		SetConsoleTitle("PAC-MAN    <..");
		Sleep(400);
		SetConsoleTitle("PAC-MAN     <.");
		Sleep(400);
		SetConsoleTitle("PAC-MAN      <");
		Sleep(400);
	}
}


void TESTHIT(COORD &, char);
void gTESTHIT(COORD &, int);
int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Position pos;
	char move;
	int count = 0;
	int gmovement = 0;
	COORD HS = { 13, 1 };
	string temp2;
	string test;
	COORD lives1 = { 7, 34 };
	COORD lives2 = { 10, 34 };
	COORD lives3 = { 13, 34 };
	bool SreS = false;
	int numpellets = 100;

	COORD ghost1 = { 13, 13 };
	COORD ghost2 = { 11, 16 };
	COORD ghost3 = { 14, 16 };
	COORD ghost4 = { 16, 16 };
	COORD start = { 0, 0 };
	StartScreen sc;
	bool pause = false;
	bool justpause = false;

	thread t1(title);
	t1.detach();

	HWND   hwndScreen;
	RECT   rectScreen;
	int    ConsolePosX;
	int    ConsolePosY;
	hwndScreen = GetDesktopWindow();
	GetWindowRect(hwndScreen, &rectScreen);
	ConsolePosX = (rectScreen.right - 500) >> 1;
	ConsolePosY = (rectScreen.bottom - 500) >> 1;
	SetWindowPos(GetConsoleWindow(), HWND_NOTOPMOST, ConsolePosX, ConsolePosY, 625, 400, SWP_NOOWNERZORDER);

	sc.menu();
	pos.loc.X = 0;
	pos.loc.Y = 16;
	CenWin();

	srand(time(NULL));
	SetConsoleCursorPosition(h, start);
	SetConsoleTextAttribute(h, 0x0f);
	cout << "         High Score: " << endl
		<< endl;


	string temp;
	for (int i = 0; i < 31; i++)
	{
		temp = STAGE[i];
		for (int i2 = 0; i2 < 28; i2++)
		{

			if (temp[i2] == '+')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << char(205);
			}
			else if (temp[i2] == '-')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << char(186);
			}
			else if (temp[i2] == '~')
			{
				SetConsoleTextAttribute(h, 0x0f);
				cout << ".";
			}
			else if (temp[i2] == '1')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << char(201);
			}
			else if (temp[i2] == '2')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << char(187);
			}
			else if (temp[i2] == '3')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << char(188);
			}
			else if (temp[i2] == '4')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << char(200);
			}
			else if (temp[i2] == 'X')
			{
				SetConsoleTextAttribute(h, 0x01);
				cout << ' ';
			}
			else if (temp[i2] == 'C')
			{
				SetConsoleTextAttribute(h, 0x07);
				cout << 'o';
			}
			else if (temp[i2] == 'G')
			{
				SetConsoleTextAttribute(h, 0x07);
				cout << '-';
			}
			else;
		}
		cout << endl;
	}

	cout << endl;
	SetConsoleTextAttribute(h, 0x0f);
	cout << "Lives: ";
	SetConsoleTextAttribute(h, 0x0E);
	cout << "<  <  <           ";
	SetConsoleTextAttribute(h, 0x0C);
	cout << char(235) << endl;
	SetConsoleTextAttribute(h, 0x0E);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
	cout << '<';

	temp2 = STAGE[ghost1.Y - 2];
	temp2[ghost1.X] = 'W';
	STAGE[ghost1.Y - 2] = temp2;
	SetConsoleCursorPosition(h, ghost1);
	SetConsoleTextAttribute(h, 0x0C);
	cout << 'W';
	SetConsoleCursorPosition(h, ghost2);
	SetConsoleTextAttribute(h, 0x0B);
	cout << 'W';
	SetConsoleCursorPosition(h, ghost3);
	SetConsoleTextAttribute(h, 0x0D);
	cout << 'W';
	SetConsoleCursorPosition(h, ghost4);
	SetConsoleTextAttribute(h, 0x0A);
	cout << 'W';

	SetConsoleCursorPosition(h, HS);
	SetConsoleTextAttribute(h, 0x0f);
	cout << HIGHSCORE;
	move = _getch();
	
	while (lives != 0 && numpellets != 0)
	{

		temp2 = STAGE[pos.loc.Y - 2];
		if (temp2[pos.loc.X] != 'X')
		{
			temp2[pos.loc.X] = 'T';
			STAGE[pos.loc.Y - 2] = temp2;
		}
		if (SreS == true)
			move = _getch(), SreS = false, gmovement = 0;

		SetConsoleTextAttribute(h, 0x0E);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
		if (pos.loc.X == ghost1.X && pos.loc.Y == ghost1.Y && pelletTimer == 35)
		{
			SreS = true;

		}
		if (pos.loc.X == ghost2.X && pos.loc.Y == ghost2.Y && pelletTimer == 35)
		{
			SreS = true;
		}
		if (pos.loc.X == ghost3.X && pos.loc.Y == ghost3.Y && pelletTimer == 35)
		{
			SreS = true;
		}
		if (pos.loc.X == ghost4.X && pos.loc.Y == ghost4.Y && pelletTimer == 35)
		{
			SreS = true;
		}
		if (pos.loc.X == ghost1.X && pos.loc.Y == ghost1.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost1 = { 13, 13 };
		}
		if (pos.loc.X == ghost2.X && pos.loc.Y == ghost2.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost2 = { 11, 16 };
		}
		if (pos.loc.X == ghost3.X && pos.loc.Y == ghost3.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost3 = { 14, 16 };
		}
		if (pos.loc.X == ghost4.X && pos.loc.Y == ghost4.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost4 = { 16, 16 };
		}
		if (_kbhit())
		{
			move = _getch();


			if (move == 'a' || move == KEY_LEFT)
			{
				if (pos.loc.X == 0 && pos.loc.Y == 16)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << ' ';
					pos.loc.X = 27;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << '>';
				}
				else
				{
					TESTHIT(pos.loc, move);
				}
			}

			else if (move == 'd' || move == KEY_RIGHT)
			{
				if (pos.loc.X == 27 && pos.loc.Y == 16)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << ' ';
					pos.loc.X = 0;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << '<';
				}
				else
				{
					TESTHIT(pos.loc, move);
				}
			}

			else if (move == 'w' || move == KEY_UP)
			{
				TESTHIT(pos.loc, move);
			}

			else if (move == 's' || move == KEY_DOWN)
			{
				TESTHIT(pos.loc, move);

			}
			else if (move == '\b')
			{
				if (Hacks == false)
					Hacks = true;
				else
					Hacks = false;
				move = 'd';
			}
			else if (move == VK_ESCAPE)
			{
				pause = true;
			}

			else;
		}
		else
		{

			if (lastmove == 'a' || lastmove == KEY_LEFT)
			{
				if (pos.loc.X == 0 && pos.loc.Y == 16)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << ' ';
					pos.loc.X = 27;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << '>';
				}
				else
				{
					TESTHIT(pos.loc, move);
				}
			}

			else if (lastmove == 'd' || lastmove == KEY_RIGHT)
			{
				if (pos.loc.X == 27 && pos.loc.Y == 16)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << ' ';
					pos.loc.X = 0;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos.loc);
					cout << '<';
				}
				else
				{
					TESTHIT(pos.loc, lastmove);
				}
			}
			else
			{
				TESTHIT(pos.loc, lastmove);
			}
		}

		Pac.X = pos.loc.X;
		Pac.Y = pos.loc.Y;
		if (pos.loc.X == ghost1.X && pos.loc.Y == ghost1.Y && pelletTimer == 35)
		{
			SreS = true;

		}
		if (pos.loc.X == ghost2.X && pos.loc.Y == ghost2.Y && pelletTimer == 35)
		{
			SreS = true;
		}
		if (pos.loc.X == ghost3.X && pos.loc.Y == ghost3.Y && pelletTimer == 35)
		{
			SreS = true;
		}
		if (pos.loc.X == ghost4.X && pos.loc.Y == ghost4.Y && pelletTimer == 35)
		{
			SreS = true;
		}
		if (pos.loc.X == ghost1.X && pos.loc.Y == ghost1.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost1 = { 13, 13 };
		}
		if (pos.loc.X == ghost2.X && pos.loc.Y == ghost2.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost2 = { 11, 16 };
		}
		if (pos.loc.X == ghost3.X && pos.loc.Y == ghost3.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost3 = { 14, 16 };
		}
		if (pos.loc.X == ghost4.X && pos.loc.Y == ghost4.Y && pelletTimer != 35)
		{
			HIGHSCORE = HIGHSCORE + 500;
			ghost4 = { 16, 16 };
		}
		if (SreS == true)
		{
			lives--;
			SetConsoleCursorPosition(h, pos.loc);
			cout << ' ';
			pos.loc.X = 0;
			pos.loc.Y = 16;
			SetConsoleCursorPosition(h, pos.loc);
			SetConsoleTextAttribute(h, 0x0E);
			cout << '<';

			string line;
			char dot;

			line = STAGE[ghost1.Y - 2];
			dot = line[ghost1.X];
			SetConsoleCursorPosition(h, ghost1);
			if (dot == 'o')
			{
				SetConsoleTextAttribute(h, 0x0f);
				cout << 'o';
			}
			else if (dot == '~' || dot == 'W')
			{
				SetConsoleTextAttribute(h, 0x07);
				cout << '.';
			}
			cout << ' ';
			ghost1 = { 13, 13 };
			line = STAGE[ghost2.Y - 2];
			dot = line[ghost2.X];
			SetConsoleCursorPosition(h, ghost2);
			if (dot == 'o')
			{
				SetConsoleTextAttribute(h, 0x0f);
				cout << 'o';
			}
			else if (dot == '~' || dot == 'W')
			{
				SetConsoleTextAttribute(h, 0x07);
				cout << '.';
			}
			else
				cout << ' ';
			ghost2 = { 11, 16 };
			line = STAGE[ghost3.Y - 2];
			dot = line[ghost3.X];
			SetConsoleCursorPosition(h, ghost3);
			if (dot == 'o')
			{
				SetConsoleTextAttribute(h, 0x0f);
				cout << 'o';
			}
			else if (dot == '~' || dot == 'W')
			{
				SetConsoleTextAttribute(h, 0x07);
				cout << '.';
			}
			else
				cout << ' ';
			ghost3 = { 14, 16 };
			line = STAGE[ghost4.Y - 2];
			dot = line[ghost4.X];
			SetConsoleCursorPosition(h, ghost4);
			if (dot == 'o')
			{
				SetConsoleTextAttribute(h, 0x0f);
				cout << 'o';
			}
			else if (dot == '~' || dot == 'W')
			{
				SetConsoleTextAttribute(h, 0x07);
				cout << '.';
			}
			else
				cout << ' ';
			ghost4 = { 16, 16 };
			gTESTHIT(ghost1, 1);
			gTESTHIT(ghost2, 2);
			gTESTHIT(ghost3, 3);
			gTESTHIT(ghost4, 4);
		}
		else
		{

			gTESTHIT(ghost1, 1);
			gTESTHIT(ghost2, 2);
			gTESTHIT(ghost3, 3);
			gTESTHIT(ghost4, 4);
		}
		SetConsoleCursorPosition(h, HS);
		SetConsoleTextAttribute(h, 0x0f);
		cout << HIGHSCORE;
		Sleep(200);

		if (lives == 2)
		{
			SetConsoleCursorPosition(h, lives3);
			cout << ' ';
		}
		if (lives == 1)
		{
			SetConsoleCursorPosition(h, lives2);
			cout << ' ';
		}

		if (pelletTimer != 35)
			pelletTimer++;

		numpellets = 0;
		for (int i = 0; i < 31; i++)
		{
			temp = STAGE[i];
			for (int i2 = 0; i2 < 28; i2++)
			{

				if (temp[i2] == '~')
				{
					numpellets++;
				}
			}

		}


		int PDIS = 0;
		COORD PAUSEMENU = { 11, 16 };
		byte PCOLOR[4] = { 0x0f, 0x0B, 0x0E, 0x0D };
		int PCchoice = 0;

		while (pause == true)
		{
			if (PDIS == 0)
			{
				SetConsoleCursorPosition(h, PAUSEMENU);
				SetConsoleTextAttribute(h, 0x0f);

				PCchoice = rand() % 4;
				if (PCchoice == 0)
				{
					SetConsoleTextAttribute(h, PCOLOR[0]);
				}
				else if (PCchoice == 1)
				{
					SetConsoleTextAttribute(h, PCOLOR[1]);
				}
				else if (PCchoice == 2)
				{
					SetConsoleTextAttribute(h, PCOLOR[2]);
				}
				else
				{
					SetConsoleTextAttribute(h, PCOLOR[3]);
				}
				cout << "PAUSED";
			}
			move = _getch();
			if (move == VK_ESCAPE)
				pause = false, justpause = true;
		}

		
		if (justpause == true)
		{
			PDIS = 0;
			SetConsoleCursorPosition(h, PAUSEMENU);
			cout << "      ";
		}
	}
	
	if (lives == 0)
	{
		SetConsoleCursorPosition(h, lives1);
		cout << ' ';
	}
	Sleep(2500);


}





void TESTHIT(COORD &pos, char dir)
{
	COORD add;
	char test;
	string temp;
	bool torf;

	int gotocheck = 0;


start:
	torf = false;
	if (dir == 'a' || dir == KEY_LEFT)
		add.X = -1, add.Y = 0;
	if (dir == 'd' || dir == KEY_RIGHT)
		add.X = 1, add.Y = 0;
	if (dir == 'w' || dir == KEY_UP)
		add.X = 0, add.Y = -1;
	if (dir == 's' || dir == KEY_DOWN)
		add.X = 0, add.Y = +1;

	temp = STAGE[pos.Y + add.Y - 2];
	test = temp[pos.X + add.X];

	if (test == '1' || test == '2' || test == '3' || test == '4' || test == '+' || test == '-' || test == 'G')
	{
		torf = false;
	}
	if (test == 'T' || test == 'C' || test == '~' || test == 'X' || test == 'W')
	{
		torf = true;

		if (test == '~' || test == 'W')
		{
			HIGHSCORE = HIGHSCORE + 10;
		}
		if (test == 'C')
		{
			pelletTimer = 0;
			HIGHSCORE = HIGHSCORE + 50;
		}
	}

	if (torf == true)
	{
		lastmove = dir;
		gotocheck = 1;

		if (dir == 'a' || dir == KEY_LEFT)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << ' ';
			pos.X = pos.X - 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << '>';
		}
		if (dir == 'd' || dir == KEY_RIGHT)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << ' ';
			pos.X = pos.X + 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << '<';
		}
		if (dir == 'w' || dir == KEY_UP)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << ' ';
			pos.Y = pos.Y - 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << 'v';
		}
		if (dir == 's' || dir == KEY_DOWN)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << ' ';
			pos.Y = pos.Y + 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			cout << '^';
		}

	}
	if (torf == false && gotocheck != 1)
	{
		gotocheck = 1;
		dir = lastmove;
		goto start;
	}

}

void gTESTHIT(COORD &pos, int GNUM)
{
	int XorY = 0;
	int X = 0;
	int Y = 0;
	bool CANMOVE = false;
	string temp;
	char test;
	byte color[5];
	COORD one = { 13, 13 };
	COORD two = { 11, 16 };
	COORD three = { 14, 16 };
	COORD four = { 16, 16 };
	COORD start = { 0, 0 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int Xdis = 0;
	int Ydis = 0;
	bool MU = false;
	bool XdisCAN = false;

	color[0] = 0x00;
	color[1] = 0x0C;
	color[2] = 0x0B;
	color[3] = 0x0D;
	color[4] = 0x0A;

	Xdis = Pac.X - pos.X;
	if (Xdis > 0)
	{
		temp = STAGE[pos.Y  - 2];
		test = temp[pos.X + 1];

		if (test == '~' || test == 'T' || test == 'C')
			XdisCAN = true;
		else
			XdisCAN = false;
	}
	else
	{
		temp = STAGE[pos.Y - 2];
		test = temp[pos.X - 1];

		if (test == '~' || test == 'T' || test == 'C')
			XdisCAN = true;
		else
			XdisCAN = false;
	}

	Ydis = Pac.Y - pos.Y;
	if (Ydis > 0)
	{
		temp = STAGE[pos.Y - 1];
		test = temp[pos.X];

		if (test == '~' || test == 'T' || test == 'C')
			MU = true;
		else
			MU = false;
	}
	else
	{
		temp = STAGE[pos.Y - 3];
		test = temp[pos.X];

		if (test == '~' || test == 'T' || test == 'C')
			MU = true;
		else
			MU = false;
	}

	
	if (pos.X == one.X && pos.Y == one.Y)
	{
		SetConsoleCursorPosition(h, one);
		SetConsoleTextAttribute(h, 0x07);
		cout << '.';
	}
	if (pos.X == two.X && pos.Y == two.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x0B);
		cout << ' ';
		pos.X = pos.X + 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (two.X + 1) && pos.Y == two.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x0B);
		cout << ' ';
		pos.X = pos.X + 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (two.X + 2) && pos.Y == two.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x09);
		cout << ' ';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (two.X + 2) && pos.Y == (two.Y - 1))
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x09);
		cout << ' ';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (two.X + 2) && pos.Y == (two.Y - 2))
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x07);
		cout << '-';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
		//SetConsoleCursorPosition(h, pos);
		//cout << ' ';
	}
	else if (pos.X == three.X && pos.Y == three.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x09);
		cout << ' ';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == three.X && pos.Y == three.Y - 1)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x09);
		cout << ' ';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == three.X && pos.Y == (three.Y - 2))
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x07);
		cout << '-';
		SetConsoleTextAttribute(h, 0x09);
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == four.X && pos.Y == four.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x0B);
		cout << ' ';
		pos.X = pos.X - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (four.X - 1) && pos.Y == four.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x0B);
		cout << ' ';
		pos.X = pos.X - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (four.X - 2) && pos.Y == four.Y)
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x0B);
		cout << ' ';
		pos.X = pos.X - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (four.X - 2) && pos.Y == (four.Y - 1))
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x09);
		cout << ' ';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (pos.X == (four.X - 2) && pos.Y == (four.Y - 2))
	{
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 0x07);
		cout << '-';
		pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}
	else if (abs(Xdis) <= 7 && XdisCAN == true && (Pac.Y -pos.Y) == 0 && pelletTimer == 35)
	{ 
		temp = STAGE[pos.Y - 2];
		test = temp[pos.X];
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		if (test == '~')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			cout << '.';
		}
		if (test == 'T')
			cout << ' ';
		if (test == 'C')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
			cout << 'o';
		}

		if (Xdis > 0)
			pos.X = pos.X + 1;
		else
			pos.X = pos.X - 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
		XdisCAN = false;

	}
	else if (abs(Ydis) <= 7 && MU == true && abs(Pac.X - pos.X) == 0 && pelletTimer == 35)
	{
		temp = STAGE[pos.Y - 2];
		test = temp[pos.X];
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		if (test == '~')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			cout << '.';
		}
		if (test == 'T')
			cout << ' ';
		if (test == 'C')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
			cout << 'o';
		}

		if (Ydis > 0)
			pos.Y = pos.Y +1;
		else
			pos.Y = pos.Y - 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
		MU = false;

	}
	
	else

	{

		while (CANMOVE != true)
		{
			X = 0;
			Y = 0;
			XorY = rand() % 2;

			if (XorY == 0)
			{
				X = rand() % 2;

				if (X == 0)
					X = -1;
			}
			if (XorY == 1)
			{
				Y = rand() % 2;
				if (Y == 0)
					Y = -1;
			}

			temp = STAGE[pos.Y + Y - 2];
			test = temp[pos.X + X];

			if (test == '~' || test == 'T' || test == 'C')
				CANMOVE = true;
		}
		temp = STAGE[pos.Y - 2];
		test = temp[pos.X ];
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		if (test == '~')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
			cout << '.';
		}
		if (test == 'T')
			cout << ' ';
		if (test == 'C')
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
			cout << 'o';
		}

		pos.X = pos.X + X;
		pos.Y = pos.Y + Y;
		if (pelletTimer < 27)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
		}
		if (pelletTimer == 28)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
		}
		if (pelletTimer == 29)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
		}
		if (pelletTimer == 30)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
		}
		if (pelletTimer == 31)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);

		}
		if (pelletTimer == 32)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
		}
		if (pelletTimer == 33)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
		}
		if (pelletTimer == 34)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
			if (Hacks == true)
			pelletTimer = 0;
		}
		if (GNUM == 1 && pelletTimer == 35)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[0]);
		}
		if (GNUM == 2 && pelletTimer == 35)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[1]);
		}
		if (GNUM == 3 && pelletTimer == 35)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[2]);
		}
		if (GNUM == 4 && pelletTimer == 35)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[3]);
		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		if (pelletTimer == 35)
			SetConsoleTextAttribute(h, color[GNUM]);
		cout << 'W';
	}

}
