#include "SidePanel.h"

bool isInRect(int x, int y, int top, int left, int width, int height)
{
	if (x >= left && x <= (left + width))
	{
		if (y >= top && y <= (top + height))
		{
			return true;
		}
	}
	return false;
}

SidePanel::SidePanel(size_t offsetX, size_t offsetY)
{
	currentSelected = std::make_pair(false, 0);
	this->m_elements.resize(2);
	this->m_elementsHover.resize(2);
	selected = 0;

	this->m_offsetX = offsetX;
	this->m_offsetY = offsetY;
	StandardTexture* temp;

	this->m_elements[0] = std::unique_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
	temp = this->m_elements[0]->GetTexture();
	temp->LoadTexture("tower1panel.png");
	this->m_elements[0]->SetZIndex(10001);
	this->m_elements[0]->SetVisibilityFlag(false);
	this->m_elements[0]->Show(true);
	this->m_elements[0]->UpdatePositions();
	this->m_elements[0]->UpdateTexCoords();
	this->m_elements[0]->setPosition(static_cast<float>(this->m_offsetX), static_cast<float>(this->m_offsetY));

	this->m_elements[1] = std::unique_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
	temp = this->m_elements[1]->GetTexture();
	temp->LoadTexture("tower2panel.png");
	this->m_elements[1]->SetZIndex(10001);
	this->m_elements[1]->SetVisibilityFlag(false);
	this->m_elements[1]->Show(true);
	this->m_elements[1]->UpdatePositions();
	this->m_elements[1]->UpdateTexCoords();
	this->m_elements[1]->setPosition(static_cast<float>(this->m_offsetX), static_cast<float>(this->m_offsetY+40));

	this->m_elementsHover[0] = std::unique_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
	temp = this->m_elementsHover[0]->GetTexture();
	temp->LoadTexture("tower1panelhover.png");
	this->m_elementsHover[0]->SetZIndex(10001);
	this->m_elementsHover[0]->SetVisibilityFlag(false);
	this->m_elementsHover[0]->UpdatePositions();
	this->m_elementsHover[0]->UpdateTexCoords();
	this->m_elementsHover[0]->setPosition(static_cast<float>(this->m_offsetX), static_cast<float>(this->m_offsetY));

	this->m_elementsHover[1] = std::unique_ptr<StaticSprite<StandardTexture>>(new StaticSprite<StandardTexture>);
	temp = this->m_elementsHover[1]->GetTexture();
	temp->LoadTexture("tower2panelhover.png");
	this->m_elementsHover[1]->SetZIndex(10001);
	this->m_elementsHover[1]->SetVisibilityFlag(false);
	this->m_elementsHover[1]->UpdatePositions();
	this->m_elementsHover[1]->UpdateTexCoords();
	this->m_elementsHover[1]->setPosition(static_cast<float>(this->m_offsetX), static_cast<float>(this->m_offsetY + 40));
}

void SidePanel::Update(sf::Vector2i position)
{
	if (isInRect(position.x, position.y, this->m_offsetY, this->m_offsetX, 100, 40))
	{
		this->currentSelected.first = true;
		this->currentSelected.second = 0;
	}
	else if (isInRect(position.x, position.y, this->m_offsetY+41, this->m_offsetX, 100, 40))
	{
		this->currentSelected.first = true;
		this->currentSelected.second = 1;

	}
}

void SidePanel::SetSelector()
{
	if (this->currentSelected.first)
	{
		if (this->selected != this->currentSelected.second)
		{
			this->m_elements[this->selected]->Show(true);
			this->m_elementsHover[this->selected]->Show(false);
			this->selected = this->currentSelected.second;
			this->m_elements[this->selected]->Show(false);
			this->m_elementsHover[this->selected]->Show(true);
		}
	}
}