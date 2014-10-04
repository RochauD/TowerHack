#ifndef ANIMATION_SPRITE_H_
#define ANIMATION_SPRITE_H

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
class AnimationSprite : public sf::Transformable, public Renderable, public TextureType
{
public:
	AnimationSprite(const std::string& filename, int zIndex, bool show = true, const sf::Time updateTime = sf::seconds(1.0f), bool paused = true, bool looped = false);
	~AnimationSprite();

	void SetColor(const sf::Color& color);
	const sf::Color& GetColor() const;
	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	void Render(sf::RenderTarget* target);
	void Play();
	void Pause();
	void Stop();
	void Update();

	bool IsLooped();
	bool IsPaused();
	sf::Time GetUpdateTime();

	void SetLooped(const bool looped);
	void SetUpdateTime(const sf::Time updateTime);
	
protected:
	void UpdatePositions();
	void UpdateTexCoords();
	sf::Vertex m_vertices[4];

	sf::Clock m_timer;
	sf::Time m_updateTime;
	bool m_isLooped;
	bool m_isPaused;

	TextureType m_texture;
private:
};

template <class TextureType>
AnimationSprite<TextureType>::AnimationSprite(const std::string& filename,
											  int zIndex,
											  bool show,
											  const sf::Time updateTime,
											  bool paused,
											  bool looped) : Renderable(zIndex)
{
	this->m_texture.LoadTextureByLoadFile(filename);
	this->m_updateTime = updateTime;
	this->m_isPaused = paused;
	this->m_isLooped = looped;
	this->m_timer = sf::Clock();
	UpdatePositions();
	UpdateTexCoords();
	this->m_visibilityFlag = show;
	if (this->m_visibilityFlag == true)
	{
		s_renderManager->AddSprite(this);
	}
}

template <class TextureType>
AnimationSprite<TextureType>::~AnimationSprite()
{
	if (this->m_visibilityFlag == true)
	{
		s_renderManager->RemoveSprite(this);
	}
}


template <class TextureType>
void AnimationSprite<TextureType>::SetColor(const sf::Color& color)
{
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;
}

template <class TextureType>
const sf::Color& AnimationSprite<TextureType>::GetColor() const
{
	return m_vertices[0].color;
}

template <class TextureType>
sf::FloatRect AnimationSprite<TextureType>::GetLocalBounds() const
{
	float width = static_cast<float>(m_texture.GetTextureRect().width);
	float height = static_cast<float>(m_texture.GetTextureRect().height);

	return sf::FloatRect(0.f, 0.f, abs(width), abs(height));
}

template <class TextureType>
sf::FloatRect AnimationSprite<TextureType>::GetGlobalBounds() const
{
	return getTransform().transformRect(GetLocalBounds());
}

template <class TextureType>
void AnimationSprite<TextureType>::Render(sf::RenderTarget* target)
{
	this->Update();
	sf::RenderStates states;
	states.blendMode = sf::BlendAlpha;
	states.shader = 0;
	states.transform *= getTransform();
	states.texture = m_texture.GetTexture();
	target->draw(m_vertices, 4, sf::Quads, states);
}

template <class TextureType>
void AnimationSprite<TextureType>::UpdatePositions()
{
	sf::FloatRect bounds = GetLocalBounds();

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, bounds.height);
	m_vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
	m_vertices[3].position = sf::Vector2f(bounds.width, 0);
}

template <class TextureType>
void AnimationSprite<TextureType>::UpdateTexCoords()
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
void AnimationSprite<TextureType>::Play()
{
	this->m_isPaused = false;
	this->m_timer.restart();
}

template <class TextureType>
void AnimationSprite<TextureType>::Pause()
{
	this->m_isPaused = true;
}

template <class TextureType>
void AnimationSprite<TextureType>::Stop()
{
	this->m_isPaused = true;
	this->m_texture.SetCurFrame(0);
}

template <class TextureType>
void AnimationSprite<TextureType>::Update()
{
	if (!this->m_isPaused && this->m_timer.getElapsedTime() >= this->m_updateTime)
	{
		if (!this->m_texture.NextFrame())
		{
			if (!this->m_isLooped)
			{
				this->Stop();
				return;
			}		
			else
			{
				this->m_texture.SetCurFrame(0);
			}
		}
		this->UpdatePositions();
		this->UpdateTexCoords();
		this->m_timer.restart();	
	}
}

template <class TextureType>
bool AnimationSprite<TextureType>::IsPaused()
{
	return this->m_isPaused;
}

template <class TextureType>
bool AnimationSprite<TextureType>::IsLooped()
{
	return this->m_isLooped;
}

template <class TextureType>
sf::Time AnimationSprite<TextureType>::GetUpdateTime()
{
	return this->m_updateTime;
}

template <class TextureType>
void AnimationSprite<TextureType>::SetLooped(const bool looped)
{
	this->m_isLooped = looped;
}

template <class TextureType>
void AnimationSprite<TextureType>::SetUpdateTime(const sf::Time updateTime)
{
	this->m_updateTime = updateTime;
}


#endif