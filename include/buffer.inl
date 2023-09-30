#include "buffer.hpp"

namespace FusionCoreEngine {
template <typename T>
void Buffer::generate(GLenum t_buffer_type, const std::vector<T>& data,
                      bool is_dynamic, unsigned int allocated_vertices) {
  if (m_is_generated) {
    std::cerr << "[WARNING]: This buffer is already generated.\n";
  }

  std::cout << "[INFO]: Generating the buffers.\n";

  glGenBuffers(1, &m_address);
  m_buffer_type = t_buffer_type;
  m_is_dynamic = is_dynamic;
  m_is_generated = true;
  m_data_length = data.size();
  std::cout << "Data Length: " << m_data_length << "\n";

  glBindBuffer(t_buffer_type, m_address);

  if (!is_dynamic) {
    glBufferData(m_buffer_type, sizeof(T) * data.size(), data.data(),
                 GL_STATIC_DRAW);
    return;
  }

  glBufferData(m_buffer_type, sizeof(T) * allocated_vertices, &data.front(),
               GL_DYNAMIC_DRAW);
}

template <typename T>
void Buffer::addAttrib(const std::uint64_t offset, unsigned int dimensions) {
  if constexpr (std::is_same_v<T, float>) {
    glVertexAttribPointer(s_AttributeCount, dimensions, GL_FLOAT, GL_FALSE,
                          sizeof(T) * dimensions,
                          reinterpret_cast<const void*>(offset));
  } else if constexpr (std::is_same_v<T, glm::vec2> ||
                       std::is_same_v<T, glm::vec3> ||
                       std::is_same_v<T, glm::vec4>) {
    T temp_vec;
    glVertexAttribPointer(s_AttributeCount, temp_vec.length(), GL_FLOAT,
                          GL_FALSE, sizeof(T),
                          reinterpret_cast<const void*>(offset));
  } else {
    static_assert(false, "Unsupported type");
  }

  glEnableVertexAttribArray(s_AttributeCount++);
}
}  // namespace FusionCoreEngine