#include "Renderable.h"

//static
RenderManager* Renderable::s_renderManager = 0;

void Renderable::SetRenderManager(RenderManager* renderManager)
{
	s_renderManager = renderManager;
}