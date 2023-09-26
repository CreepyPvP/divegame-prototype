#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct DivegameWindow {
    int width;
    int height;
    GLFWwindow* handle;

    void init();
    void setResizeCallback(GLFWframebuffersizefun cb);
    bool shouldClose();
};
