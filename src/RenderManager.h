#ifndef RENDERMANAGER_H_
#define RENDERMANAGER_H_

#include <vector>
#include <set>
#include <string>
#include <memory>
#include <SFML\Graphics.hpp>

class TextureManager;
class Renderable;

struct zindex_compare
{
	bool operator() (Renderable* lhs, Renderable* rhs) const;
};

class RenderManager
{
public:
	RenderManager(const std::string &texturePath, sf::RenderWindow* renderWindow);
	RenderManager(const char* texturePath, sf::RenderWindow* renderWindow);
	RenderManager(const RenderManager &other) = delete; // non construction-copyable
	RenderManager &operator=(const RenderManager &) = delete; // non copyable
	~RenderManager();

	void AddSprite(Renderable* renderObject);
	void RemoveSprite(Renderable* renderObject);
	void Draw();

protected:
private:

	sf::RenderWindow* m_renderWindow;
	std::unique_ptr<TextureManager> m_textureManager;
	std::multiset<Renderable*, zindex_compare> m_renderSet;
};



#endif