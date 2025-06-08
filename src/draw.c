#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Vars.h"

#define rainbow_color(hue) ({ \
    int h = (hue) % 1536; \
    int r = 0, g = 0, b = 0; \
    int min_brightness = 128; \
    if (h < 256)      { r = 255;     g = h;       b = 0;     } \
    else if (h < 512) { r = 511 - h; g = 255;     b = 0;     } \
    else if (h < 768) { r = 0;       g = 255;     b = h - 512; } \
    else if (h < 1024){ r = 0;       g = 1023 - h; b = 255;   } \
    else if (h < 1280){ r = h - 1024; g = 0;      b = 255;   } \
    else              { r = 255;     g = 0;       b = 1535 - h; } \
    r = (r / 2) + min_brightness; \
    g = (g / 2) + min_brightness; \
    b = (b / 2) + min_brightness; \
    (0x80 << 24) | (g << 16) | (b << 8) | r; \
})

void _start() {
	// Crash if we run this code on the loading screens... so just don't run it.
	if(should_load || hide_gui)
		return;
	
	uint32_t color = rainbow_color(frames_since_spawn * 5);

	uint y_ofs = 0x14f;
	uint x_ofs = 0x52;
	draw_box(0x40 + x_ofs, y_ofs - 0x4, -0x4b + x_ofs, y_ofs + 0x55, 0x70000000, 0);

	text_small_right(-0x2 - 0x45 + x_ofs, 0x0 + y_ofs, color, formatted_time_string, -1);
	text_small_right(-0x2 - 0x45 + x_ofs, 0x10 + y_ofs, color, formatted_frames, -1);
	text_small_right(-0x2 - 0x45 + x_ofs, 0x20 + y_ofs, color, formatted_status_string, -1);
	text_small_right(-0x2 - 0x45 + x_ofs, 0x30 + y_ofs, color, formatted_ntrl, -1);
    text_small_right(-0x2 - 0x45 + x_ofs, 0x40 + y_ofs, color, formatted_state, -1);
} 