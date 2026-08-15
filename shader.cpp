#include "shader.hpp"
#include <iostream>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "void main() {\n"
    "gl_Position.xyz = vertexPosition_modelspace;\n"
    "gl_Position.w = 1.0;\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;"
                                   "void main() {\n"
                                   "FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
                                   "}\0";

void checkShaderCompile(GLuint shader, const char *label) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "Shader compile error (" << label << "): " << infoLog
              << std::endl;
  }
}

void checkProgramLink(GLuint program) {
  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "Program link error: " << infoLog << std::endl;
  }
}

GLuint createShaders() {
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderCompile(vertexShader, "vertex");

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderCompile(fragmentShader, "fragment");

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  checkProgramLink(shaderProgram);
  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shaderProgram;
}
