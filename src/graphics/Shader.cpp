#include "Shader.h"


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  std::string vertexSource = ParseShader(vertexPath);
  std::string fragmentSource = ParseShader(fragmentPath);
  m_RendererID = CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
  glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
  glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
  glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name)
{
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }
  int location = glGetUniformLocation(m_RendererID, name.c_str());
  if (location == -1) std::cout << "Uniform not found\n";
  m_UniformLocationCache[name] = location;
  return location;
}

void Shader::setUniform4f(const std::string& name, const glm::vec4& vec)
{
  glUniform4f(GetUniformLocation(name), vec.r, vec.g, vec.b, vec.a);
}


void Shader::setUniformMat4f(const std::string& name, const glm::mat4& mat)
{
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}



std::string Shader::ParseShader(const std::string& path)
{
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Couldn't open file\n";
    return "";
  }

  std::stringstream ss;

  std::string line;
  while (std::getline(file, line))
  {
    ss << line << '\n';
  }
  file.close();
  return ss.str();
}


unsigned int Shader::CompileShader(GLenum type, const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, NULL);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)malloc(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader\n";
    std::cout << message << '\n';
    free(message);
    glDeleteShader(id);
    return 0;
  }

  return id;
}

unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

