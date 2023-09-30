#include "application.hpp"

int main(int argc, char* argv[]) {
  auto* app =
      new FusionCoreEngine::Application(1200, 700, "Fusion Engine v1.0 Indev");

  while (!glfwWindowShouldClose(app->getWindow())) {
    app->update(FusionCoreEngine::deltaTime);
    app->render();
    app->events();
  }

  app->destroy();

  return 0;
}