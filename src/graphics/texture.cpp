#include <aires/graphics/texture.hpp>

using namespace Aires::Graphics;

Texture::Texture(GraphicsBackend* backend, uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format) : Texture(backend, width, height, 0, format) {}

Texture::Texture(GraphicsBackend* backend, uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format) {
	this->backend = backend;
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->format = format;
}

uint32_t Texture::getWidth() {
	return this->width;
}

uint32_t Texture::getHeight() {
	return this->height;
}

uint8_t Texture::getDepth() {
	return this->depth;
}

AIRES_COLOR_FORMAT Texture::getColorFormat() {
	return this->format;
}
