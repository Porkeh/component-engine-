
#include "ModelReader.h"


ModelReader::ModelReader(string filename, bool large)
{
	//if large file reserve memory space
	if(large)
	{
	m_vertices.reserve(100000);
	m_vertexNormals.reserve(100000);
	m_vertexTextureCoordinates.reserve(100000);
	m_faceVertexIndices.reserve(100000);
	m_faceTextureIndices.reserve(100000);
	m_faceNormalIndices.reserve(100000);
	m_vertexTriplets.reserve(100000);
	m_vertexNormalTriplets.reserve(100000);
	m_vertexTexturePairs.reserve(100000);
	}
	//ready file
	ReadModelObjData(filename);
	
	//expand the data suitable for lDrawArrays()
	CreateExpandedVertices();
	CreateExpandedNormals();
	CreateExpandedTextureCoordinates();
}

ModelReader::~ModelReader(void)
{
}

void ModelReader::ReadModelObjData(string filename)
{
	std::fstream modelfile(filename, std::ios_base::in);

	if(!modelfile.is_open())
	{
		
		throw std::invalid_argument( "File not found" );
		return;	//ERROR!!!
	}

	string line;
	string token = "";
	while (getline(modelfile, line))
	{
		istringstream iss(line);

		// process the line
		token = "";

		iss >> token; // read to first whitespace
	
		if (token == "#")
		{
			// ignore rest of line
			// iss >> s;
		}
		else if (token == "g")
		{
			// read the model name
			iss >> m_modelName;
			// ignore rest of line
		}
		else if (token == "v")
		{
			//process vertex
			ProcessVertexLine(iss);
		}
		else if (token == "vn")
		{
			//process normal
			ProcessVertexNormalLine(iss);
		}
		else if (token == "vt")
		{
			//process texture
			ProcessVertexTextureLine(iss);
		}
		else if (token == "f")
		{
			//process face
			ProcessFaceLine(iss);
		}
		else
		{
			// ignore any line without these qualifiers
			// ignore rest of line
		}
	}
	modelfile.close();

	GenerateIndices();

}

void ModelReader::GenerateIndices()
{
	for (int i = 0; i < m_faceTextureIndices.size(); i++)
	{
		m_indices.push_back(i);
	}
}
void ModelReader::ProcessVertexLine(istringstream& iss)
{

	//push vertex into vector
	float i = 0;
	float j = 0;
	float k = 0;
	iss >> i >> j >> k;
	m_vertices.push_back(i);
	m_vertices.push_back(j);
	m_vertices.push_back(k);

}

void ModelReader::ProcessVertexNormalLine(istringstream& iss)
{
	//push normal into vector	
	float i;
	float j;
	float k;
	iss >> i >> j >> k;
	m_vertexNormals.push_back(i);
	m_vertexNormals.push_back(j);
	m_vertexNormals.push_back(k);

}

void ModelReader::ProcessVertexTextureLine(istringstream& iss)
{
	//push texture coords into vector
	float i;
	float j;
	iss >> i >> j;
	m_vertexTextureCoordinates.push_back(i);
	m_vertexTextureCoordinates.push_back(j);

}


void ModelReader::ProcessFaceLine(istringstream& iss)
{
	//push face into vector based on format of obj
	static const int forwardSlash = 0x2F;
	
	float current;
	

	for(int i = 0; i < 3; i++)
	{
	iss >> current;
	m_faceVertexIndices.push_back(current-1);

	int lookAhead = iss.peek();

	if(lookAhead == forwardSlash)
	{
		iss.get();
		lookAhead = iss.peek();
		if(lookAhead == forwardSlash)
		{
			iss.get();
			iss >> current;
			m_faceNormalIndices.push_back(current - 1);
		}
		else
		{
			iss >> current;
			m_faceTextureIndices.push_back(current-1);
			iss.get();
			iss >> current;
			m_faceNormalIndices.push_back(current-1);
		}
	}
	}


}


void ModelReader::CreateExpandedVertices()
{
	//scale and push vertices into vector so openGl can use
	for (std::vector<unsigned int>::iterator it = m_faceVertexIndices.begin() ; it != m_faceVertexIndices.end(); ++it)
	{
		int vertexNumber = (*it);
		// 3 floats per triangular face
		int scaledVertexNumber = vertexNumber*3;

		
		m_vertexTriplets.push_back(m_vertices.at(scaledVertexNumber));
		m_vertexTriplets.push_back(m_vertices.at(scaledVertexNumber+1));
		m_vertexTriplets.push_back(m_vertices.at(scaledVertexNumber+2));

	}
}
void ModelReader::CreateExpandedNormals()
{
		//scale and push normals into vector so openGl can use

	for (std::vector<unsigned int>::iterator it = m_faceNormalIndices.begin() ; it != m_faceNormalIndices.end(); ++it)
	{
		
		int vertexNormalNumber = (*it);
		int scaledVertexNumber = vertexNormalNumber*3;

		m_vertexNormalTriplets.push_back(m_vertexNormals.at(scaledVertexNumber));
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(scaledVertexNumber+1));
		m_vertexNormalTriplets.push_back(m_vertexNormals.at(scaledVertexNumber+2));

	}
}
void ModelReader::CreateExpandedTextureCoordinates()
{
		//scale and push textures into vector so openGl can use
	for (std::vector<unsigned int>::iterator it = m_faceTextureIndices.begin() ; it != m_faceTextureIndices.end(); ++it)
	{
		int vertexTextureNumber = (*it);
		int scaledVertexTextureNumber = vertexTextureNumber * 2;
		m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(scaledVertexTextureNumber));
		m_vertexTexturePairs.push_back(m_vertexTextureCoordinates.at(scaledVertexTextureNumber+1));
	}

}


// Get methods gove access to the vector data

vector<GLfloat>& ModelReader::GetUV()
{
	return m_vertexTexturePairs;
}

vector<GLfloat>& ModelReader::GetVertex()
{
	return m_vertexTriplets;
}
vector<GLuint>& ModelReader::GetIndices()
{
	return m_indices;
}
vector<float>& ModelReader::GetVertices()
{
	return m_vertexTriplets;
}
vector<float>& ModelReader::GetNormals()
{
	return m_vertexNormalTriplets;
}
vector<float>& ModelReader::GetTextureCoordinates()
{
	return m_vertexTexturePairs;
}