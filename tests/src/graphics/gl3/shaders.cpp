#include <aires/graphics.hpp>
#include <aires/utils/file.hpp>
#include <gtest/gtest.h>

using namespace Aires::Graphics;
using namespace Aires::Utils;
using namespace testing;

TEST(AiresGL3, Shaders) {
	GraphicsBackend* backend = createBackend();
	Window* win = backend->createWindow(640, 480, "Shaders test");
	GraphicsAPI* gfx = createGraphicsAPI(win);
	ShaderProgram* shader = gfx->createShaderProgram(FileUtils::readFile("assets/shaders/gl3/test-vert.glsl"), FileUtils::readFile("assets/shaders/gl3/test-frag.glsl"));
}

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
