entry:
    lis r9, 0x1be
    lwz r10, 0x34(r9)   # 0x1be0034 set_flip
    cmpwi r10, 1
    blt     .flip
    blr
.flip:
    ba 0x10e3b6c
