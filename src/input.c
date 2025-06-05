#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define rta_sec ( \
    ((start_real_time_nsec - nsec_offset) < 0) ? (start_real_time_sec - sec_offset - 1) : (start_real_time_sec - sec_offset) \
)

#define rta_cs ( \
    ((start_real_time_nsec - nsec_offset) < 0) ? ((start_real_time_nsec - nsec_offset + 1000000000) / 10000000) : ((start_real_time_nsec - nsec_offset) / 10000000) \
)

#define reset_timers() do { \
    sec_offset = start_real_time_sec; \
    nsec_offset = start_real_time_nsec; \
    frame_timer = 0; \
} while (0)

#define sys_time_get(sec_ptr, nsec_ptr) syscall(0x91, (sec_ptr), (nsec_ptr))

void _start() {
	sys_time_get(start_real_time_sec_ptr, start_real_time_nsec_ptr);

	if(!sec_offset || load_in_level)
		reset_timers();

	if (framestep_mode) {
		if (!step_frame) {
			while (framestep_mode && !step_frame) {
				syscall(sys_usleep, 10000);
			}
		}
		if (framestep_mode)
			step_frame = 0;
	}

	if(frame_to_stop_at != 0 && frame_timer == frame_to_stop_at)
		framestep_mode = 1;

	uint neutral = (uint)(neutral_speed * 100000);

	// Destination planet is set when you change planet, so we will just not update the sprintfs to "stop" the timer.
	if(!destination_planet) { 
		sprintf(formatted_time_string, "RTA: %d.%02d", rta_sec, rta_cs); // floats dont work
		sprintf(formatted_frames, "Frames: %d", frame_timer);
		sprintf(formatted_status_string, "Mode: %s", 
			(tas_state == 5) ? "Playing" : 
			(tas_state == 2) ? "Recording" : "Idle");
		sprintf(formatted_ntrl, "Ntrl: 0.%05d", neutral);

	}
	
    // Used for load_in_level macro.
    old_should_load = should_load;
} 