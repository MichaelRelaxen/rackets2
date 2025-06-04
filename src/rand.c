#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define rand_count  (*((volatile uint32_t *)0x1800000))
#define last_caller  (*((volatile uint32_t *)0x1800004))
#define SCRAMBLE_FRAME(f) \
    ((uint32_t)((((f) * 0x45d9f3bU) ^ ((f) >> 3)) * 0x45d9f3bU) ^ \
               ((f) * 0x27d4eb2dU))

register unsigned int ctr asm("ctr");
register unsigned int lr asm("lr");

// ctr and 0xffff0000 takes care of enemies syncing? and some particle fx
// 0b5d500.. idk this doesnt work. bolts still are diff for each replay but i cant be bothered rn.
#define _caller ((ctr != 0) ? ctr : ((lr < 0xB5d500) ? (lr & 0xFFFF0000) : (lr & 0xFFFFF000)))

uint32_t _start(void)
{
    if (last_caller != _caller) {
        last_caller = _caller;
        rand_count = 1;
    } else {
        rand_count += 1000;
    }

    return SCRAMBLE_FRAME(frames_since_spawn + rand_count) & 0x3fffffff;
}