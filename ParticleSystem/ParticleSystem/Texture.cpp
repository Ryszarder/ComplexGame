#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string filename)
{
    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channelCount, 0);

    //FIXME this needs proper error handling. For now we're just going to assume the load worked, and if it doesn't, we'll probably crash.

    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    if (channelCount == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    }
    else if (channelCount == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }
    //glGenerateMipmap(GL_TEXTURE_2D);

    //Instead of generating mipmaps, we can set the texture parameter to not use mipmaps. But we have to do one of these or else the texture won't appear.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);
    successfullyLoaded = true;
}

Texture::~Texture()
{
    if (successfullyLoaded)
    {
        glDeleteTextures(1, &textureID);
    }
}

Texture::Texture(Texture&& otherTexture)
{
    if (&otherTexture == this)
    {
        return;
    }
    if (successfullyLoaded)
    {
        glDeleteTextures(1, &textureID);
    }
    this->textureID = otherTexture.textureID;
    this->height = otherTexture.height;
    this->width = otherTexture.width;
    this->channelCount = otherTexture.channelCount;

    otherTexture.successfullyLoaded = false;
}

Texture& Texture::operator=(Texture&& otherTexture)
{
    if (&otherTexture == this)
    {
        return *this;
    }
    if (successfullyLoaded)
    {
        glDeleteTextures(1, &textureID);
    }

    this->textureID = otherTexture.textureID;
    this->height = otherTexture.height;
    this->width = otherTexture.width;
    this->channelCount = otherTexture.channelCount;

    otherTexture.successfullyLoaded = false;

    return *this;
}

void Texture::Bind(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind(int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}