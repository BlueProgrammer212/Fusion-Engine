#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "vertex.hpp"

// #include <json/json.h>

// using json = nlohmann::json;

#define SAFE_DELETE(ptr) \
  if (ptr != nullptr)    \
    delete ptr;

namespace FusionCoreEngine {
void framebuffer_callback(GLFWwindow* window, int width, int height);

class Buffer;
class Shader;
class Mesh;
class Scene;

struct Buffers {
  Buffer* vbo = nullptr;
  Buffer* ibo = nullptr;
};

class Application {
 public:
  Application(const int width, const int height, const char* title);
  ~Application();

  [[nodiscard]] GLFWwindow* getWindow() { return m_window; };

  void init(const int width, const int height, const char* title);

  void update(float deltaTime);
  void render();
  void events();

  inline void destroy() { delete this; }

 private:
  GLFWwindow* m_window;
  std::unique_ptr<Scene> m_game_editor_scene;
  std::shared_ptr<Mesh> m_quad_mesh_debug;
};

extern float deltaTime;
extern float currentTick;
extern float previousTick;
};  // namespace FusionCoreEngine
