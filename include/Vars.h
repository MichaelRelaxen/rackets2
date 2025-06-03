/*--------------------------------------------------
----------------Custom variables <3-----------------
--------------------------------------------------*/

#define NO_CUBOID (0xFFFFFFFF)
#define NULL 0
#define CUSTOM_VAR (0x1BE0000)

#define start_real_time_sec_ptr (((int*)CUSTOM_VAR) + 0)
#define start_real_time_sec (*(((int*)CUSTOM_VAR) + 1))
#define start_real_time_nsec_ptr (((int*)CUSTOM_VAR) + 2)
#define start_real_time_nsec (*(((int*)CUSTOM_VAR) + 3))

#define old_should_load (*(((int*)CUSTOM_VAR) + 4))

#define sec_offset (*(((int*)CUSTOM_VAR) + 5))
#define nsec_offset (*(((int*)CUSTOM_VAR) + 6))

#define timer_state (*(((int*)CUSTOM_VAR) + 7))
#define frame_timer (*(((int*)CUSTOM_VAR) + 8))
#define scrambled_frame (*(((int*)CUSTOM_VAR) + 9))

#define framestep_mode (*(((int*)CUSTOM_VAR) + 10))
#define step_frame (*(((int*)CUSTOM_VAR) + 11))

#define rng_seed (*(unsigned int*)(r13 - 0x7000))
#define rng_init (*(int*)(r13 - 0x6FFC))

#define formatted_time_string ((char*)CUSTOM_VAR + 0x100)
#define formatted_status_string ((char*)CUSTOM_VAR + 0x150)
#define formatted_rng ((char*)CUSTOM_VAR + 0x200)

#define remote_pressed_buttons *((int*)(CUSTOM_VAR + 0x250))
#define last_remote_pressed_buttons *((int*)(CUSTOM_VAR + 0x254))
#define remote_joysticks *((int*)(CUSTOM_VAR + 0x258))

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

#define queried_inputs ((cellPadData*)(CUSTOM_VAR + 0x500))



#define sys_fs_open 0x321
#define sys_fs_read 0x322
#define sys_fs_write 0x323
#define sys_fs_close 0x324

#define TIMER_STOPPED 0
#define TIMER_WAITING 1
#define TIMER_RUNNING 2
#define TIMER_ENDED   3

