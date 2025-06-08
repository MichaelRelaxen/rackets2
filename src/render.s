entry:
    lis     r3, 0x1be
    lwz     r4, 0x30(r3)   # 0x1be0030 should_render
    cmpwi   r4, 1          # dont jump to render if its 1
    blt     .render
    blr
.render:
    ba      0xb101d8
    