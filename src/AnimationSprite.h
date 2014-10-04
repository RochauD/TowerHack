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
	AnimationSprite(const std::string& filename, int zIndex, bool show = true);
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
	int GetFramesPerRow();
	int GetFramesPerColumn();
	sf::Time GetUpdateTime();

	void SetLooped(const bool looped);
	void SetUpdateTime(const sf::Time updateTime);
	void SetFramesGrid(const int framesPerRow, const int framesPerColumn);
	
protected:
	void UpdatePositions();
	void UpdateTexCoords();
	void SetTextureRect(const sf::IntRect& rectangle);
	sf::Vertex m_vertices[4];

	void CalcNextFrame();
	sf::Clock m_timer;
	sf::Time m_updateTime;
	bool m_isLooped;
	bool m_isPaused;
	sf::Vector2i m_currentPos;
	sf::Vector2i m_frameSize;
	int m_maxFrames;
	int m_currentFrame;
	int m_columns;
	int m_rows;

	TextureType m_texture;
private:
};

template <class TextureType>
AnimationSprite<TextureType>::AnimationSprite(const std::string& filename, int zIndex, bool show) : Renderable(zIndex)
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

#endif