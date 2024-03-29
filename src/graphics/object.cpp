#include <aires/graphics/object.hpp>

using namespace Aires::Graphics;

GraphicsObject::GraphicsObject(GraphicsBackend* backend, glm::vec3 pos) {
	this->backend = backend;
	this->transform = glm::translate(glm::mat4(0.0f), pos);
}

void GraphicsObject::setShaderProgram(ShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
	this->loadShaders(this->shaderProgram);
}

void GraphicsObject::render() {
	this->render(nullptr);
}

unsigned int* GraphicsObject::getElementsArray() {
	unsigned int* elems = new unsigned int[this->elements.size()];
	size_t i = 0;
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) elems[i++] = *it;
	return elems;
}

float* GraphicsObject::getVerticesArray() {
	float* elems = new float[this->vertices.size() * 10];
	size_t i = 0;
	for (auto it = this->vertices.begin(); it != this->vertices.end(); it++) {
		Vertex vert = (*it).clone();
		float* a = vert.array();
		for (size_t x = 0; x < 10; x++) elems[i++] = a[x];
	}
	return elems;
}