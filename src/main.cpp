#include <X11/X.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "platform.hpp"
#include "window.hpp"
#include "shader.hpp"

static DivegameWindow globalWindow;

int main() {
    globalWindow.init();

    while(!globalWindow.shouldClose()) {

        glfwSwapBuffers(globalWindow.handle);
        glfwPollEvents();
    }

    glfwTerminate();
}
