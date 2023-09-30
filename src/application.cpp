// clang-format off
#include "application.hpp"
#include "buffer.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "scene.hpp"
// clang-format on

namespace FusionCoreEngine {
float deltaTime = 0.0f;
float currentTick = 0.0f;
float previousTick = 0.0f;

void framebuffer_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

Application::Application(int width, int height, const char* title)
    : m_window(nullptr) {
  this->init(width, height, title);
};

Application::~Application() {
  std::cout << "[INFO]: Terminating the program.\n";
  // SAFE_DELETE(m_buffers.vbo);
  // SAFE_DELETE(m_buffers.ibo);
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Application::init(const int width, const int height, const char* title) {
  if (!glfwInit()) {
    std::cerr << "Failed to initiate GLFW.\n";
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  glfwMakeContextCurrent(m_window);

  glewExperimental = true;

  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initiate GLEW.\n";
    return;
  }

  glEnable(GL_DEPTH_TEST);

#ifdef ENABLE_VSYNC
  glfwSwapInterval(1);
#endif

  // clang-format off
  static const std::vector<glm::vec3> quad_vertices = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f)
  };

  static const std::vector<unsigned int> quad_indices = {
    0, 1, 2,
    2, 3, 0
  };
  // clang-format on

  std::vector<struct Vertex> vertices = {};
  std::vector<unsigned int> indices = {};

  // Populate the vertex array.
  for (const glm::vec3& pos : quad_vertices) {
    Vertex vert;
    vert.position = pos;

    vertices.push_back(vert);
  }

  indices.insert(indices.end(), quad_indices.begin(), quad_indices.end());

  m_game_editor_scene = std::make_unique<Scene>(width, height);
  m_game_editor_scene->init();

  m_game_editor_scene->addMesh(vertices, indices);

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_callback);
}

void Application::update(float t_deltaTime) {
  currentTick += 0.01f;
  deltaTime = currentTick - previousTick;
  previousTick = currentTick;

  m_game_editor_scene->update(0.01f);
}

void Application::render() {
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_game_editor_scene->render();

  glfwSwapBuffers(m_window);
}

void Application::events() {
  glfwPollEvents();

  m_game_editor_scene->events();
};
};  // namespace FusionCoreEngine