#include "game.h"

void printText(float r, float g, float b, float x, float y, std::string text) {
	int i;
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

void printModeName(enum mode m) {
	switch (m) {
	case NORMAL:
		std::cout << "NORMAL mode\n";
		break;
	case ALLPASS:
		std::cout << "All PASS mode\n";
		break;
	case ALLFAIL:
		std::cout << "ALL FAIL mode\n";
		break;
	}
}

Game::Game()
{
	mode = NORMAL;
}

void Game::changeMode(enum mode m)
{
	mode = m;
	printModeName(m);
}

void Game::printTitle()
{
	float x = 0.0;
	float y = 0.1;

	printText(0.9, 0.9, 0.9, x-0.3, y, "Fortress");
	printText(0.9, 0.9, 0.9, x-0.6, y-= 0.1, "Press ENTER to play");
	printText(0.9, 0.9, 0.9, x-0.6, y -= 0.3, "developed by DimSum");
}

void Game::printGameOver()
{
	float x = 0.0;
	float y = 0.0;

	printText(0.9, 0.0, 0.0, x, y, "GAME OVER...");
}

void Game::printStatus()
{
	float x = -1.0;
	float y = 1.0;

	printText(0.9, 0.9, 0.9, x, y, "hello");
	printText(0.9, 0.9, 0.9, x, y -= 0.1, "world");
}
