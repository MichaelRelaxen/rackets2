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
    frame_timer = 1; \
} while (0)

#define sys_time_get(sec_ptr, nsec_ptr) syscall(0x91, (sec_ptr), (nsec_ptr))

#define set_aside_file() \
    for (int i = 0; i < 0x200000; i += 0x8000) { \
        memcpy((void*)((int)api_aside_buf + i), (void*)((int)savedata_buf + i), 0x8000); \
    }


void _start() {
	

	
	// just set this on startup
	if(!sec_offset) 
		api_savemode = -1;

	sys_time_get(start_real_time_sec_ptr, start_real_time_nsec_ptr);

	if(!sec_offset || load_in_level)
		reset_timers();


	if (framestep_mode) {
		if (!step_frame) {
			while (framestep_mode && !step_frame) {
				syscall(sys_usleep, 10000);
			}
		}
		step_frame = 0;
	}

	if(render_all_toggle) {
		memset(render_all_region, 0xff, 0xff);
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
        sprintf(formatted_state, "State: %d", player_state);

	}

	if(api_setaside) {
		api_setaside = 0;
		set_aside_file();
	}
	if(api_load) {
		rng_nudge = 0;
        if (!*(int*)api_aside_buf)
            set_aside_file();

		perform_load(0, api_aside_buf);
		api_load = 0;
	}

	/* run save handler function if set
	SAVE_MENU 0
	LOAD_MENU 1
	AUTO_SAVE 3
	*/
	if(api_savemode != -1) {
		save_handler(api_savemode);
		api_savemode = -1;
	}
	
    // Used for load_in_level macro.
    old_should_load = should_load;
} 