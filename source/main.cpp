/*
	Project Title : Centipede
	Date : 1/24/2018
	Description : Recreate classic arcade game centipede
*/

#include "stdafx.h"
#include <ctime>
#include "CentipedeGame.h"
using namespace std;

void splashScreen(sf::RenderWindow&);

int main() {

	std::time_t seed = time(NULL);
	srand(seed);

	sf::Vector2u winDim(480, 504);

	sf::RenderWindow window(sf::VideoMode(winDim.x, winDim.y), "Centipede", sf::Style::Resize | sf::Style::Close);

	CentipedeGame game(&window, winDim);

	window.setFramerateLimit(60);
	//window.setKeyRepeatEnabled(false);

	bool frameByFrameMode(false), enterPressed(false);

	sf::Event event;

	splashScreen(window);

	while (window.isOpen()) {


		if (frameByFrameMode) {
			if (enterPressed) {
				game.update();
				enterPressed = false;
			}
		}
		else
			game.update();


		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {//resize to keep original aspect ratio

                //Notice: Unexpected behaviour on XFCE which prevents window from being resized by the application, presumembly a bug in SFML
                //In order to get the expected window, maximise and then un-maximise the window

                winDim.x = event.size.width;
                winDim.y = static_cast<int>(static_cast<float>(event.size.width) * 1.05);
				window.setSize(winDim);
			}
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::F1)
					frameByFrameMode = !frameByFrameMode;
				else if (event.key.code == sf::Keyboard::Return)
					enterPressed = true;
		}
	}

	return 0;
}

void splashScreen(sf::RenderWindow &window) {
    sf::Texture startingScreen;
	startingScreen.loadFromFile("../Sprites/startscreen.png");

	sf::Sprite sprite;
	sprite.setTexture(startingScreen);
	sprite.setScale(1.95f, 2.05f);

	window.draw(sprite);
	window.display();

	while (!(sf::Mouse::getPosition(window).x > 185 &&
        sf::Mouse::getPosition(window).x < 305 &&
		sf::Mouse::getPosition(window).y > 335 &&
		sf::Mouse::getPosition(window).y < 385 &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))) {}

    window.setMouseCursorVisible(false);
}
