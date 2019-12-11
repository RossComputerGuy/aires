#pragma once

#include <aires/graphics/color.hpp>
#include <stdint.h>

namespace Aires {
	namespace Graphics {
		class GraphicsBackend;
		class Texture {
			public:
				Texture(GraphicsBackend* backend, uint32_t width, uint32_t height, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB);
				Texture(GraphicsBackend* backend, uint32_t width, uint32_t height, uint8_t depth, AIRES_COLOR_FORMAT format=AIRES_COLOR_RGB);

				virtual void upload(float* buffer) = 0;
				virtual void use() = 0;

				uint32_t getWidth();
				uint32_t getHeight();
				uint8_t getDepth();

				AIRES_COLOR_FORMAT getColorFormat();
			protected:
				GraphicsBackend* backend;
			private:
				uint32_t width;
				uint32_t height;
				uint8_t depth;
				AIRES_COLOR_FORMAT format;
		};
	};
};
