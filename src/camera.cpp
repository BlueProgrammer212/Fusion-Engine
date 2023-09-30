#include "camera.hpp"

namespace FusionCoreEngine {
// TODO: Create a .json for these initial values.
Camera::Camera()
    : m_view(glm::mat4(1.0f)),
      m_perspective(glm::mat4(1.0f)),
      m_FOV(80.0F),
      m_position(glm::vec3(0.0f, 0.0f, 0.1f)),
      m_direction(glm::vec3(0.0f)),
      m_up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

Camera::~Camera() {}

void Camera::setupPerspectiveMat(const int screen_width,
                                 const int screen_height) {
  m_perspective = glm::perspective(
      glm::radians(m_FOV),
      static_cast<float>(screen_width) / static_cast<float>(screen_height),
      0.1f, 100.0f);
}

void Camera::setupViewMat() {
  m_view = glm::lookAt(m_position, m_direction, m_up);
}
};  // namespace FusionCoreEngine
