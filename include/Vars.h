/*--------------------------------------------------
----------------Custom variables <3-----------------
--------------------------------------------------*/

// A little bit messy sorry.

#define CUSTOM_VAR (0x1BE0000)

// input.c
#define start_real_time_sec_ptr (((int*)CUSTOM_VAR) + 0)
#define start_real_time_sec (*(((int*)CUSTOM_VAR) + 1))
#define start_real_time_nsec_ptr (((int*)CUSTOM_VAR) + 2)
#define start_real_time_nsec (*(((int*)CUSTOM_VAR) + 3))
#define old_should_load (*(((int*)CUSTOM_VAR) + 4))
#define sec_offset (*(((int*)CUSTOM_VAR) + 5))
#define nsec_offset (*(((int*)CUSTOM_VAR) + 6))
#define frame_timer (*(((int*)CUSTOM_VAR) + 8))

#define frame_to_stop_at (*(((int*)CUSTOM_VAR) + 9))

#define framestep_mode (*(((int*)CUSTOM_VAR) + 10))
#define step_frame (*(((int*)CUSTOM_VAR) + 11))


#define rng_nudge (*(((int*)CUSTOM_VAR) + 12))
#define nudged_frames (*(((int*)CUSTOM_VAR) + 13))

#define formatted_time_string ((char*)CUSTOM_VAR + 0x100)
#define formatted_status_string ((char*)CUSTOM_VAR + 0x120)
#define formatted_frames ((char*)CUSTOM_VAR + 0x140)
#define formatted_ntrl ((char*)CUSTOM_VAR + 0x155)

// pad_redirect.c
#define recorded_buttons *((ushort*)(CUSTOM_VAR + 0x260))
#define recorded_sticks *((uint*)(CUSTOM_VAR + 0x262))
#define recorded_pad_state *((uint*)(CUSTOM_VAR + 0x300))
#define recorded_pad_len *((uint*)(CUSTOM_VAR + 0x304))

#define tas_state *((uint*)(CUSTOM_VAR + 0x270))
#define tas_stop_api *((uint*)(CUSTOM_VAR + 0x274))

#define tas_fd_ptr ((int*)(CUSTOM_VAR + 0x278))
#define tas_nread_ptr ((unsigned int*)(CUSTOM_VAR + 0x280))

#define tas_buttons *((uint*)(CUSTOM_VAR + 0x290))
#define tas_sticks *((uint*)(CUSTOM_VAR + 0x294))

#define TIMER_STOPPED 0
#define TIMER_WAITING 1
#define TIMER_RUNNING 2
#define TIMER_ENDED   3

