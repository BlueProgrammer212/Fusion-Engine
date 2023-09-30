#pragma once

#include "application.hpp"

namespace FusionCoreEngine {
class Buffer {
 public:
  Buffer();
  ~Buffer();

  template <typename T>
  void generate(GLenum t_buffer_type, const std::vector<T>& data,
                bool is_dynamic = false,
                unsigned int allocated_vertices = 1024U);

  template <typename T>
  void addAttrib(const std::uint64_t offset, unsigned int dimensions = 3);

  inline void bind() { glBindBuffer(m_buffer_type, m_address); }
  inline void unbind() { glBindBuffer(m_buffer_type, 0); }

  [[nodiscard]] inline unsigned int getAddress() const { return m_address; }

  [[nodiscard]] inline unsigned int getAttributeCount() const {
    return m_local_attribute_count;
  }

  [[nodiscard]] inline std::size_t getDataLength() const {
    return m_data_length;
  }

  [[nodiscard]] inline bool isGenerated() const { return m_is_generated; }

 private:
  unsigned int m_address;
  static unsigned int s_AttributeCount;
  unsigned int m_local_attribute_count;
  std::size_t m_data_length;

  bool m_is_generated;
  GLenum m_buffer_type;

  bool m_is_dynamic;
};
};  // namespace FusionCoreEngine

#include "buffer.inl"