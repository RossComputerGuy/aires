#include <aires/graphics/backends/glfw.hpp>
#include <cstring>
#include <stdexcept>

/** Window **/
using namespace Aires::Graphics::Windows;

GLFWWindow::GLFWWindow(Aires::Graphics::Backends::GLFWBackend* backend, uint32_t width, uint32_t height, const char* title) : Window(backend, width, height, title) {
	if ((this->_win = glfwCreateWindow(width, height, title, NULL, NULL)) == NULL) {
		const char* error_msg = "";
		glfwGetError(&error_msg);
		throw std::runtime_error(std::string("Failed to create GLFW window: ") + error_msg);
	}
	this->title = (char*)title;
	glfwMakeContextCurrent(this->_win);
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(this->_win);
}

bool GLFWWindow::isClosed() {
	return !glfwWindowShouldClose(this->_win);
}

void GLFWWindow::setTitle(const char* string) {
	this->title = (char*)string;
	glfwSetWindowTitle(this->_win, title);
}

char* GLFWWindow::getTitle() {
	return this->title;
}

uint32_t GLFWWindow::getXPosition() {
	int pos;
	glfwGetWindowPos(this->_win, &pos, NULL);
	return pos;
}

uint32_t GLFWWindow::getYPosition() {
	int pos;
	glfwGetWindowPos(this->_win, NULL, &pos);
	return pos;
}

void GLFWWindow::setPosition(uint32_t x, uint32_t y) {
	glfwSetWindowPos(this->_win, x, y);
}

/** Backend **/
using namespace Aires::Graphics;
using namespace Aires::Graphics::Backends;

GLFWBackend::GLFWBackend() {
	if (!glfwInit()) {
		const char* error_msg = "";
		glfwGetError(&error_msg);
		throw std::runtime_error(std::string("Failed to initialize GLFW: ") + error_msg);
	}
}

GLFWBackend::~GLFWBackend() {
	for (auto it = this->windows.begin(); it != this->windows.end(); it++) {
		GLFWWindow* win = *it;
		delete win;
	}
	glfwTerminate();
}

void GLFWBackend::onWindowDestroyed(Window* win) {
	this->windows.remove(reinterpret_cast<GLFWWindow*>(win));
}

Window* GLFWBackend::createWindow(uint32_t width, uint32_t height, const char* title) {
	GLFWWindow* win = new GLFWWindow(this, width, height, title);
	win->onDestroy.bind(&GLFWBackend::onWindowDestroyed, this);
	this->windows.push_back(win);
	return win;
}

void* GLFWBackend::getAPIFunction(AIRES_GRAPHICS_API api, const char* name) {
	switch (api) {
		case AIRES_GRAPHICS_API_GL3: return (void*)glfwGetProcAddress(name);
		default: throw std::runtime_error("Unsupported graphics API");
	}
	return NULL;
}

bool GLFWBackend::hasAPIExtension(AIRES_GRAPHICS_API api, const char* name) {
	switch (api) {
		case AIRES_GRAPHICS_API_GL3: return glfwExtensionSupported(name) == GLFW_TRUE;
		default: throw std::runtime_error("Unsupported graphics API");
	}
	return false;
}
