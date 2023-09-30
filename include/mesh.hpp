// #pragma once

// #include "application.hpp"

// class Mesh {
//  public:
//   Mesh(const std::vector<Vertex>& t_vertices,
//        const std::vector<unsigned int>& t_indices,
//        bool t_enable_backface_culling);

//   ~Mesh();

//   void setup();

//   std::vector<Vertex> vertices;
//   std::vector<unsigned int> indices;

//   void render();
//   void update();

//  private:
//   std::unique_ptr<Buffer> m_vbo;
//   std::unique_ptr<Buffer> m_ibo;
//   unsigned int m_vao;

//   bool m_enable_backface_culling;
// };