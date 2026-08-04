#include <iostream>

#include <core.hpp>

namespace AuraEngine {
Core::Core() { m_renderer = new Renderer(); }
Core::~Core() {}

void Core::Init() {
  std::cout << "Starting engine job.." << std::endl;
  std::cout << "Aura-Engine specification 0.1, OpenGL 3.3" << std::endl;

  std::cout << "Creating framebuffer.." << std::endl;
  m_renderer->CreateFramebuffer();
}

void Core::Update() {}
} // namespace AuraEngine
