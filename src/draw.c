#include "../include/Moby.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"

void _start() {
	if(should_load)
		return;
	
	uint32_t color = RAINBOW_COLOR(frames_since_spawn * 5);
	
	draw_something_text(0x44, 0x51, 0xFF000000, formatted_time_string, -1);
	draw_something_text(0x44, 0x50, color, formatted_time_string, -1);
	
	draw_something_text(0x44, 0x71, 0xFF000000, formatted_rng, -1);
	draw_something_text(0x44, 0x70, color, formatted_rng, -1);
} 