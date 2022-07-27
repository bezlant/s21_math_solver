#include <GLFW/glfw3.h>
#include <stdio.h>

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(void) {
    GLFWwindow *window;
    /* Get human-readable error outputs */
    glfwSetErrorCallback(glfw_error_callback);

    /* Initialize the library */
    if (!glfwInit()) {
        glfwTerminate();
        return -1;
    }

    /* Create a windowed mode window and it's OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello, Dear ImGui!", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap fron and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
