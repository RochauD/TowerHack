#ifndef SIDEPANEL_H_
#define SIDEPANEL_H_

#include <vector>
#include "StaticSprite.h"
#include "StandardTexture.h"

class SidePanel
{
public:
	SidePanel(size_t offsetX, size_t offsetY);
	void Update(sf::Vector2i position);
	void SetSelector();

private:
	size_t m_offsetX;
	size_t m_offsetY;
	std::vector<std::unique_ptr<StaticSprite<StandardTexture>>> m_elements;
	std::vector<std::unique_ptr<StaticSprite<StandardTexture>>> m_elementsHover;
	std::pair<bool, int> currentSelected;
	


	int selected;
};

#endif