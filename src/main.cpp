#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "utils/shader.hpp"
#include "utils/sphere.hpp"
#include "utils/gl_vertices.hpp"
#include "utils/camera.hpp"


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

    Utils::Sphere sphere(10, 10, 1);
    sphere.init();
    sphere.print_attr();

    Utils::GLVertices glVertices;
    glVertices.set_vertex_data(sphere.points_coordinate(), sphere.vertices_size());
    glVertices.set_indices(sphere.indices(), sphere.indices_size());

    Utils::Camera camera;
    Utils::Shader shader(vertex_src_path, fragment_src_path);
    shader.Use();
    shader.setMat4f("projection_mat", camera.projection_mat());
    shader.setMat4f("mv_mat", camera.view_mat());
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, sphere.triangle_vertices_num(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
