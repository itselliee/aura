#include <renderer.hpp>

namespace AuraEngine {
void Renderer::CreateFramebuffer() {
  glGenFramebuffers(1, &m_Framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

  glGenTextures(1, &m_ColorTexture);
  glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorTexture, 0);

  glGenRenderbuffers(1, &m_DepthRBO);
  glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_RENDERBUFFER,
                            m_DepthRBO);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Framebuffer is not complete!" << std::endl;
  }

  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindFramebuffer(GL_RENDERBUFFER, 0);

  std::cout << "Framebuffer initialized ready for output" << std::endl;
}

void Renderer::Render() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
  glViewport(0, 0, width, height);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // render content goes here, probably when ECS is out.

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::CleanupContext() {
  // make sure you check if your windowing system's context is checked before
  // you call this. SDL3 example: if (SDL_GL_GetCurrentContext() == nullptr) {
  //   std::cout << "oh nooo" << std::endl;
  //   return;
  // }

  if (m_Framebuffer != 0) {
    glDeleteFramebuffers(1, &m_Framebuffer);
    m_Framebuffer = 0;
  }
  if (m_ColorTexture != 0) {
    glDeleteTextures(1, &m_ColorTexture);
    m_Framebuffer = 0;
  }
  if (m_DepthRBO != 0) {
    glDeleteRenderbuffers(1, &m_DepthRBO);
    m_Framebuffer = 0;
  }
}
} // namespace AuraEngine
