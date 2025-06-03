#include "../include/Moby.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

void _start() {
	frame_timer += 1;
	// Frame timer since spawn and time gotten from PS3's system clock.
	sys_time_get(start_real_time_sec_ptr, start_real_time_nsec_ptr);

	// Corrupted my fucking system software??????
	/*
	if (framestep_mode) {
		while (!step_frame) {
			int32_t ret = cellPadGetData(0, queried_inputs);
			uint16_t btns = ((queried_inputs->buttons_high & 0xFF) << 8) | (queried_inputs->buttons_low & 0xFF);
			if(btns == BTN_UP)
				step_frame = 1;
			syscall(0x8D, 10000); // Sleep 10ms
		}
	}

	if(recorded_buttons == 5 || framestep_mode)
    	framestep_mode ^= 1;
	*/

	if (framestep_mode) {
		if (!step_frame) {
			// Stay frozen until step_frame is set, or framestep_mode is turned off
			while (framestep_mode && !step_frame) {
				syscall(0x8D, 10000); // Sleep 10ms
			}
		}
		
		// Only consume step if we're still in step mode
		if (framestep_mode) {
			step_frame = 0;
		}
	}

	// Reset timers and RNG on reload.
	if(load_in_level) { 
		reset_rta_timer();
		frame_timer = 0;
	}

	// Floats don't work so we have to represent them like this. RTA_SEC and RTA_MS are macros.
	// Destination planet is set when you change planet, so we will stop the timer on leaving planet.
	if(!destination_planet) { 
		sprintf(formatted_time_string, "RTA: %d.%02d", RTA_SEC, RTA_MS);
		sprintf(formatted_rng, "Frames: %10d", frame_timer);
		sprintf(formatted_status_string, "Mode: %s", 
			(tas_state == 5) ? "Playback" : 
			(tas_state == 2) ? "Recording" : "Idle");

	}
	
    // Used for load_in_level macro.
    old_should_load = should_load;
} 