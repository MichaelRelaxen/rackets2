rand:
    blr
#     # assume linkreg = 0x0
#     # assume r2 = 0x131d0f0
# 
#     addis    r7, r13, 0x0
#     subi     r9, r7, 0x6ff8
#     lbz      r0, 0x0(r9)
#     cmpwi    cr7, r0, 0x0
#     bne      cr7, rng_already_initalized
# 
#     # Original instructions
#     # addis    r4, r13, 0x0
#     # lis      r0, 0x19
#     # subi     r9, r4, 0x7000
#     # li       r11, 0x8
#     # ori      r0, r0, 0x660d
#     lis      r4, 0x01BE           # r4 = 0x01BE0000
#     lwz      r6, 0x20(r4)         # r6 = frame_timer (0x01BE0020)
#     subi     r9, r13, 0x7000      # r9 = RNG seed location
#     stw      r6, 0x0(r9)          # store frame_timer as RNG seed
#     li       r11, 0x8
#     mtspr    CTR, r11
#     lwz      r6, 0x0(r9)
#     
# 
# seed_update_loop:
#     mullw    r9, r6, r0
#     addis    r9, r9, 0x3c6f
#     subi     r6, r9, 0xca1
#     # bdnz     seed_update_loop
# 
#     subi     r11, r4, 0x7000
#     addis    r3, r13, 0x0
#     lis      r8, 0x19
#     subi     r9, r3, 0x6ff0
#     ori      r8, r8, 0x660d
#     addi     r0, r9, 0x80
#     or       r10, r9, r9
#     
#     nop      # og instr- stw      r6, 0x0(r11)
# 
# buffer_seed_fill_loop:
#     rldicl   r9, r10, 0x0, 0x20
#     addi     r10, r10, 0x4
#     mullw    r11, r6, r8
#     addis    r11, r11, 0x3c6f
#     cmpw     cr7, r10, r0
#     subi     r6, r11, 0xca1
# 
#     nop      # og instr-  stw      r6, 0x0(r9) 
#     bne      cr7, buffer_seed_fill_loop
# 
#     addis    r9, r13, 0x0
#     addis    r5, r13, 0x0
#     subi     r9, r9, 0x6ff0
#     subi     r10, r7, 0x6ff8
#     subi     r8, r4, 0x7000
#     subi     r7, r5, 0x6ff4
#     li       r0, 0x1
#     lwz      r11, 0x7c(r9)
#     stb      r0, 0x0(r10)
# 
#     nop      # og instr- stw      r6, 0x0(r8)
#     stw      r11, 0x0(r7)
# 
# generate_random_num:
#     subi     r8, r4, 0x7000
#     lis      r0, 0x19
#     subi     r7, r5, 0x6ff4
#     ori      r0, r0, 0x660d
#     subi     r10, r3, 0x6ff0
#     lwz      r11, 0x0(r8)
#     lwz      r9, 0x0(r7)
#     mullw    r11, r11, r0
#     rlwinm   r9, r9, 0x2, 0x19, 0x1d
#     addis    r11, r11, 0x3c6f
#     add      r9, r9, r10
#     subi     r11, r11, 0xca1
#     rldicl   r9, r9, 0x0, 0x20
#     stw      r11, 0x0(r8) # this was nopped before.
#     lwz      r3, 0x0(r9)
#     stw      r3, 0x0(r7)
#     rldicl   r3, r3, 0x0, 0x22
#     stw      r11, 0x0(r9)
#     blr
# 
# rng_already_initalized:
#     addis    r5, r13, 0x0
#     addis    r4, r13, 0x0
#     addis    r3, r13, 0x0
#     b        generate_random_num
#     