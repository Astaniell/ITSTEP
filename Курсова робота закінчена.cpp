#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
const int NotUsed = system("color 13");
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int max = 0;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic(int difficul)
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	
	if (difficul == 1)
	{
		if (x > width || x < 0 || y > height || y < 0)
			gameOver = true;
	}
	else if (difficul == 2)
	{

		if (x >= width)
			x = 0;
		else if (x < 0)
			x = width - 1;
		if (y >= height)
			y = 0;
		else if (y < 0)
			y = height - 1;

		for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}
int main()
{
	setlocale(0, "");
	cout << "\t\t\t  Hello! I`m a snake-game!" << endl;

	Sleep(2000);
	system("cls");
	//while (true)
	//{
		gameOver = false;
		//system("cls");
		cout << "\t\t\t  Enter your choice" << endl;
		int choice_menu;
		cout << "\t\t  1)Start game, 2) GameStat, 3)Exit" << endl;
		cin >> choice_menu;
		cin.ignore(256,'\n');
		switch (choice_menu)
		{//switch
		case 1:
		{//case 1
				  cout << "Enter name!" << endl;
				  string name;
				  getline(cin, name);
				  cout << "Enter difficul" << endl;
				  cout << "1)Hard; 2)Easy" << endl;
				  int choice_game;
				  cin >> choice_game;
				  cin.ignore(256, '\n');
				  Setup();
				  while (!gameOver)
				  {
					  Draw();
					  Input();
					  Logic(choice_game);
					  Sleep(150); //sleep(10);
				  }
				  ofstream gameStat;
				  gameStat.open("GameStat.txt");
				  gameStat << name <<":   "<< score << endl;
				  gameStat.close();
				  system("cls");
				  cout << "\t\t\t\tGame Over" << endl;
				  cout << "\t\t\t\tYout score: " << score << endl;
				  break;
		}//case1
		case 2:
		{//cace2
				  char buff[50];
				  cout << "Последний результат: " << endl;
				  cout << "___________" << endl;

				  ifstream statistik("GameStat.txt");
				  statistik.getline(buff, 50);
				  cout << buff << endl;
				  Sleep(5000);
				  break;
		}//case2





		}//switch
		if (choice_menu == 3)
			exit; 
//	}
	

		cout << "\t\t\t\tBYE! See you later" << endl;
	system("pause");
}
