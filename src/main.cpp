#include <vector>
#include <SFML\Graphics.hpp>
#include "RenderManager.h"
#include "StaticSprite.h"
#include "StandardTexture.h"
#include "AnimationSprite.h"
#include "RectTexture.h"

int main()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	sf::RenderWindow window(sf::VideoMode(modes[0].width, modes[0].height), "SFML works!", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	RenderManager renderManger("", &window);

	std::string str = "bild1.png";
	std::string str2 = "bild2.png";
	StaticSprite<StandardTexture> test(str, 100);
	StaticSprite<StandardTexture> test2(str, 10);
	AnimationSprite<RectTexture> test3("info.txt", 1000, true, sf::milliseconds(10000 / 24), false, true);
	test.setPosition(0, 0);
	test2.setPosition(100, 200);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				test2.SetZIndex(1000);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				test2.SetZIndex(10);
			}
		}

		window.clear();
		renderManger.Draw();
		window.display();
	}

	return 0;
}