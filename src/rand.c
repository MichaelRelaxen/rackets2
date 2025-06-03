#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define rand_count  (*((volatile uint32_t *)0x1800000))
#define last_caller  (*((volatile uint32_t *)0x1800004))
#define SCRAMBLE_FRAME(f) \
    (((uint32_t)((((f) * 0x45d9f3bU) ^ ((f) >> 3)) * 0x45d9f3bU) ^ \
               ((f) * 0x27d4eb2dU)) | ((f) == 0 ? 0xDEADBEEF : 0))

uint32_t _start(void)
{   
    if (last_caller != (((uint32_t)__builtin_return_address(0)) /*& 0xffffff00*/)) {
        last_caller = (((uint32_t)__builtin_return_address(0)) /*& 0xffffff00*/);
        rand_count = 1;
    } else {
        rand_count += 1000;
    }
    uint32_t frame = frames_since_spawn + rand_count;
    
    return SCRAMBLE_FRAME(frame) & 0x3fffffff;
}

// TODO: Fix particle rand update funcs
/*
0xb5abcc
0xB5D258
0xb5d25c
0xb5b188
0xb5d56c 
0xb5d53c
0xb5d1e0
0xb5b118 // rain and fuck idk smolg jumppad particle
0xb9ce48
0xB9CDF4
0xb9ce90
0xB5D504

|| (uint32_t)__builtin_return_address(0) < 0xBA0000
im not gonna cap bro i cant be bothered 4 dis shit rn fuck this

I'm putting this here so if I ever decide to go back to it I won't completely forgot wtf I was tryna do here sorry if its rambling.

The motive is to have RNG that is fully controlled and consistent just from frame_timer, to avoid desyncs.
So the rand count and last caller thingy is all just to give the SAME RNG for every single call to rand(). 
If some return addr calls rand() multiple times it'll increment rand_count, re-scrambling the RNG
This gives us a new RNG value for any return addr that calls it multiple times

It seems to work for enemies syncing but particle effects are all fucked. 
Using __builtin_return_address(0) gets lr, which points to the instruction after the call.
If a function has multiple calls to rand(), each one gives a different lr, so the logic thinks it's a new caller every time → rand_count gets reset repeatedly.
This causes all those calls to return the same scrambled value, breaking effects like particles
*/