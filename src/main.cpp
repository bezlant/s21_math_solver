#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <math.h>
#include <stdio.h>

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(void) {
    /* Get human-readable error outputs */
    glfwSetErrorCallback(glfw_error_callback);

    /* Initialize the library */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // GL 3.2 + GLSL 150
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac

    /* Create a windowed mode window and it's OpenGL context */
    GLFWwindow *window =
        glfwCreateWindow(1280, 720, "Hello, Dear ImGui!", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    // Keyboard controls
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Colorscheme
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Default state
    bool show_demo_window = true;
    bool show_another_window = false;
    bool show_plot_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float x_plot[180] = {0};
    float y_plot[180] = {0};

    int j = 0;
    for (float i = -M_PI; j < 180 && i <= M_PI; i += M_PI / 180, j++) {
        x_plot[j] = i;
        y_plot[j] = sin(x_plot[j]);
    }

    while (!glfwWindowShouldClose(window)) {
        /* Poll for and process events */
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            static float f = 0.0f;
            static int counter = 0;

            // Create a window
            ImGui::Begin("Hello, World!");

            ImGui::Text("This text is so useful!");
            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::Checkbox("Another Window", &show_another_window);
            ImGui::Checkbox("Plot Window", &show_plot_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float *)&clear_color);

            if (ImGui::Button("Button"))
                counter++;

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (show_another_window) {
            ImGui::Begin("Another window", &show_another_window);
            ImGui::Text("Hello from Another Window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;

            ImGui::End();
        }

        if (show_plot_window) {
            ImGui::Begin("Plot window", &show_plot_window);
            if (ImPlot::BeginPlot("My plot")) {
                ImPlot::PlotLine("My Line Plot", x_plot, y_plot, 180);
                ImPlot::EndPlot();
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w,
                     clear_color.y * clear_color.w,
                     clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
