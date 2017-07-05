#pragma once
#include <tinyxml2.h>
#include <vector>
#include <GameObject.h>

using namespace tinyxml2;

class XMLParser
{
public:
	XMLParser(const char * filePath);
	~XMLParser();

	std::vector<GameObject*> load();

private:
	

	bool CompareString(const char * string1, const char * string2)
	{
		if (strcmp(string1, string2) == 0)
		{
			return true;
		}
		return false;
	}

	XMLDocument doc;

};
