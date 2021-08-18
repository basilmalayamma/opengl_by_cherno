#include <texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>

Texture::Texture(std::string file_name) {
    int width;
    int height;
    unsigned char *data = stbi_load(
		    file_name.c_str(),
		    &width,
		    &height, 0, 4);
    if(data == NULL) {
	std::cout << "data is null" << std::endl;
    }

    glGenTextures(1, &mID);
    glBindTexture(GL_TEXTURE_2D, mID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
	GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
	GL_UNSIGNED_BYTE, data);

    std::cout << "Resolution = (" << width << "x" << height << ")" << std::endl;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::Bind(int slot) {
    glBindTextureUnit(slot, mID);
}

void Texture::unBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &mID);
}
