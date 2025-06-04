/*--------------------------------------------------
---------------------Macros <3 <3-------------------
--------------------------------------------------*/

#define load_in_level ((!should_load) && (old_should_load))

#define syscall ((int (*)(int, ...))0x10bbd00)
#define sys_time_get(sec_ptr, nsec_ptr) syscall(0x91, (sec_ptr), (nsec_ptr))

#define rta_sec ( \
    ((start_real_time_nsec - nsec_offset) < 0) ? (start_real_time_sec - sec_offset - 1) : (start_real_time_sec - sec_offset) \
)

#define rta_cs ( \
    ((start_real_time_nsec - nsec_offset) < 0) ? ((start_real_time_nsec - nsec_offset + 1000000000) / 10000000) : ((start_real_time_nsec - nsec_offset) / 10000000) \
)

#define reset_rta_timer() do { \
    sec_offset = start_real_time_sec; \
    nsec_offset = start_real_time_nsec; \
} while (0)

#define rainbow_color(hue) ({ \
    int h = (hue) % 1536; \
    int r = 0, g = 0, b = 0; \
    int min_brightness = 128; \
    if (h < 256)      { r = 255;     g = h;       b = 0;     } \
    else if (h < 512) { r = 511 - h; g = 255;     b = 0;     } \
    else if (h < 768) { r = 0;       g = 255;     b = h - 512; } \
    else if (h < 1024){ r = 0;       g = 1023 - h; b = 255;   } \
    else if (h < 1280){ r = h - 1024; g = 0;      b = 255;   } \
    else              { r = 255;     g = 0;       b = 1535 - h; } \
    r = (r / 2) + min_brightness; \
    g = (g / 2) + min_brightness; \
    b = (b / 2) + min_brightness; \
    (0x80 << 24) | (g << 16) | (b << 8) | r; \
})



