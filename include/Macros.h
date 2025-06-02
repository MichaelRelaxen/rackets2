/*--------------------------------------------------
---------------------Macros <3 <3-------------------
--------------------------------------------------*/

// Used for syscalls // Arguments: call, ...
#define syscall ((int (*)(int, ...))0x10bbd00)


#define load_in_level ((!should_load) && (old_should_load))

// Timer stuff
#define sys_time_get(sec_ptr, nsec_ptr) syscall(0x91, (sec_ptr), (nsec_ptr))

#define RTA_SEC ( \
    ((start_real_time_nsec - nsec_offset) < 0) ? (start_real_time_sec - sec_offset - 1) : (start_real_time_sec - sec_offset) \
)

#define RTA_MS ( \
    ((start_real_time_nsec - nsec_offset) < 0) ? ((start_real_time_nsec - nsec_offset + 1000000000) / 10000000) : ((start_real_time_nsec - nsec_offset) / 10000000) \
)

#define reset_rta_timer() do { \
    sec_offset = start_real_time_sec; \
    nsec_offset = start_real_time_nsec; \
} while (0)
	

// RNG




// Rainbow text lmao
#define INT_ABS(x) ((x) < 0 ? -(x) : (x))

#define RAINBOW_COLOR(hue) ({ \
    int h = (hue) % 1536; \
    int r = 0, g = 0, b = 0; \
    int min_brightness = 128; /* half brightness floor */ \
    if (h < 256)      { r = 255;     g = h;       b = 0;     } \
    else if (h < 512) { r = 511 - h; g = 255;     b = 0;     } \
    else if (h < 768) { r = 0;       g = 255;     b = h - 512; } \
    else if (h < 1024){ r = 0;       g = 1023 - h; b = 255;   } \
    else if (h < 1280){ r = h - 1024; g = 0;      b = 255;   } \
    else              { r = 255;     g = 0;       b = 1535 - h; } \
    /* apply brightness floor and scale to avoid zeros */ \
    r = (r / 2) + min_brightness; \
    g = (g / 2) + min_brightness; \
    b = (b / 2) + min_brightness; \
    (0xFF << 24) | (g << 16) | (b << 8) | r; \
})





// Stuff from plat bolt project

#define coords_for_bolt(planetId, slot) \
    (&coords_array[4 * (planetId * 4 + slot)])

#define animation_for_bolt(planetId, slot) \
    (anim_array[4 * planetId + slot])

#define bolt_collected(planetId, slot) \
    (collected_bolts_array[planetId * 4 + slot])

#define moby_is_active(state) \
    ((state != 0xFE) && (state != 0xFD))
	
// Macro for checking for any moby with a non-zero UID, and activated state (1)
#define get_moby_with_oclass(o_class_value, moby_var)                  \
    for (Moby* moby_var = moby_instance_table; moby_var <= moby_instance_perm_end; ++moby_var)   \
        if (moby_var->state > 0 && moby_var->oClass == (o_class_value) && (moby_var)->UID != 0)

#define ship_level (current_planet == FELTZIN || current_planet == HRUGIS || current_planet == GORN)

// Choose between the two functions based on level ID
#define spawn_bolt_macro (ship_level ? spawn_ship_bolt : spawn_game_bolt)

#define oclass_macro (ship_level ? 0x126c : 0x46e)

#define is_ptr_valid(moby) (moby && moby->oClass == oclass_macro)