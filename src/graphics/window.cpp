#include <aires/graphics/window.hpp>

using namespace Aires::Graphics;

Window::Window(GraphicsBackend* backend, uint32_t width, uint32_t height, const char* title) {
	this->backend = backend;
}

Window::~Window() {
	this->onDestroy.emit(this);
}

GraphicsBackend* Window::getGraphicsBackend() {
	return this->backend;
}
