#include "../include/Moby.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

void _start() {
	// Frame timer since spawn and time gotten from PS3's system clock.
	frame_timer += 1;
	sys_time_get(start_real_time_sec_ptr, start_real_time_nsec_ptr);


	// Reset timers and RNG on reload.
	if(load_in_level) { 
		reset_rta_timer();
		frame_timer = 0;
		rng_seed = 0;   
		rng_init = 0;
	}

	// Floats don't work so we have to represent them like this. RTA_SEC and RTA_MS are macros.
	// Destination planet is set when you change planet, so we will stop the timer on leaving planet.
	if(!destination_planet) { 
		sprintf(formatted_time_string, "RTA: %d.%02d", RTA_SEC, RTA_MS);
		sprintf(formatted_rng, "%10d", rng_seed);
		sprintf(formatted_status_string, "Mode: %s", 
			(tas_state == 5) ? "Playback" : 
			(tas_state == 2) ? "Recording" : "Idle");

	}
	
    // Used for load_in_level macro.
    old_should_load = should_load;
} 