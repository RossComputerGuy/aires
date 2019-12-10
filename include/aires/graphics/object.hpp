#pragma once

#include <aires/graphics/backend.hpp>
#include <aires/graphics/shader.hpp>
#include <aires/graphics/vertex.hpp>
#include <list>

namespace Aires {
	namespace Graphics {
		class GraphicsObject {
			public:
				GraphicsObject(GraphicsBackend* backend, glm::vec3 pos);

				glm::vec3 pos;
				std::list<Vertex> vertices;
				std::list<unsigned int> elements;

				virtual void update() = 0;
				virtual void render() = 0;

				void setShaderProgram(ShaderProgram* shaderProgram);
				unsigned int* getElementsArray();
				float* getVerticesArray();
			protected:
				ShaderProgram* shaderProgram;
				GraphicsBackend* backend;

				virtual void loadShaders(ShaderProgram* shaderProgram) = 0;
		};
	};
};
