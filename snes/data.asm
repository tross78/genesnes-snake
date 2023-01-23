.include "hdr.asm"

.section ".rodata1" superfree


tilepal: .incbin "tilesheet.pal"

tileset: .incbin "tilesheet.pic"
tilesetend:

snesfont: .incbin "mariofont.pic"
snesfont_end:

snespal: .incbin "mariofont.pal"


.ends
