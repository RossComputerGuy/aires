#pragma once

#include <aires/graphics/api.hpp>
#include <aires/graphics/window.hpp>
#include <cstdbool>
#include <signal.h>

namespace Aires {
	namespace Graphics {
		class GraphicsBackend : public SigSlotBase {
			public:
				GraphicsBackend();

				virtual Window* createWindow(uint32_t width, uint32_t height, const char* title) = 0;

				virtual void* getAPIFunction(AIRES_GRAPHICS_API api, const char* name) = 0;
				virtual bool hasAPIExtension(AIRES_GRAPHICS_API api, const char* name) = 0;
		};
	};
};
