#pragma once

#include <cstdbool>
#include <functional>
#include <signal.h>
#include <stdint.h>

namespace Aires {
	namespace Graphics {
		class GraphicsBackend;
		class Window {
			public:
				Window(GraphicsBackend* backend, uint32_t width, uint32_t height, const char* title);
				~Window();

				Signal<Window*> onDestroy;

				GraphicsBackend* getGraphicsBackend();

				virtual bool isClosed() = 0;

				virtual void setTitle(const char* string) = 0;
				virtual char* getTitle() = 0;

				virtual uint32_t getXPosition() = 0;
				virtual uint32_t getYPosition() = 0;

				virtual void setPosition(uint32_t x, uint32_t y) = 0;

				virtual void render(std::function<void()> cb) = 0;
			protected:
				GraphicsBackend* backend;
		};
	};
};
