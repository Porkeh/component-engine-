
#include <components\renderer\texture.h>
#include <fstream>


void Texture::LoadBMP()
{
	
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins

	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;
	

	FILE *file;
	errno_t err;
	err = fopen_s(&file, texPath, "rb");
	if (!file) { printf("Image could not be opened\n");  }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way


										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);


	gl::GenTextures(1, &textureID);             // Generate a texture
	gl::BindTexture(gl::TEXTURE_2D, textureID); // Bind that texture temporarily
                  // Set the mode

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::NEAREST);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::NEAREST);

	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, width, height, 0, gl::BGR, gl::UNSIGNED_BYTE, data);
	gl::BindTexture(gl::TEXTURE_2D, NULL);





}
GLuint Texture::getTexture()
{
	return textureID;
}
void Texture::Update(float deltaT, Renderer * renderer)
{}

void Texture::Render(Renderer * renderer)
{
	gl::BindTexture(gl::TEXTURE_2D, textureID);
}
void Texture::Initialize()
{
	LoadBMP();
}


Texture::Texture(char * filePath)
{
	texPath = filePath;
}