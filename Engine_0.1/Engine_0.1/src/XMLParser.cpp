#include <XMLParser.h>


XMLParser::XMLParser(const char * filePath)
{
	XMLError err = doc.LoadFile(filePath);
	if (err != XML_SUCCESS)
	{
		return;
	}



}

std::vector<GameObject*> XMLParser::load()
{
	vector<GameObject*> tempVector;
	tempVector.reserve(100);
	XMLElement * root = doc.FirstChildElement("scene");
	XMLElement * child = root->FirstChildElement("gameobject");

	while (child != nullptr)
	{

		GameObject * obj = new GameObject();


		XMLElement * component = child->FirstChildElement();

		while (component != nullptr)
		{

			const char * componentName = child->Name();

			if (CompareString(componentName, "transform"))
			{
				Transform * temp = nullptr;
				glm::vec3 position, scale, rotation;
				XMLElement * componentChild = component->FirstChildElement();
				while (componentChild != nullptr)
				{

					const char * componentChildName = componentChild->Name();

					if (CompareString(componentChildName, "position"))
					{
						float x, y, z;
						componentChild->QueryFloatAttribute("x", &x);
						componentChild->QueryFloatAttribute("y", &y);
						componentChild->QueryFloatAttribute("z", &z);

						position = glm::vec3(x, y, z);

					}


					componentChild = componentChild->NextSiblingElement();
				}

				temp = new Transform(position, scale, rotation);
				obj->AddComponent(temp);
			}

			if (CompareString(componentName, "mesh"))
			{
				Mesh * temp = nullptr;
				char * path = nullptr;;


				component->Attribute("path", path);



				temp = new Mesh(path);
				obj->AddComponent(temp);
			}


			component = component->NextSiblingElement();
		}

		component = component->NextSiblingElement();








		tempVector.push_back(obj);

		child = child->NextSiblingElement("gameobject");



	}

	return tempVector;
}


XMLParser::~XMLParser()
{
}