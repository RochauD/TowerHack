#include "TextureManager.h"


TextureManager::TextureManager(const std::string& texturePath)
{
	this->m_textureContainer.reserve(100);
	this->m_texturePath = texturePath;
}

TextureManager::TextureManager(const char* texturePath)
{
	this->m_textureContainer.reserve(100);
	this->m_texturePath = texturePath;
}

TextureManager::~TextureManager()
{
	this->DeleteAllTextures();
}

bool TextureManager::LoadTextures(std::vector<std::pair<std::string, bool>>& stringVector)
{
	std::vector<std::pair<std::string, bool>>::iterator iter;
	for (iter = stringVector.begin(); iter != stringVector.end(); iter++)
	{
		sf::Texture* tempTexture = new sf::Texture;
		if (!tempTexture->loadFromFile(this->m_texturePath + iter->first))
		{
			if (tempTexture)
			{
				delete tempTexture;
			}
			return false;
		}
		TextureData tempTextureData;
		tempTextureData.count = 1;
		tempTextureData.texture = tempTexture;
		tempTextureData.persistent = iter->second;
		this->m_textureContainer.insert(std::pair<std::string, TextureData>(iter->first, tempTextureData));
	}
	return true;
}

bool TextureManager::LoadTextures(std::vector<std::string>& stringVector, bool persistent)
{
	std::vector<std::string>::iterator iter;
	for (iter = stringVector.begin(); iter != stringVector.end(); iter++)
	{
		sf::Texture* tempTexture = new sf::Texture;
		if (!tempTexture->loadFromFile(this->m_texturePath + *iter))
		{
			if (tempTexture)
			{
				delete tempTexture;
			}
			return false;
		}
		TextureData tempTextureData;
		tempTextureData.count = 1;
		tempTextureData.texture = tempTexture;
		tempTextureData.persistent = persistent;
		this->m_textureContainer.insert(std::pair<std::string, TextureData>(*iter, tempTextureData));
	}
	return true;
}

bool TextureManager::GetTexture(const std::string& filename, sf::Texture** parTexture, const bool persistent)
{
	std::unordered_map<std::string, TextureData>::iterator iter;
	if ((iter = this->m_textureContainer.find(filename)) != this->m_textureContainer.end())
	{
		if (persistent == true)
		{
			iter->second.persistent = true;
		}
		iter->second.count++;
		*parTexture = iter->second.texture;
		return true;
	}
	else
	{
		try
		{
			sf::Texture* tempTexture = new sf::Texture;
			if (!tempTexture->loadFromFile(this->m_texturePath + filename))
			{
				if (tempTexture)
				{
					delete tempTexture;
				}
				return false;
			}
			TextureData tempTextureData;
			tempTextureData.count = 1;
			tempTextureData.texture = tempTexture;
			tempTextureData.persistent = persistent;
			this->m_textureContainer.insert(std::pair<std::string, TextureData>(filename, tempTextureData));
			*parTexture = tempTexture;
			return true;
		}
		catch (std::bad_alloc& ba)
		{
			ba.what(); //@todo add log entry
			return false;
		}
	}
}

void TextureManager::DeleteTexture(const std::string& filename)
{
	if (!filename.empty())
	{
		std::unordered_map<std::string, TextureData>::iterator iter;
		if ((iter = this->m_textureContainer.find(filename)) != this->m_textureContainer.end())
		{
			if (iter->second.count == 1 && iter->second.persistent == false)
			{
				if (iter->second.texture)
				{
					delete iter->second.texture;
					iter->second.texture = 0;
				}
				iter->second.count = 0;
				this->m_textureContainer.erase(iter);
			}
			else
			{
				iter->second.count--;
			}
		}
	}
}

void TextureManager::DeleteAllTextures()
{
	for (auto iter = this->m_textureContainer.cbegin(); iter != this->m_textureContainer.cend();)
	{
		delete iter->second.texture;
		this->m_textureContainer.erase(iter++);
	}
}

void TextureManager::IncrementTextureRefCounter(const std::string& filename)
{
	std::unordered_map<std::string, TextureData>::iterator iter;
	if ((iter = this->m_textureContainer.find(filename)) != this->m_textureContainer.end())
	{
		iter->second.count++;
	}
	else
	{
		throw std::runtime_error("Invalid filename!"); // @todo add better error handling
	}
}
