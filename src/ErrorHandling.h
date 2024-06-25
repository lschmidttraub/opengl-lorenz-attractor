#pragma once
#include <GL/glew.h>

#if DEBUG == 1
#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


void GLAPIENTRY ErrorCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);
