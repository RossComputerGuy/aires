#pragma once

#include <aires/graphics/vertex.hpp>
#include <list>

namespace Aires {
	namespace Graphics {
		class GraphicsObject {
			public:
				GraphicsObject(glm::vec3 pos);

				glm::vec3 pos;

				virtual void render() = 0;
			protected:
				std::list<Vertex> vertecies;
		};
	};
};
