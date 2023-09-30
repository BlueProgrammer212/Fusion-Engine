#include "buffer.hpp"

namespace FusionCoreEngine {
Buffer::Buffer()
    : m_address(0),
      m_local_attribute_count(0),
      m_data_length(0),
      m_is_generated(false),
      m_buffer_type(GL_ARRAY_BUFFER),
      m_is_dynamic(false){};

Buffer::~Buffer() {
  std::cout << "[INFO]: Deleting the "
            << (m_buffer_type == GL_ARRAY_BUFFER ? "vertex buffer object."
                                                 : "index buffer object.")
            << "\n";

  glDeleteBuffers(1, &m_address);
};

unsigned int Buffer::s_AttributeCount = 0U;
};  // namespace FusionCoreEngine