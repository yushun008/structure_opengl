#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "utils/shader.hpp"

std::string vertex_src_path = "/Volumes/develop/develop/learn_opengl/structured_opengl/Shader/vertex.vert";
std::string fragment_src_path = "/Volumes/develop/develop/learn_opengl/structured_opengl/Shader/fragment.frag";
int main() {
    if (!glfwInit()) {
        std::cerr << "glfw init error!" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(600, 600, "main window", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "glad load opengl failed!" << std::endl;
        exit(-1);
    }
    glViewport(0, 0, 600, 600);
    Utils::Shader shader(vertex_src_path, fragment_src_path);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3f, 0.2f, 0.6f, 0.2f);
        shader.Use();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
