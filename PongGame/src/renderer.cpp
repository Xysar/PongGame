void render_background() {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = x * y;
		}
	}
}

void clear_screen(unsigned int color) {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}


void drawRectinPixels(int x0, int y0, int width, int height, unsigned int color) {
	int rectHeight = y0 + height;
	int rectWidth = x0 + width;

	int fullscreen = GetSystemMetrics(16);

	x0 = clamp(0, x0, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	rectWidth = clamp(0, rectWidth, render_state.width);
	rectHeight = clamp(0, rectHeight, render_state.height);

	for (int y = y0; y < rectHeight ; y++) {
		unsigned int* pixel = (unsigned int*)render_state.memory+ x0 + y * render_state.width;
		for (int x = x0; x < rectWidth; x++) {
			*pixel++ = color;
		}
	}
}

static float UIscale = 0.01f;

static void drawRect(float x, float y, float halfsize_x, float halfsize_y, unsigned int color) {
	x *= render_state.height * UIscale;
	y *= render_state.height * UIscale;
	halfsize_x *= render_state.height * UIscale;
	halfsize_y *= render_state.height * UIscale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;
	
	int x0 = x - halfsize_x;
	int y0 = y - halfsize_y;
	int width = halfsize_x * 2;
	int height = halfsize_y * 2;

	drawRectinPixels(x0, y0, width, height, color);
}