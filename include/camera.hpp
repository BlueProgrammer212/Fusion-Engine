#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace FusionCoreEngine {
class Camera {
 public:
  Camera();
  ~Camera();

  [[nodiscard]] inline glm::mat4& getViewMat() { return m_view; }

  [[nodiscard]] inline glm::mat4& getPerspectiveMat() { return m_perspective; }

  void setupPerspectiveMat(const int screen_width, const int screen_height);
  void setupViewMat();

 private:
  glm::mat4 m_view;
  glm::mat4 m_perspective;

  glm::vec3 m_position;
  glm::vec3 m_direction;
  glm::vec3 m_up;

  float m_FOV;
};
};  // namespace FusionCoreEngine