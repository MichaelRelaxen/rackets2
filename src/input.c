#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

void _start() {
	frame_timer += 1;
	sys_time_get(start_real_time_sec_ptr, start_real_time_nsec_ptr);

	// TODO: Add racman integration for framestep.
	if (framestep_mode) {
		if (!step_frame) {
			while (framestep_mode && !step_frame) {
				syscall(sys_usleep, 10000);
			}
		}
		if (framestep_mode)
			step_frame = 0; // break out of the loop.
	}

	// Reset timers and RNG on reload.
	if(load_in_level) { 
		reset_rta_timer();
		frame_timer = 0;
	}

	// Destination planet is set when you change planet, so we will just not update the sprintf when we leave the level.
	if(!destination_planet) { 
		sprintf(formatted_time_string, "RTA: %d.%02d", RTA_SEC, RTA_MS); // floats dont work
		sprintf(formatted_frames, "Frames: %10d", frame_timer);
		sprintf(formatted_status_string, "Mode: %s", 
			(tas_state == 5) ? "Playback" : 
			(tas_state == 2) ? "Recording" : "Idle");

	}
	
    // Used for load_in_level macro.
    old_should_load = should_load;
} 