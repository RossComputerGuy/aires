#include <aires/graphics/api.hpp>

using namespace Aires::Graphics;

GraphicsAPI::GraphicsAPI(Window* win) {
	this->win = win;
}

ShaderProgram* GraphicsAPI::createShaderProgram(const char* vert, const char* frag, bool compiled) {
	return this->createShaderProgram(std::string(vert), std::string(frag), compiled);
}
