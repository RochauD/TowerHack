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
	test.setPosition(0, 0);


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

			}

		}

		window.clear();
		test.Render(&window);
		renderManger.Draw();
		window.display();
	}

	return 0;
}