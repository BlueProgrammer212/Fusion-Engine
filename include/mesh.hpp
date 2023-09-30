#pragma once

#include "application.hpp"

namespace FusionCoreEngine {
class Mesh {
 public:
  Mesh(const std::vector<struct Vertex>& t_vertices,
       const std::vector<unsigned int>& t_indices);
  ~Mesh();

  [[nodiscard]] inline const std::vector<struct Vertex>& getVertices() const {
    return m_vertices;
  }

  [[nodiscard]] inline const std::vector<unsigned int>& getIndices() const {
    return m_indices;
  }

  void setup();

  void render();
  void update();

 private:
  Buffers m_buffers;
  unsigned int m_vao_address;

  std::vector<struct Vertex> m_vertices;
  std::vector<unsigned int> m_indices;

  bool m_backface_culling_enabled;
};
};  // namespace FusionCoreEngine