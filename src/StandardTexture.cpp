#include "StandardTexture.h"
#include "TextureManager.h"

StandardTexture::StandardTexture() : BaseTexture()
{

}

StandardTexture::StandardTexture(const StandardTexture& rhs) : BaseTexture(rhs)
{
	this->m_textureName = rhs.m_textureName;
	this->m_textureRect = rhs.m_textureRect;
	s_textureManager->IncrementTextureRefCounter(this->m_textureName);
}

StandardTexture::StandardTexture(std::string& textureName) : BaseTexture()
{
	this->LoadTexture(textureName);
}

StandardTexture::~StandardTexture()
{
	s_textureManager->DeleteTexture(this->m_textureName);
}

StandardTexture& StandardTexture::operator= (const StandardTexture& other)
{
	BaseTexture::operator=(static_cast<BaseTexture const&>(other));
	this->m_textureName = other.m_textureName;
	this->m_textureRect = other.m_textureRect;
	s_textureManager->IncrementTextureRefCounter(this->m_textureName);
	return *this;
}

void StandardTexture::LoadTexture(const std::string& textureName)
{
	sf::Texture* bufferTexturePtr = 0;
	this->m_textureName = textureName;
	if (!s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr))
	{
		std::string errorStr = "Could not load the texture: " + this->m_textureName;
		throw std::runtime_error(errorStr); // @todo add better exception handling
	}
	this->m_texture = bufferTexturePtr;
	this->m_textureRect.left = 0;
	this->m_textureRect.top = 0;
	this->m_textureRect.width = this->m_texture->getSize().x;
	this->m_textureRect.height = this->m_texture->getSize().y;
}

sf::Rect<unsigned int> StandardTexture::GetTextureRect() const
{
	return this->m_textureRect;
}