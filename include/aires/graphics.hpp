#pragma once

#include <aires/graphics/api.hpp>
#include <aires/graphics/backend.hpp>
#include <aires/graphics/camera.hpp>
#include <aires/graphics/color.hpp>
#include <aires/graphics/object.hpp>
#include <aires/graphics/texture.hpp>
#include <aires/graphics/shader.hpp>
#include <aires/graphics/window.hpp>
#include <aires/graphics/vertex.hpp>
#include <string>

namespace Aires {
	namespace Graphics {
		GraphicsBackend* createBackend();
		GraphicsBackend* createBackend(std::string name);
		GraphicsAPI* createGraphicsAPI(Window* win);
	};
};
