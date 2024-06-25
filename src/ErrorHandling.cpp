#include "ErrorHandling.h"

#include <iostream>

void GLClearError()
{
	while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " <<
			" " << file << " " << line << '\n';
		return true;
	}
	return false;
}

void GLAPIENTRY ErrorCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	printf("Message from OpenGL:\nSource: 0x%x\nType: 0x%x\n"
		"Id: 0x%x\nSeverity: 0x%x\n", source, type, id, severity);
	printf("%s\n", message);
}


