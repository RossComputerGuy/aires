#include <aires/graphics/vertex.hpp>

using namespace Aires::Graphics;

Vertex::Vertex() {}

Vertex::Vertex(glm::vec3 pos) : Vertex(pos, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
}

Vertex::Vertex(glm::vec3 pos, glm::vec4 color) : Vertex(pos, color, glm::vec3(0.0f, 0.0f, 0.0f)) {
}

Vertex::Vertex(glm::vec3 pos, glm::vec4 color, glm::vec3 texture_cord) {
	this->pos = pos;
	this->color = color;
	this->texture_cord = texture_cord;
}

float* Vertex::array() {
       return new float[10] {
	       this->pos[0], this->pos[1], this->pos[2],
	       this->color[0], this->color[1], this->color[2], this->color[3],
	       this->texture_cord[0], this->texture_cord[1], this->texture_cord[2]
       };
}
