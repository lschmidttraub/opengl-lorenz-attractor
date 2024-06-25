#include "Geometry.h"

void BuildCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, float radius, float height, unsigned int nSides)
{
  vertices.clear();
  indices.clear();
  vertices.push_back({ {0.0f, 0.0f, 0.0f} });
  vertices.push_back({ {0.0f, 0.0f, height} });

  float theta = 0.0f;
  float inc = 2 * PI / nSides;

  for (unsigned int i = 0; i < nSides; ++i)
  {
    vertices.push_back({ {cos(theta)*radius, sin(theta)*radius, 0.0f } });
    theta += inc;
    indices.insert(indices.end(), { 0, i + 2, (i+1)%nSides + 2,     1, i + 2, (i+1)%nSides + 2});
  }
}