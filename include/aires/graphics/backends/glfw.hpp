#pragma once

#include <aires/graphics/backend.hpp>
#include <GLFW/glfw3.h>
#include <list>

namespace Aires {
	namespace Graphics {
		namespace Backends { class GLFWBackend; };
		namespace Windows {
			class GLFWWindow : public Window {
				public:
					GLFWWindow(Aires::Graphics::Backends::GLFWBackend* backend, uint32_t width, uint32_t height, const char* title);
					~GLFWWindow();

					bool isClosed();

					void setTitle(const char* string);
					char* getTitle();

					uint32_t getXPosition();
					uint32_t getYPosition();

					void setPosition(uint32_t x, uint32_t y);	
				private:
					GLFWwindow* _win;
					char* title;
			};
		};
		namespace Backends {
			class GLFWBackend : public GraphicsBackend {
				public:
					GLFWBackend();
					~GLFWBackend();

					Window* createWindow(uint32_t width, uint32_t height, const char* title);
					
					void* getAPIFunction(AIRES_GRAPHICS_API api, const char* name);
					bool hasAPIExtension(AIRES_GRAPHICS_API api, const char* name);
				private:
					std::list<Aires::Graphics::Windows::GLFWWindow*> windows;

					void onWindowDestroyed(Window* win);
			};
		};
	};
};
