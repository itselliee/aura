#include <glad/glad.h>
#include <iostream>

namespace AuraEngine {
class Renderer {
public:
  Renderer();
  ~Renderer();

  static Renderer &Get() {
    static Renderer instance;
    return instance;
  }

  Renderer(const Renderer &) = delete;
  void operator=(const Renderer &) = delete;

  void CreateFramebuffer();

  void InitializeRenderBuffer();

  void PreRender();
  void Render();
  void PostRender();

  void CleanupContext();

private:
  const int width = 1920;
  const int height = 1080;

  GLuint m_Framebuffer = 0;
  GLuint m_ColorTexture = 0;
  GLuint m_DepthRBO = 0;

  GLuint VBO = 0;
  GLuint VAO = 0;
  GLuint EBO = 0;
};
} // namespace AuraEngine
