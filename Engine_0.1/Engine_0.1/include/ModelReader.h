#pragma once

#include <vector>
#include <string.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <gl_core_4_3.hpp>
using namespace std;

class ModelReader
{
	private:
		
		// need to know ascii for forward slash
		static const int forwardSlash = 0x2F;

		//
		// this is the data read from the OBJ file....
		//

		vector<GLfloat> m_vertices;					// v
		vector<GLfloat> m_vertexNormals;				// vn
		vector<GLfloat> m_vertexTextureCoordinates;	// vt only U V

		// f   v/vt/vn  (vt and vn optional)
		// these are unsigned as opengl expected unsigned data
		vector<GLuint> m_faceVertexIndices;
		vector<GLuint> m_faceTextureIndices;
		vector<GLuint> m_faceNormalIndices;
		vector<GLuint> m_indices;

		string m_modelName;

		// because maya output indices that don't necessarily match for
		// faces normals and textures we have two options
		// 1. rebalance the texture and normal indices to match the face indices - then draw with glDrawElements
		// 2. Create buffers with duplicated vertices, texture coordinates and normals and use glDrawArrays
		//
		// 1 is probably more efficient but 2 is perhaps a little clearer...

		// to simply test we generate a set of vertex triplets that repeat vertices
		// but which ww can simply pass to open gl in sequence to draw each triangle
		// in the model

		vector<float> m_vertexTriplets;	// v
		vector<float> m_vertexNormalTriplets; 
		vector<float> m_vertexTexturePairs;

	public:
		ModelReader(string filename, bool large);
		~ModelReader(void);
		void GenerateIndices();
		void ReadModelObjData(string filename);

		void ProcessVertexLine(istringstream& iss);
		void ProcessVertexNormalLine(istringstream& iss);
		void ProcessVertexTextureLine(istringstream& iss);
		void ProcessFaceLine(istringstream& iss);


		void CreateExpandedVertices();
		void CreateExpandedNormals();
		void CreateExpandedTextureCoordinates();

		vector<GLfloat>& GetUV();
		vector<GLfloat>& GetVertex();
		vector<GLuint>& GetIndices();
		vector<float>& GetVertices();
		vector<float>& GetNormals();
		vector<float>& GetTextureCoordinates();

};

