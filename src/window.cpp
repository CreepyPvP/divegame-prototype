#include "window.hpp"
#include "GLFW/glfw3.h"

#include <stdio.h>

void DivegameWindow::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    width = 1280;
    height = 720;
    handle = glfwCreateWindow(width, height, "Divegame", NULL, NULL);
    if (!handle) {
        printf("Failed to create window\n");
    }
    glfwMakeContextCurrent(handle);
}

void DivegameWindow::setResizeCallback(GLFWframebuffersizefun cb) {
    glfwSetFramebufferSizeCallback(handle, cb);
}

bool DivegameWindow::shouldClose() {
    return glfwWindowShouldClose(handle);
}
