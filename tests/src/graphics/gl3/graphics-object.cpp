#include <aires/graphics.hpp>
#include <aires/utils/file.hpp>
#include <gtest/gtest.h>

using namespace Aires::Graphics;
using namespace Aires::Utils;
using namespace testing;

TEST(AiresGL3, graphicsObject) {
	GraphicsBackend* backend = createBackend();
	Window* win = backend->createWindow(640, 480, "Rendering test");
	GraphicsAPI* gfx = createGraphicsAPI(win);
	GraphicsObject* obj = gfx->createObject();
	obj->setShaderProgram(gfx->createShaderProgram(FileUtils::readFile("assets/shaders/gl3/test-vert.glsl"), FileUtils::readFile("assets/shaders/gl3/test-frag.glsl")));
	obj->vertices.push_back(Vertex(glm::vec3(0.0f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	obj->vertices.push_back(Vertex(glm::vec3(0.0f, 0.5f, 0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
	obj->vertices.push_back(Vertex(glm::vec3(0.0f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	obj->vertices.push_back(Vertex(glm::vec3(0.0f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	obj->vertices.push_back(Vertex(glm::vec3(0.0f, -0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
	obj->vertices.push_back(Vertex(glm::vec3(0.0f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	obj->elements.push_back(0);
	obj->elements.push_back(1);
	obj->elements.push_back(2);
	obj->elements.push_back(2);
	obj->elements.push_back(3);
	obj->elements.push_back(0);
	obj->update();
	gfx->render([ & ] () {
		obj->render();
	});
}

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
