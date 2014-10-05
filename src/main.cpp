#include <vector>
#include <SFML\Graphics.hpp>
#include "RenderManager.h"
#include "StaticSprite.h"
#include "StandardTexture.h"
#include "AnimationSprite.h"
#include "RectTexture.h"
#include "Grid.h"
#include "SidePanel.h"

int main()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	sf::RenderWindow window(sf::VideoMode(modes[0].width, modes[0].height), "SFML works!", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	RenderManager renderManger("", &window);
	StaticSprite<StandardTexture> test("bild1.png", 1000000, true);

	Grid grid(std::string("field.txt"), 250, 250);
	SidePanel sidepanel(1400, 400);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i pos = sf::Mouse::getPosition();
				sidepanel.Update(pos);
				test.setPosition(pos.x, pos.y);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sidepanel.SetSelector();
			}

		}

		window.clear();
		renderManger.Draw();
		window.display();
	}

	return 0;
}