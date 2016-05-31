#pragma once
#include <GL/glew.h>

#include "JPGLHelper.h"
class TextureWrapper
{
	GLuint activeID;
	GLuint textureID;
	GLuint shaderID;
	GLuint GPUtextureID;

public:
	TextureWrapper(GLuint activeTextureID, GLuint shaderID, const char* filename, const char* textureName);
	~TextureWrapper();

	void SendToGPU();
};

