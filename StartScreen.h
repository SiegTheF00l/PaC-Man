#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

#ifndef STARTSCREEN
#define STARTSCREEN

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_RETURN 0x0D


class StartScreen
{
private:
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	string start[7];
	string options[4];
	string pc[14];
	string ctr;
	string hs;
	string cr;
	string control[22];
	string credits[22];
	string temp;
	byte DEFAULT = 0x77;
	byte HOVER = 0xff;
	byte PAC = 0xEE;
	byte BLANK = 0x00;
	byte cstart = 0xff;
	byte coptions = 0x77;
	byte cctr = 0x00f;
	byte chs = 0x07;
	byte cc = 0x07;
	int dec;

	void get();
	void PD(COORD);
	void clrPD(COORD);
	void SC(COORD);
	void ST(byte);
	void opt();
	void optget();
	void optDisplay();
	void end();
public:
	void Display();
	void menu();

};

void StartScreen::SC(COORD xy)
{
	SetConsoleCursorPosition(h, xy);
}

void StartScreen::ST(byte color)
{
	SetConsoleTextAttribute(h, color);
}

void StartScreen::get()
{
	start[0] = "SSSXSSSSSXXSSXXXSSXXSSSSS";
	start[1] = "SXSXXXSXXXSXXSXSXXSXXXSXX";
	start[2] = "SXXXXXSXXXSXXSXSXXSXXXSXX";
	start[3] = "SSSXXXSXXXSSSSXSSSXXXXSXX";
	start[4] = "XXSXXXSXXXSXXSXSXSXXXXSXX";
	start[5] = "SXSXXXSXXXSXXSXSXXSXXXSXX";
	start[6] = "SSSXXXSXXXSXXSXSXXSXXXSXX";

	options[0] = "OOOXOOOXOOOXOOOXOOOXOOXOXOO";
	options[1] = "OXOXOXOXXOXXXOXXOXOXOXOOXOX";
	options[2] = "OXOXOOOXXOXXXOXXOXOXOXOOXXO";
	options[3] = "OOOXOXXXXOXXOOOXOOOXOXXOXOO";


	pc[0] = "XXXXXXXXXXXX";
	pc[1] = "XXXXPPPPPXXX";
	pc[2] = "XXPPPPPPPPPX";
	pc[3] = "XPPPXPPPPPPP";
	pc[4] = "XPPXXXPPPPPP";
	pc[5] = "PPPPXPPPPPCC";
	pc[6] = "PPPPPPPCCCCC";
	pc[7] = "PPPPPCCCCCCC";
	pc[8] = "PPPPPPPCCCCC";
	pc[9] = "PPPPPPPPPPCC";
	pc[10] = "XPPPPPPPPPPP";
	pc[11] = "XPPPPPPPPPPP";
	pc[12] = "XXPPPPPPPPPX";
	pc[13] = "XXXXPPPPPXXX";
}

void StartScreen::PD(COORD pospc)
{
	for (int i = 0; i < 18; i++)
	{
		SC(pospc);

		temp = options[i];
		for (int x = 0; x < 11; x++)
		{
			if (temp[x] == 'P')
			{
				ST(PAC);
				cout << ' ';
			}
			if (temp[x] == 'X' || temp[x] == 'C')
			{
				ST(BLANK);
				cout << ' ';
			}

		}

		pospc.Y++;
	}
}

void StartScreen::clrPD(COORD pospc)
{
	for (int i = 0; i < 18; i++)
	{
		SC(pospc);

		temp = options[i];
		for (int x = 0; x < 11; x++)
		{
			if (temp[x] == 'P')
			{
				ST(BLANK);
				cout << ' ';
			}
			if (temp[x] == 'X')
			{
				ST(BLANK);
				cout << ' ';
			}

		}

		pospc.Y++;
	}
}
void StartScreen::Display()
{
	COORD pos = { 24, 3 };
	COORD pos2 = { 28, 11 };
	COORD pos3 = { 3, -1 };
	get();

	for (int i = 0; i < 7; i++)
	{
		SC(pos);
		temp = start[i];


		for (int x = 0; x < 25; x++)
		{
			if (temp[x] == 'S')
			{
				ST(cstart);
				cout << ' ';
			}
			if (temp[x] == 'X')
			{
				ST(BLANK);
				cout << ' ';
			}
		}
		pos.Y++;

	}

	//ST(0x07);
	for (int i = 0; i < 4; i++)
	{
		SC(pos2);

		temp = options[i];
		for (int x = 0; x < 28; x++)
		{
			if (temp[x] == 'O')
			{
				ST(coptions);
				cout << ' ';
			}
			if (temp[x] == 'X')
			{
				ST(BLANK);
				cout << ' ';
			}
		}

		pos2.Y++;
	}

	PD(pos3);

}

void StartScreen::menu()
{
	char key;
	dec = 1;

	Display();
	do
	{
		key = _getch();
		if (key == 's' || key == KEY_DOWN)
		{
			dec++;
			if (dec > 2)
				dec = 1;
		}

		if (key == 'w' || key == KEY_UP)
		{
			dec--;
			if (dec < 1)
				dec = 2;
		}


		if (dec == 1)
			cstart = HOVER, coptions = DEFAULT;
		if (dec == 2)
			cstart = DEFAULT, coptions = HOVER;
		Display();
		Sleep(200);
	} while (key != KEY_RETURN);

	if (dec == 1)
		end();
	else
		opt();
}

void StartScreen::end()
{
	COORD pos3 = { 3, -1 };

	clrPD(pos3);
	pos3.X++;
	for (int i = 0; i < 8; i++)
	{
		clrPD(pos3);
		pos3.X += 7;
		PD(pos3);
		Sleep(200);
	}
	Sleep(200);
	system("cls");


}


void StartScreen::optget()
{

	/*inFile.open("optionsmenu.txt");
	getline(inFile, ctr);
	getline(inFile, hs);
	getline(inFile, cr);
	for (int i = 0; i < 22; i++)
	getline(inFile, control[i]);
	for (int i = 0; i < 22; i++)
	getline(inFile, credits[i]);
	inFile.close();*/
	ctr = "Controls";
	hs = "High Score";
	cr = "Credits";

	control[0] = "------------";
	control[1] = "-XLeftXkeyX-";
	control[2] = "-XtoXXexitX-";
	control[3] = "------------";
	control[4] = "XXXXXXXXXXXX";
	control[5] = "X(WASD)XXXXX";
	control[6] = "XXXXXXXXXXXX";
	control[7] = "XXXXorXXXXXX";
	control[8] = "X^XXXXXXX|XX";
	control[9] = "X|,<_,_>,vXX";
	control[10] = "XXXXXXXXXXXX";
	control[11] = "XXXXX^XXXXXX";
	control[12] = "XUP:w,|XXXXX";
	control[13] = "XXXXXXXXXXXX";
	control[14] = "XDOWN:s,|XXX";
	control[15] = "XXXXXXXXvXXX";
	control[16] = "XXXXXXXXXXXX";
	control[17] = "XLEFT:a,<_XX";
	control[18] = "XXXXXXXXXXXX";
	control[19] = "XRIGHT:d,_>X";
	control[20] = "XXXXXXXXXXXX";
	control[21] = "XXXXXXXXXXXX";

	credits[0] ="XXXXXXXXXXXX";
	credits[1] = "XXXXXXXXXXXX";
	credits[2] = "XXX++X-XXX-XX";
	credits[3] = "XXX+XX--X--XX";
	credits[4] = "XXX+XX-X-X-X";
	credits[5] = "XXX++X-XXX-XX";
	credits[6] = "XXXXXXXXXXXX";
	credits[7] = "XXXXXXXXXXXX";
	credits[8] = "XBy:XXXXXXXX";
	credits[9] = "XChaseXXXXXX";
	credits[10] = "XMasonXXXXXX";
	credits[11] = "XXXXXXXXXXXX";
	credits[12] = "XBased offXX";
	credits[13] = "Xof:XXXXXXXX";
	credits[14] = "XPac/ManXXXX";
	credits[15] = "XXXXXXXXXXXX";
	credits[16] = "XXXXXXXXXXXX";
	credits[17] = "PeerXReview:";
	credits[18] = "XXXXXXXXXXXX";
	credits[19] = "XXXXXXXXXXXX";
	credits[20] = "XXXXXXXXXXXX";
	credits[21] = "XXXXXXXXXXXX";
}


void StartScreen::optDisplay()
{
	COORD line = { 45, 0 };
	ST(0x87);
	for (int i = 0; i < 25; i++)
	{
		SC(line);
		cout << "||";
		line.Y++;
	}

	COORD st = { 14, 7 };
	SC(st);

	ST(cctr);
	cout << ctr;

	COORD opt2 = { 15, 9 };
	SC(opt2);
	ST(chs);
	cout << hs;


	COORD opt3 = { 16, 11 };
	SC(opt3);
	ST(cc);
	cout << cr;

}
void StartScreen::opt()
{
	int counter = 1;
	char ke = NULL;
	system("cls");
	optget();

	do
	{

		if (ke == 'w' || ke == KEY_UP)
			counter--;
		if (ke == 's' || ke == KEY_DOWN)
			counter++;

		if (counter < 1)
			counter = 3;
		if (counter > 3)
			counter = 1;

		if (counter == 1)
		{
			COORD sdr = { 57, 0 }; // start drawing at
			cctr = 0x0f;
			chs = 0x07;
			cc = 0x07;

			optDisplay();
			for (int i = 0; i < 22; i++)
			{
				SC(sdr);
				temp = control[i];
				for (int count = 0; count < 13; count++)
				{

					if (temp[count] == 'X')
					{
						ST(BLANK);
						cout << ' ';
					}
					else if (temp[count] == '-')
					{
						ST(0x4c);
						cout << '=';
					}
					else if (temp[count] == '_')
					{
						ST(0x07);
						cout << '-';
					}
					else
					{
						ST(0x07);
						cout << temp[count];
					}

				}
				sdr.Y++;
			}

		}
		else if (counter == 2)
		{
			COORD sdr = { 57, 0 };

			cctr = 0x07;
			chs = 0x0f;
			cc = 0x07;

			optDisplay();
			ST(BLANK);
			for (int i = 0; i < 22; i++)
			{
				SC(sdr);
				cout << "             ";
				sdr.Y++;
			}
		}
		else if (counter == 3)
		{
			COORD sdr = { 57, 0 }; // start drawing at
			cctr = 0x07;
			chs = 0x07;
			cc = 0x0f;

			optDisplay();
			for (int i = 0; i < 22; i++)
			{
				SC(sdr);
				temp = credits[i];
				for (int count = 0; count < 13; count++)
				{

					if (temp[count] == 'X')
					{
						ST(BLANK);
						cout << ' ';
					}

					else if (temp[count] == '+')
					{
						ST(0x99);
						cout << ' ';
					}

					else if (temp[count] == '-')
					{
						ST(0xDD);
						cout << ' ';
					}
					else if (temp[count] == '/')
					{
						ST(0x07);
						cout << '-';
					}

					else
					{
						ST(0x07);
						cout << temp[count];
					}

				}
				sdr.Y++;
			}
		}
		ke = _getch();
		Sleep(200);
	} while (ke != KEY_LEFT && ke != 'a');

	system("cls");

	cstart = 0xff;
	coptions = 0x77;
	menu();
}
#endif
