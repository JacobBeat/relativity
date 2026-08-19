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

bool pause = false;

void bindVertexData(unsigned int &VAO, unsigned int &VBO, const float *vertices,
                    int vertex_count);
void processInput(GLFWwindow *window);

class Particle {
public:
  unsigned int VAO, VBO;
  constexpr static int triangle_count = 50;
  constexpr static float radius = 0.02;
  int vertex_count;

  vec2 position = vec2(0.0, 0.0);
  vec2 velocity = vec2(0.0, 0.0);
  double mass;
  double time = 0.0; // local time

  void Draw() {}

  std::vector<float> genVertexData() {
    std::vector<float> vertices;
    for (int i = 0; i < triangle_count; i++) {
      vertices.push_back(position.x / 5);
      vertices.push_back(position.y / 5);
      vertices.push_back(0.0);

      vertices.push_back(position.x / 5 +
                         radius * std::cos(2 * pi * i / triangle_count));
      vertices.push_back(position.y / 5 +
                         radius * std::sin(2 * pi * i / triangle_count));
      vertices.push_back(0.0);

      vertices.push_back(position.x / 5 +
                         radius * std::cos(2 * pi * (i + 1) / triangle_count));
      vertices.push_back(position.y / 5 +
                         radius * std::sin(2 * pi * (i + 1) / triangle_count));
      vertices.push_back(0.0);
    }
    return vertices;
  }

  Particle(double x, double y, double vx, double vy, double mass) {
    this->position = vec2(x, y);
    this->velocity = vec2(vx, vy);
    this->mass = mass;

    std::vector<float> vertices = genVertexData();
    vertex_count = vertices.size();
    bindVertexData(VAO, VBO, vertices.data(), vertex_count);
  }

  void update(double dt) {
    position += (velocity * dt) / 5;
    time += dt;

    std::vector<float> vertices = genVertexData();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);
  }

  void print() {
    std::cout << "\033[K" << "Position (" << position.x << "," << position.y
              << ")\n";
    std::cout << "\033[K" << "Velocity (" << velocity.x << "," << velocity.y
              << ")\n";
    std::cout << "\033[K" << "Time " << time << "\n";
    std::cout << std::flush;
  }
};

class System {
public:
  std::vector<Particle> particles;
  vec2 origin_position = vec2(0.0, 0.0);
  vec2 origin_velocity = vec2(0.0, 0.0);
  double time = 0.0;

  void lorentz_transform(vec2 transformed_velocity) {}

  void update(double dt) {}

  void printInfo() {
    for (int i = 0; i < particles.size(); i++) {
      std::cout << "\033[K" << "Particle: " << i + 1 << "\n";
      particles[i].print();
    }
    std::cout << "\033[" << 4 * particles.size() << "A";
  }

  System(std::vector<Particle> &p_system) { this->particles = p_system; }
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
  glewInit();

  glViewport(0, 0, screen_width, screen_height);

  GLuint shaderProgram = createShaders();

  std::vector<Particle> particles;
  particles.push_back(Particle(0.0, 0.0, 0.0, 0.0, 2));
  particles.push_back(Particle(0.0, 1.0, 1.0, 0.0, 2));
  particles.push_back(Particle(1.0, 0.0, 0.0, 1.0, 2));
  System sys = System(particles);
  float lastFrame = 0;
  float dt;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;
    processInput(window);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    for (Particle &p : sys.particles) {
      glBindVertexArray(p.VAO);
      glDrawArrays(GL_TRIANGLES, 0, p.vertex_count / 3);
      if (!pause) {
        p.update(dt);
      }
    }
    sys.printInfo();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void bindVertexData(unsigned int &VAO, unsigned int &VBO, const float *vertices,
                    int vertex_count) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    pause = !pause;
  }
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
  }
}
