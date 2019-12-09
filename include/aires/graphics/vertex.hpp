#pragma once

#include <glm/glm.hpp>
#include <stdexcept>

namespace Aires {
	namespace Graphics {
		class Vertex {
			public:
				Vertex();
				Vertex(glm::vec3 pos);
				Vertex(glm::vec3 pos, glm::vec4 color);
				Vertex(glm::vec3 pos, glm::vec4 color, glm::vec3 texture_cord);
				Vertex(glm::vec3 pos, glm::vec4 color, glm::vec3 texture_cord, int next);

				glm::vec3 pos;
				glm::vec4 color;
				glm::vec3 texture_cord;
				int next;

				float &operator[](int i) {
					if (i >= 0 && i < 3) return this->pos[i];
					if (i >= 3 && i < 7) return this->color[i - 3];
					if (i >= 7 && i < 10) return this->texture_cord[i - 7];
					throw std::runtime_error("Index out of bounds");
				}

				float* array();

				Vertex clone();
		};
	};
};
