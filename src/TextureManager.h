#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <unordered_map>
#include <string>
#include <new>
#include <SFML\Graphics.hpp>

struct TextureData
{
	sf::Texture* texture;
	size_t count;
	bool persistent;
};

class TextureManager
{
public:
	TextureManager(const std::string& texturePath);
	TextureManager(const char* texturePath);
	TextureManager(const TextureManager& other) = delete; // non construction-copyable
	TextureManager& operator=(const TextureManager&) = delete;  // non copyable
	~TextureManager();

	bool LoadTextures(std::vector<std::pair<std::string, bool>>& stringVector);
	bool LoadTextures(std::vector<std::string>& stringVector, const bool persistent);
	bool GetTexture(const std::string& filename, sf::Texture** parTexture, const bool persistent = false);
	void DeleteTexture(const std::string& filename);
	void DeleteAllTextures();
	void IncrementTextureRefCounter(const std::string& filename);

protected:
private:
	std::unordered_map<std::string, TextureData> m_textureContainer;
	std::string m_texturePath;
};

#endif
