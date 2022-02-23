#ifndef ZELDAS_INVENTORY_CORE_H
#define ZELDAS_INVENTORY_CORE_H

#include <gb/gb.h>

typedef enum
{
    ZELDA_WEAPON_UNDEFINED = 0,
    ZELDA_WEAPON_BOOMERANG,
    ZELDA_WEAPON_BOWANDARROW,
    ZELDA_WEAPON_BROADSWORD,
    ZELDA_WEAPON_CALM,
    ZELDA_WEAPON_DAGGER,
    ZELDA_WEAPON_GOLDNECKLACE,
    ZELDA_WEAPON_FEATHER,
    ZELDA_WEAPON_FIRESTORM,
    ZELDA_WEAPON_HAMMER,
    ZELDA_WEAPON_JADEAMULET,
    ZELDA_WEAPON_JADERING,
    ZELDA_WEAPON_JOUST,
    ZELDA_WEAPON_NOISE,
    ZELDA_WEAPON_PYROS,
    ZELDA_WEAPON_RINGSOFFIRE,
    ZELDA_WEAPON_ROARSTICK,
    ZELDA_WEAPON_SHORTAXE,
    ZELDA_WEAPON_TURQUOISERING,
    ZELDA_WEAPON_WAND,
} ZELDA_WEAPONS;

/**
 * 
 */
void InitWeapons();

/**
 * 
 */
void InitZeldaInventory();

#endif
