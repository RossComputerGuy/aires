#include <aires/graphics.hpp>
#include <gtest/gtest.h>

using namespace Aires::Graphics;
using namespace testing;

TEST(AiresGL3, Textures2D) {
	GraphicsBackend* backend = createBackend();
	Window* win = backend->createWindow(640, 480, "Textures test");
	GraphicsAPI* gfx = createGraphicsAPI(win);
	Texture* tex = gfx->createTexture(1, 1);
	tex->upload(new float[3]{ 0.1f, 0.1f, 0.1f });
}

TEST(AiresGL3, Textures3D) {
	GraphicsBackend* backend = createBackend();
	Window* win = backend->createWindow(640, 480, "Textures test");
	GraphicsAPI* gfx = createGraphicsAPI(win);
	Texture* tex = gfx->createTexture(1, 1, 1);
	tex->upload(new float[3]{ 0.1f, 0.1f, 0.1f });
}

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
