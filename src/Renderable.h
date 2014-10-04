#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <SFML\Graphics\RenderTarget.hpp>
#include "RenderManager.h"
#include "TextureManager.h"

class Renderable
{
public:
	Renderable();
	Renderable(int zIndex);
	~Renderable();

	virtual void Render(sf::RenderTarget* target) = 0;
	void Show(bool showFlag = true);

	void SetZIndex(int zIndex);
	int GetZIndex();
	
	//static
	static void SetRenderManager(RenderManager* renderManager);

protected:
	int m_zIndex;
	bool m_visibilityFlag;
	//static
	static RenderManager* s_renderManager;
private:

};

inline Renderable::Renderable()
{

}

inline Renderable::Renderable(int zIndex)
{
	this->m_zIndex = zIndex;
}

inline Renderable::~Renderable()
{

}

inline void Renderable::SetZIndex(int zIndex)
{
	this->m_zIndex = zIndex;
}

inline int Renderable::GetZIndex()
{
	return this->m_zIndex;
}

inline void Renderable::Show(bool showFlag)
{
	if (this->m_visibilityFlag != showFlag)
	{
		if (showFlag == true)
		{
			s_renderManager->AddSprite(this);
		}
		else
		{
			s_renderManager->RemoveSprite(this);
		}
		this->m_visibilityFlag = showFlag;
	}
}


#endif