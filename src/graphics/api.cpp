#include <aires/graphics/api.hpp>

using namespace Aires::Graphics;

GraphicsAPI::GraphicsAPI(Window* win) {
	this->win = win;
}

ShaderProgram* GraphicsAPI::createShaderProgram(const char* vert, const char* frag, bool compiled) {
	return this->createShaderProgram(std::string(vert), std::string(frag), compiled);
}

Texture* GraphicsAPI::createTexture(uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format) {
	return this->createTexture(width, height, 0, format);
}

GraphicsObject* GraphicsAPI::createObject() {
	return this->createObject(glm::vec3(0.0f, 0.0f, 0.0f));
}