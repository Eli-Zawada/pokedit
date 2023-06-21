#pragma once
#include "guicodes.h"


#ifndef ADDRESS
#define ADDRESS
#define ADD_LEVEL_TABLE 0
extern const unsigned int GS_LEVEL_TABLE;
extern const unsigned int GS_JP_LEVEL_TABLE;
extern const unsigned int C_LEVEL_TABLE;
extern const unsigned int C_JP_LEVEL_TABLE;

#define ADD_EGG_TABLE 1
extern const unsigned int GS_EGG_TABLE;
extern const unsigned int GS_JP_EGG_TABLE;
extern const unsigned int C_EGG_TABLE;
extern const unsigned int C_JP_EGG_TABLE;

#define ADD_BASE_STATS 2
extern const unsigned int GS_BASE_STATS;
extern const unsigned int GS_JP_BASE_STATS;
extern const unsigned int C_BASE_STATS;
extern const unsigned int C_JP_BASE_STATS;

#define ADD_TRAINER_TABLE 3
extern const unsigned int GS_TRAINER_TABLE;
extern const unsigned int GS_JP_TRAINER_TABLE;
extern const unsigned int C_TRAINER_TABLE;
extern const unsigned int C_JP_TRAINER_TABLE;

#define ADD_TRAINER_CLASSES 4
extern const unsigned int GS_TRAINER_TYPES;
extern const unsigned int GS_JP_TRAINER_TYPES;
extern const unsigned int C_TRAINER_TYPES;
extern const unsigned int C_JP_TRAINER_TYPES;

#define ADD_MAP_HEADER_TABLE 5
extern const unsigned int GS_MAP_TABLE;
extern const unsigned int GS_JP_MAP_TABLE;
extern const unsigned int C_MAP_TABLE;
extern const unsigned int C_JP_MAP_TABLE;

#define ADD_MAP_NAME_TABLE 6
extern const unsigned int GS_LOCATION_NAME_TABLE;
extern const unsigned int GS_JP_LOCATION_NAME_TABLE;
extern const unsigned int C_LOCATION_NAME_TABLE;
extern const unsigned int C_JP_LOCATION_NAME_TABLE;

#define ADD_JOHTO_GRASS 7
extern const unsigned int GS_JOHTO_GRASS;
extern const unsigned int GS_JP_JOHTO_GRASS;
extern const unsigned int C_JOHTO_GRASS;
extern const unsigned int C_JP_JOHTO_GRASS;

#define ADD_KANTO_GRASS 8
extern const unsigned int GS_KANTO_GRASS;
extern const unsigned int GS_JP_KANTO_GRASS;
extern const unsigned int C_KANTO_GRASS;
extern const unsigned int C_JP_KANTO_GRASS;

#define ADD_JOHTO_SURF 9
extern const unsigned int GS_JOHTO_SURF;
extern const unsigned int GS_JP_JOHTO_SURF;
extern const unsigned int C_JOHTO_SURF;
extern const unsigned int C_JP_JOHTO_SURF;

#define ADD_KANTO_SURF 10
extern const unsigned int GS_KANTO_SURF;
extern const unsigned int GS_JP_KANTO_SURF;
extern const unsigned int C_KANTO_SURF;
extern const unsigned int C_JP_KANTO_SURF;

#define ADD_SWARM_GRASS 11
extern const unsigned int GS_SWARM_GRASS;
extern const unsigned int GS_JP_SWARM_GRASS;
extern const unsigned int C_SWARM_GRASS;
extern const unsigned int C_JP_SWARM_GRASS;

#define ADD_SWARM_SURF 12
extern const unsigned int GS_SWARM_SURF;
extern const unsigned int GS_JP_SWARM_SURF;
extern const unsigned int C_SWARM_SURF;
extern const unsigned int C_JP_SWARM_SURF;

#define ADD_POKEMON_COLORS 13
extern const unsigned int GS_POKEMON_COLORS;
extern const unsigned int GS_JP_POKEMON_COLORS;
extern const unsigned int C_POKEMON_COLORS;
extern const unsigned int C_JP_POKEMON_COLORS;

#define ADD_MARTS 14
extern const unsigned int GS_MARTS;

#define ADD_MARTS_TOTAL 15
extern const unsigned int GS_MARTS_TOTAL;

#define ADD_TM_MOVES 16
extern const unsigned int GS_TM_MOVES;

#define ADD_ITEMS 17
extern const unsigned int GS_ITEMS;

#define ADD_ITEM_STR_PNTR 18
extern const unsigned int GS_ITEM_STR_PNTR;

#define ADD_TRNR_STR_PNTR 19
extern const unsigned int GS_TRNR_STR_PNTR;

#define ADD_POKE_STR_PNTR 20
extern const unsigned int GS_POKE_STR_PNTR;

#define ADD_MOVE_STR_PNTR 21
extern const unsigned int GS_MOVE_STR_PNTR;
#endif

unsigned int GetAddress(int type);

void SetAddress(int type, unsigned int address);