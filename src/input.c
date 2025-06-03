#include "../include/Moby.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define SCRAMBLE_FRAME(f) ((uint32_t)((((f) * 0x45d9f3b) ^ ((f) >> 3)) * 0x45d9f3b) ^ ((f) * 0x27d4eb2d))

#define RNG_SEED_ADDR ((volatile uint32_t*)0x10000060)     // RNG seed at 0x10000060
#define RNG_BUFFER_ADDR ((volatile uint32_t*)0x1000006C)   // RNG buffer starts at 0x10000070
#define RNG_BUFFER_SIZE 32                                 // 32 entries * 4 bytes = 128 bytes
#define FRAME_TIMER_ADDR ((volatile uint32_t*)0x01BE0020) // frame timer address

// chatgpt
#define XORSHIFT32(state) ( \
    (state) ^= ((state) << 13), \
    (state) ^= ((state) >> 17), \
    (state) ^= ((state) << 5), \
    (state) \
)

// nah
#define UPDATE_RNG_BUFFER() do { \
    int _ft_seed = frame_timer ^ 0xA5A5A5A5; \
    int _i; \
    for (_i = 0; _i < RNG_BUFFER_SIZE; _i++) { \
        int _state = _ft_seed + _i * 0x9E3779B9; \
        _state ^= (_state << 13); \
        _state ^= (_state >> 17); \
        _state ^= (_state << 5); \
        RNG_BUFFER_ADDR[_i] = _state; \
    } \
} while (0)

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
		scrambled_frame = 0;
	}
	scrambled_frame = SCRAMBLE_FRAME(frame_timer);
	// rng_seed = scrambled_frame;
	UPDATE_RNG_BUFFER();


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