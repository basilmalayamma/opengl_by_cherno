#ifndef GL_DEBUG_H_
#define GL_DEBUG_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x) if((!x)) return 0;

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall());

void GLClearError();
int GLLogCall();

#endif
