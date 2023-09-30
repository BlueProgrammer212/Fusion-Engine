#include "application.hpp"
#include "buffer.hpp"
#include "shader.hpp"

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

  // Setup the shader program.
  m_main_shader =
      std::make_unique<Shader>("../../res/shaders/vertex_shader.glsl",
                               "../../res/shaders/fragment_shader.glsl");

  m_main_shader->use();

  m_camera = std::make_unique<Camera>();
  m_camera->setupPerspectiveMat(width, height);
  m_camera->setupViewMat();

  // Initialize the MVP matrix uniforms.
  m_main_shader->setUniform<glm::mat4>("u_Model", glm::mat4(1.0f));
  m_main_shader->setUniform<glm::mat4>("u_View", m_camera->getViewMat());
  m_main_shader->setUniform<glm::mat4>("u_Projection",
                                       m_camera->getPerspectiveMat());

  // Generate a vertex array object. (Required in core profile.)
  glGenVertexArrays(1, &m_vao_address);
  glBindVertexArray(m_vao_address);

  // Populate the vertex struct array.
  vertices.clear();

  auto vertexPopulation = [](const glm::vec3& pos) {
    Vertex vert;
    vert.position = pos;

    vertices.push_back(vert);
  };

  std::for_each(std::begin(quad_vertices), std::end(quad_vertices),
                vertexPopulation);

  // Create buffers for debugging purposes.
  m_buffers.vbo = new FusionCoreEngine::Buffer();
  m_buffers.vbo->generate<Vertex>(GL_ARRAY_BUFFER, vertices, false);

  m_buffers.vbo->addAttrib<glm::vec3>(offsetof(Vertex, position));

  // Populate the index array.
  indices.clear();
  indices.insert(indices.end(), quad_indices.begin(), quad_indices.end());

  // Create an index buffer object.
  m_buffers.ibo = new FusionCoreEngine::Buffer();
  m_buffers.ibo->generate<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, indices,
                                        false);

// Unbind the buffer objects to prevent accidental data alteration during debugging.
#ifdef __DEBUG__
  m_buffers.vbo->unbind();
  m_buffers.ibo->unbind();
#endif

  Shader::disable();
  glBindVertexArray(0);

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_callback);
}

void Application::update(float t_deltaTime) {
  currentTick += 0.01f;
  deltaTime = currentTick - previousTick;
  previousTick = currentTick;
}

void Application::render() {
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_main_shader->use();

  glBindVertexArray(m_vao_address);

#ifdef __DEBUG__
  m_buffers.ibo->bind();
  m_buffers.vbo->bind();
#endif

  glDrawElements(GL_TRIANGLES,
                 static_cast<GLsizei>(m_buffers.ibo->getDataLength()),
                 GL_UNSIGNED_INT, nullptr);

#ifdef __DEBUG__
  m_buffers.ibo->unbind();
  m_buffers.vbo->unbind();
#endif

  Shader::disable();
  glBindVertexArray(0);

  glfwSwapBuffers(m_window);
}

void Application::events() {
  glfwPollEvents();
};
};  // namespace FusionCoreEngine