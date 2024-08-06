enum GraphicsApi
{
	OpenGL,
	Vulkan
};

class Globals
{
public:
	static GraphicsApi graphicsApi;
};

GraphicsApi Globals::graphicsApi = OpenGL;