#include <components\renderer\mesh.h>

Mesh::Mesh()
{

}

Mesh::Mesh(char * filePath)
{
	LoadMeshFromOBJ(filePath);
}

void Mesh::Update(float deltaT, Renderer * renderer)
{

}

void Mesh::Initialize()
{




	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	GLuint vboHandles[3];
	gl::GenBuffers(3, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint uvBufferHandle = vboHandles[1];
	GLuint indicesBufferHandle = vboHandles[2];

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, modelLoader->GetVertex().size()*sizeof(GLfloat), &modelLoader->GetVertex()[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, modelLoader->GetUV().size()*sizeof(GLfloat), &modelLoader->GetUV()[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indicesBufferHandle);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, modelLoader->GetIndices().size()*sizeof(GLuint), &modelLoader->GetIndices()[0], gl::STATIC_DRAW);






	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::EnableVertexAttribArray(1);  // Vertex color

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);
	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

}

void Mesh::Render(Renderer * renderer)
{
	gl::BindVertexArray(vaoHandle);
	renderer->MessageGLi("size", modelLoader->GetIndices().size());
}

void Mesh::LoadMeshFromOBJ(char * filePath)
{
	modelLoader = new ModelReader(filePath, false);
}

GLuint Mesh::GetIndicesSize()
{
	return modelLoader->GetIndices().size();
}
GLuint Mesh::GetVAO()
{
	return vaoHandle;
}