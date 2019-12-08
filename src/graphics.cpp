#include <aires/config.h>
#include <aires/graphics.hpp>
#include <stdexcept>

/** APIs **/
#ifdef AIRES_API_GL3
#include <aires/graphics/apis/gl3.hpp>
#endif

/** Backends **/
#ifdef AIRES_BACKEND_GLFW
#include <aires/graphics/backends/glfw.hpp>
#endif

using namespace Aires::Graphics::APIs;
using namespace Aires::Graphics::Backends;
using namespace Aires;

Graphics::GraphicsBackend* Graphics::createBackend() {
#ifdef AIRES_BACKEND_GLFW
	return new GLFWBackend();
#else
	throw std::runtime_error("No backends were enabled for graphics");
#endif
}

Graphics::GraphicsBackend* Graphics::createBackend(std::string name) {
	if (name == "glfw") {
#ifdef AIRES_BACKEND_GLFW
		return new GLFWBackend();
#else
		throw std::runtime_error("GLFW backend is disabled therefore it cannot be used");
#endif
	}
	throw std::runtime_error("No backend was found for " + name);
}

Graphics::GraphicsAPI* Graphics::createGraphicsAPI(Window* win) {
#ifdef AIRES_API_GL3
	return new GL3GraphicsAPI(win);
#else
	throw std::runtime_error("No APIs were enabled for graphics");
#endif
}
