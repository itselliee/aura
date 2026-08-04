#include <renderer.hpp>

namespace AuraEngine {
class Core {
public:
  Core();
  ~Core();

  void Init();
  void Update(); // call this every frame in your editor
private:
  Renderer *m_renderer;
};
} // namespace AuraEngine
