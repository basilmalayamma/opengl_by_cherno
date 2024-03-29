#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

class Texture {
public:
    Texture(std::string file_name);
    ~Texture();

    void Bind();
    void Bind(int slot);
    void unBind();

private:
    unsigned int mID;
};

#endif
