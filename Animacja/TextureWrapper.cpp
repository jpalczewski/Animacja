#include "TextureWrapper.h"


TextureWrapper::TextureWrapper(GLuint activeTextureID, GLuint _shaderID, const char* filename, const char* textureName) : shaderID(_shaderID), activeID(activeTextureID)
{
	textureID = JPGLHelper::LoadTexture(filename);
	GPUtextureID = glGetUniformLocation(_shaderID, textureName);
}


TextureWrapper::~TextureWrapper()
{
}

void TextureWrapper::SendToGPU()
{
	glActiveTexture(activeID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(GPUtextureID, activeID - GL_TEXTURE0);
}