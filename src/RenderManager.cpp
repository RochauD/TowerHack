#include "RenderManager.h"
#include "TextureManager.h"
#include "Renderable.h"
#include "BaseTexture.h"

bool zindex_compare::operator() (Renderable* lhs, Renderable* rhs) const
{
	return lhs->GetZIndex() < rhs->GetZIndex();
}

RenderManager::RenderManager(const std::string &texturePath, sf::RenderWindow* renderWindow)
{
	this->m_textureManager.reset(new TextureManager(texturePath));
	this->m_renderWindow = renderWindow;
	Renderable::SetRenderManager(this);
	BaseTexture::SetTextureManager(this->m_textureManager.get());
}

RenderManager::RenderManager(const char* texturePath, sf::RenderWindow* renderWindow)
{
	this->m_textureManager.reset(new TextureManager(texturePath));
	this->m_renderWindow = renderWindow;
	Renderable::SetRenderManager(this);
	BaseTexture::SetTextureManager(this->m_textureManager.get());
}

RenderManager::~RenderManager()
{

}

void RenderManager::AddSprite(Renderable* renderObject)
{
	this->m_renderSet.insert(renderObject);
}

void RenderManager::RemoveSprite(Renderable* renderObject)
{
	auto iter = this->m_renderSet.begin();
	for (iter; iter != this->m_renderSet.end(); iter++)
	{
		if (*iter == renderObject)
		{
			this->m_renderSet.erase(iter);
			break;
		}
	}
}

void RenderManager::Draw()
{
	auto iter = this->m_renderSet.begin();
	for (iter; iter != this->m_renderSet.end(); iter++)
	{
		(*iter)->Render(this->m_renderWindow);
	}
}
