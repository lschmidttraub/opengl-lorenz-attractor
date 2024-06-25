#include "Attractor.h"

Attractor::Attractor(glm::vec3 position, float s, float r, float b, float speed)
  : m_position{ position }, m_s{ s }, m_r{ r }, m_b{ b }, speed{ speed }
{
  CalculateGradient();
}

void Attractor::CalculateGradient()
{
  float x = m_position.x;
  float y = m_position.y;
  float z = m_position.z;
  m_grad = {
    m_s * (y - x),
    x * (m_r - z) - y,
    x * y - m_b * z
  };
}

void Attractor::Update(double deltaTime)
{
  CalculateGradient();
  m_path.push_back({ {m_position.x, m_position.y, m_position.z} });
  m_position += (float)deltaTime * speed * m_grad;
}

glm::vec3 Attractor::getPosition() const
{
  return m_position;
}

const std::vector<Vertex>& Attractor::getPath() const
{
  return m_path;
}

glm::vec3 Attractor::getGrad() const
{
  return m_grad;
}

void Attractor::reset(glm::vec3 position)
{
  m_path.clear();
  m_position = position;
  speed = 1.0f;
}

