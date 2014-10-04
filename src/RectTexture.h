#ifndef RECTTEXTURE_H_
#define RECTTEXTURE_H_

#include <string>
#include <SFML/Graphics.hpp>

#include "BaseTexture.h"

class RectTexture : public BaseTexture
{
public:
	RectTexture();
	RectTexture(const RectTexture& rhs);
	RectTexture(std::string& textureName);
	~RectTexture();

	RectTexture& operator= (const RectTexture& other);

	const size_t GetNumberOfRects() const;
	sf::Rect<unsigned int> GetTextureRect() const;

	void SetTextureRectVec(std::vector<sf::Rect <unsigned int>>& textureRectVec);
	void GetTextureRectVec(std::vector<sf::Rect <unsigned int>>* retTextureRectVec);

	void LoadTexture(std::string& textureName, std::vector<sf::Rect<unsigned int>>& textureRectVec);
	void LoadTextureByLoadFile(const std::string& loadFilename);
	bool NextFrame();
	bool PreviousFrame();
	void SetCurFrame(size_t curFrame);
	size_t GetCurFrame();
protected:
	void LoadTexture(const std::string& textureName);
	bool CheckTextureRectCorrectness();
	std::string m_textureName;
	size_t m_numberOfRects;
	std::vector<sf::Rect<unsigned int>> m_textureRectVec;
	size_t curFrame;
private:

};

#endif