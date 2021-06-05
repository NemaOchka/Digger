#include "Classes.h"

void Window::Box() {
	//paint grey oulline
	SetConsoleScreenBufferSize(handle, { 119, 29 });
	unsigned char c = 176;
	COORD coordA = { 0,0 }, coordB = { 119, 29 };
	COORD coordAtemp = coordA, coordBtemp = coordB;
	SetConsoleCursorPosition(handle, coordA);

	for (int k = 1, t = 0; t < 2;) {
		for (int l = 0; l < 2; l++) {
			if (t % 2 == 0) {
				for (; coordAtemp.X <= coordB.X && coordAtemp.X >= 0 + t; coordAtemp.X += k) {
					SetConsoleCursorPosition(handle, coordAtemp);
					cout << c;
				}
			}

			if (k > 0) {
				coordAtemp.X = coordB.X;
			}
			else {
				coordAtemp.X = 0 + t;
			}

			for (; coordAtemp.Y <= coordB.Y && coordAtemp.Y >= 0 + t; coordAtemp.Y += k) {
				SetConsoleCursorPosition(handle, coordAtemp);
				cout << c;
			}
			k = -k;
			coordAtemp.X--;
			coordAtemp.Y--;
		}
		coordB.X--;
		t++;
		coordAtemp.X = coordA.X + t;
		if (t % 2 != 0) {
			coordAtemp.Y = coordA.Y + t;
			coordB.Y--;
		}
	}

	coordA = { 2, 1 };
	vector <unsigned char> b = { 201, 205, 187, 186, 188, 205, 200, 186, 0 };

	//paint strict outline
	SetConsoleCursorPosition(handle, coordA);
	for (int i = 0, j = 0, k = 1; i < 2; i++, j++, k = -k, coordA.X -= 2, coordA.Y) {
		c = b[j];
		cout << c;
		j++;
		c = b[j];
		for (coordA.X++; coordA.X < coordB.X && coordA.X >= 2; coordA.X += k) {
			SetConsoleCursorPosition(handle, coordA);
			cout << c;
		}
		j++;
		if (k < 0) {
			coordA.X++;
			SetConsoleCursorPosition(handle, coordA);
		}
		c = b[j];
		cout << c;
		j++;
		c = b[j];
		if (k < 0) {
			coordA.Y -= 2;
			SetConsoleCursorPosition(handle, coordA);
		}
		for (coordA.Y++; coordA.Y < coordB.Y && coordA.Y > 1; coordA.Y += k) {
			SetConsoleCursorPosition(handle, coordA);
			cout << c;
		}
		SetConsoleCursorPosition(handle, coordA);
	}
}

void Window::Menu() {
	COORD coord0 = { 3, 2 };
	vector <COORD> a = { menu, line, play, score_list, instruction, exit, arrow, enter };
	vector <string> b = { "Menu", "-----------------------------", "Play", "Score  list", "Instruction", "Exit", "Press ARROW to move...", "Press ENTER to choose..." };

	for (int i = 0; i < 29 - 3; coord0.Y++, i++) {
		FillConsoleOutputAttribute(handle, 0, 119 - 5, coord0, &dwNumWritten);
	}
	for (int i = 0; i < 8; i++) {
		SetConsoleCursorPosition(handle, a[i]);
		cout << b[i];
	}
}

int Window::Menu_Result() {
	COORD now;
	int result = 0;
	now = play;
	SetConsoleCursorPosition(handle, now);
	SetConsoleTextAttribute(handle, 11);
	cout << "Play";
	SetConsoleTextAttribute(handle, 15);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	while (1) {
		result = _getch();

		if (result == 80) {
			PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
			SetConsoleTextAttribute(handle, 15);				// Checking where you are, so depending from the arrow you press, move up or down
			this->Menu();										// The direction of move depends from the coord.Y you at right now, then its changes
			SetConsoleTextAttribute(handle, 11);
			if (now.Y == 11) {
				now = score_list;
				SetConsoleCursorPosition(handle, now);
				cout << "Score  list";

			}
			else if (now.Y == 14) {
				now = instruction;
				SetConsoleCursorPosition(handle, now);
				cout << "Instruction";
			}
			else if (now.Y == 17) {
				now = exit;
				SetConsoleCursorPosition(handle, now);
				cout << "Exit";
			}
			else if (now.Y == 20) {
				now = play;
				SetConsoleCursorPosition(handle, now);
				cout << "Play";
			}
			SetConsoleTextAttribute(handle, 15);
		}
		else if (result == 72) {
			PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
			SetConsoleTextAttribute(handle, 15);
			this->Menu();
			SetConsoleTextAttribute(handle, 11);
			if (now.Y == 11) {
				now = exit;
				SetConsoleCursorPosition(handle, now);
				cout << "Exit";

			}
			else if (now.Y == 14) {
				now = play;
				SetConsoleCursorPosition(handle, now);
				cout << "Play";
			}
			else if (now.Y == 17) {
				now = score_list;
				SetConsoleCursorPosition(handle, now);
				cout << "Score  list";
			}
			else if (now.Y == 20) {
				now = instruction;
				SetConsoleCursorPosition(handle, now);
				cout << "Instruction";
			}
			SetConsoleTextAttribute(handle, 15);
		}
		else if (result == 13) {		// Return the otion that you chose in menu
			PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (now.Y == 11) {
				return 1;	//Play
			}
			else if (now.Y == 14) {
				return 2;	//Score  list
			}
			else if (now.Y == 17) {
				return 3;	// Instruction
			}
			else if (now.Y == 20) {
				return 0;	// Exit
			}
		}
	}
}

int Window::Score_Board(vector <Game_Result> b) {
	COORD coord0 = { 3, 2 }, table = { 54, 3 }, list = { 44, 6 }, exit = { 4, 26 };
	DWORD dwNumWritten;
	int key;
	for (int i = 0; i < 26; coord0.Y++, i++) {
		FillConsoleOutputAttribute(handle, 0, 114, coord0, &dwNumWritten);		// Clear background
	}
	SetConsoleCursorPosition(handle, table);
	cout << "Score List";
	if (!b.size()) {
		SetConsoleCursorPosition(handle, list);
		cout << "You haven`t play any game yet!";
	}
	else {
		for (unsigned int i = 0; i < b.size(); i++) {						// We use unsingned? because it is type of b.size()
			Game_Result max = b[i];
			for (unsigned int j = i + 1; j < b.size(); j++) {				// Sort array of played games
				if (max.score < b[j].score) {
					max = b[j];
					b[j] = b[i];
					b[i] = max;
				}
				else if (max.score == b[j].score) {
					if (max.time > b[j].time) {
						max = b[j];
						b[j] = b[i];
						b[i] = max;
					}
				}
			}
		}
		int k = b.size();
		if (b.size() > 10) k = 10;
		for (int i = 0; i < k; i++, list.Y += 2) {					// Output top 10 best game`s result
			SetConsoleCursorPosition(handle, list);
			cout << i + 1 << ". " << b[i].name << " " << b[i].score << " " << b[i].time / 60000 << "min " << b[i].time % 60000 / 1000 << "sec";
		}
	}

	SetConsoleCursorPosition(handle, exit);
	cout << "Press ESC to exit...";

	while (1) {
		key = _getch();
		if (key == 27) {
			PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;
		}
	}
}

int Window::Insturction() {
	COORD coord0 = { 3, 2 }, instr = { 55, 4 }, text = { 25, 7};
	vector <string> a = { "In this game you have to move your character (white dot) through",	"ARROWS. You cannot cross though the box line, so be attention.", 
		"Your goal is to gether as much gems as you can, unless enemy (red",	"dot) reach you. Every game there are will be two types of gems: one", 
		"of them is the static one - they will be on the same place each game,", "anothe one - is dynamic, their location will be randomly changed each", 
		"game. That`s all. Be clever, find the shortest way and do your best!" };
	int res;

	for (int i = 0; i < 29 - 3; coord0.Y++, i++) {
		FillConsoleOutputAttribute(handle, 0, 119 - 5, coord0, &dwNumWritten);
	}

	SetConsoleCursorPosition(handle, instr);
	cout << "Instruction";
	SetConsoleCursorPosition(handle, line);
	cout << "-----------------------------";			// Print text
	for (int i = 0; i < 7; i++, text.Y += 2) {
		SetConsoleCursorPosition(handle, text);
		cout << a[i];
	}
	SetConsoleCursorPosition(handle, enter);
	cout << "Press ESC to quit...";

	while (1) {				// For exiting needed to ESC be pressed
		res = _getch();
		if (res == 27) {
			PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;
		}
	}
}