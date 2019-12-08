#include <aires/graphics/shader.hpp>

using namespace Aires::Graphics;

ShaderProgram::ShaderProgram(GraphicsBackend* backend) {
	this->backend = backend;
}

ShaderProgram::ShaderProgram(GraphicsBackend* backend, const char* vert, const char* frag) : ShaderProgram(backend) {}
