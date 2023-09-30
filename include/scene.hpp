#pragma once

#include "application.hpp"

namespace FusionCoreEngine {
class Scene {
 public:
  Scene(int t_screen_width, int t_screen_height);
  ~Scene();

  virtual void init();
  virtual void render();
  virtual void update(float fixed_delta_time);
  virtual void events();

  void addMesh(const std::vector<struct Vertex>& t_vertices,
               const std::vector<unsigned int>& t_indices);

 private:
  std::unique_ptr<Camera> m_camera;
  std::unique_ptr<Shader> m_shader;

  int m_screen_width;
  int m_screen_height;

  float m_time;
  float m_last_time;
  float m_delta_time;

  std::vector<std::shared_ptr<Mesh>> m_meshes;

  // Separate the transparent and opaque meshes for alpha blending.
  std::vector<std::shared_ptr<Mesh>> m_transparent_meshes;
};
};  // namespace FusionCoreEngine