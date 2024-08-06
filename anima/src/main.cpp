#include <iostream>

#include "lifecycle/OpenGLApp.h"
#include "lifecycle/VulkanApp.h"
#include "util/Globals.h"

int main(int argc, char* argv[])
{
    // Select graphics API
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        // Check for specific flags
        if (arg == "-v" || arg == "--vulkan")
        {
            Globals::graphicsApi = Vulkan;
        }
        else
        {
            std::cerr << "Error: Unknown flag or option: " << arg << std::endl;
            return 1;  // Return error code
        }
    }

    try
    {
        if (Globals::graphicsApi == OpenGL)
        {
            std::cout << "Using OpenGL" << std::endl;
            OpenGLApp app;
            app.run();
        }
        else if (Globals::graphicsApi == Vulkan)
        {
            std::cout << "Using Vulkan" << std::endl;
            VulkanApp app;
            app.run();
        }
        else
        {
			std::cout << "Unsupported graphics API" << std::endl;
			return EXIT_FAILURE;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
