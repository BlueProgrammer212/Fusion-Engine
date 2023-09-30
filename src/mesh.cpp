// #include "mesh.hpp"
// #include "buffer.hpp"

// Mesh::Mesh(const std::vector<Vertex>& t_vertices,
//            const std::vector<unsigned int>& t_indices,
//            bool t_enable_backface_culling)
//     : vertices(t_vertices),
//       indices(t_indices),
//       m_enable_backface_culling(t_enable_backface_culling),
//       m_vbo(std::make_unique<Buffer>(vertices, GL_ARRAY_BUFFER)),
//       m_ibo(std::make_unique<Buffer>(indices, GL_ELEMENT_ARRAY_BUFFER)) {
//   this->setup();
// }

// Mesh::~Mesh() {}

// void Mesh::setup() {
//   glGenVertexArrays(1, &m_vao);
//   glBindVertexArray(m_vao);

//   glBindVertexArray(0);
//   m_vbo->unbind();
//   m_ibo->unbind();
// }

// void Mesh::render() {
//   glBindVertexArray(m_vao);
//   m_vbo->bind();
//   m_ibo->bind();

//   if (m_enable_backface_culling) {
//     glEnable(GL_CULL_FACE);
//   } else {
//     glDisable(GL_CULL_FACE);
//   }

//   glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
//                  GL_UNSIGNED_INT, 0);

//   m_vbo->unbind();
//   m_ibo->unbind();
//   glBindVertexArray(0);
// }

// void Mesh::update() {}