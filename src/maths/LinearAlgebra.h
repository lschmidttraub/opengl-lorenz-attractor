#pragma once
#include <glm/glm.hpp>

namespace lin
{
  glm::mat4 translate(glm::vec3 pos);
  glm::mat4 rotate(float pitch, float roll, float yaw);
  glm::mat4 rotateX(float angle);
  glm::mat4 rotateY(float angle);
  glm::mat4 rotateZ(float angle);
  glm::mat4 lookAt(glm::vec3 eye, glm::vec3 obj, glm::vec3 up);
  glm::mat4 perspective(float yFov, float aspect, float zNear, float zFar);
  glm::mat4 scale(glm::vec3 factors);
  glm::mat4 orient(glm::vec3 front, glm::vec3 right);
}