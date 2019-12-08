#pragma once

#include <aires/graphics/shader.hpp>
#include <aires/graphics/window.hpp>
#include <string>

typedef enum {
	AIRES_GRAPHICS_API_GL3 = 1
} AIRES_GRAPHICS_API;

namespace Aires {
	namespace Graphics {
		class GraphicsAPI {
			public:
				GraphicsAPI(Window* win);

				virtual ShaderProgram* createShaderProgram() = 0;
				virtual ShaderProgram* createShaderProgram(std::string vert, std::string frag, bool compiled=false) = 0;
				ShaderProgram* createShaderProgram(const char* vert, const char* frag, bool compiled=false);
			protected:
				Window* win;
		};
	};
};
