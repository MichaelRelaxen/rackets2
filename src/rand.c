#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define rand_count  (*((volatile uint32_t *)0x1800000))
#define last_caller  (*((volatile uint32_t *)0x1800004))
#define SCRAMBLE_FRAME(f) \
    ((uint32_t)((((f) * 0x45d9f3bU) ^ ((f) >> 3)) * 0x45d9f3bU) ^ \
               ((f) * 0x27d4eb2dU))

#define SCRAMBLE_FRAME_FAST(f)   ((uint32_t)(((f) ^ ((f) >> 3)) * 0x27d4eb2dU))



register unsigned int ctr asm("ctr");
register unsigned int lr asm("lr");

register uint32_t *r1 asm("r1");

#define _caller (*((uint32_t *)(*(r1 + 1)) + 5))

// not using this but yea sure ok whatever
#define get_func_that_calls_rand() ({ \
  int32_t o = (int32_t)(*((uint32_t *)(_caller - 4)) & 0x03FFFFFC); \
  (o & 0x02000000) ? ((_caller - 4) + (o | 0xFC000000)) : ((_caller - 4) + o); \
})

// i have no idea anymore
#define caller ((ctr != 0) ? ctr : ((lr < 0xB5d500) ? (lr & 0xFFFF0000) : (_caller)))

uint32_t _start(void)
{
    if (last_caller != caller) {
        last_caller = caller;
        rand_count = 1;
    } else {
        rand_count += 1000;
    }

    return SCRAMBLE_FRAME_FAST(frames_since_reload + rand_count + rng_nudge) /*& 0x3fffffff*/;
}