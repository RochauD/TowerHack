#include "BaseTexture.h"

BaseTexture::BaseTexture()
{

}

BaseTexture::BaseTexture(const BaseTexture& rhs)
{
	this->m_texture = rhs.m_texture;
}

BaseTexture::~BaseTexture()
{

}

BaseTexture& BaseTexture::operator= (const BaseTexture& other)
{
	this->m_texture = other.m_texture;
	return *this;
}

const sf::Texture* BaseTexture::GetTexture() const
{
	return this->m_texture;
}


//static
TextureManager* BaseTexture::s_textureManager = 0;

void BaseTexture::SetTextureManager(TextureManager* textureManager)
{
	s_textureManager = textureManager;
}
