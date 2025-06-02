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

#define formatted_time_string ((char*)CUSTOM_VAR + 0x100)
#define formatted_rng ((char*)CUSTOM_VAR + 0x200)

#define TIMER_STOPPED 0
#define TIMER_WAITING 1
#define TIMER_RUNNING 2
#define TIMER_ENDED   3