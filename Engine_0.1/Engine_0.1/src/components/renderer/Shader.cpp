#include <components\renderer\shader.h>

#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>
using std::string;

Shader::Shader(int id)
{ 
	shaderID = id;
}

void Shader::Initialize()
{
	// Load contents of file
	std::string fileName = "shader/basic_";
	fileName.append(std::to_string(shaderID));
	fileName.append(".vert");
		ifstream inFile(fileName);
	if (!inFile) {
		fprintf(stderr, "Error opening file: shader/basic.vert\n");
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	GLuint vertShader = gl::CreateShader(gl::VERTEX_SHADER);
	if (0 == vertShader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = { codeStr.c_str() };
	gl::ShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(vertShader);

	// Check compilation status
	GLint result;
	gl::GetShaderiv(vertShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(vertShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file into shaderCode here
	fileName = "shader/basic_";
	fileName.append(std::to_string(shaderID));
	fileName.append(".frag");
	ifstream fragFile(fileName);
	if (!fragFile) {
		fprintf(stderr, "Error opening file: shader/basic.frag\n");
		exit(1);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Create the shader object
	GLuint fragShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (0 == fragShader) {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	gl::ShaderSource(fragShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(fragShader);

	shaderProgram = gl::CreateProgram();
	if (0 == shaderProgram) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}


	// Attach the shaders to the program object
	gl::AttachShader(shaderProgram, vertShader);
	gl::AttachShader(shaderProgram, fragShader);

	// Link the program
	gl::LinkProgram(shaderProgram);
}

void Shader::Update(float deltaT, Renderer * renderer)
{

}

void Shader::Render(Renderer * renderer)
{

	gl::UseProgram(shaderProgram);
	SetUniform("M", renderer->GetModel());
	SetUniform("V", renderer->GetView());
	SetUniform("P", renderer->GetProjection());
}

GLuint Shader::GetProgram()
{
	return shaderProgram;
}

void Shader::SetUniform(char * name, GLuint data)
{
	GLint loc = gl::GetUniformLocation(shaderProgram, name);
	gl::Uniform1i(loc, data);

}
void Shader::SetUniform(char * name, glm::mat4 data)
{
	GLint loc = gl::GetUniformLocation(shaderProgram, name);
	gl::UniformMatrix4fv(loc, 1, NULL, &data[0][0]);

}