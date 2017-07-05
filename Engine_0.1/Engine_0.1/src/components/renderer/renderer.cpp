#include <components\renderer\renderer.h>
#include <components\QuatCamera.h>


Renderer::Renderer()
{

	//shader = new Shader(0);
	//shader->Initialize();



	
	
}


void Renderer::Initialize()
{

}



void Renderer::Update(float deltaT, vector<GameObject*> comp)
{
	for (auto c : comp)
	{
		c->Update(deltaT, this);
	}
}


void Renderer::Render(vector<GameObject*> comp)
{
	//Shader * s = dynamic_cast<Shader*>(components.at(0));
	//gl::UseProgram(s->GetProgram());
	//gl::UseProgram(shader->GetProgram());
	//Mesh * m = dynamic_cast<Mesh*>(components.at(1));
	//Texture * t = dynamic_cast<Texture*>(components.at(2));
//	gl::BindTexture(gl::TEXTURE_2D, t->getTexture());
	//gl::BindTexture(gl::TEXTURE_2D, texture->getTexture());
	//gl::BindVertexArray(m->GetVAO());
	//gl::BindVertexArray(mesh->GetVAO());


	for (auto c : comp)
	{
		model = c->GetComponentByType<Transform>()->getModel();
		c->Render(this);
		gl::DrawElements(gl::TRIANGLES, indicesSize, gl::UNSIGNED_INT, NULL);
	}
	
	

}

void Renderer::MessageGLi(char* msg,GLuint value)
{
	if (msg == "size")
	{
		indicesSize = value;
	}
}

void Renderer::MessageGLm(char* msg, glm::mat4 value)
{
	if (msg == "model")
	{
		model = value;
	}

	if (msg == "view")
	{
		view = value;
	}

	if (msg == "projection")
	{
		proj= value;
	}
}

glm::mat4 Renderer::GetModel()
{
	return model;
}
glm::mat4 Renderer::GetView()
{
	return view;
}

glm::mat4 Renderer::GetProjection()
{
	return proj;
}


Renderer::~Renderer()
{

}