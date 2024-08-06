#pragma once

#define GLFW_INCLUDE_VULKAN
#include "../glfw/glfw3.h"

class Application
{
public:
    void run()
    {
        initWindow();
        initApi();
        mainLoop();
        cleanUp();
    }

    virtual void initWindow() = 0;
    virtual void initApi() = 0;
    virtual void mainLoop() = 0;
    virtual void cleanUp() = 0;
};
