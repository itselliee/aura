#include <renderer.hpp>

namespace AuraEngine {
Renderer::Renderer() {
  // let me compile
}

Renderer::~Renderer() {
  // let me compile
}

void Renderer::CreateFramebuffer() {

// Apple deprecated OpenGL, only allowing up to OpenGL 4.1, so we have to do
// some work to fix it. Article link:
// https://appleinsider.com/articles/18/06/04/opengl-opencl-deprecated-in-favor-of-metal-2-in-macos-1014-mojave
#ifdef IS_APPLE_PLATFORM
  glGenFramebuffers(1, &m_Framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

  glGenTextures(1, &m_ColorTexture);
  glBindTexture(GL_TEXTURE_2D, m_ColorTexture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_ColorTexture, 0);

  glGenRenderbuffers(1, &m_DepthRBO);
  glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, m_DepthRBO);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Framebuffer not complete (OGL 4.1)" << std::endl;
  }

  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
#else
  glCreateFramebuffers(1, &m_Framebuffer);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorTexture);
  glTextureStorage2D(m_ColorTexture, 1, GL_RGB8, width, height);

  glTextureParameteri(m_ColorTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(m_ColorTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glNamedFramebufferTexture(m_Framebuffer, GL_COLOR_ATTACHMENT0, m_ColorTexture,
                            0);

  glCreateRenderbuffers(1, &m_DepthRBO);
  glNamedRenderbufferStorage(m_DepthRBO, GL_DEPTH_COMPONENT24, width, height);
  glNamedFramebufferRenderbuffer(m_Framebuffer, GL_DEPTH_ATTACHMENT,
                                 GL_RENDERBUFFER, m_DepthRBO);

  if (glCheckNamedFramebufferStatus(m_Framebuffer, GL_FRAMEBUFFER) !=
      GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Frambuffer not complete (OGL 4.6)" << std::endl;
  }
#endif
}

void Renderer::InitializeRenderBuffer() {}

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
