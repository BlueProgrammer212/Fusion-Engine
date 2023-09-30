#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace FusionCoreEngine {
struct Vertex {
  glm::vec3 position;
};

extern std::vector<struct Vertex> vertices;
extern std::vector<unsigned int> indices;
};  // namespace FusionCoreEngine