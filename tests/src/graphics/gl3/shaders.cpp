#include <aires/graphics/apis/gl3.hpp>
#include <aires/graphics/backends/glfw.hpp>
#include <aires/utils/file.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace Aires::Graphics::APIs;
using namespace Aires::Graphics::Backends;
using namespace Aires::Graphics::Shaders;
using namespace Aires::Graphics;
using namespace Aires::Utils;
using namespace testing;

TEST(AiresGL3Shaders, GLFWSimple) {
	GLFWBackend* backend = new GLFWBackend();
	Window* win = backend->createWindow(640, 480, "GLFW Simple");
	GL3GraphicsAPI* gfx = new GL3GraphicsAPI(win);
	ShaderProgram* shader = gfx->createShaderProgram(FileUtils::readFile("assets/shaders/gl3/test-vert.glsl"), FileUtils::readFile("assets/shaders/gl3/test-frag.glsl"));
}

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
