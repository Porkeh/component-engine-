#include <components\GUIRenderer.h>
#include <glm/gtx/transform.hpp>

void GUIRenderer::Update(float deltaT, Renderer * Renderer)
{

}
void GUIRenderer::Initialize()
{
	proj = glm::ortho((800.f / 2) * 0, 800.f, 600.f, (600.f / 2) * 0, -1.0f, 1.0f);
	view = glm::lookAt(glm::vec3(1, 1, 1),
		glm::vec3(1, 1, 0),
		glm::vec3(0, 1, 0));

}
void GUIRenderer::Render(Renderer * renderer)
{
	//gl::Disable(gl::DEPTH_TEST);
	renderer->MessageGLm("view", view);
	renderer->MessageGLm("projection", proj);
}
GUIRenderer::GUIRenderer()
{

}