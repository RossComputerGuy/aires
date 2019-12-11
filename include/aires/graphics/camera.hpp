#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace Aires {
	namespace Graphics {
		class Camera {
			public:
				Camera();

				glm::mat4 model;
				glm::mat4 view;
				glm::mat4 proj;

				glm::mat4 calc();
		};
	};
};
