#include <aires/graphics/apis/gl3.hpp>
#include <aires/graphics/backend.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstring>
#include <stdexcept>

/** GraphicsObject **/
using namespace Aires::Graphics::GraphicsObjects;
using namespace Aires::Graphics::Shaders;

GL3GraphicsObject::GL3GraphicsObject(GraphicsBackend* backend, glm::vec3 pos) : GraphicsObject(backend, pos) {
	_glGenVertexArrays genVertexArrays = (_glGenVertexArrays)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGenVertexArrays");
	_glGenBuffers genBuffers = (_glGenBuffers)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGenBuffers");

	genVertexArrays(1, &this->vao);
	genBuffers(1, &this->vbo);
	genBuffers(1, &this->ebo);
}

GL3GraphicsObject::~GL3GraphicsObject() {
	_glDeleteBuffers deleteBuffers = (_glDeleteBuffers)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glDeleteBuffers");
	_glDeleteVertexArrays deleteVertexArrays = (_glDeleteVertexArrays)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glDeleteVertexArrays");

	deleteBuffers(1, &this->ebo);
	deleteBuffers(1, &this->vbo);
	deleteVertexArrays(1, &this->vao);
}

void GL3GraphicsObject::update() {
	_glBindBuffer bindBuffer = (_glBindBuffer)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glBindBuffer");
	_glBufferData bufferData = (_glBufferData)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glBufferData");

	GLfloat* verts = this->getVerticesArray();
	bindBuffer(GL_ARRAY_BUFFER, this->vbo);
	bufferData(GL_ARRAY_BUFFER, this->vertices.size(), verts, GL_STATIC_DRAW);

	GLuint* elems = this->getElementsArray();
	bindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	bufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size(), elems, GL_STATIC_DRAW);
}

void GL3GraphicsObject::render() {
	_glDrawElements drawElements = (_glDrawElements)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glDrawElements");

	if (this->shaderProgram != NULL && this->shaderProgram != nullptr) this->shaderProgram->use();
	drawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, 0);
}

void GL3GraphicsObject::loadShaders(ShaderProgram* shaderProgram) {
	GL3ShaderProgram* glShader = reinterpret_cast<GL3ShaderProgram*>(shaderProgram);
	GLuint shader = glShader->getID();

	_glGetAttribLocation getAttribLoc = (_glGetAttribLocation)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGetAttribLocation");
	_glEnableVertexAttribArray enableVertexAttribArray = (_glEnableVertexAttribArray)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glEnableVertexAttribArray");
	_glVertexAttribPointer vertexAttribPointer = (_glVertexAttribPointer)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glVertexAttribPointer");

	glShader->use();

	GLint attrPos = getAttribLoc(shader, "position");
	enableVertexAttribArray(attrPos);
	vertexAttribPointer(attrPos, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), 0);

	GLint attrColor = getAttribLoc(shader, "color");
	enableVertexAttribArray(attrColor);
	vertexAttribPointer(attrColor, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLint attrTexCord = getAttribLoc(shader, "texCord");
	enableVertexAttribArray(attrTexCord);
	vertexAttribPointer(attrTexCord, 8, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
}

/** Texture **/
using namespace Aires::Graphics::Textures;

GL3Texture::GL3Texture(GraphicsBackend* backend, GLenum index, uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format) : GL3Texture(backend, index, width, height, 0, format) {}

GL3Texture::GL3Texture(GraphicsBackend* backend, GLenum index, uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format) : Texture(backend, width, height, depth, format) {
	_glActivateTexture activateTexture = (_glActivateTexture)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glActivateTexture");
	_glGenTextures genTextures = (_glGenTextures)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glGenTextures");
	_glBindTexture bindTexture = (_glBindTexture)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glBindTexture");
	_glTexParameteri texParamI = (_glTexParameteri)backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glTexParameteri");

	this->index = index;

	activateTexture(this->index);
	genTextures(1, &this->id);
	bindTexture(depth == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, this->id);
	texParamI(depth == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texParamI(depth == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texParamI(depth == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texParamI(depth == 0 ? GL_TEXTURE_2D : GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GL3Texture::~GL3Texture() {
	_glDeleteTextures deleteTextures = (_glDeleteTextures)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glDeleteTextures");
	deleteTextures(1, &this->id);
}

void GL3Texture::upload(float* buffer) {
	_glTexImage2D texImage2D = (_glTexImage2D)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glTexImage2D");
	_glTexImage3D texImage3D = (_glTexImage3D)this->backend->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glTexImage3D");

	GLenum format = this->getColorFormat() == AIRES_COLOR_RGB ? GL_RGB : GL_RGBA;
	if (this->getDepth() == 0) texImage2D(GL_TEXTURE_2D, 0, format, this->getWidth(), this->getHeight(), 0, format, GL_FLOAT, buffer);
	else texImage3D(GL_TEXTURE_3D, 0, format, this->getWidth(), this->getHeight(), this->getDepth(), 0, format, GL_FLOAT, buffer);
}

/** Shader **/
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

GLuint GL3ShaderProgram::getID() {
	return this->prog;
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

GraphicsObject* GL3GraphicsAPI::createObject(glm::vec3 pos) {
	return new GL3GraphicsObject(this->win->getGraphicsBackend(), pos);
}

Texture* GL3GraphicsAPI::createTexture(uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format) {
	GL3Texture* tex = new GL3Texture(this->win->getGraphicsBackend(), GL_TEXTURE0 + this->textures.size(), width, height, depth, format);
	this->textures.push_back(tex);
	return tex;
}

void GL3GraphicsAPI::render(std::function<void()> cb) {
	this->win->render([ this, cb ] () {
		_glClear clear = (_glClear)this->win->getGraphicsBackend()->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glClear");
		_glClearColor clearColor = (_glClearColor)this->win->getGraphicsBackend()->getAPIFunction(AIRES_GRAPHICS_API_GL3, "glClearColor");

		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		cb();
	});
}