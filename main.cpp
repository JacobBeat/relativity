#include "3vec.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

constexpr int screen_width = 800;
constexpr int screen_height = 800;
constexpr float pi = 3.14159265359;

GLuint drawTriangle() {
  float vertex_data[] = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};

  unsigned int vertex_array_object;
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  unsigned int vertex_buffer_object;
  glGenBuffers(1, &vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertex_data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  return vertex_array_object;
}

void drawCircle(float xPos, float yPos, float radius, int res) {
  unsigned int vertex_array;
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  float vertices[3 * (res + 1)];
  vertices[0] = (xPos);
  vertices[1] = (yPos);
  vertices[2] = 0.0;
  for (int i = 0; i < res; i++) {
    vertices[3 * (i + 1)] =
        (xPos + radius * std::cos(2 * pi * i / (res))); // x coord
    vertices[1 + 3 * (i + 1)] =
        (yPos + radius * std::sin(2 * pi * i / (res))); // y coord
    vertices[2 + 3 * (i + 1)] = 0.0;                    // z coord
  }

  unsigned int vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

  glBufferData(GL_ARRAY_BUFFER, 9 * res * sizeof(float), vertices,
               GL_STATIC_DRAW);

  unsigned int index[3 * res];
  for (int i = 0; i < res - 1; i++) {
    index[3 * i] = 0;
    index[1 + 3 * i] = 1 + i;
    index[2 + 3 * i] = 2 + i;
  }
  index[3 * (res - 1)] = 0;
  index[3 * (res - 1) + 1] = res;
  index[3 * (res - 1) + 2] = 1;

  unsigned int element_buffer;
  glGenBuffers(1, &element_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * res * sizeof(unsigned int), index,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(vertex_array);
  glDrawElements(GL_TRIANGLES, 3 * res, GL_UNSIGNED_INT, 0);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // drawCircle(-1.0 + (2 * xpos / screen_width),
    //            1.0 - (2 * ypos / screen_height), 0.1, 100);
  }
}
class Particle {
public:
  constexpr static int triangle_count = 50;
  constexpr static float radius = 0.05;
  vec2 position = vec2(0.0, 0.0);
  vec2 velocity = vec2(0.0, 0.0);
  double mass;
  double time = 0.0; // local time

  void Draw() { drawCircle(position.x, position.y, radius, triangle_count); }

  Particle(double x, double y, double vx, double vy, double mass) {
    this->position = vec2(x, y);
    this->velocity = vec2(vx, vy);
    this->mass = mass;
  }

  void update(double dt) { position += (velocity * dt); }
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

  Particle particles[] = {Particle(0.0, 0.0, 0.0, 0.0, 2),
                          Particle(0.0, 0.0, 0.1, 0.0, 2),
                          Particle(0.2, 0.0, 0.0, 0.1, 2)};

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glewInit();

  glViewport(0, 0, screen_width, screen_height);

  GLuint shaderProgram = createShaders();

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // glClearColor(0.0, 0.0, 0.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    for (Particle p : particles) {
      p.Draw();
      p.update(0.001);
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
