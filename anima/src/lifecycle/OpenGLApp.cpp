#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../profiling/tracy/Tracy.hpp"
#include "../render/glad/glad.h"
#include "../game/Sample.h"
#include "OpenGLApp.h"

Game* gGame = 0;
GLuint gVertexArrayObject = 0;

void OpenGLApp::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(800, 600, "anima", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void OpenGLApp::initApi()
{
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);
}

void OpenGLApp::mainLoop()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    gGame = new Sample();
    gGame->Initialize();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (gGame != 0)
        {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glPointSize(5.0f);
            glBindVertexArray(gVertexArrayObject);
            glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            gGame->ImGUI();
            gGame->Update(deltaTime);
            gGame->Render((float)width / (float)height);
        }

        FrameMark;
    }
}

void OpenGLApp::cleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &gVertexArrayObject);
    gVertexArrayObject = 0;
    glfwDestroyWindow(window);
    glfwTerminate();
    return;
}

void OpenGLApp::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLApp::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}