#include "shader.hpp"

namespace FusionCoreEngine {
Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path)
    : m_vertex_shader_path(vertex_shader_path),
      m_fragment_shader_path(fragment_shader_path) {
  this->createProgram();
};

Shader::~Shader() {
  std::cout << "[INFO]: Deleting the shader program\n";
  glDeleteProgram(m_program);
}

void Shader::createProgram() {
  const std::string& vertex_shader_source = parseFile(m_vertex_shader_path);
  const std::string& fragment_shader_source = parseFile(m_fragment_shader_path);

  std::cout << vertex_shader_source << "\n";
  std::cout << fragment_shader_source << "\n";

  unsigned int vertex_shader =
      compileShader(vertex_shader_source, GL_VERTEX_SHADER);
  unsigned int fragment_shader =
      compileShader(fragment_shader_source, GL_FRAGMENT_SHADER);

  m_program = glCreateProgram();
  glAttachShader(m_program, vertex_shader);
  glAttachShader(m_program, fragment_shader);
  glLinkProgram(m_program);
  glValidateProgram(m_program);

  int result;
  glGetProgramiv(m_program, GL_LINK_STATUS, &result);

  if (result == GL_FALSE) {
    int length;

    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
    char* message = static_cast<char*>(alloca(length * sizeof(char)));
    glGetProgramInfoLog(m_program, length, &length, message);

    std::cout << "An error occured while linking this program, " << message
              << "\n";

    glDeleteProgram(m_program);
  }

  // Delete the shaders that are no longer needed.
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

unsigned int Shader::compileShader(const std::string& shader_source,
                                   GLenum type) {
  unsigned int id = glCreateShader(type);

  const char* src = shader_source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;

  glGetShaderiv(id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {
    int length;

    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    char* message = static_cast<char*>(alloca(length * sizeof(char)));
    glGetShaderInfoLog(id, length, &length, message);

    std::cout << "An error occured while compiling this shader, " << message
              << "\n";

    glDeleteShader(id);

    return -1;
  }

  return id;
}

auto Shader::parseFile(std::string shader_file_path) -> const std::string {
  std::string shader_source;
  std::ifstream shader_file(shader_file_path);

  if (!shader_file.is_open()) {
    std::cerr << "Failed to open shader file: " << shader_file_path << "\n";
    return shader_source;
  }

  std::stringstream shader_stream;
  shader_stream << shader_file.rdbuf();
  shader_file.close();

  shader_source = shader_stream.str();

  return shader_source;
}
};  // namespace FusionCoreEngine