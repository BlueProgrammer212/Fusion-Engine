#include "mesh.hpp"
#include "buffer.hpp"

namespace FusionCoreEngine {
Mesh::Mesh(const std::vector<struct Vertex>& t_vertices,
           const std::vector<unsigned int>& t_indices)
    : m_vertices(t_vertices), m_indices(t_indices) {
  this->setup();
};

Mesh::~Mesh() {
  SAFE_DELETE(m_buffers.vbo);
  SAFE_DELETE(m_buffers.ibo);
}

void Mesh::setup() {
  glGenVertexArrays(1, &m_vao_address);
  glBindVertexArray(m_vao_address);

  m_buffers.vbo = new FusionCoreEngine::Buffer();
  m_buffers.vbo->generate<Vertex>(GL_ARRAY_BUFFER, m_vertices, false);

  m_buffers.vbo->addAttrib<glm::vec3>(0);

  m_buffers.ibo = new FusionCoreEngine::Buffer();
  m_buffers.ibo->generate<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, m_indices,
                                        false);

#ifdef __DEBUG__
  m_buffers.vbo->unbind();
  m_buffers.ibo->unbind();
#endif

  glBindVertexArray(0);
}

void Mesh::update() {}

void Mesh::render() {
  glBindVertexArray(m_vao_address);

#ifdef __DEBUG__
  m_buffers.vbo->bind();
  m_buffers.ibo->bind();
#endif

  glDrawElements(GL_TRIANGLES,
                 static_cast<GLsizei>(m_buffers.ibo->getDataLength()),
                 GL_UNSIGNED_INT, nullptr);

  glBindVertexArray(0);

#ifdef __DEBUG__
  m_buffers.vbo->unbind();
  m_buffers.ibo->unbind();
#endif
}
}  // namespace FusionCoreEngine