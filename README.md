# Anima

This project is an application of the concepts and code presented in Gabor Szauer's [Hands-On C++ Game Animation Programming](https://animationprogramming.com).
It supports **loading a [glTF](https://www.khronos.org/Gltf) model and rendering blended skinned animations**, with the skinning logic being run on the GPU or on the CPU depending
on the configuration. It is written in C++, with OpenGL being used for rendering and [glfw](https://www.glfw.org/) for the window context.

![anima](https://github.com/user-attachments/assets/b6eeb8b1-5818-4e72-8c25-32a02670819e)

## Dependencies
- STB ([source](https://github.com/nothings/stb), [license](https://github.com/nothings/stb?tab=License-1-ov-file#readme))
- Tracy ([source](https://github.com/wolfpld/tracy), [license](https://github.com/wolfpld/tracy?tab=License-1-ov-file#readme))
- glad ([source](https://github.com/Dav1dde/glad), [license](https://github.com/Dav1dde/glad?tab=License-1-ov-file#readme))
- cgltf ([source](https://github.com/jkuhlmann/cgltf), [license](https://github.com/jkuhlmann/cgltf?tab=MIT-1-ov-file#readme))
- glfw ([source](https://github.com/glfw/glfw), [license](https://github.com/glfw/glfw?tab=Zlib-1-ov-file#readme))
- dear Imgui ([source](https://github.com/ocornut/imgui), [license](https://github.com/ocornut/imgui?tab=MIT-1-ov-file#readme))
- 3D model and animations from [mixamo.com](https://www.mixamo.com) - Terms of use [here](https://www.adobe.com/legal/terms.html)
