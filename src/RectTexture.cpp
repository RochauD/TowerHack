#include "RectTexture.h"
#include "TextureManager.h"
#include <fstream>

RectTexture::RectTexture() : BaseTexture()
{

}
RectTexture::RectTexture(const RectTexture& rhs) : BaseTexture(rhs)
{
	this->m_textureName = rhs.m_textureName;
	this->m_numberOfRects = rhs.m_numberOfRects;
	this->m_textureRectVec = rhs.m_textureRectVec;
	s_textureManager->IncrementTextureRefCounter(this->m_textureName);
}
RectTexture::RectTexture(std::string& textureName)
{
	this->LoadTexture(textureName);
}
RectTexture::~RectTexture()
{
	s_textureManager->DeleteTexture(this->m_textureName);
}

RectTexture& RectTexture::operator= (const RectTexture& other)
{
	BaseTexture::operator=(static_cast<BaseTexture const&>(other));
	this->m_textureName = other.m_textureName;
	this->m_numberOfRects = other.m_numberOfRects;
	this->m_textureRectVec = other.m_textureRectVec;
	s_textureManager->IncrementTextureRefCounter(this->m_textureName);
	return *this;
}

const size_t RectTexture::GetNumberOfRects() const
{
	return this->m_numberOfRects;
}

sf::Rect<unsigned int> RectTexture::GetTextureRect() const
{
	return this->m_textureRectVec[this->curFrame];
}

void RectTexture::SetTextureRectVec(std::vector<sf::Rect <unsigned int>>& textureRectVec)
{
	this->m_textureRectVec = textureRectVec;
}

void RectTexture::GetTextureRectVec(std::vector<sf::Rect <unsigned int>>* retTextureRectVec)
{
	retTextureRectVec = &this->m_textureRectVec;
}

void RectTexture::LoadTexture(std::string& textureName, std::vector<sf::Rect<unsigned int>>& textureRectVec)
{
	this->m_textureName = textureName;
	this->LoadTexture(textureName);
	this->m_textureRectVec = textureRectVec;	
}

void RectTexture::LoadTextureByLoadFile(const std::string& loadFilename)
{
	std::ifstream file(loadFilename);
	if (file.is_open())
	{
		file >> this->m_textureName;
		file >> this->m_numberOfRects;
	}
	else
	{
		std::string errorStr = "Could not parse the texture information file: " + loadFilename;
		throw std::runtime_error(errorStr); // @todo add better exception handling
	}
	sf::Rect<unsigned int> rect;
	unsigned int left;
	unsigned int top;
	unsigned int height;
	unsigned int width;
	for (size_t i = 0; i < this->m_numberOfRects; ++i)
	{
		this->m_textureRectVec.reserve(this->m_numberOfRects);
		if (file.is_open())
		{
			file >> left;
			file >> top;
			file >> height;
			file >> width;
			rect.left = left;
			rect.top = top;
			rect.height = height;
			rect.width = width;
			this->m_textureRectVec.push_back(rect);
		}
		else
		{
			std::string errorStr = "Could not parse the texture information file: " + loadFilename;
			throw std::runtime_error(errorStr); // @todo add better exception handling
		}
	}
	file.close();
	this->LoadTexture(this->m_textureName);
	if (!this->CheckTextureRectCorrectness())
	{
		std::string errorStr = "Could not parse the texture information file: " + loadFilename;
		throw std::runtime_error(errorStr); // @todo add better exception handling
	}
	this->curFrame = 0;
}

bool RectTexture::NextFrame()
{
	this->curFrame++;
	if (this->curFrame == this->m_numberOfRects)
	{
		this->curFrame = this->m_numberOfRects - 1;
		return false;
	}
	return true;
}

bool RectTexture::PreviousFrame()
{
	if (this->curFrame == 0)
	{
		this->curFrame = this->m_numberOfRects - 1;
		return false;
	}
	this->curFrame--;
	return true;

}

void RectTexture::SetCurFrame(size_t curFrame)
{
	if (curFrame < this->m_numberOfRects)
	{
		this->curFrame = curFrame;
	}
}

size_t RectTexture::GetCurFrame()
{
	return this->curFrame;
}

void RectTexture::LoadTexture(const std::string& textureName)
{
	sf::Texture* bufferTexturePtr = 0;
	if (!s_textureManager->GetTexture(this->m_textureName, &bufferTexturePtr))
	{
		std::string errorStr = "Could not load the texture: " + this->m_textureName;
		throw std::runtime_error(errorStr); // @todo add better exception handling
	}
	this->m_texture = bufferTexturePtr;
}

bool RectTexture::CheckTextureRectCorrectness()
{
	//do that later :)
	return true;
}