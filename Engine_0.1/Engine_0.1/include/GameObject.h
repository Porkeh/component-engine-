#pragma once
#include <components\component.h>
#include <vector>
#include <components\renderer\renderer.h>
#include <components\component.h>

class GameObject
{
private:
	std::vector<Component*> components;


public:

	GameObject();
	~GameObject();
	void Initialize();
	void AddComponent(Component * c);
	void Update(float deltaT, Renderer * renderer);
	void Render(Renderer * renderer);
	template<typename G>
	G* GetComponentByType() {
		for (auto c : components)
		{
			if (c != nullptr)
				if (G* type = dynamic_cast<G*>(c))
					return type;
		}

	}
};
