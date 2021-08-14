#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>
#include <vertexBuffer.h>
#include <iostream>

class vertexArray {
public:
   vertexArray(int vertexSize);
   ~vertexArray();
   void bind();
   void unBind(void);
   void enablePointer(GLint prgm, std::string name, int offset);
   int size();

private:
   unsigned int mVAO;
   int mVertexSize;
};

#endif
