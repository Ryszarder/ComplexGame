#pragma once

#include "Graphics.h"
#include <string>

class Texture
{
private:
	GLuint textureID;

	int width;
	int height;
	int channelCount;

	bool successfullyLoaded = false;

public:
	Texture() {}
	Texture(std::string filename);

	~Texture();

	//We don't want to be copying our textures around.
	Texture(const Texture& otherTexture) = delete;
	Texture& operator=(const Texture& otherTexture) = delete;


	//But moving them is legit and useful.
	Texture(Texture&& otherTexture);
	Texture& operator=(Texture&& otherTexture);

	void Bind(int textureUnit = 0);

	static void Unbind(int textureUnit = 0);

};