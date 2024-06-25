#pragma once
#include "maths/Geometry.h"

#include <glm/glm.hpp>

#include <vector>

class Attractor
{
private:
  glm::vec3 m_position;
  float m_s;
  float m_r;
  float m_b;
  glm::vec3 m_grad;
  std::vector<Vertex> m_path;

public:
  Attractor(glm::vec3 position, float s, float r, float b, float speed);

  float speed;
  
  void CalculateGradient();
  void Update(double deltaTime);
  glm::vec3 getPosition() const;
  glm::vec3 getGrad() const;
  const std::vector<Vertex>& getPath() const;
  void reset(glm::vec3 position);
};

