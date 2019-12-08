#pragma once

#include <glm/glm.hpp>

namespace Aires {
	namespace Graphics {
		class GraphicsBackend;
		class ShaderProgram {
			public:
				ShaderProgram(GraphicsBackend* backend);
				ShaderProgram(GraphicsBackend* backend, const char* vert, const char* frag);

				virtual void set(const char* name, int v) = 0;
				virtual void set(const char* name, float v) = 0;
				virtual void set(const char* name, glm::mat2 v) = 0;
				virtual void set(const char* name, glm::mat3 v) = 0;
				virtual void set(const char* name, glm::mat4 v) = 0;
				virtual void use() = 0;

			protected:
				GraphicsBackend* backend;
		};
	};
};
