#include <aires/graphics/apis/gl3.hpp>
#include <aires/graphics/backend.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstring>
#include <stdexcept>

/** Texture **/
using namespace Aires::Graphics::Textures;

GL3Texture::GL3Texture(GraphicsBackend* backend, uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format) : GL3Texture(backend, width, height, 0, format) {}

GL3Texture::GL3Texture(GraphicsBackend* backend, uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format) : Texture(backend, width, height, depth, format) {
	_glGenTextures genTextures = (_glGenTextures)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGenTextures");
	_glBindTexture bindTexture = (_glBindTexture)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glBindTexture");

	genTextures(1, &this->id);
	bindTexture(depth == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, this->id);
}

void GL3Texture::upload(float* buffer) {
	_glTexImage2D texImage2D = (_glTexImage2D)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glTexImage2D");
	_glTexImage3D texImage3D = (_glTexImage3D)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glTexImage3D");

	GLenum format = this->getColorFormat() == AIRES_COLOR_RGB ? GL_RGB : GL_RGBA;
	if (this->getDepth() == 0) texImage2D(GL_TEXTURE_2D, 0, format, this->getWidth(), this->getHeight(), 0, format, GL_FLOAT, buffer);
	else texImage3D(GL_TEXTURE_3D, 0, format, this->getWidth(), this->getHeight(), this->getDepth(), 0, format, GL_FLOAT, buffer);
}

/** Shader **/
using namespace Aires::Graphics::Shaders;

GL3ShaderProgram::GL3ShaderProgram(GraphicsBackend* backend) : ShaderProgram(backend) {
	glCreateShader createShader = (glCreateShader)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glCreateShader");
	glCreateProgram createProgram = (glCreateProgram)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glCreateProgram");

	this->shader_vert = createShader(GL_VERTEX_SHADER);
	this->shader_frag = createShader(GL_FRAGMENT_SHADER);
	this->prog = createProgram();
}

GL3ShaderProgram::GL3ShaderProgram(GraphicsBackend* backend, std::string vert, std::string frag, bool compiled) : GL3ShaderProgram(backend) {
	char infoLog[512];
	if (!compiled) {
		glShaderSource shaderSource = (glShaderSource)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glShaderSource");
		glCompileShader compileShader = (glCompileShader)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glCompileShader");
		glGetShaderiv getShaderiv = (glGetShaderiv)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetShaderiv");
		glGetShaderInfoLog getShaderInfoLog = (glGetShaderInfoLog)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetShaderInfoLog");

		int success;

		const char* vertstr = vert.c_str();
		const char* fragstr = frag.c_str();

		shaderSource(this->shader_vert, 1, (const char*)&vertstr, NULL);
		compileShader(this->shader_vert);
		getShaderiv(this->shader_vert, GL_COMPILE_STATUS, &success);
		if (!success) {
			getShaderInfoLog(this->shader_vert, 512, NULL, infoLog);
			throw std::runtime_error(std::string("Failed to compile vertex shader: ") + infoLog);
		}

		shaderSource(this->shader_frag, 1, (const char*)&fragstr, NULL);
		compileShader(this->shader_frag);
		getShaderiv(this->shader_frag, GL_COMPILE_STATUS, &success);
		if (!success) {
			getShaderInfoLog(this->shader_frag, 512, NULL, infoLog);
			throw std::runtime_error(std::string("Failed to compile fragment shader: ") + infoLog);
		}
	} else throw std::runtime_error("Feature not yet implemented: compiled shader programs for GL3");

	glAttachShader attachShader = (glAttachShader)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glAttachShader");
	glLinkProgram linkProgram = (glLinkProgram)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glLinkProgram");
	glGetProgramiv getProgramiv = (glGetProgramiv)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetProgramiv");
	glGetProgramInfoLog getProgramInfoLog = (glGetProgramInfoLog)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetProgramInfoLog");

	int success;
	
	attachShader(this->prog, this->shader_vert);
	attachShader(this->prog, this->shader_frag);
	linkProgram(this->prog);
	getProgramiv(this->prog, GL_LINK_STATUS, &success);
	if (!success) {
		getProgramInfoLog(this->prog, 512, NULL, infoLog);
		throw std::runtime_error(std::string("Failed to link shader program: ") + infoLog);
	}
}

void GL3ShaderProgram::set(const char* name, int v) {
	glGetUniformLocation getUniformLocation = (glGetUniformLocation)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetUniformLocation");
	glUniform1i uniform = (glUniform1i)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glUniform1i");

	unsigned int loc = getUniformLocation(this->prog, name);
	uniform(loc, v);
}

void GL3ShaderProgram::set(const char* name, float v) {
	glGetUniformLocation getUniformLocation = (glGetUniformLocation)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetUniformLocation");
	glUniform1f uniform = (glUniform1f)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glUniform1f");

	unsigned int loc = getUniformLocation(this->prog, name);
	uniform(loc, v);
}

void GL3ShaderProgram::set(const char* name, glm::mat2 v) {
	glGetUniformLocation getUniformLocation = (glGetUniformLocation)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetUniformLocation");
	glUniformMatrix2f uniform = (glUniformMatrix2f)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glUniformMatrix2f");

	unsigned int loc = getUniformLocation(this->prog, name);
	uniform(loc, 1, GL_FALSE, (const float*)glm::value_ptr(v));
}

void GL3ShaderProgram::set(const char* name, glm::mat3 v) {
	glGetUniformLocation getUniformLocation = (glGetUniformLocation)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetUniformLocation");
	glUniformMatrix3f uniform = (glUniformMatrix3f)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glUniformMatrix3f");

	unsigned int loc = getUniformLocation(this->prog, name);
	uniform(loc, 1, GL_FALSE, (const float*)glm::value_ptr(v));
}

void GL3ShaderProgram::set(const char* name, glm::mat4 v) {
	glGetUniformLocation getUniformLocation = (glGetUniformLocation)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetUniformLocation");
	glUniformMatrix4f uniform = (glUniformMatrix4f)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glUniformMatrix4f");

	unsigned int loc = getUniformLocation(this->prog, name);
	uniform(loc, 1, GL_FALSE, (const float*)glm::value_ptr(v));
}

void GL3ShaderProgram::use() {
	glUseProgram useProgram = (glUseProgram)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glUseProgram");
	useProgram(this->prog);
}

/** API **/
using namespace Aires::Graphics::APIs;
using namespace Aires::Graphics;

GL3GraphicsAPI::GL3GraphicsAPI(Window* win) : GraphicsAPI(win) {
}

ShaderProgram* GL3GraphicsAPI::createShaderProgram() {
	return new GL3ShaderProgram(this->win->getGraphicsBackend());
}

ShaderProgram* GL3GraphicsAPI::createShaderProgram(std::string vert, std::string frag, bool compiled) {
	return new GL3ShaderProgram(this->win->getGraphicsBackend(), vert, frag, compiled);
}

Texture* GL3GraphicsAPI::createTexture(uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format) {
	return new GL3Texture(this->win->getGraphicsBackend(), width, height, depth, format);
}
