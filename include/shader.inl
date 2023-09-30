#include "shader.hpp"

namespace FusionCoreEngine {
template <typename T>
void Shader::setUniform(const char* t_uniform_name, const T& data) {
  // Make sure, we activate the shader first before setting the uniforms.
  this->use();

  auto it = m_uniform_cache.find(t_uniform_name);

  if (it == m_uniform_cache.end()) {
    const int location = glGetUniformLocation(m_program, t_uniform_name);
    m_uniform_cache[t_uniform_name] = location;
  }

  if constexpr (std::is_same_v<T, glm::mat4>) {
    glUniformMatrix4fv(m_uniform_cache.at(t_uniform_name), 1, GL_FALSE,
                       glm::value_ptr(data));
  } else if constexpr (std::is_same_v<T, float>) {
    glUniform1f(m_uniform_cache.at(t_uniform_name), data);
  } else if constexpr (std::is_same_v<T, int>) {
    glUniform1i(m_uniform_cache.at(t_uniform_name), data);
  } else if constexpr (std::is_same_v<T, glm::vec4>) {
    glUniform4f(m_uniform_cache.at(t_uniform_name), RGBA(data));
  } else if constexpr (std::is_same_v<T, glm::vec3>) {
    glUniform3f(m_uniform_cache.at(t_uniform_name), data.x, data.y, data.z);
  } else if constexpr (std::is_same_v<T, glm::vec2>) {
    glUniform2f(m_uniform_cache.at(t_uniform_name), data.x, data.y);
  } else {
    std::cout << "Unsupported type.\n"
              << "\n";
  }
}
};