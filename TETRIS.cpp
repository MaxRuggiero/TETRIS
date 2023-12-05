#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <fstream>

using namespace std;
using namespace sf;

int main() {

	Board board;

	RenderWindow window(VideoMode(400, 404), "Tetris");
	window.setFramerateLimit(60);

	board.InstallPart();

	int right = 0, left = 0, up = 0;

	bool live = 1;


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		if (live) {
			if (Keyboard::isKeyPressed(Keyboard::W) && !up) board.RotatePart(), up = 1;
			else if (!Keyboard::isKeyPressed(Keyboard::W)) {
				up = 0;
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) board.UpdateLimitTimer(5);
			else board.UpdateLimitTimer(30);

			if (Keyboard::isKeyPressed(Keyboard::D) && !right) {
				board.Right();
				right = 1;
			}
			else if (!Keyboard::isKeyPressed(Keyboard::D)) {
				right = 0;
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) && right) {
				right++;
				if (right == 6) right = 0;
			}

			if (Keyboard::isKeyPressed(Keyboard::A) && !left) {
				board.Left();
				left = 1;
			}
			else if (!Keyboard::isKeyPressed(Keyboard::A)) {
				left = 0;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) && left) {
				left++;
				if (left == 6) left = 0;
			}

			if (board.UpdateBoard()) {
				if (!board.InstallPart()) {
					live = 0;
					board.ClearBoard();
				}
			}
			board.UpdateBoardColors();
		}

		window.clear(Color(30, 30, 30));
		window.draw(board);
		window.display();
	}
	return 0;
}