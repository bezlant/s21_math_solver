#define GL_SILENCE_DEPRECATION
#include "includes/calc.h"
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
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Default state
    bool show_demo_window = true;
    bool show_credit_window = true;
    bool show_deposit_window = true;
    bool show_plot_window = false;
    bool show_plot_demo_window = false;

    ImVec4 clear_color = ImVec4(0.0, 0.376, 0.564, 1.00f);

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

        if (show_plot_demo_window)
            ImPlot::ShowDemoWindow(&show_plot_demo_window);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            // Create a window
            ImGui::Begin("Main Menu");

            ImGui::Text("Please choose available options: ");
            ImGui::Checkbox("Gui Demo Window", &show_demo_window);
            ImGui::Checkbox("Plot Demo Window", &show_plot_demo_window);
            ImGui::Checkbox("Credit Calculator", &show_credit_window);
            ImGui::Checkbox("Deposit Calculator", &show_deposit_window);
            ImGui::Checkbox("Plot", &show_plot_window);

            ImGui::ColorEdit3("Background color", (float *)&clear_color);

            ImGui::End();
        }

        if (show_credit_window) {
            ImGui::SetNextWindowSize(ImVec2(269, 187), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(343, 61), ImGuiCond_FirstUseEver);
            ImGui::Begin("Credit Calculator", &show_credit_window);

            ImGui::Text("Loan Amount: ");
            ImGui::SameLine();
            static char loan_amount[64] = "42069.69";
            ImGui::InputText("$USD##loan", loan_amount, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Loan Term: ");
            ImGui::SameLine();
            static char term[64] = "69";
            ImGui::InputText("month(s)", term, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Interest Rate: ");
            ImGui::SameLine();
            static char interest_rate[64] = "4.20";
            ImGui::InputText("%", interest_rate, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            static int credit_type = ANNUITY;

            ImGui::RadioButton("Annuity", &credit_type, ANNUITY);
            ImGui::SameLine();
            ImGui::RadioButton("Differentiated", &credit_type, DIFFERENTIATED);

            char *stopstring = NULL;
            long double ld_term = strtoul(term, &stopstring, 10);
            long double ld_loan_amount =
                fabsl(strtold(loan_amount, &stopstring));
            long double ld_interest_rate =
                fabsl(strtold(interest_rate, &stopstring));
            long double montly = 0;
            long double total_payment = 0;

            if (credit_type == ANNUITY) {
                montly = annuity_get_montly(ld_interest_rate, ld_term,
                                            ld_loan_amount);
                total_payment = annuity_get_total(montly, ld_term);
            } else {
                total_payment = differentiated_get_total(
                    ld_loan_amount, ld_term, ld_interest_rate);
                montly = differentiated_get_montly(total_payment, ld_term);
            }

            long double total_interest =
                get_overpayment(total_payment, ld_loan_amount);

            ImGui::Text("Payment Every Month = %.2Lf", montly);
            ImGui::Text("Total Interest = %.2Lf", total_interest);
            ImGui::Text("Total Payment = %.2Lf", total_payment);

            ImGui::End();
        }

        if (show_deposit_window) {
            ImGui::SetNextWindowSize(ImVec2(573, 253), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(45, 317), ImGuiCond_FirstUseEver);
            ImGui::Begin("Deposit Calculator", &show_deposit_window);

            static int periodicity = MONTHLY;

            ImGui::Text("Initial Deposit: ");
            ImGui::SameLine();
            static char initial_deposit[64] = "69420.0";
            ImGui::InputText("$USD##init_deposit", initial_deposit, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Deposit Term: ");
            ImGui::SameLine();
            static char term[64] = "69";
            ImGui::InputText(periodicity == MONTHLY ? "month(s)" : "year(s)",
                             term, 64, ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Interest Rate: ");
            ImGui::SameLine();
            static char interest_rate[64] = "6.9";
            ImGui::InputText("%##Interest", interest_rate, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Tax Rate: ");
            ImGui::SameLine();
            static char tax_rate[64] = "0";
            ImGui::InputText("%##Tax", tax_rate, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Payout/Capitalization rate: ");
            ImGui::SameLine();
            ImGui::RadioButton("Montly", &periodicity, MONTHLY);
            ImGui::SameLine();
            ImGui::RadioButton("Yearly", &periodicity, YEARLY);

            static bool capitalized = false;

            ImGui::SameLine();
            ImGui::Checkbox("Capitalize Interest", &capitalized);

            ImGui::Text("Replenish Monthly: ");
            ImGui::SameLine();
            static char replenish_amount[64] = "0";
            ImGui::InputText("$USD##replenish", replenish_amount, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            ImGui::Text("Withdraw Monthly: ");
            ImGui::SameLine();
            static char withdrawal_amount[64] = "0";
            ImGui::InputText("$USD##withdraw", withdrawal_amount, 64,
                             ImGuiInputTextFlags_CharsDecimal);

            char *stopstring = NULL;
            long double ld_term = strtoul(term, &stopstring, 10);
            long double ld_initial_deposit =
                strtold(initial_deposit, &stopstring);
            long double ld_interest_rate = strtold(interest_rate, &stopstring);
            long double ld_tax_rate = strtold(tax_rate, &stopstring);
            long double ld_replenish_amount =
                strtold(replenish_amount, &stopstring);
            long double ld_withdrawal_amount =
                strtold(withdrawal_amount, &stopstring);

            long double earnings = get_earnings(
                &ld_initial_deposit, ld_term, ld_interest_rate, capitalized,
                periodicity, ld_replenish_amount, ld_withdrawal_amount);
            long double taxes = get_tax(earnings, ld_tax_rate);
            long double overall =
                get_overall(ld_initial_deposit, earnings) - taxes;

            ImGui::Text("Earnings = %.2Lf", earnings);
            ImGui::Text("Taxes = %.2Lf", taxes);
            ImGui::Text("Overall = %.2Lf", overall);
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
