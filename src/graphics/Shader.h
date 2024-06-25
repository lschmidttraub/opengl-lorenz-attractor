#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Shader
{
private:
  unsigned int m_RendererID;
  std::unordered_map<std::string, int> m_UniformLocationCache;

public:
  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  ~Shader();
  void Bind() const;
  void Unbind() const;

  int GetUniformLocation(const std::string& name);
  void setUniform4f(const std::string& name, const glm::vec4& vec);
  void setUniformMat4f(const std::string& name, const glm::mat4& mat);

  std::string ParseShader(const std::string& path);
  unsigned int CompileShader(GLenum type, const std::string& source);
  unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
};

