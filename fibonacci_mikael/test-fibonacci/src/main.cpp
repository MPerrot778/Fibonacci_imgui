//// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
//// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
//// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
#include "fibonacci.h"
#include "fibDraw.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>


//
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);


    // Our state
    static int values[2];
    static float scale_value = 1;
    static bool sim_start = false;
    int temp = 0;
    int counter = 0;

    char input1[] = "##input1";
    char input2[] = "##input2";
    char input3[] = "##input3";
    char file_name[15] = "myFile";
    std::ifstream in_file;

    bool values_checkbox = false;
    bool save_data = false;
    bool load_data = false;
    bool disp_all = false;
    bool disp_only_showed = false;
    bool disp_spirals = false;
    bool disp_squares = false;

    std::vector<double> buffer(2);

    fibonacci fib_serie = fibonacci(buffer);

    ImVec2 fibWin_size = ImVec2(500.0,300.0);
    ImVec2 fibWin_pos = ImVec2(0.0,0.0);
    ImVec2 simWin_size = ImVec2(800.0, 1000.0);
    ImVec2 simWin_pos = ImVec2(500.0, 0.0);
    ImVec2 initial_spiral_pos = ImVec2(900.0, 500.0);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop

    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        // main window
        ImGui::SetNextWindowPos(fibWin_pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(fibWin_size, ImGuiCond_Once);
        ImGui::Begin("Fibonnaci");   
        if (!sim_start) {
            if (!load_data) {

                // Data Input
                ImGui::Text("Fibonacci serie parameters: ");
                ImGui::Checkbox("Same Value for both", &values_checkbox);
                ImGui::Text("Size of the serie :");
                ImGui::InputInt(input1, &values[0]);
                if (values_checkbox) {
                    values[1] = values[0];
                }
                ImGui::Text("Number of spiral to display :");
                ImGui::Text("(must be smaller of equal to the size)");
                ImGui::InputInt(input2, &values[1], 1);

                // Verify if both values are over 0
                if (values[0] < 0 || values[1] < 0) {
                    values[0] = 0;
                    values[1] = 0;
                }

                // Give the same value to both inputs, if values[1] is greater than values[0]
                if (values[1] > values[0]) {
                    values[1] = values[0];
                }

                // If condition are respected, "Run simulation" appear
                if (values[0] > 0 && values[1] > 0) {
                    if (ImGui::Button("Run simulation")) {
                        sim_start = true;
                        buffer = fib_serie.createFib(values[0], values[1]);
                    }
                }

                // Let the user load data (doesn<t work yet)
                if (ImGui::Button("Load data")) {
                    load_data = true;
                }
            }

            else {
                // Doesn't work, but i'll do something like that if it wasworking

                //if (ImGui::InputText("File name", file_name, sizeof(file_name), ImGuiInputTextFlags_EnterReturnsTrue)) {
                    //std::strcat(file_name, ".txt");
                    
                    //in_file.open(file_name);
                    //if (!in_file) {
                    //    std::cout << "Unable to open file";
                    //    load_data = false;
                    //}
                    //while (in_file >> temp) {
                    //    counter++;
                    //}
                    
                    //buffer = fib_serie.createFib(counter);
                    
                    //in_file.close();
                load_data = false;
            }

        }
        else{
            // Stop simulation
            if (ImGui::Button("Stop simulation")) {
                sim_start = false;
            }
            save_data = ImGui::Button("Save Data");

            // Display Fibonacci coeffs
            ImGui::Checkbox("Display all Fibonacci coefficients", &disp_all);
            ImGui::Checkbox("Display only coefficients showed in the simulation", &disp_only_showed);
            ImGui::Checkbox("Display Fibonacci spirals", &disp_spirals);
            ImGui::Checkbox("Display Fibonnaci squares", &disp_squares);
            ImGui::Text("Zoom");
            ImGui::DragFloat("##zoom", &scale_value,0.1,0.01,25.0);
            ImGui::SameLine();
            ImGui::Text("(%d (%))", (int)(scale_value * 100.0));
            if (disp_all || (disp_all && disp_only_showed)) {
                fib_serie.listAll();
            }
            else if (disp_only_showed) {
                fib_serie.listOnlyShowed();
            }
        }
        ImGui::End();

        // simulation window
        ImGui::SetNextWindowPos(simWin_pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(simWin_size, ImGuiCond_Appearing);
        ImGui::Begin("Simulation");
        
        if (sim_start) {
            ImDrawList* list = ImGui::GetWindowDrawList();
            fibDraw fib_draw = fibDraw(list);
            if(disp_spirals)
                fib_draw.drawFibSpiral(values[1], buffer, initial_spiral_pos,scale_value);
            if(disp_squares)
                fib_draw.drawfibSquare(values[1], buffer, initial_spiral_pos,scale_value);
        }
        ImGui::End();

        // Would do that if it worked....
        if (save_data) {
            //std::ofstream data_file(file_name);
            //if (data_file.is_open()) {
            //    for (int i = 0; i <= values[0]; i++) {
            //        data_file << (int)buffer[i] << std::endl;
            //    }
            //    data_file.flush();
            //    data_file.close();
            //    std::cout << buffer[i] << std::endl;
            //}
            //else {
            //    std::cout << "failed opening file" << std::endl;
            //}
            save_data = false;
        }



        // Rendering
        ImGui::Render();
        
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


