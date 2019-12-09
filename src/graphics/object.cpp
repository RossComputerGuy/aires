#include <aires/graphics/object.hpp>

using namespace Aires::Graphics;

GraphicsObject::GraphicsObject(GraphicsBackend* backend, glm::vec3 pos) {
	this->backend = backend;
	this->pos = pos;
}

void GraphicsObject::setShaderProgram(ShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
	this->loadShaders(this->shaderProgram);
}

int* GraphicsObject::getElementsArray() {
	int* elems = new int[this->elements.size()];
	size_t i = 0;
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) elems[i++] = *it;
	return elems;
}

float* GraphicsObject::getVerticiesArray() {
	float* elems = new float[this->vertices.size() * 10];
	size_t i = 0;
	for (auto it = this->vertices.begin(); it != this->vertices.end(); it++) {
		Vertex vert = (*it).clone();
		vert.pos += this->pos;
		float* a = vert.array();
		for (size_t x = 0; x < 10; x++) elems[i++] = a[x];
	}
	return elems;
}