#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>
#include <vertexBuffer.h>

class vertexArray {
public:
   //vertexArray(unsigned int count);
   vertexArray();
   ~vertexArray();
   void bind();
   void unBind(void);
   void enablePointer();

private:
   unsigned int mVAO;
};

#endif
