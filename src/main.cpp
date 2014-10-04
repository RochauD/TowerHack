#include <SFML\Graphics.hpp>
#include "RenderManager.h"
#include "StaticSprite.h"
#include "StandardTexture.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");
	window.setVerticalSyncEnabled(true);
	RenderManager renderManger("", &window);

	std::string str = "bild1.png";
	StaticSprite<StandardTexture> test(str, 100);
	StaticSprite<StandardTexture> test2(str, 10);
	test.setPosition(0, 0);
	test2.setPosition(10, 20);


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