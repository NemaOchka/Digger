#include "Classes.h"

Game_Result Game::Game_Play() {
	PlaySound(TEXT("background.wav"), NULL, SND_ASYNC);
	vector <COORD> gems;
	vector <int> movements;
	COORD player_coord = { 61, 26 }, enemy_coord = { 114, 3 };
	clock_t start_t = clock();
	Check_Score result;
	int player_attribute = 255, enemy_attribute = 68, delay = 100, direction, buffer, i = 0, score = 0, time = start_t, time_of_game = start_t, difficulty = start_t;
	for (int i = 0; i < 24; i++) movements.push_back(4);
	for (int i = 0; i < 23; i++) movements.push_back(3);			// The way enemy has to cross to the first player coordinats
 	for (int i = 0; i < 29; i++) movements.push_back(4);
	this->Map();
	this->Body_Creating(player_coord, player_attribute);
	this->Body_Creating(enemy_coord, enemy_attribute);
	gems = this->Gems();

	while (1) {
		if (clock() - start_t > 10) {
			if (player_coord.X == enemy_coord.X && player_coord.Y == enemy_coord.Y) {			// Checking if the enemy approach to player
				time_of_game = clock() - time_of_game;
				PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
				return this->Game_End(score, time_of_game);
			}
		}
		if (clock() - start_t > delay) {
			buffer = movements[i];
			i++;
			enemy_coord = this->Move(buffer, enemy_coord, enemy_attribute);			// Moving enemy
			start_t = clock();
		}
		direction = this->Direction();
		if (direction && clock() - time > 100) {
			player_coord = this->Move(direction, player_coord, player_attribute);
			result = this->Check_Gems(score, player_coord, gems);
			score = result.score1;
			gems = result.gems1;
			movements.push_back(direction);		// Remembering where you went
			direction = 0;
			time = clock();
			if (score == 4000) {
				time_of_game = clock() - time_of_game;
				PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
				return Game_End(score, time_of_game);
			}
			if (clock() - difficulty > 1500) {
				delay -= 1;
				difficulty = clock();
			}
		}
	}
}

void Game::Map() {
	COORD coord0 = { 3, 2 };
	COORD A = { 10, 5 };
	COORD B = { 70, 26 };
	DWORD dwNumWritten;

	for (int i = 0; i < 26; coord0.Y++, i++) {
		FillConsoleOutputAttribute(handle, 136, 114, coord0, &dwNumWritten);		// Paint all workplace in grey (color of ground)
	}

	int arr[6] = { 15, 8, 3, 17, 3, 55 }, k = 0;

	for (int j = 0; j < 3; j++, k++) {
		for (int i = 0; i < arr[k]; i++) {
			FillConsoleOutputAttribute(handle, 0, 1, A, &dwNumWritten);				// Painting the route
			A.Y++;
		}
		k++;
		for (int i = 0; i < arr[k]; i++) {
			FillConsoleOutputAttribute(handle, 0, 1, A, &dwNumWritten);
			A.X++;
		}

	}

	for (int i = 0; i < 23; A.Y--, i++) {
		FillConsoleOutputAttribute(handle, 0, 1, A, &dwNumWritten);					// Painting the route
	}							

	for (int i = 0; i < 25; A.X++, i++) {
		FillConsoleOutputAttribute(handle, 0, 1, A, &dwNumWritten);
	}

	for (int i = 0; i < 21; B.Y--, i++) {
		FillConsoleOutputAttribute(handle, 0, 1, B, &dwNumWritten);					// Painting the route
	}

	for (int i = 0; i < 27; B.X--, i++) {
		FillConsoleOutputAttribute(handle, 0, 1, B, &dwNumWritten);
	}

	for (int i = 0; i < 5; B.Y++, i++) {
		FillConsoleOutputAttribute(handle, 0, 1, B, &dwNumWritten);
	}
}

vector <COORD> Game::Gems() {
	COORD cryst1 = { 22, 8 }, cryst2 = { 96, 15 }, cryst3 = { 111, 26 }, temp_coord, banned_coord = { 115, 3 };
	DWORD dwNumWritten;
	vector <COORD> a; // vector of gems coord
	vector <COORD> b; // vector of coord where enymy will be going
	SetConsoleCursorPosition(handle, cryst1);
	srand((unsigned int)time(NULL));

	for (int k = 25, j = 0; j < 2 ; k += 3, j++) {
		for (int i = 0; i < k; i++) {
			banned_coord.X--;
			b.push_back(banned_coord);
		}
		if (!j) {
			for (int i = 0; i < 23; i++, banned_coord.Y++) {
				b.push_back(banned_coord);
			}
		}
	}


	for (int i = 0; i < 3; i++, cryst1.X += 2, cryst1.Y -= 8) {
		for (int j = 0; j < 4; j++, cryst1.Y += 2) {
			FillConsoleOutputAttribute(handle, 34, 1, cryst1, &dwNumWritten);		// Creating 1 group of gems
			a.push_back(cryst1);
		}
	}

	for (int i = 0; i < 6; i++, cryst2.X += 2, cryst2.Y -= 4) {
		for (int j = 0; j < 2; j++, cryst2.Y += 2) {
			FillConsoleOutputAttribute(handle, 34, 1, cryst2, &dwNumWritten);		// Creating 2 group of gems
			a.push_back(cryst2);
		}
	}
		

	for (int i = 0, k = 1; i < 3; i++, k++, cryst3.X += 2, cryst3.Y = 26) {
		for (int j = 0; j < k; j++, cryst3.Y -= 2) {
			FillConsoleOutputAttribute(handle, 34, 1, cryst3, &dwNumWritten);		// Creating 3 group of gems
			a.push_back(cryst3);
		}
	}

	for (int i = 0, k = 1; i < 10; i++, k = 1) {
		int x = rand() % 113 + 3, y = rand() % 25 + 2;								// Randomly spawning 10 gems
		for (unsigned int j = 0; j < a.size(); j++) {			
			if (x == a[j].X && y == a[j].Y) k = 0;	// Cheking if there isn`t already spawned gems or it on the way of enemy
		}
		for (unsigned int g = 0; g < b.size(); g++) {		// Using unsigned, because it is type of b.size()
			if (x == b[g].X && y == b[g].Y) k = 0;
		}
		if (k) {
			temp_coord.X = x;
			temp_coord.Y = y;
			FillConsoleOutputAttribute(handle, 34, 1, temp_coord, &dwNumWritten);
			a.push_back(temp_coord);
		}
		else i--;
	}

	return a;
}

COORD Game::Body_Creating(COORD coord, int attribute) {
	FillConsoleOutputAttribute(handle, attribute, 1, coord, &dwNumWritten);

	return coord;
}

COORD Game::Move(int direction, COORD coord, int attribute) {
	FillConsoleOutputAttribute(handle, 0, 1, coord, &dwNumWritten);
	switch (direction) {
	case 1: if (coord.Y - 1 != 1) coord.Y--; break;				// Checkong if we are not crossing the board!
	case 2: if (coord.X + 1 != 117) coord.X++; break;
	case 3: if (coord.Y + 1 != 28) coord.Y++; break;
	case 4: if (coord.X - 1 != 2) coord.X--; break;
	case 0:; break;
	}
	SetConsoleCursorPosition(handle, coord);
	FillConsoleOutputAttribute(handle, attribute, 1, coord, &dwNumWritten);

	return coord;
}

int Game::Direction() {
	if (GetKeyState(VK_UP) == -127 || GetKeyState(VK_UP) == -128) {
		return 1;
	}
	else if (GetKeyState(VK_RIGHT) == -127 || GetKeyState(VK_RIGHT) == -128) {
		return 2;
	}
	else if (GetKeyState(VK_DOWN) == -127 || GetKeyState(VK_DOWN) == -128) {
		return 3;
	}
	else if (GetKeyState(VK_LEFT) == -127 || GetKeyState(VK_LEFT) == -128) {
		return 4;
	}
	else return 0;
}

Game_Result Game::Game_End(int score, int time_of_game) {
	COORD background = { 35, 9 }, lose_or_win = { 56, 10 }, enter_name = { 38, 17 }, score1 = { 38, 13 }, time1 = { 38, 15 };
	DWORD dwNumWritten;
	string name;

	for (int i = 0; i < 10; i++, background.Y++) {
		FillConsoleOutputAttribute(handle, 0, 49, background, &dwNumWritten);
	}
	SetConsoleTextAttribute(handle, 15);
	SetConsoleCursorPosition(handle, lose_or_win);
	if (score == 4000) {
		cout << "You win!";
	}
	else {
		cout << "You lose!";
	}

	SetConsoleCursorPosition(handle, score1);
	cout << "Score: " << score;

	SetConsoleCursorPosition(handle, time1);
	cout << "Time: " << time_of_game / 60000 << "min " << time_of_game % 60000 / 1000 << "sec";

	SetConsoleCursorPosition(handle, enter_name);
	cout << "Enter your name: ";
	cin.clear();
	fflush(stdin);
	cin >> name;
	PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Game_Result result = { score, time_of_game, name };

	return  result;
}

Check_Score Game::Check_Gems(int score, COORD coord, vector <COORD> gems) {
	for (int i = 0; i < 40; i++) {
		if (coord.X == gems[i].X && coord.Y == gems[i].Y) {
			score += 100;
			//PlaySound(TEXT("gem.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gems[i] = { 0, 0 };
		}
	}
	Check_Score result = { score, gems };

	return result;
}