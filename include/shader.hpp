#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "application.hpp"

namespace FusionCoreEngine {
class Shader {
 public:
  explicit Shader(std::string vertex_shader_path,
                  std::string fragment_shader_path);
  virtual ~Shader();

  void createProgram();
  unsigned int compileShader(const std::string& shader_source, GLenum type);

  auto parseFile(std::string shader_file_path) -> const std::string;

  [[nodiscard]] inline unsigned int getProgram() const { return m_program; }

  inline void use() { glUseProgram(m_program); }

  static inline void disable() { glUseProgram(0); }

  template <typename T>
  void setUniform(const char* t_uniform_name, const T& data);

 private:
  unsigned int m_program;

  std::string m_vertex_shader_path;
  std::string m_fragment_shader_path;

  std::unordered_map<const char*, int> m_uniform_cache;
};
};  // namespace FusionCoreEngine

#include "shader.inl"