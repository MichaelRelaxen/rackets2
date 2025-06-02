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


#define formatted_time_string ((char*)CUSTOM_VAR + 0x100)
#define formatted_status_string ((char*)CUSTOM_VAR + 0x150)
#define formatted_rng ((char*)CUSTOM_VAR + 0x200)

#define remote_pressed_buttons *((int*)(CUSTOM_VAR + 0x250))
#define last_remote_pressed_buttons *((int*)(CUSTOM_VAR + 0x254))
#define remote_joysticks *((int*)(CUSTOM_VAR + 0x258))

#define fmt_buttons *((ushort*)(CUSTOM_VAR + 0x260))
#define fmt_sticks *((uint*)(CUSTOM_VAR + 0x262))

#define tas_state *((uint*)(CUSTOM_VAR + 0x270))
#define tas_stop_api *((uint*)(CUSTOM_VAR + 0x274))

#define tas_fd_ptr ((int*)(CUSTOM_VAR + 0x278))
#define tas_nread_ptr ((unsigned int*)(CUSTOM_VAR + 0x280))

#define tas_buttons *((uint*)(CUSTOM_VAR + 0x290))
#define tas_sticks *((uint*)(CUSTOM_VAR + 0x294))

#define TAS_RECORDING_WAIT 1
#define TAS_RECORDING 2
#define TAS_SAVE 3
#define TAS_PLAYBACK_WAIT 4
#define TAS_PLAYBACK 5
#define TAS_STOP 6

#define sys_fs_open 0x321
#define sys_fs_read 0x322
#define sys_fs_write 0x323
#define sys_fs_close 0x324

#define TIMER_STOPPED 0
#define TIMER_WAITING 1
#define TIMER_RUNNING 2
#define TIMER_ENDED   3

