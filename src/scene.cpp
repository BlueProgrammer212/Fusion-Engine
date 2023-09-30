#include "scene.hpp"
#include "mesh.hpp"
#include "shader.hpp"

namespace FusionCoreEngine {
Scene::Scene(int t_screen_width, int t_screen_height)
    : m_time(0.0f),
      m_last_time(0.0f),
      m_delta_time(0.0f),
      m_screen_width(t_screen_width),
      m_screen_height(t_screen_height){};

Scene::~Scene(){};

// TODO: Segregate transparent from opaque meshes based on their alpha values.
void Scene::addMesh(const std::vector<struct Vertex>& t_vertices,
                    const std::vector<unsigned int>& t_indices) {
  m_meshes.push_back(std::make_shared<Mesh>(t_vertices, t_indices));
}

void Scene::init() {
  // Default scene shaders.
  m_shader = std::make_unique<Shader>("../../res/shaders/vertex_shader.glsl",
                                      "../../res/shaders/fragment_shader.glsl");

  m_shader->use();

  m_camera = std::make_unique<Camera>();
  m_camera->setupPerspectiveMat(m_screen_width, m_screen_height);
  m_camera->setupViewMat();

  // Initialize the MVP matrix uniforms.
  m_shader->setUniform<glm::mat4>("u_Model", glm::mat4(1.0f));
  m_shader->setUniform<glm::mat4>("u_View", m_camera->getViewMat());
  m_shader->setUniform<glm::mat4>("u_Projection",
                                  m_camera->getPerspectiveMat());

  Shader::disable();
}

void Scene::render() {
  m_shader->use();

  for (auto mesh : m_meshes) {
    mesh->render();
  }

  for (auto transparent_mesh : m_transparent_meshes) {
    transparent_mesh->render();
  }

  Shader::disable();
}

void Scene::update(float fixed_delta_time) {
  m_time += fixed_delta_time;
  m_delta_time = m_time - m_last_time;
  m_last_time = m_time;

  for (auto mesh : m_meshes) {
    mesh->update();
  }

  for (auto transparent_mesh : m_transparent_meshes) {
    transparent_mesh->update();
  }
}

void Scene::events() {}
};  // namespace FusionCoreEngine