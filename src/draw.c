#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"

void _start() {
	// Crash if we run this code on the loading screens... so just don't run it.
	if(should_load)
		return;
	
	uint32_t color = rainbow_color(frames_since_spawn * 5);

	uint y_ofs = 0x15f;
	uint x_ofs = 0x52;
	draw_box(0x40 + x_ofs, y_ofs - 0x4, -0x4b + x_ofs, y_ofs + 0x45, 0x70000000, 0);

	text_small_right(-0x2 - 0x45 + x_ofs, 0x0 + y_ofs, color, formatted_time_string, -1);
	text_small_right(-0x2 - 0x45 + x_ofs, 0x10 + y_ofs, color, formatted_frames, -1);
	text_small_right(-0x2 - 0x45 + x_ofs, 0x20 + y_ofs, color, formatted_status_string, -1);
	text_small_right(-0x2 - 0x45 + x_ofs, 0x30 + y_ofs, color, formatted_ntrl, -1);
} 