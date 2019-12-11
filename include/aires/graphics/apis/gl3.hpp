#pragma once

#include <aires/graphics/api.hpp>
#include <aires/graphics/color.hpp>
#include <aires/graphics/object.hpp>
#include <aires/graphics/shader.hpp>
#include <aires/graphics/texture.hpp>
#include <GL/gl.h>

typedef GLuint (*glCreateShader)(GLenum);
typedef GLuint (*glCreateProgram)();
typedef void (*glShaderSource)(GLuint, GLsizei, const GLchar*, const GLint*);
typedef void (*glCompileShader)(GLuint);
typedef void (*glAttachShader)(GLuint, GLuint);
typedef void (*glLinkProgram)(GLuint);
typedef void (*glGetShaderiv)(GLuint, GLenum, GLint*);
typedef void (*glGetShaderInfoLog)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef glGetShaderiv glGetProgramiv;
typedef glGetShaderInfoLog glGetProgramInfoLog;
typedef void (*glUniform1f)(GLuint, GLfloat);
typedef void (*glUniform2f)(GLuint, GLfloat, GLfloat);
typedef void (*glUniform3f)(GLuint, GLfloat, GLfloat, GLfloat);
typedef void (*glUniform4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (*glUniform1i)(GLuint, GLint);
typedef void (*glUniform2i)(GLuint, GLint, GLint);
typedef void (*glUniform3i)(GLuint, GLint, GLint, GLint);
typedef void (*glUniform4i)(GLuint, GLint, GLint, GLint, GLint);
typedef void (*glUniformMatrix2f)(GLint, GLsizei, GLboolean, const GLfloat* value);
typedef void (*glUniformMatrix3f)(GLint, GLsizei, GLboolean, const GLfloat* value);
typedef void (*glUniformMatrix4f)(GLint, GLsizei, GLboolean, const GLfloat* value);
typedef GLuint (*glGetUniformLocation)(GLuint, const GLchar*);
typedef void (*glUseProgram)(GLuint);
typedef void (*_glGenTextures)(GLsizei, GLuint*);
typedef void (*_glBindTexture)(GLenum, GLuint);
typedef void (*_glTexImage2D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (*_glTexImage3D)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (*_glClear)(GLbitfield);
typedef void (*_glClearColor)(GLclampf, GLclampf, GLclampf, GLclampf);
typedef void (*_glActivateTexture)(GLenum);
typedef void (*_glTexParameterf)(GLenum, GLenum, GLfloat);
typedef void (*_glTexParameteri)(GLenum, GLenum, GLint);
typedef void (*_glDeleteTextures)(GLsizei, const GLuint*);
typedef void (*_glGenVertexArrays)(GLsizei, GLuint*);
typedef void (*_glBindVertexArray)(GLuint);
typedef void (*_glDeleteVertexArrays)(GLsizei, const GLuint*);
typedef void (*_glGenBuffers)(GLsizei, GLuint*);
typedef void (*_glDeleteBuffers)(GLsizei, const GLuint*);
typedef void (*_glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*_glEnableVertexAttribArray)(GLuint);
typedef void (*_glDisableVertexAttribArray)(GLuint);
typedef GLint (*_glGetAttribLocation)(GLuint, const GLchar*);
typedef void (*_glDrawElements)(GLenum, GLsizei, GLenum, const void*);
typedef void (*_glBindBuffer)(GLenum, GLuint);
typedef void (*_glBufferData)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (*_glDrawArrays)(GLenum, GLint, GLsizei);

namespace Aires {
	namespace Graphics {
		namespace GraphicsObjects {
			class GL3GraphicsObject : public GraphicsObject {
				public:
					GL3GraphicsObject(GraphicsBackend* backend, glm::vec3 pos);
					~GL3GraphicsObject();

					void update();
					void render();
				protected:
					void loadShaders(ShaderProgram* shaderProgram);
				private:
					GLfloat* _verts;
					GLuint* _elems;

					GLuint vao;
					GLuint vbo;
					GLuint ebo;
			};
		};
		namespace Textures {
			class GL3Texture : public Texture {
				public:
					GL3Texture(GraphicsBackend* backend, GLenum index, uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB);
					GL3Texture(GraphicsBackend* backend, GLenum index, uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB);
					~GL3Texture();

					void upload(float* buffer);
				private:
					GLuint id;
					GLenum index;
			};
		};
		namespace Shaders {
			class GL3ShaderProgram : public ShaderProgram {
				public:
					GL3ShaderProgram(GraphicsBackend* backend);
					GL3ShaderProgram(GraphicsBackend* backend, std::string vert, std::string frag, bool compiled=false);

					void set(const char* name, int v);
					void set(const char* name, float v);
					void set(const char* name, glm::mat2 v);
					void set(const char* name, glm::mat3 v);
					void set(const char* name, glm::mat4 v);
					void use();

					GLuint getID();
				private:
					int prog;
					int shader_vert;
					int shader_frag;
			};
		};
		namespace APIs {
			class GL3GraphicsAPI : public GraphicsAPI {
				public:
					GL3GraphicsAPI(Window* win);

					ShaderProgram* createShaderProgram();
					ShaderProgram* createShaderProgram(std::string vert, std::string frag, bool compiled=false);

					GraphicsObject* createObject(glm::vec3 pos);

					Texture* createTexture(uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB);
					void render(std::function<void()> cb);
				private:
					std::list<Aires::Graphics::Textures::GL3Texture*> textures;
			};
		};
	};
};
