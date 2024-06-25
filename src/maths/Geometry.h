#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#define PI glm::pi<float>()

struct Vertex
{
  float coords[3];
};


void BuildCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float radius, float height, unsigned int nSides);
