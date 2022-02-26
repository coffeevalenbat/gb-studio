#include <gb/gb.h>
#include "zeldasInventoryCore.h"

// custom tilesets and tilemaps for the inventory screen
// -----------------------------------------------------
const unsigned char staticTileset[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC3,0xC3,0xBD,0xBD,0xBD,0xBD,0x7D,0x7D,0x63,0x63,0x7B,0x7B,0x85,0x85,0xFF,0xFF,
0xDD,0xDD,0xDD,0xDD,0xBB,0xBB,0xBB,0xBB,0x77,0x77,0x77,0x77,0x8F,0x8F,0xFF,0xFF,
0xC1,0xC1,0xDF,0xDF,0xDF,0xDF,0x83,0x83,0xBF,0xBF,0x7F,0x7F,0x03,0x03,0xFF,0xFF,
0xC3,0xC3,0xBD,0xBD,0xBF,0xBF,0xC7,0xC7,0xFB,0xFB,0x7B,0x7B,0x87,0x87,0xFF,0xFF,
0x81,0x81,0xEF,0xEF,0xEF,0xEF,0xDF,0xDF,0xDF,0xDF,0xBF,0xBF,0xBF,0xBF,0xFF,0xFF,
0xFD,0xFD,0xF9,0xF9,0xF5,0xF5,0xED,0xED,0xC1,0xC1,0xBD,0xBD,0x7D,0x7D,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x72,0x72,0x8A,0x8A,0x8A,0x8A,0x8A,0x8A,0xAA,0xAA,0x92,0x92,0x69,0x69,
0x00,0x00,0x2E,0x2E,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0xCE,0xCE,
0x00,0x00,0xF8,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x00,0x00,0x71,0x71,0x8A,0x8A,0x82,0x82,0x73,0x73,0x0A,0x0A,0x8A,0x8A,0x72,0x72,
0x00,0x00,0xC8,0xC8,0x28,0x28,0x28,0x28,0xE8,0xE8,0x25,0x25,0x25,0x25,0x22,0x22,
0x00,0x00,0xBE,0xBE,0xA0,0xA0,0xA0,0xA0,0xBC,0xBC,0x20,0x20,0x20,0x20,0x3E,0x3E,
0xC3,0xC3,0xDD,0xDD,0xBD,0xBD,0x83,0x83,0xB7,0xB7,0x77,0x77,0x77,0x77,0xFF,0xFF,
0xBD,0xBD,0xBD,0xBD,0xBB,0xBB,0x6B,0x6B,0x4B,0x4B,0x27,0x27,0x77,0x77,0xFF,0xFF,
0xC3,0xC3,0xDD,0xDD,0xBD,0xBD,0x83,0x83,0xBF,0xBF,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,
0xC3,0xC3,0xBD,0xBD,0xBD,0xBD,0x7D,0x7D,0x7B,0x7B,0x7B,0x7B,0x87,0x87,0xFF,0xFF,
0xDD,0xDD,0xDD,0xDD,0x8D,0x8D,0xAB,0xAB,0xB3,0xB3,0x7B,0x7B,0x7B,0x7B,0xFF,0xFF,
0xF7,0xF7,0xF3,0xF3,0x81,0x81,0x80,0x80,0x81,0x81,0xF3,0xF3,0xF7,0xF7,0xFF,0xFF,
0xF7,0xF7,0xE7,0xE7,0xC0,0xC0,0x80,0x80,0xC0,0xC0,0xE7,0xE7,0xF7,0xF7,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x1C,0x1C,0x3E,0x22,0x71,0x4F,0x60,0x5F,0x60,0x5F,0x40,0x7F,
0x00,0x00,0x00,0x00,0x38,0x38,0x7C,0x44,0x8E,0xF2,0x06,0xFA,0x06,0xFA,0x02,0xFE,
0x20,0x3F,0x10,0x1F,0x08,0x0F,0x04,0x07,0x02,0x03,0x01,0x01,0x00,0x00,0x00,0x00,
0x04,0xFC,0x08,0xF8,0x10,0xF0,0x20,0xE0,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x1E,0x1E,0x3F,0x21,0x3F,0x2D,0x3F,0x2D,0x3F,0x2D,0x3F,0x21,0x1E,0x1E,
0x00,0x00,0x3E,0x3E,0x3E,0x2A,0xFE,0xFE,0xFE,0x02,0xFE,0xFE,0x00,0x00,0x00,0x00
};

// All tile references offset by 194 (0xc2), the number of inventory tiles
const unsigned char questStatusMap[] = {
0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,
0xc3,0xc3,0xc3,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc3,0xc7,0xc8,0xc9,0xc8,0xc5,0xc7,0xc3,0xc3,0xc3,0xc3, // quest status
0xc3,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xc3, // dotted lines
0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,
0xc3,0xc2,0xcb,0xcc,0xcd,0xc2,0xc2,0xc2,0xc2,0xc3,0xc3,0xc2,0xc2,0xc2,0xc2,0xce,0xcf,0xd0,0xc2,0xc3, // quit save
0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xd8,0xd9,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,
0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xda,0xdb,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,
0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,
0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,
0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,
0xc3,0xc3,0xc3,0xc3,0xc8,0xd1,0xc6,0xc9,0xc7,0xc5,0xd1,0xc6,0xc7,0xc3,0xc3,0xc3,0xc3,0xdc,0xdd,0xc3, // treasures
0xc3,0xc3,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xc3,0xc2,0xc2,0xc3,
0xc3,0xd7,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xd6,0xc3,0xc3,0xc3,
0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc2,0xc2,0xc3,
0xc3,0xc3,0xc3,0xc3,0xd2,0xc6,0xc9,0xd3,0xd4,0xd5,0xc7,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc2,0xc2,0xc3, // weapons
0xc3,0xc3,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xc3,0xc3,0xc3,0xc3,
0xc3,0xd7,0xc3,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc3,0xd6,0xc3,0xc3,0xc3,
0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,
};

// pointer to GB Studio variables $06 - $12
UINT16 *_inventoryInteraction = (UINT16 *)0xcb2b;
UINT16 *_inventoryFlags1 = (UINT16 *)0xcb2d;
UINT16 *_inventoryFlags2 = (UINT16 *)0xcb2f;
UINT16 *_inventoryFlags3 = (UINT16 *)0xcb31;
UINT16 *_inventoryFlags4 = (UINT16 *)0xcb33;
UINT16 *_equipped = (UINT16 *)0xcb35;
UINT16 *_overworldFlags = (UINT8 *)0xcb39;

const UINT8 maxItemsOnScreen = 6;
const UINT8 totalWeaponsAvailable = 19;
const UINT8 totalTreasuresAvailable = 40;

UINT8 slot = 0;
unsigned char firstWeaponTile = 0x00;
unsigned char firstTreasureTile = 0x4C;

UINT8 totalWeaponsFound = 0;
UINT8 weaponScrollOffset = 0;
ZELDA_WEAPONS weapons[19];

UINT8 totalTreasuresFound = 0;
UINT8 treasureScrollOffset = 0;
ZELDA_TREASURES treasures[40];

// on screen view of weapons
unsigned char weaponPanel[] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2,
                               0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
// on screen view of treasures
unsigned char treasurePanel[] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2,
                                 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2, 0xC2};

unsigned char equippedPanel[] = {0xC2, 0xC2, 
                                 0xC2, 0xC2};

UBYTE GetBit(UINT16 byte, UINT8 bit)
{
    return (byte & (1 << bit)) != 0;
}

// weapons 1-19 = inventory1 (0-15) + inventory2 (0-2)
// treasures 1-40 = inventory2 (2-15), inventory3 (0-15), inventory4 (0-10)
void IdentifyWeaponsTreasuresFound()
{
    // populate weapons array by interrogate GB Studio
    totalWeaponsFound = 0;
    for (UINT8 i = 0; i < 16; i++)
    {
        // populate weapons
        if (GetBit(*_inventoryFlags1, i)) 
        {
            // when i = 0, i+1 = 1 (ZELDA_WEAPON_WAND)
            weapons[totalWeaponsFound] = i+1;
            totalWeaponsFound++;
        }
    }

    for (UINT8 i = 0; i < 16; i++)
    {
        // populate weapons
        if (i < 3 && GetBit(*_inventoryFlags2, i)) 
        {
            // when i = 0, i+17 = 17 (ZELDA_WEAPON_SHORTAXE)
            weapons[totalWeaponsFound] = i+17;
            totalWeaponsFound++;
        }

        // populate treasures
        if (i > 2 && GetBit(*_inventoryFlags2, i)) 
        {
            // when i = 3, i-2 = 1 (ZELDA_TREASURE_LADDER)
            treasures[totalTreasuresFound] = i-2;
            totalTreasuresFound++;
        }
    }

    for (UINT8 i = 0; i < 16; i++)
    {
        if (GetBit(*_inventoryFlags3, i)) 
        {
            // when i = 0, i+14 = 14 (ZELDA_TREASURE_TICKETA)
            treasures[totalTreasuresFound] = i+14;
            totalTreasuresFound++;
        }
    }

    for (UINT8 i = 0; i < 16; i++)
    {
        if (GetBit(*_inventoryFlags4, i)) 
        {
            // when i = 0, i+30 = 30 (ZELDA_TREASURE_COMPASS5)
            treasures[totalTreasuresFound] = i+30;
            totalTreasuresFound++;
        }
    }
}

void DrawWeaponsTreasures()
{
    // add weapons to on screen weaponPanel
    slot = 0;
    for (UINT8 i = weaponScrollOffset; i < maxItemsOnScreen + weaponScrollOffset; i++)
    {
        for (UINT8 j = 1; j <= totalWeaponsAvailable; j++)
        {
            if (weapons[i] == j) 
            {
                weaponPanel[slot] = firstWeaponTile + ((j-1) * 4);
                weaponPanel[slot + 1] = firstWeaponTile + ((j-1) * 4) + 1;
                weaponPanel[slot + 12] = firstWeaponTile + ((j-1) * 4) + 2;
                weaponPanel[slot + 13] = firstWeaponTile + ((j-1) * 4) + 3;
                slot += 2;
                if (*_equipped == j) 
                {
                    equippedPanel[0] = firstWeaponTile + ((j-1) * 4);
                    equippedPanel[1] = firstWeaponTile + ((j-1) * 4) + 1;
                    equippedPanel[2] = firstWeaponTile + ((j-1) * 4) + 2;
                    equippedPanel[3] = firstWeaponTile + ((j-1) * 4) + 3;
                }
                continue;
            }
        }
    }

    slot = 0;
    for (UINT8 i = treasureScrollOffset; i < maxItemsOnScreen + treasureScrollOffset; i++)
    {
        for (UINT8 j = 1; j <= totalTreasuresAvailable; j++)
        {
            if (treasures[i] == j) 
            {
                treasurePanel[slot] = firstTreasureTile + ((j-1) * 4);
                treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) + 1;
                treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) + 2;
                treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) + 3;
                slot += 2;
                // if (*_equipped == j) 
                // {
                //     equippedPanel[0] = firstWeaponTile + ((j-1) * 4);
                //     equippedPanel[1] = firstWeaponTile + ((j-1) * 4) + 1;
                //     equippedPanel[2] = firstWeaponTile + ((j-1) * 4) + 2;
                //     equippedPanel[3] = firstWeaponTile + ((j-1) * 4) + 3;
                // }
                continue;
            }
        }
    }

    set_bkg_tiles(3, 15, 12, 2, weaponPanel);
    set_bkg_tiles(17, 13, 2, 2, equippedPanel);
    set_bkg_tiles(3, 11, 12, 2, treasurePanel);
}

void ScrollWeaponsRight()
{
    if (weaponScrollOffset < totalWeaponsFound - maxItemsOnScreen)
    {
        weaponScrollOffset++;
        DrawWeaponsTreasures();
    }
}

void ScrollWeaponsLeft()
{
    if (weaponScrollOffset > 0)
    {
        weaponScrollOffset--;
        DrawWeaponsTreasures();
    }
}

void ScrollTreasuresRight()
{
    if (treasureScrollOffset < totalTreasuresFound - maxItemsOnScreen)
    {
        treasureScrollOffset++;
        DrawWeaponsTreasures();
    }
}

void ScrollTreasuresLeft()
{
    if (treasureScrollOffset > 0)
    {
        treasureScrollOffset--;
        DrawWeaponsTreasures();
    }
}

void SelectWeapon(UINT8 weaponSlot) 
{
    *_equipped = weapons[weaponSlot + weaponScrollOffset];
    DrawWeaponsTreasures();
}

void SelectTreasure(UINT8 treasureSlot) 
{
    *_equipped = treasures[treasureSlot + treasureScrollOffset] + totalWeaponsAvailable;
    DrawWeaponsTreasures();
}

// void DrawTreasures()
// {
//     // add weapons to on screen weaponPanel
//     slot = 0;
//     for (UINT8 i = treasureScrollOffset; i < maxItemsOnScreen + treasureScrollOffset; i++)
//     {
//         for (UINT8 j = 1; j <= totalTreasuresAvailable; j++)
//         {
//             if (j < 3)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + ((j-1) * 4);
//                     treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) + 1;
//                     treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) + 2;
//                     treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) + 3;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // special case for bone which requires borrowing a joust tile
//             if (j == 3)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + ((j-1) * 4);
//                     treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) + 1;
//                     treasurePanel[slot + 12] = firstWeaponTile + 42; // reuse joust BL time
//                     treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) + 2;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // items after the bone
//             if (j > 3 && j < 9)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + ((j-1) * 4) -1;
//                     treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4);
//                     treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) + 1;
//                     treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) + 2;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // special case for compasses
//             if (j > 8 && j < 16)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + 103;
//                     treasurePanel[slot + 1] = firstTreasureTile + 118;
//                     treasurePanel[slot + 12] = firstTreasureTile + 104;
//                     treasurePanel[slot + 13] = firstTreasureTile + 104 + j - 7;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // items after the compasses
//             if (j > 15 && j < 24)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + ((j-1) * 4) - 29;
//                     treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) - 29 + 1;
//                     treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) - 29 + 2;
//                     treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) - 29 + 3;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // special case for compasses
//             if (j > 23 && j < 31)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + 101;
//                     treasurePanel[slot + 1] = firstTreasureTile + 118;
//                     treasurePanel[slot + 12] = firstTreasureTile + 102;
//                     treasurePanel[slot + 13] = firstTreasureTile + 104 + j - 22;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // items after the compasses
//             if (j > 30 && j < 38)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + ((j-1) * 4) - 57;
//                     treasurePanel[slot + 1] = firstTreasureTile + ((j-1) * 4) - 57 + 1;
//                     treasurePanel[slot + 12] = firstTreasureTile + ((j-1) * 4) - 57 + 2;
//                     treasurePanel[slot + 13] = firstTreasureTile + ((j-1) * 4) - 57 + 3;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // items after the compasses
//             if (j == 38)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + 83;
//                     treasurePanel[slot + 1] = firstTreasureTile + 84;
//                     treasurePanel[slot + 12] = firstTreasureTile + 91;
//                     treasurePanel[slot + 13] = firstTreasureTile + 92;
//                     slot += 2;
//                     continue;
//                 }
//             }
//             // items after the compasses
//             if (j == 39)
//             {
//                 if (treasures[i] == j) 
//                 {
//                     treasurePanel[slot] = firstTreasureTile + 93;
//                     treasurePanel[slot + 1] = firstTreasureTile + 94;
//                     treasurePanel[slot + 12] = firstTreasureTile + 95;
//                     treasurePanel[slot + 13] = firstTreasureTile + 96;
//                     slot += 2;
//                     continue;
//                 }
//             }
//         }
//     }

//     set_bkg_tiles(3, 11, 12, 2, treasurePanel);
//     set_bkg_tiles(17, 13, 2, 2, equippedPanel);
// }

// void DrawCelestialSignIndicator()
// {
//     unsigned char celestialPanel[16] = {0xc2,0xc3,0xc3,0xc2,
//                                         0xc3,0xd8,0xd9,0xc3,
//                                         0xc3,0xda,0xdb,0xc3,
//                                         0xc2,0xc3,0xc3,0xc2
//                                         };
//     // draw a 0
//     celestialPanel[1] = firstWeaponTile + 181;
    
//     // draw a 1
//     if (GetBit(*_overworldFlags, 0)) celestialPanel[2] = firstWeaponTile + 182;
//     // draw a 2
//     if (GetBit(*_overworldFlags, 1)) celestialPanel[7] = firstWeaponTile + 183;
//     // draw a 3
//     if (GetBit(*_overworldFlags, 2)) celestialPanel[11] = firstWeaponTile + 184;
//     // draw a 4
//     if (GetBit(*_overworldFlags, 3)) celestialPanel[14] = firstWeaponTile + 185;
//     // draw a 5
//     if (GetBit(*_overworldFlags, 4)) celestialPanel[13] = firstWeaponTile + 186;
//     // draw a 6
//     if (GetBit(*_overworldFlags, 5)) celestialPanel[8] = firstWeaponTile + 187;
//     // draw a 7
//     if (GetBit(*_overworldFlags, 6)) celestialPanel[4] = firstWeaponTile + 188;

//     set_bkg_tiles(8, 4, 4, 4, celestialPanel);
// }

void DrawKeyIndicator()
{
    unsigned char keyPanel[16] = {0xc2,0xc2};
    // draw a 0
    keyPanel[0] = firstWeaponTile + 181;
    keyPanel[1] = firstWeaponTile + 181;
    set_bkg_tiles(17, 11, 2, 1, keyPanel);
}

void InitZeldaInventory() 
{
    // load the core tiles that won't change (22 tiles)
    // data starts at 194 to account for inventory item tiles
    set_bkg_data(194, 28, staticTileset);

    // draw the background tiles
    set_bkg_tiles(0, 0, 20, 18, questStatusMap);

    // write 1-7 depending on dungeons complete
    // DrawCelestialSignIndicator();

    // write 0-1 depending on keys found
    DrawKeyIndicator();

    // initialise the weapon tiles
    IdentifyWeaponsTreasuresFound();
    DrawWeaponsTreasures();
}

void CheckForInventoryInteraction() 
{
    if (*_inventoryInteraction != 0) 
    {
        // weapon interaction
        if (*_inventoryInteraction == 1) 
        {
            *_inventoryInteraction = 0;
            ScrollWeaponsLeft();
        }
        if (*_inventoryInteraction == 2) 
        {
            *_inventoryInteraction = 0;
            ScrollWeaponsRight();
        }
        if (*_inventoryInteraction >= 3 && *_inventoryInteraction <= 8) 
        {
            SelectWeapon(*_inventoryInteraction - 3);
            *_inventoryInteraction = 0;
        }

        // treasure interaction
        if (*_inventoryInteraction == 9) 
        {
            *_inventoryInteraction = 0;
            ScrollTreasuresLeft();
        }
        if (*_inventoryInteraction == 10) 
        {
            *_inventoryInteraction = 0;
            ScrollTreasuresRight();
        }
        // if (*_inventoryInteraction >= 11 && *_inventoryInteraction <= 16) 
        // {
        //     SelectTreasure(*_inventoryInteraction - 11);
        //     *_inventoryInteraction = 0;
        // }
    }    
}
