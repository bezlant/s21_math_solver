#define GL_SILENCE_DEPRECATION
#include "includes/main.h"

#define MAX 420420
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
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Math Solver", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImPlot::CreateContext();

    // Keyboard controls
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Colorscheme
    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Default states start
    // bool show_demo_window = false;
    bool show_credit_window = true;
    bool show_deposit_window = true;
    bool show_calc_window = true;

    ImVec4 clear_color = ImVec4(0.0, 0.376, 0.564, 1.00f);

    ImPlotStyle &plot_style = ImPlot::GetStyle();
    plot_style.PlotDefaultSize = ImVec2(317, 419);

    const float TEXT_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    struct Tokens *tok = {0};
    struct Tokens *rpn = {0};
    static float x_plot[MAX + 1] = {0};
    static float y_plot[MAX + 1] = {0};
    // Default states end

    while (!glfwWindowShouldClose(window)) {
        /* Poll for and process events */
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            // Main Menu
            ImGuiStyle &style = ImGui::GetStyle();
            style.FrameBorderSize = 1.0f;
            static ImGuiStyle ref_saved_style;
            ImGui::SetNextWindowPos(ImVec2(21, 19), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(418, 182), ImGuiCond_FirstUseEver);
            ImGui::Begin("Main Menu");

            ImGui::Text("Please choose available options: ");
            ImGui::Checkbox("Math Expression Evaluator", &show_calc_window);
            ImGui::Checkbox("Credit Calculator", &show_credit_window);
            ImGui::Checkbox("Deposit Calculator", &show_deposit_window);
            if (ImGui::ShowStyleSelector("Colorscheme##Selector"))
                ref_saved_style = style;
            ImGui::ColorEdit3("Background Color", (float *)&clear_color);

            ImGui::End();
        }

        if (show_credit_window)
            show_credit_calc(show_credit_window);

        if (show_deposit_window)
            show_deposit_calc(show_deposit_window);

        if (show_calc_window) {
            ImGui::SetNextWindowPos(ImVec2(599, 17), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(655, 681), ImGuiCond_FirstUseEver);
            ImGui::Begin("Math Solver", &show_calc_window);

            ImGui::Text("Expression: ");
            ImGui::SameLine();
            static char expression[256] = "sin(cos(x))";
            ImGui::InputText("##ExpressionInput", expression, 256);

            ImGui::SameLine();

            static int eval_clicked = 0;
            if (ImGui::Button("Evaluate!"))
                eval_clicked++;

            bool valid = is_valid(expression);

            if (eval_clicked && valid) {
                tok = tokenize(expression);
                if (!tok)
                    valid = false;
                if (valid) {
                    valid = brackets_ok(tok);
                }
                if (valid) {
                    valid = operators_ok(tok);
                }
                if (valid) {
                    valid = numbers_ok(tok);
                }
                if (valid) {
                    valid = functions_ok(tok);
                }
            }

            if (eval_clicked && valid) {

                rpn = convert_to_rpn(tok);
                if (!rpn)
                    valid = false;
            }

            if (eval_clicked && valid) {
                size_t j = 0;
                for (long double i = -1000; i <= 1000;
                     i += 2000.0L / MAX, j++) {
                    x_plot[j] = i;
                    y_plot[j] = calculate(rpn, x_plot[j]);
                }

                eval_clicked = 0;
            } else if (!valid) {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
                                   "Error occured please try again!");
            }

            if (ImPlot::BeginPlot("Graph", ImVec2(-1, 0),
                                  ImPlotFlags_NoTitle)) {
                static float constraints[4] = {-100, 100, 1, 200};
                ImPlot::SetupAxesLimits(-10, 10, -10, 10);
                ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, constraints[0],
                                                   constraints[1]);
                ImPlot::SetupAxisZoomConstraints(ImAxis_X1, constraints[2],
                                                 constraints[3]);
                ImPlot::SetupAxisLimitsConstraints(ImAxis_Y1, constraints[0],
                                                   constraints[1]);
                ImPlot::SetupAxisZoomConstraints(ImAxis_Y1, constraints[2],
                                                 constraints[3]);
                ImPlot::PlotLine("##Plot", x_plot, y_plot, MAX + 1);
                ImPlot::EndPlot();
            }

            draw_help_table(TEXT_HEIGHT);

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

void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void show_credit_calc(bool &show_credit_window) {
    ImGui::SetNextWindowPos(ImVec2(21, 231), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(490, 179), ImGuiCond_FirstUseEver);
    ImGui::Begin("Credit Calculator", &show_credit_window);

    ImGui::Text("Loan Amount: ");
    ImGui::SameLine();
    static char loan_amount[64] = "42069.69";
    ImGui::InputText("$USD##loan", loan_amount, 64,
                     ImGuiInputTextFlags_CharsDecimal);

    ImGui::Text("Loan Term: ");
    ImGui::SameLine();
    static char term[64] = "69";
    ImGui::InputText("month(s)", term, 64, ImGuiInputTextFlags_CharsDecimal);

    ImGui::Text("Interest Rate: ");
    ImGui::SameLine();
    static char interest_rate[64] = "4.20";
    ImGui::InputText("%", interest_rate, 64, ImGuiInputTextFlags_CharsDecimal);

    static int credit_type = ANNUITY;

    ImGui::RadioButton("Annuity", &credit_type, ANNUITY);
    ImGui::SameLine();
    ImGui::RadioButton("Differentiated", &credit_type, DIFFERENTIATED);

    char *stopstring = NULL;
    long double ld_term = strtoul(term, &stopstring, 10);
    long double ld_loan_amount = fabsl(strtold(loan_amount, &stopstring));
    long double ld_interest_rate = fabsl(strtold(interest_rate, &stopstring));
    long double montly = 0;
    long double total_payment = 0;

    if (credit_type == ANNUITY) {
        montly = annuity_get_montly(ld_interest_rate, ld_term, ld_loan_amount);
        total_payment = annuity_get_total(montly, ld_term);
    } else {
        total_payment =
            differentiated_get_total(ld_loan_amount, ld_term, ld_interest_rate);
        montly = differentiated_get_montly(total_payment, ld_term);
    }

    long double total_interest = get_overpayment(total_payment, ld_loan_amount);

    ImGui::Text("Payment Every Month = %.2Lf", montly);
    ImGui::Text("Total Interest = %.2Lf", total_interest);
    ImGui::Text("Total Payment = %.2Lf", total_payment);

    ImGui::End();
}

void show_deposit_calc(bool &show_deposit_window) {
    ImGui::SetNextWindowPos(ImVec2(21, 445), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(573, 253), ImGuiCond_FirstUseEver);
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
    ImGui::InputText(periodicity == MONTHLY ? "month(s)" : "year(s)", term, 64,
                     ImGuiInputTextFlags_CharsDecimal);

    ImGui::Text("Interest Rate: ");
    ImGui::SameLine();
    static char interest_rate[64] = "6.9";
    ImGui::InputText("%##Interest", interest_rate, 64,
                     ImGuiInputTextFlags_CharsDecimal);

    ImGui::Text("Tax Rate: ");
    ImGui::SameLine();
    static char tax_rate[64] = "0";
    ImGui::InputText("%##Tax", tax_rate, 64, ImGuiInputTextFlags_CharsDecimal);

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
    long double ld_initial_deposit = strtold(initial_deposit, &stopstring);
    long double ld_interest_rate = strtold(interest_rate, &stopstring);
    long double ld_tax_rate = strtold(tax_rate, &stopstring);
    long double ld_replenish_amount = strtold(replenish_amount, &stopstring);
    long double ld_withdrawal_amount = strtold(withdrawal_amount, &stopstring);

    long double earnings = get_earnings(
        &ld_initial_deposit, ld_term, ld_interest_rate, capitalized,
        periodicity, ld_replenish_amount, ld_withdrawal_amount);
    long double taxes = get_tax(earnings, ld_tax_rate);
    long double overall = get_overall(ld_initial_deposit, earnings) - taxes;

    ImGui::Text("Earnings = %.2Lf", earnings);
    ImGui::Text("Taxes = %.2Lf", taxes);
    ImGui::Text("Overall = %.2Lf", overall);
    ImGui::End();
}

void draw_help_table(float height) {
    if (ImGui::BeginTable("Main_table", 2,
                          ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable |
                              ImGuiTableFlags_Reorderable |
                              ImGuiTableFlags_Hideable)) {
        ImGui::TableSetupColumn("Functions");
        ImGui::TableSetupColumn("Arithmetic Operators");
        ImGui::TableHeadersRow();

        ImGui::TableNextColumn();
        {
            float rows_height = height * 2;
            if (ImGui::BeginTable("Functions", 2,
                                  ImGuiTableFlags_Borders |
                                      ImGuiTableFlags_Resizable |
                                      ImGuiTableFlags_Reorderable |
                                      ImGuiTableFlags_Hideable)) {
                ImGui::TableSetupColumn("Description");
                ImGui::TableSetupColumn("Function");
                ImGui::TableHeadersRow();

                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Cosine");
                ImGui::TableNextColumn();
                ImGui::Text("cos(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Sine");
                ImGui::TableNextColumn();
                ImGui::Text("sin(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Tangent");
                ImGui::TableNextColumn();
                ImGui::Text("tan(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Arc cosine");
                ImGui::TableNextColumn();
                ImGui::Text("acos(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Arc sine");
                ImGui::TableNextColumn();
                ImGui::Text("asin(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Arc tangent");
                ImGui::TableNextColumn();
                ImGui::Text("atan(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Square root");
                ImGui::TableNextColumn();
                ImGui::Text("sqrt(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Natural logarithm");
                ImGui::TableNextColumn();
                ImGui::Text("ln(x)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Common logarithm");
                ImGui::TableNextColumn();
                ImGui::Text("log(x)");

                ImGui::EndTable();
            }
        }
        ImGui::TableNextColumn();
        {
            float rows_height = height * 2;
            if (ImGui::BeginTable("Arithmetic_operators", 2,
                                  ImGuiTableFlags_Borders |
                                      ImGuiTableFlags_Resizable |
                                      ImGuiTableFlags_Reorderable |
                                      ImGuiTableFlags_Hideable)) {
                ImGui::TableSetupColumn("Operator");
                ImGui::TableSetupColumn("Example");
                ImGui::TableHeadersRow();

                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Brackets");
                ImGui::TableNextColumn();
                ImGui::Text("(a + b)");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Addition");
                ImGui::TableNextColumn();
                ImGui::Text("a + b");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Subtraction");
                ImGui::TableNextColumn();
                ImGui::Text("a - b");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Multiplication");
                ImGui::TableNextColumn();
                ImGui::Text("a * b");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Division");
                ImGui::TableNextColumn();
                ImGui::Text("a / b");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Power");
                ImGui::TableNextColumn();
                ImGui::Text("a ^ b");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Modulus");
                ImGui::TableNextColumn();
                ImGui::Text("a %% b");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Unary plus");
                ImGui::TableNextColumn();
                ImGui::Text("+a");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                ImGui::TableNextColumn();
                ImGui::Text("Unary minus");
                ImGui::TableNextColumn();
                ImGui::Text("-a");

                ImGui::EndTable();
            }
        }
        ImGui::EndTable();
    }
}
