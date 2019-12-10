#pragma once

#include <aires/graphics/object.hpp>
#include <aires/graphics/texture.hpp>
#include <aires/graphics/shader.hpp>
#include <aires/graphics/window.hpp>
#include <functional>
#include <string>

namespace Aires {
	namespace Graphics {
		class GraphicsAPI {
			public:
				GraphicsAPI(Window* win);

				virtual ShaderProgram* createShaderProgram() = 0;
				virtual ShaderProgram* createShaderProgram(std::string vert, std::string frag, bool compiled=false) = 0;
				ShaderProgram* createShaderProgram(const char* vert, const char* frag, bool compiled=false);

				virtual Texture* createTexture(uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB) = 0;
				Texture* createTexture(uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB);

				virtual GraphicsObject* createObject(glm::vec3 pos) = 0;
				GraphicsObject* createObject();

				virtual void render(std::function<void()> cb) = 0;
			protected:
				Window* win;
		};
	};
};
