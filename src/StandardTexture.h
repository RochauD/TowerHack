#ifndef STANDARDTEXTURE_H_
#define STANDARDTEXTURE_H_

#include <string>
#include <SFML/Graphics.hpp>

#include "BaseTexture.h"

class StandardTexture : public BaseTexture
{
public:
	StandardTexture();
	StandardTexture(const StandardTexture& rhs);
	StandardTexture(std::string& textureName);
	~StandardTexture();

	StandardTexture& operator= (const StandardTexture& other);

	void LoadTexture(const std::string& textureName);
	sf::Rect<unsigned int> GetTextureRect() const;

protected:
	std::string m_textureName;
	sf::Rect<unsigned int> m_textureRect;
private:

};

#endif