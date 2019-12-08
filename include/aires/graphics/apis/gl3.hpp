#pragma once

#include <aires/graphics/api.hpp>
#include <aires/graphics/shader.hpp>
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

namespace Aires {
	namespace Graphics {
		namespace Shaders {
			class GL3ShaderProgram : public ShaderProgram {
				public:
					GL3ShaderProgram(GraphicsBackend* backend);
					GL3ShaderProgram(GraphicsBackend* backend, const char* vert, const char* frag, bool compiled=false);

					void set(const char* name, int v);
					void set(const char* name, float v);
					void set(const char* name, glm::mat2 v);
					void set(const char* name, glm::mat3 v);
					void set(const char* name, glm::mat4 v);
					void use();
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
					ShaderProgram* createShaderProgram(const char* vert, const char* frag, bool compiled=false);
			};
		};
	};
};
