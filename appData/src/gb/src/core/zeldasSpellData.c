// regex formatting to display 16 bits (1 tile) per line with:
// find: (0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],)
// replace: $1\n

#pragma bank 5

#include <gb/gb.h>
#include "bankdata.h"
#include "zeldasInventoryCore.h"

UINT8 tileOffset = 0x00;

UINT8 *spriteMemory[128] = {
(UINT8 *)0x8000, (UINT8 *)0x8010, (UINT8 *)0x8020, (UINT8 *)0x8030, (UINT8 *)0x8040, (UINT8 *)0x8050, (UINT8 *)0x8060, (UINT8 *)0x8070, (UINT8 *)0x8080, (UINT8 *)0x8090, (UINT8 *)0x80A0, (UINT8 *)0x80B0, (UINT8 *)0x80C0, (UINT8 *)0x80D0, (UINT8 *)0x80E0, (UINT8 *)0x80F0,
(UINT8 *)0x8100, (UINT8 *)0x8110, (UINT8 *)0x8120, (UINT8 *)0x8130, (UINT8 *)0x8140, (UINT8 *)0x8150, (UINT8 *)0x8160, (UINT8 *)0x8170, (UINT8 *)0x8180, (UINT8 *)0x8190, (UINT8 *)0x81A0, (UINT8 *)0x81B0, (UINT8 *)0x81C0, (UINT8 *)0x81D0, (UINT8 *)0x81E0, (UINT8 *)0x81F0,
(UINT8 *)0x8200, (UINT8 *)0x8210, (UINT8 *)0x8220, (UINT8 *)0x8230, (UINT8 *)0x8240, (UINT8 *)0x8250, (UINT8 *)0x8260, (UINT8 *)0x8270, (UINT8 *)0x8280, (UINT8 *)0x8290, (UINT8 *)0x82A0, (UINT8 *)0x82B0, (UINT8 *)0x82C0, (UINT8 *)0x82D0, (UINT8 *)0x82E0, (UINT8 *)0x82F0,
(UINT8 *)0x8300, (UINT8 *)0x8310, (UINT8 *)0x8320, (UINT8 *)0x8330, (UINT8 *)0x8340, (UINT8 *)0x8350, (UINT8 *)0x8360, (UINT8 *)0x8370, (UINT8 *)0x8380, (UINT8 *)0x8390, (UINT8 *)0x83A0, (UINT8 *)0x83B0, (UINT8 *)0x83C0, (UINT8 *)0x83D0, (UINT8 *)0x83E0, (UINT8 *)0x83F0,
(UINT8 *)0x8400, (UINT8 *)0x8410, (UINT8 *)0x8420, (UINT8 *)0x8430, (UINT8 *)0x8440, (UINT8 *)0x8450, (UINT8 *)0x8460, (UINT8 *)0x8470, (UINT8 *)0x8480, (UINT8 *)0x8490, (UINT8 *)0x84A0, (UINT8 *)0x84B0, (UINT8 *)0x84C0, (UINT8 *)0x84D0, (UINT8 *)0x84E0, (UINT8 *)0x84F0,
(UINT8 *)0x8500, (UINT8 *)0x8510, (UINT8 *)0x8520, (UINT8 *)0x8530, (UINT8 *)0x8540, (UINT8 *)0x8550, (UINT8 *)0x8560, (UINT8 *)0x8570, (UINT8 *)0x8580, (UINT8 *)0x8590, (UINT8 *)0x85A0, (UINT8 *)0x85B0, (UINT8 *)0x85C0, (UINT8 *)0x85D0, (UINT8 *)0x85E0, (UINT8 *)0x85F0,
(UINT8 *)0x8600, (UINT8 *)0x8610, (UINT8 *)0x8620, (UINT8 *)0x8630, (UINT8 *)0x8640, (UINT8 *)0x8650, (UINT8 *)0x8660, (UINT8 *)0x8670, (UINT8 *)0x8680, (UINT8 *)0x8690, (UINT8 *)0x86A0, (UINT8 *)0x86B0, (UINT8 *)0x86C0, (UINT8 *)0x86D0, (UINT8 *)0x86E0, (UINT8 *)0x86F0,
(UINT8 *)0x8700, (UINT8 *)0x8710, (UINT8 *)0x8720, (UINT8 *)0x8730, (UINT8 *)0x8740, (UINT8 *)0x8750, (UINT8 *)0x8760, (UINT8 *)0x8770, (UINT8 *)0x8780, (UINT8 *)0x8790, (UINT8 *)0x87A0, (UINT8 *)0x87B0, (UINT8 *)0x87C0, (UINT8 *)0x87D0, (UINT8 *)0x87E0, (UINT8 *)0x87F0,
};

/* transforming a 48x16px spell sprite into a format ready for the game requires 3 steps.
 * step 1. convert the png to a tile array using the ggbgfx cli command:
 *         ggbgfx sprite -o spellWand.c .\spell-wand.png
 * step 2. use a regex to split the 12 tiles (each tile is 8x8px and there are 6x2 tiles)
 *         find: (0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],0x[0-9A-F][0-9A-F],)
 *         replace: $1\n
 * step 3. Add a trailing comma to the last element, then reorder the tiles into the required layout for tile memory
 *         find: (0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)(0x.*?\n)
 *         replace: $11$12$9$10$7$8$5$6$3$4$1$2
 */
const unsigned char spellWand[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // A
0x0C,0x0C,0x1E,0x16,0xEF,0xF1,0xEF,0x31,0xEF,0xF1,0x1E,0x16,0x0C,0x0C,0x00,0x00, // B
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 8
0x00,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x41,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00, // 9
0x1C,0x1C,0x3E,0x22,0x7F,0x63,0x7F,0x41,0x22,0x3E,0x1C,0x1C,0x1C,0x14,0x1C,0x1C, // 6
0x1C,0x14,0x1C,0x14,0x1C,0x14,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 4
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 5
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 2
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // 3
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x28,0x38,0x28,0x38,0x28, // 0
0x38,0x38,0x38,0x28,0x38,0x38,0x44,0x7C,0xFE,0x82,0xFE,0xC6,0x7C,0x44,0x38,0x38, // 1
};

const unsigned char spellArrow[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x1C,0x14,0xFE,0xFA,0x3F,0xE5,
0x3F,0xE5,0xFE,0xFA,0x1C,0x14,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x80,0xFF,
0x80,0xFF,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0xC0,0x40,0xE0,0xA0,0xF0,0x50,0xF0,0x70,0xC0,0xC0,0x40,0xC0,0x40,0xC0,
0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x01,0x01,0x03,0x02,0x07,0x05,0x0F,0x0A,0x0F,0x0E,0x03,0x03,0x02,0x03,0x02,0x03,
0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x01,0x01,
0x80,0x80,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,
0x40,0xC0,0x40,0xC0,0xC0,0xC0,0xF0,0x70,0xF0,0x50,0xE0,0xA0,0xC0,0x40,0x80,0x80,
0x01,0x01,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,
0x02,0x03,0x02,0x03,0x03,0x03,0x0F,0x0E,0x0F,0x0A,0x07,0x05,0x03,0x02,0x01,0x01,
};

const unsigned char spellBroadsword[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0xFF,0x01,
0x01,0xFF,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x0A,0x0E,0x77,0x7F,0x97,0xFC,
0x94,0xFF,0x77,0x7F,0x0A,0x0E,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,
0x40,0xC0,0x70,0xF0,0xD0,0xF0,0x20,0xE0,0xC0,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x01,0x01,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,
0x03,0x02,0x0F,0x0E,0x0B,0x0F,0x04,0x07,0x03,0x03,0x02,0x03,0x02,0x03,0x01,0x01,
0x80,0x80,0x40,0xC0,0x40,0xC0,0xC0,0xC0,0x20,0xE0,0xD0,0xF0,0xF0,0x70,0xC0,0x40,
0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0x80,0x80,
0x01,0x01,0x02,0x03,0x02,0x03,0x03,0x03,0x04,0x07,0x0B,0x0F,0x0E,0x0F,0x02,0x03,
0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x01,0x01,
};

const unsigned char spellCalm[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x78,0xFC,0x84,0xFE,0x02,0xFF,0x01,0xFF,0x01,
0xFF,0x01,0xFF,0x01,0xFF,0x01,0xFE,0x02,0xFC,0x84,0x78,0x78,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x0F,0x0E,0x3F,0x30,
0x7F,0x40,0x3F,0x30,0x0F,0x0E,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xE0,0xE0,0xF0,0x10,0xF8,0x08,0xFC,0x04,0xFC,0x04,0xFC,0x04,0xFC,0x04,
0xF8,0x08,0xF0,0x10,0xE0,0x20,0xE0,0x20,0xE0,0x20,0xC0,0x40,0xC0,0x40,0x80,0x80,
0x00,0x00,0x03,0x03,0x07,0x04,0x0F,0x08,0x1F,0x10,0x1F,0x10,0x1F,0x10,0x1F,0x10,
0x0F,0x08,0x07,0x04,0x03,0x02,0x03,0x02,0x03,0x02,0x01,0x01,0x01,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xE0,0x20,
0xF0,0x10,0xF8,0x08,0xF8,0x08,0xF8,0x08,0xF8,0x08,0xF0,0x10,0xE0,0x20,0xC0,0xC0,
0x00,0x00,0x01,0x01,0x03,0x02,0x03,0x02,0x07,0x04,0x07,0x04,0x07,0x04,0x0F,0x08,
0x1F,0x10,0x3F,0x20,0x3F,0x20,0x3F,0x20,0x3F,0x20,0x1F,0x10,0x0F,0x08,0x07,0x07,
};

const unsigned char spellFeather[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xC1,0x3F,0xE1,0x1F,0x92,0x6E,
0x74,0x8C,0xF8,0x18,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x07,0x05,0x0F,0x08,
0x7E,0x79,0xF9,0x8E,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x70,0x70,0x90,0xF0,0x10,0xF0,0x10,0xF0,0x90,0x70,0x50,0xB0,0x70,0x90,0xF0,0x10,
0xE0,0x60,0xE0,0x20,0xC0,0x40,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x03,0x02,0x07,0x04,0x07,0x04,0x06,0x05,
0x06,0x05,0x05,0x06,0x05,0x06,0x07,0x07,0x07,0x05,0x07,0x05,0x07,0x05,0x02,0x02,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0x40,0xC0,0xC0,
0xE0,0x20,0xE0,0x20,0xA0,0x60,0x20,0xE0,0x20,0xE0,0x20,0xE0,0x20,0xE0,0xE0,0xE0,
0x04,0x04,0x0E,0x0A,0x0E,0x0A,0x0E,0x0A,0x0F,0x0F,0x0B,0x0C,0x0B,0x0C,0x0D,0x0A,
0x0D,0x0A,0x0E,0x09,0x0E,0x09,0x07,0x04,0x04,0x07,0x02,0x03,0x01,0x01,0x00,0x00,
};

const unsigned char spellringsOfFire[] = {
0x00,0x00,0xE0,0xE0,0x10,0xF0,0xE8,0xF8,0x14,0x1C,0x14,0x1C,0x0A,0x0E,0x0A,0x0E,
0x0A,0x0E,0x0A,0x0E,0x14,0x1C,0x14,0x1C,0xE8,0xF8,0x10,0xF0,0xE0,0xE0,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x05,0x07,0x05,0x07,0x0A,0x0E,0x0A,0x0E,
0x0A,0x0E,0x0A,0x0E,0x05,0x07,0x05,0x07,0x02,0x03,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xC0,0x30,0xF0,0xC8,0xF8,0x34,0x3C,0x0A,0x0E,0x0A,0x0E,0x0A,0x0E,
0x34,0x3C,0xC8,0xF8,0x30,0xF0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x03,0x0C,0x0F,0x13,0x1F,0x2C,0x3C,0x50,0x70,0x50,0x70,0x50,0x70,
0x2C,0x3C,0x13,0x1F,0x0C,0x0F,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x30,0xF0,0xC8,0xF8,0x34,0x3C,
0x0A,0x0E,0x0A,0x0E,0x0A,0x0E,0x34,0x3C,0xC8,0xF8,0x30,0xF0,0xC0,0xC0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x0C,0x0F,0x13,0x1F,0x2C,0x3C,
0x50,0x70,0x50,0x70,0x50,0x70,0x2C,0x3C,0x13,0x1F,0x0C,0x0F,0x03,0x03,0x00,0x00,
};

const unsigned char spellFirestorm[] = {
0x00,0x00,0x00,0x00,0xE0,0xE0,0xD8,0x38,0x74,0x8C,0xFA,0x06,0xEA,0x76,0x35,0xFB,
0x35,0xFB,0xEA,0x76,0xFA,0x06,0x74,0x8C,0xD8,0x38,0xE0,0xE0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x03,0x04,0x07,0x02,0x03,0x0D,0x0E,0x33,0x3C,0x5F,0x60,
0x5F,0x60,0x33,0x3C,0x0D,0x0E,0x02,0x03,0x04,0x07,0x03,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0x60,0xE0,0x90,0x70,0x68,0x98,0xB8,0xC8,0xF4,0xCC,0x7C,0xC4,
0x6C,0x94,0xE4,0x1C,0xD4,0x3C,0xA8,0x68,0xA0,0x60,0xC0,0x40,0x40,0xC0,0x80,0x80,
0x00,0x00,0x01,0x01,0x06,0x07,0x09,0x0E,0x16,0x19,0x1D,0x13,0x2F,0x33,0x3E,0x23,
0x36,0x29,0x27,0x38,0x2B,0x3C,0x15,0x16,0x05,0x06,0x03,0x02,0x02,0x03,0x01,0x01,
0x00,0x00,0x80,0x80,0x40,0xC0,0xC0,0x40,0xA0,0x60,0xA8,0x68,0xD4,0x3C,0xE4,0x1C,
0x6C,0x94,0x7C,0xC4,0xF4,0xCC,0xB8,0xC8,0x68,0x98,0x90,0x70,0x60,0xE0,0x80,0x80,
0x00,0x00,0x01,0x01,0x02,0x03,0x03,0x02,0x05,0x06,0x15,0x16,0x2B,0x3C,0x27,0x38,
0x36,0x29,0x3E,0x23,0x2F,0x33,0x1D,0x13,0x16,0x19,0x09,0x0E,0x06,0x07,0x01,0x01,
};

const unsigned char spellGoldNecklace[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x02,0xFE,0x79,0x87,0xFD,0x03,
0xFD,0x03,0xFD,0x03,0x79,0x87,0x02,0xFE,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0xA6,0xE7,0x58,0x7F,
0x23,0x3C,0x18,0x1F,0x06,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE0,0xE0,0x10,0xF0,0xC8,0x38,0xE8,0x18,0xE8,0x18,0xE8,0x18,0xE8,0x18,0xC8,0x38,
0x90,0x70,0xA0,0x60,0x20,0xE0,0x40,0xC0,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,
0x03,0x03,0x04,0x07,0x09,0x0E,0x0B,0x0C,0x0B,0x0C,0x0B,0x0C,0x0B,0x0C,0x09,0x0E,
0x04,0x07,0x02,0x03,0x02,0x03,0x01,0x01,0x01,0x01,0x02,0x03,0x05,0x07,0x02,0x02,
0x40,0x40,0xA0,0xE0,0x40,0xC0,0x80,0x80,0x80,0x80,0x40,0xC0,0x40,0xC0,0x20,0xE0,
0x90,0x70,0xD0,0x30,0xD0,0x30,0xD0,0x30,0xD0,0x30,0x90,0x70,0x20,0xE0,0xC0,0xC0,
0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x02,0x03,0x04,0x07,0x05,0x06,0x09,0x0E,
0x13,0x1C,0x17,0x18,0x17,0x18,0x17,0x18,0x17,0x18,0x13,0x1C,0x08,0x0F,0x07,0x07,
};

const unsigned char spellHammer[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x8C,0xF4,0x8E,0xF6,0x8F,0xF5,
0x8F,0xF5,0x86,0xFE,0x8C,0xF4,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,0x7F,0x40,
0x7F,0x40,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0xC0,0x40,0xF0,0xF0,0xB0,0x50,0x10,0xF0,0x10,0xF0,0x10,0xF0,0xF0,0xF0,
0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0x80,0x80,0x00,0x00,
0x01,0x01,0x03,0x02,0x0F,0x0F,0x0F,0x08,0x08,0x0F,0x08,0x0F,0x08,0x0F,0x0F,0x0F,
0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x01,0x01,0x00,0x00,
0x00,0x00,0x80,0x80,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,
0xF0,0xF0,0x10,0xF0,0x10,0xF0,0x10,0xF0,0xF0,0x10,0xF0,0xF0,0xC0,0x40,0x80,0x80,
0x00,0x00,0x01,0x01,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,
0x0F,0x0F,0x08,0x0F,0x08,0x0F,0x08,0x0F,0x0D,0x0A,0x0F,0x0F,0x03,0x02,0x01,0x01,
};

const unsigned char spellJadeAmulet[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0xFE,0x02,0x87,0x79,0x03,0xFD,
0x03,0xFD,0x03,0xFD,0x87,0x79,0xFE,0x02,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x41,0xE7,0xA6,0x7F,0x58,
0x3C,0x23,0x1F,0x18,0x07,0x06,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE0,0xE0,0xF0,0x10,0x38,0xC8,0x18,0xE8,0x18,0xE8,0x18,0xE8,0x18,0xE8,0x38,0xC8,
0x70,0x90,0x60,0xA0,0xE0,0x20,0xC0,0x40,0xC0,0x40,0x80,0x80,0x00,0x00,0x00,0x00,
0x03,0x03,0x07,0x04,0x0E,0x09,0x0C,0x0B,0x0C,0x0B,0x0C,0x0B,0x0C,0x0B,0x0E,0x09,
0x07,0x04,0x03,0x02,0x03,0x02,0x01,0x01,0x01,0x01,0x03,0x02,0x07,0x05,0x02,0x02,
0x40,0x40,0xE0,0xA0,0xC0,0x40,0x80,0x80,0x80,0x80,0xC0,0x40,0xC0,0x40,0xE0,0x20,
0x70,0x90,0x30,0xD0,0x30,0xD0,0x30,0xD0,0x30,0xD0,0x70,0x90,0xE0,0x20,0xC0,0xC0,
0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x02,0x03,0x02,0x07,0x04,0x06,0x05,0x0E,0x09,
0x1C,0x13,0x18,0x17,0x18,0x17,0x18,0x17,0x18,0x17,0x1C,0x13,0x0F,0x08,0x07,0x07,
};

const unsigned char spellJoust[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0xFF,0x01,
0x01,0xFF,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x77,0x7F,0x97,0xFC,
0x94,0xFF,0x77,0x7F,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,
0x40,0xC0,0x40,0xC0,0xC0,0xC0,0x20,0xE0,0xC0,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x01,0x01,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,
0x03,0x02,0x03,0x02,0x03,0x03,0x04,0x07,0x03,0x03,0x02,0x03,0x02,0x03,0x01,0x01,
0x80,0x80,0x40,0xC0,0x40,0xC0,0xC0,0xC0,0x20,0xE0,0xC0,0xC0,0xC0,0x40,0xC0,0x40,
0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0x80,0x80,
0x01,0x01,0x02,0x03,0x02,0x03,0x03,0x03,0x04,0x07,0x03,0x03,0x02,0x03,0x02,0x03,
0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x01,0x01,
};

const unsigned char spellJadeRing[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x22,0x3E,0xDD,0xFF,0x55,0xF7,0x55,0xF7,
0x55,0xF7,0x55,0xF7,0xDD,0xFF,0x22,0x3E,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x24,0x27,0x5B,0x7F,0xAB,0xFF,
0xAB,0xFF,0x5B,0x7F,0x24,0x27,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE0,0xE0,0x10,0xF0,0xE8,0xF8,0x28,0x38,0xE8,0xF8,0x10,0xF0,0xE0,0xE0,0x20,0xE0,
0xD0,0xF0,0xD0,0xF0,0x20,0xE0,0xC0,0xC0,0x40,0xC0,0xA0,0xE0,0x40,0xC0,0x80,0x80,
0x07,0x07,0x08,0x0F,0x17,0x1F,0x14,0x1C,0x17,0x1F,0x08,0x0F,0x07,0x07,0x04,0x07,
0x0B,0x0F,0x0B,0x0F,0x04,0x07,0x03,0x03,0x02,0x03,0x05,0x07,0x02,0x03,0x01,0x01,
0x80,0x80,0x40,0xC0,0xA0,0xE0,0x40,0xC0,0xC0,0xC0,0x20,0xE0,0xD0,0xF0,0xD0,0xF0,
0x20,0xE0,0xE0,0xE0,0x10,0xF0,0xE8,0xF8,0x28,0x38,0xE8,0xF8,0x10,0xF0,0xE0,0xE0,
0x01,0x01,0x02,0x03,0x05,0x07,0x02,0x03,0x03,0x03,0x04,0x07,0x0B,0x0F,0x0B,0x0F,
0x04,0x07,0x07,0x07,0x08,0x0F,0x17,0x1F,0x14,0x1C,0x17,0x1F,0x08,0x0F,0x07,0x07,
};

const unsigned char spellDagger[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x01,0xFF,
0xFF,0x01,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x0E,0x0A,0x7F,0x77,0xFC,0x97,
0xFF,0x94,0x7F,0x77,0x0E,0x0A,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,
0xC0,0x40,0xF0,0x70,0xF0,0xD0,0xE0,0x20,0xC0,0xC0,0xC0,0x40,0xC0,0x40,0x80,0x80,
0x01,0x01,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,
0x02,0x03,0x0E,0x0F,0x0F,0x0B,0x07,0x04,0x03,0x03,0x03,0x02,0x03,0x02,0x01,0x01,
0x80,0x80,0xC0,0x40,0xC0,0x40,0xC0,0xC0,0xE0,0x20,0xF0,0xD0,0x70,0xF0,0x40,0xC0,
0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x01,0x01,0x03,0x02,0x03,0x02,0x03,0x03,0x07,0x04,0x0F,0x0B,0x0F,0x0E,0x03,0x02,
0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x01,0x01,
};

const unsigned char spellNoise[] = {
0xC0,0xC0,0xA0,0xE0,0x50,0x70,0x28,0x38,0x14,0x1C,0x8A,0x8E,0x4A,0xCE,0x45,0xC7,
0x45,0xC7,0x4A,0xCE,0x8A,0x8E,0x14,0x1C,0x28,0x38,0x50,0x70,0xA0,0xE0,0xC0,0xC0,
0x00,0x00,0x00,0x00,0x0C,0x0C,0x0A,0x0E,0x65,0x67,0x52,0x73,0x29,0x39,0x29,0x39,
0x29,0x39,0x29,0x39,0x52,0x73,0x65,0x67,0x0A,0x0E,0x0C,0x0C,0x00,0x00,0x00,0x00,
0x00,0x00,0x80,0x80,0x60,0xE0,0x90,0xF0,0x68,0x78,0x14,0x1C,0x0A,0x0E,0xC5,0xC7,
0x23,0xE3,0xD0,0xF0,0x28,0x38,0x14,0x1C,0xCC,0xCC,0x20,0xE0,0xD0,0xF0,0x30,0x30,
0x00,0x00,0x01,0x01,0x06,0x07,0x09,0x0F,0x16,0x1E,0x28,0x38,0x50,0x70,0xA3,0xE3,
0xC4,0xC7,0x0B,0x0F,0x14,0x1C,0x28,0x38,0x33,0x33,0x04,0x07,0x0B,0x0F,0x0C,0x0C,
0x00,0x00,0x30,0x30,0xD0,0xF0,0x20,0xE0,0xCC,0xCC,0x14,0x1C,0x28,0x38,0xD0,0xF0,
0x23,0xE3,0xC5,0xC7,0x0A,0x0E,0x14,0x1C,0x68,0x78,0x90,0xF0,0x60,0xE0,0x80,0x80,
0x00,0x00,0x0C,0x0C,0x0B,0x0F,0x04,0x07,0x33,0x33,0x28,0x38,0x14,0x1C,0x0B,0x0F,
0xC4,0xC7,0xA3,0xE3,0x50,0x70,0x28,0x38,0x16,0x1E,0x09,0x0F,0x06,0x07,0x01,0x01,
};

const unsigned char spellPyros[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x98,0x00,0x68,0x90,0xC8,0xB0,0xA8,0xF0,0xF6,0xF8,0x35,0xFA,0x93,0x7E,0xBB,0x5E,
0xEB,0x1E,0xED,0x1E,0xED,0x1E,0xDA,0x3C,0x32,0xFC,0xE4,0xF8,0x18,0xE0,0xE0,0x00,
0x19,0x00,0x16,0x09,0x13,0x0D,0x15,0x0F,0x6F,0x1F,0xAC,0x5F,0xC9,0x7E,0xDD,0x7A,
0xD7,0x78,0xB7,0x78,0xB7,0x78,0x5B,0x3C,0x4C,0x3F,0x27,0x1F,0x18,0x07,0x07,0x00,
0x98,0x98,0x68,0xF8,0xC8,0x78,0xA8,0x58,0xF6,0x0E,0x35,0xCF,0x93,0xED,0xBB,0xE5,
0xEB,0xF5,0xED,0xF3,0xED,0xF3,0xDA,0xE6,0x32,0xCE,0xE4,0x1C,0x18,0xF8,0xE0,0xE0,
0x19,0x19,0x16,0x1F,0x13,0x1E,0x15,0x1A,0x6F,0x70,0xAC,0xF3,0xC9,0xB7,0xDD,0xA7,
0xD7,0xAF,0xB7,0xCF,0xB7,0xCF,0x5B,0x67,0x4C,0x73,0x27,0x38,0x18,0x1F,0x07,0x07,
};

const unsigned char spellRoarStick[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x01,0xFF,
0x31,0xFF,0x0E,0xFE,0x88,0xF8,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,0x40,0x7F,
0x40,0x7F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0x40,0xC0,0x40,0xC0,0x60,0xE0,0x90,0xF0,0x90,0xF0,0x10,0xF0,0x20,0xE0,
0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,0x00,0x00,
0x01,0x01,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,
0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x01,0x01,0x00,0x00,
0x00,0x00,0x80,0x80,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,
0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x00,0x00,0x01,0x01,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,
0x04,0x07,0x08,0x0F,0x09,0x0F,0x09,0x0F,0x06,0x07,0x02,0x03,0x02,0x03,0x01,0x01,
};

const unsigned char spellAxe[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0xFE,0xCE,0x79,0xCF,
0x79,0xCF,0xFE,0x86,0xEE,0x12,0xFC,0x84,0x78,0x78,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x80,0xFF,
0x80,0xFF,0x7F,0x7F,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0x60,0xE0,0x70,0xD0,0xF8,0x88,0xD8,0x28,0xF8,0x08,0xF8,0x88,0x70,0xD0,
0x60,0xE0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x01,0x01,0x02,0x03,0x02,0x03,0x03,0x03,0x07,0x04,0x07,0x04,0x03,0x03,0x02,0x03,
0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x01,0x01,
0x80,0x80,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x40,0xC0,
0x40,0xC0,0xC0,0xC0,0xE0,0x20,0xE0,0x20,0xC0,0xC0,0x40,0xC0,0x40,0xC0,0x80,0x80,
0x01,0x01,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x02,0x03,0x06,0x07,
0x0E,0x0B,0x1F,0x11,0x1F,0x10,0x1B,0x14,0x1F,0x11,0x0E,0x0B,0x06,0x07,0x01,0x01,
};

const unsigned char spellTurquoiseRing[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x78,0x84,0xFC,0x32,0xCE,0x79,0x87,0xFD,0x03,
0xFD,0x03,0xFD,0x03,0x79,0x87,0x32,0xCE,0x84,0xFC,0x78,0x78,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x0E,0x0F,0x30,0x3F,
0x47,0x78,0x30,0x3F,0x0E,0x0F,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE0,0xE0,0x10,0xF0,0xC8,0x38,0xE4,0x1C,0xF4,0x0C,0xF4,0x0C,0xE4,0x1C,0xC8,0x38,
0x90,0x70,0xA0,0x60,0xA0,0x60,0x20,0xE0,0x40,0xC0,0x40,0xC0,0x80,0x80,0x00,0x00,
0x03,0x03,0x04,0x07,0x09,0x0E,0x13,0x1C,0x17,0x18,0x17,0x18,0x13,0x1C,0x09,0x0E,
0x04,0x07,0x02,0x03,0x02,0x03,0x02,0x03,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x40,0xC0,0x40,0xC0,0x40,0xC0,0x20,0xE0,
0x90,0x70,0xC8,0x38,0xE8,0x18,0xE8,0x18,0xC8,0x38,0x90,0x70,0x20,0xE0,0xC0,0xC0,
0x00,0x00,0x01,0x01,0x02,0x03,0x02,0x03,0x04,0x07,0x05,0x06,0x05,0x06,0x09,0x0E,
0x13,0x1C,0x27,0x38,0x2F,0x30,0x2F,0x30,0x27,0x38,0x13,0x1C,0x08,0x0F,0x07,0x07,
};

const unsigned char spellBoomerang[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x40,0xC0,0xA0,0x60,0xD0,0x30,0xF0,0x10,
0xF0,0x10,0xD0,0x30,0xA0,0x60,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0x0F,0x0E,0x09,0x0B,0x0C,0x05,0x06,0x02,0x03,0x01,0x01,
0x01,0x01,0x02,0x03,0x05,0x06,0x0B,0x0C,0x0E,0x09,0x0F,0x0F,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xA0,0x60,0xD0,0x30,0xE8,0x18,
0xB4,0xCC,0x5C,0x64,0x2C,0x34,0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x05,0x06,0x0B,0x0C,0x17,0x18,
0x2D,0x33,0x3A,0x26,0x34,0x2C,0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x2C,0x34,0x5C,0x64,0xB4,0xCC,
0xE8,0x18,0xD0,0x30,0xA0,0x60,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x34,0x2C,0x3A,0x26,0x2D,0x33,
0x17,0x18,0x0B,0x0C,0x05,0x06,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void FindFirstSpellTile() BANKED
{
    while (tileOffset == 0) {
        for (UINT8 i = 0; i < 128; i++)
        {
            if (*spriteMemory[i] == 0xff && *(spriteMemory[i] + 1) == 0xc3 &&
                *(spriteMemory[i] + 2) == 0xff && *(spriteMemory[i] + 3) == 0x99 &&
                *(spriteMemory[i] + 4) == 0xff && *(spriteMemory[i] + 5) == 0x99 &&
                *(spriteMemory[i] + 6) == 0xff && *(spriteMemory[i] + 7) == 0xc1 &&
                *(spriteMemory[i] + 8) == 0xff && *(spriteMemory[i] + 9) == 0xf9 &&
                *(spriteMemory[i] + 10) == 0xff && *(spriteMemory[i] + 11) == 0x99 &&
                *(spriteMemory[i] + 12) == 0xff && *(spriteMemory[i] + 13) == 0xc3 &&
                *(spriteMemory[i] + 14) == 0xff && *(spriteMemory[i] + 15) == 0xff)
            {
                tileOffset = i;
                break;
            }
        }
    }
}

void LoadSpell(UINT16 equipped) BANKED
{
    FindFirstSpellTile();
    
    switch (equipped) {
        case ZELDA_WEAPON_BOWANDARROW:
            set_sprite_data(tileOffset, 12, spellArrow);
            break;
        case ZELDA_WEAPON_BROADSWORD:
            set_sprite_data(tileOffset, 12, spellBroadsword);
            break;
        case ZELDA_WEAPON_CALM:
            set_sprite_data(tileOffset, 12, spellCalm);
            break;
        case ZELDA_WEAPON_FEATHER:
            set_sprite_data(tileOffset, 12, spellFeather);
            break;
        case ZELDA_WEAPON_RINGSOFFIRE:
            set_sprite_data(tileOffset, 12, spellringsOfFire);
            break;
        case ZELDA_WEAPON_FIRESTORM:
            set_sprite_data(tileOffset, 12, spellFirestorm);
            break;
        case ZELDA_WEAPON_GOLDNECKLACE:
            set_sprite_data(tileOffset, 12, spellGoldNecklace);
            break;
        case ZELDA_WEAPON_HAMMER:
            set_sprite_data(tileOffset, 12, spellHammer);
            break;
        case ZELDA_WEAPON_JADEAMULET:
            set_sprite_data(tileOffset, 12, spellJadeAmulet);
            break;
        case ZELDA_WEAPON_JOUST:
            set_sprite_data(tileOffset, 12, spellJoust);
            break;
        case ZELDA_WEAPON_JADERING:
            set_sprite_data(tileOffset, 12, spellJadeRing);
            break;
        case ZELDA_WEAPON_DAGGER:
            set_sprite_data(tileOffset, 12, spellDagger);
            break;
        case ZELDA_WEAPON_NOISE:
            set_sprite_data(tileOffset, 12, spellNoise);
            break;
        case ZELDA_WEAPON_PYROS:
            set_sprite_data(tileOffset, 12, spellPyros);
            break;
        case ZELDA_WEAPON_ROARSTICK:
            set_sprite_data(tileOffset, 12, spellRoarStick);
            break;
        case ZELDA_WEAPON_SHORTAXE:
            set_sprite_data(tileOffset, 12, spellAxe);
            break;
        case ZELDA_WEAPON_TURQUOISERING:
            set_sprite_data(tileOffset, 12, spellTurquoiseRing);
            break;
        case ZELDA_WEAPON_BOOMERANG:
            set_sprite_data(tileOffset, 12, spellBoomerang);
            break;
        default:
            set_sprite_data(tileOffset, 12, spellWand);
    }
}
