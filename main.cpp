#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>

constexpr int screen_width = 800;
constexpr int screen_height = 600;

struct Surface {
  std::vector<double> xyzArray;

  Surface(int VertexCountPerSide) {
    const int CoordinateCount = VertexCountPerSide * VertexCountPerSide * 3;
    const double vertexStep = 2.0 / (VertexCountPerSide - 1);

    xyzArray.resize(VertexCountPerSide);

    for (int row = 0; row < VertexCountPerSide; row++) {
      for (int column = 0; column < VertexCountPerSide; column++) {
        const double x = -1.0 + column * vertexStep;
        const double y = -1.0 + row * vertexStep;
        const double z = 0.0;

        const double vertexStartIndex = (row * VertexCountPerSide + column) * 3;
        xyzArray[vertexStartIndex] = x;
        xyzArray[vertexStartIndex + 1] = y;
        xyzArray[vertexStartIndex + 2] = z;
      }
    }
  }
};

int main() {
  if (!glfwInit()) {
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(screen_width, screen_height, "3D Window", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_CLEAR_VALUE);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
