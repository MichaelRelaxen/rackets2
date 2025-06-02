#include "../include/Moby.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"

void _start() {
	/*if (current_planet == MAIN_MENU)
        return;*/
	
	
	sys_time_get(start_real_time_sec_ptr, start_real_time_nsec_ptr);
	
	
	if(load_in_level) { // Reset timer and RNG back to default seed.
		reset_rta_timer();
		rng_seed = 0;    
		rng_init = 0; 
	}
	
	
	if(!destination_planet) { // floats dont work with sprintf via racman patching
		sprintf(formatted_time_string, "RTA: %d.%02d", RTA_SEC, RTA_MS);
		sprintf(formatted_rng, "%10d", rng_seed);
	}
	
    
    old_should_load = should_load;
} 