namespace AuraEngine {
class Renderer {
public:
  static Renderer &Get() {
    static Renderer instance;
    return instance;
  }

  Renderer(const Renderer &) = delete;
  void operator=(const Renderer &) = delete;

  void CreateFramebuffer();

  void PreRender();
  void Render();
  void PostRender();

private:
  Renderer();
  ~Renderer();
};
} // namespace AuraEngine
