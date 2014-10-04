#ifndef STATICSPRITE_H_
#define STATICSPRITE_H_

#include "Renderable.h"

#include <string>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <cmath>

template<class TextureType>
class StaticSprite : public sf::Transformable, public Renderable, public TextureType
{
public:
	StaticSprite();
	StaticSprite(const std::string& filename, int zIndex, bool show = true);
	~StaticSprite();
	void SetColor(const sf::Color& color);
	const sf::Color& GetColor() const;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
	void Render(sf::RenderTarget* target);
	void UpdatePositions();
	void UpdateTexCoords();

protected:
	void SetTextureRect(const sf::IntRect& rectangle);
	sf::Vertex m_vertices[4];

	TextureType m_texture;
private:

};

template <class TextureType>
StaticSprite<TextureType>::StaticSprite()
{

}

template <class TextureType>
StaticSprite<TextureType>::StaticSprite(const std::string& filename, int zIndex, bool show) : Renderable(zIndex)
{
	this->m_texture.LoadTexture(filename);
	UpdatePositions();
	UpdateTexCoords();
	this->m_visibilityFlag = show;
	if (this->m_visibilityFlag == true)
	{
		s_renderManager->AddSprite(this);
	}
}

template <class TextureType>
StaticSprite<TextureType>::~StaticSprite()
{
	if (this->m_visibilityFlag == true)
	{
		s_renderManager->RemoveSprite(this);
	}
}

template <class TextureType>
void StaticSprite<TextureType>::SetColor(const sf::Color& color)
{
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;
}

template <class TextureType>
const sf::Color& StaticSprite<TextureType>::GetColor() const
{
	return m_vertices[0].color;
}

template <class TextureType>
sf::FloatRect StaticSprite<TextureType>::GetLocalBounds() const
{
	float width = static_cast<float>(m_texture.GetTextureRect().width);
	float height = static_cast<float>(m_texture.GetTextureRect().height);
	
	return sf::FloatRect(0.f, 0.f, abs(width), abs(height));
}

template <class TextureType>
sf::FloatRect StaticSprite<TextureType>::GetGlobalBounds() const
{
	return getTransform().transformRect(GetLocalBounds());
}

template <class TextureType>
void StaticSprite<TextureType>::Render(sf::RenderTarget* target)
{
	sf::RenderStates states;
	states.blendMode = sf::BlendAlpha;
	states.shader = 0;
	states.transform *= getTransform();
	states.texture = m_texture.GetTexture();
	target->draw(m_vertices, 4, sf::Quads, states);
}

template <class TextureType>
void StaticSprite<TextureType>::UpdatePositions()
{
	sf::FloatRect bounds = GetLocalBounds();

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, bounds.height);
	m_vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
	m_vertices[3].position = sf::Vector2f(bounds.width, 0);
}

template <class TextureType>
void StaticSprite<TextureType>::UpdateTexCoords()
{
	float left = static_cast<float>(m_texture.GetTextureRect().left);
	float right = left + m_texture.GetTextureRect().width;
	float top = static_cast<float>(m_texture.GetTextureRect().top);
	float bottom = top + m_texture.GetTextureRect().height;

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left, bottom);
	m_vertices[2].texCoords = sf::Vector2f(right, bottom);
	m_vertices[3].texCoords = sf::Vector2f(right, top);
}

template <class TextureType>
void  StaticSprite<TextureType>::SetTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != m_texture.GetTextureRect())
	{
		m_texture.SetTextureRect(rectangle);
		UpdatePositions();
		UpdateTexCoords();
	}
}


#endif