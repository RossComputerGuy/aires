#pragma once

#include <aires/graphics/backend.hpp>
#include <aires/graphics/camera.hpp>
#include <aires/graphics/shader.hpp>
#include <aires/graphics/texture.hpp>
#include <aires/graphics/vertex.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

namespace Aires {
	namespace Graphics {
		class GraphicsObject {
			public:
				GraphicsObject(GraphicsBackend* backend, glm::vec3 pos);

				glm::mat4 transform;
				std::list<Vertex> vertices;
				std::list<unsigned int> elements;
				Texture* texture = nullptr;

				virtual void update() = 0;
				virtual void render(Camera* cam) = 0;

				void render();

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
