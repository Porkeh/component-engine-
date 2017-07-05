#include <GameObject.h>


GameObject::GameObject()
{
	

	//mesh = new Mesh();
	//mesh->Initialize();

	//components.push_back(new Mesh(mesh));
	
	//texture = new Texture();
	//texture->Initialize();

	
	

	//shader->SetUniform("tex", 0);

}

GameObject::~GameObject()
{
	for (int i = 0; i<components.size(); i++)
	{
		delete components[i];
	}
}

void GameObject::Initialize()
{
	for (auto c : components)
	{
		c->Initialize();
	}

}
void GameObject::AddComponent(Component  * c)
{
	components.push_back(c);
}

void GameObject::Update(float deltaT, Renderer * renderer)
{
	for (auto c : components)
	{
		c->Update(deltaT, renderer);
	}

}
void GameObject::Render(Renderer * render)
{
	for (auto c : components)
	{
		c->Render(render);
	}
}