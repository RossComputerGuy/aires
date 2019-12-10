#include <aires/graphics.hpp>
#include <gtest/gtest.h>

using namespace Aires::Graphics;
using namespace testing;

TEST(AiresGL3, graphicsObject) {
	GraphicsBackend* backend = createBackend();
	Window* win = backend->createWindow(640, 480, "Rendering test");
	GraphicsAPI* gfx = createGraphicsAPI(win);
	GraphicsObject* obj = gfx->createObject();
	gfx->render([ & ] () {
		obj->render();
	});
}

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
