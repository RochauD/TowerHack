#ifndef BASETEXTURE_H_
#define BASETEXTURE_H_

#include <SFML/Graphics/Texture.hpp>

//forward declaration
class TextureManager;

class BaseTexture
{
public:
	BaseTexture();
	BaseTexture(const BaseTexture& rhs);
	~BaseTexture();

	BaseTexture& operator= (const BaseTexture& other);

	const sf::Texture* GetTexture() const;

	//static
	static void SetTextureManager(TextureManager* textureManager);


protected:
	const sf::Texture* m_texture;
	// static
	static TextureManager* s_textureManager;

private:
};

#endif