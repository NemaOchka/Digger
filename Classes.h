#include <iostream>	
#include <conio.h>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

void ShowConsoleCursor(bool showFlag);
int Check_Pressed_Button();

struct Check_Score {
	int score1 = 0;
	vector <COORD> gems1;
};
struct Game_Result {
	int score, time;
	string name;
};

class Window {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD menu = { 58, 4 }, line = { 45, 5 }, play = { 58, 11 }, score_list = { 55, 14 }, instruction = { 55, 17 }, exit = { 58, 20 }, arrow = { 4, 26 }, enter = { 4, 27 };  //coord of menu parts
	DWORD dwNumWritten;

public:
	void Box();
	void Menu();
	int Menu_Result();
	int Score_Board(vector <Game_Result> b);
	int Insturction();
};

class Game {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwNumWritten;

public:
	Game_Result Game_Play();
	void Map();
	vector <COORD> Gems();
	COORD Body_Creating(COORD coord, int attribute);
	COORD Move(int direction, COORD coord, int attribute);
	int Direction();
	Game_Result Game_End(int score, int time_of_game);
	Check_Score Check_Gems(int score, COORD coord, vector <COORD> gems);
};