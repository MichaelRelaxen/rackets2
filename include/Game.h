/*--------------------------------------------------
---------------------Functions----------------------
--------------------------------------------------*/
// Call PS3 lv2 syscalls. Function comes from the lv2.s file.
#define syscall ((int (*)(int, ...))0x10bbd00)

// Used for copying memory. Arguments: destination, source, size
#define memcpy ((void (*)(void*, void*, int))0x119a97c)

// Used for setting memory. Arguments: destination, value to set, size
#define memset ((void (*)(void*, char, int))0x011a4fec)

// Spawn plat bolt on a normal level (0x46e). arg: coords, slot, cuboid id, cuboid id
#define spawn_game_bolt ((Moby* (*)(float*, unsigned int, unsigned int, unsigned int))0x0ccbe40)

// Spawn plat bolt on a ship level (0x126c): coords, slot, cuboid id, cuboid id
#define spawn_ship_bolt ((Moby* (*)(float*, unsigned int, unsigned int, unsigned int))0x0020f40)

// Sets moby's state to -3, effectively despawning it. arg: moby ptr
#define despawn_moby ((void (*)(Moby*))0xb575ec)

// Used for drawing text. Needs to be called at a specific point in the draw loop.
// Arguments: x, y, color, text, max_length
#define text_medium_left ((void (*)(int, int, unsigned int, char*, int))0xb14624)
#define text_medium_center ((void (*)(int, int, unsigned int, char*, int))0xb14a44)
#define text_medium_right ((void (*)(int, int, unsigned int, char*, int))0xb142b8)

#define text_small_right ((void (*)(int, int, unsigned int, char*, int))0xb14784)
#define text_small_center ((void (*)(int, int, unsigned int, char*, int))0xb0e960)
#define text_small_left ((void (*)(int, int, unsigned int, char*, int))0xb0e758)

#define text_large_center ((void (*)(int, int, unsigned int, char*, int))0xb14d54)
#define text_large_right ((void (*)(int, int, unsigned int, char*, int))0xb1331c)

#define text_large_as_fuck ((void (*)(int, int, unsigned int, char*, int))0xb14ebc)

#define draw_box ((void (*)(int, int, int, int, int, char))0xb2e98c)

// #define text_opt_draw ((void (*)(textOpt*, unsigned int, char*, int))0xb14ebc)

// Toasts a message? args: formatted txt, length.
#define toast_message ((void (*)(char*, int))0x0b55218)

// Used for formatting strings.
// Arguments: destination, format, ...
#define sprintf ((void (*)(char*, char*, ...))0x11a2154)

// Print to tty console. 
// Arguments: format, ...
#define printf ((void (*)(char*, ...))0x10d4a1c)

// Get current controller inputs etc. Args: Port no, cellPadGetData struct.
#define cellPadGetData ((int32_t (*)(uint32_t, cellPadData *))0x122479C)

// Arguments: unk, buf
#define perform_load ((void (*)(int, void*))0x83250)

// Arguments: Mode to save
#define save_handler ((void (*)(int))0x82e08)
/*--------------------------------------------------
---------------------Variables----------------------
--------------------------------------------------*/

#define render_all_region ((void*)0x156B100)

// A pointer to the current save data info in memory.
#define savedata_info (*((void**)0x1410E50))
// A pointer path to the current save data buffer.
#define savedata_buf (*(void**)((int)savedata_info + 4))

// Array of all bolts that have been collected. 4 bytes per planet indexed by planet ID 
#define collected_bolts_array ((char*)0x1562540)
// Table of how how many bolts you can have in the ship menu, indexed by planet ID.
#define game_max_bolts_table ((int*) 0x013453f8) 

// Frames since spawning on either death or just landing on a planet.
#define frames_since_spawn (*((int*)0x1480470))
// Frames since landing on a planet.
#define frames_since_reload (*((int*)0x1F67130))
// Count of how many times the player has died.
#define death_count (*((int*)0x1569774))
// Current gamestate.
#define gamestate (*((int*)0x156B064))
// The player's current state.
#define player_state (*((int*)0x1481474))
// Currently loaded planet.
#define current_planet (*((int*)0x1329A3C))
// The player's current position.
#define player_coords (*((Vec4*)0x147F260))
// Weapon that's currently being held.
#define current_weapon (*((int*)0x14814C4))

// Ratchet's current speed value.
#define neutral_speed (*((float*)0x147F394))


// Modifier for how large the scale of normal 0x46e plat bolts should be.
#define game_bolt_scale ((float*)0x01373EA0)
// Modifier for how large the scale of ship level 0x126c plat bolts should be.
#define ship_bolt_scale ((float*)0x013182A0)
// Acceleration for the jump_pad
#define jump_pad_accel ((float*)0x13185B8)

// Current type of loading screen that's being shown
#define load_screen_type (*((int*)0x147A254))
// Count of how many load screens have been shown.
#define load_screen_count (*((int*)0x147A258))
// Whether or not the game is currently loading `destination_planet`.
#define should_load (*((int*)0x156B050))
// Planet that's currently being loaded.
#define destination_planet (*((int*)0x156B054))

#define load_in_level ((!should_load) && (old_should_load))

#define button_bitmask (*((uint*)0x147A430))

#define RIGHT_STICK_X (*(float *)0x147A60C)
#define RIGHT_STICK_Y (*(float *)0x147A610)
#define LEFT_STICK_X  (*(float *)0x147A614)
#define LEFT_STICK_Y  (*(float *)0x147A618)

// Weapons/Gadget IDs
#define ELECTROLYZER 38

// Save handler modes
#define SAVE_MENU 0
#define LOAD_MENU 1
#define AUTO_SAVE 3


// Gamestates
#define INGAME 0
#define CINEMATIC 1
#define IN_LEVEL_MOVIE 2
#define PAUSED 3
#define LOADING 6
#define IN_ELECTROLYZER 7

// Planet IDs
#define MAIN_MENU -1
#define ARANOS_TUTORIAL 0
#define OOZLA 1
#define MAKTAR 2
#define ENDAKO 3
#define BARLOW 4
#define FELTZIN 5
#define NOTAK 6
#define SIBERIUS 7
#define TABORA 8
#define DOBBO 9
#define HRUGIS 10
#define JOBA 11
#define TODANO 12
#define BOLDAN 13
#define ARANOS_REVISIT 14
#define GORN 15
#define SNIVELAK 16
#define SMOLG 17
#define DAMOSEL 18
#define GRELBIN 19
#define YEEDIL 20
#define MUSEUM 21
#define DOBBO_ORBIT 22
#define DAMOSEL_ORBIT 23
#define SHIP_SHACK 24
#define WUPASH 25
#define JAMMING_ARRAY 26

// Syscalls
#define sys_usleep 0x8d
#define sys_fs_open 0x321
#define sys_fs_read 0x322
#define sys_fs_write 0x323
#define sys_fs_close 0x324