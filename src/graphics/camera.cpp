#include <aires/graphics/camera.hpp>

using namespace Aires::Graphics;

Camera::Camera() {}

glm::mat4 Camera::calc() {
	return this->proj * this->view * this->model;
}
