#include "vertex.hpp"

namespace FusionCoreEngine {
// Ensure that the vertex array is not empty to prevent runtime errors.
std::vector<struct Vertex> vertices = {Vertex{glm::vec3(0.0f)}};

// Ensure that the index array is not empty.
std::vector<unsigned int> indices = {0};
};  // namespace FusionCoreEngine