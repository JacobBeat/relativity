#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

void checkShaderCompile(GLuint shader, const char *label);
void checkProgramLink(GLuint program);
GLuint createShaders();
