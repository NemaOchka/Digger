#include "Classes.h"

//Виправити баг з буферизацією name

int main() {
	system("title Digger");
	ShowConsoleCursor(FALSE);

	Window window;
	Game game;
	Game_Result result;
	vector <Game_Result> b;
	int menu;

	window.Box();
	while (1) {
		window.Menu();
		menu = window.Menu_Result();
		switch (menu) {
			case 1: {
				result = game.Game_Play();
				b.push_back(result);
			} break;
			case 2: {
				window.Score_Board(b);
			} break;
			case 3: {
				window.Insturction();
			} break;
			case 0: {
				return 0;
			}break;
		}
	}
}