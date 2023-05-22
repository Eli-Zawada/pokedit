#include "address.h"

const unsigned int GS_LEVEL_TABLE = (unsigned int)0x427bd;
const unsigned int GS_JP_LEVEL_TABLE = (unsigned int)0x4295F;
const unsigned int C_LEVEL_TABLE = (unsigned int)0x425b1;
const unsigned int C_JP_LEVEL_TABLE = (unsigned int)0x42753;

const unsigned int GS_EGG_TABLE = (unsigned int)0x239fe;
const unsigned int GS_JP_EGG_TABLE = (unsigned int)0x23B07;
const unsigned int C_EGG_TABLE = (unsigned int)0x23b11;
const unsigned int C_JP_EGG_TABLE = (unsigned int)0x23b8C;

const unsigned int GS_BASE_STATS = (unsigned int)0x51b0b;
const unsigned int GS_JP_BASE_STATS = (unsigned int)0x51AA9;
const unsigned int C_BASE_STATS = (unsigned int)0x51424;
const unsigned int C_JP_BASE_STATS = (unsigned int)0x514ba;

const unsigned int GS_TRAINER_TABLE = (unsigned int)0x3993E;
const unsigned int GS_JP_TRAINER_TABLE = (unsigned int)0x3995C;
const unsigned int C_TRAINER_TABLE = (unsigned int)0x39999;
const unsigned int C_JP_TRAINER_TABLE = (unsigned int)0x399BA;

const unsigned int GS_TRAINER_TYPES = (unsigned int)0x1B0955;
const unsigned int GS_JP_TRAINER_TYPES = (unsigned int)0x2D2D6;
const unsigned int C_TRAINER_TYPES = (unsigned int)0x2C1EF;
const unsigned int C_JP_TRAINER_TYPES = (unsigned int)0x2D319;

const unsigned int GS_MAP_TABLE = (unsigned int)0x940ED;
const unsigned int GS_JP_MAP_TABLE = (unsigned int)0x940ED;
const unsigned int C_MAP_TABLE = (unsigned int)0x94000;
const unsigned int C_JP_MAP_TABLE = (unsigned int)0x94000;

const unsigned int GS_LOCATION_NAME_TABLE = (unsigned int)0x92382;
const unsigned int GS_JP_LOCATION_NAME_TABLE = (unsigned int)0x924B6;
const unsigned int C_LOCATION_NAME_TABLE = (unsigned int)0x1CA8C3;
const unsigned int C_JP_LOCATION_NAME_TABLE = (unsigned int)0x92557;

const unsigned int GS_JOHTO_GRASS = (unsigned int)0x2AB35;
const unsigned int GS_JP_JOHTO_GRASS = (unsigned int)0x2AC1B;
const unsigned int C_JOHTO_GRASS = (unsigned int)0x2A5E9;
const unsigned int C_JP_JOHTO_GRASS = (unsigned int)0x2A60C;

const unsigned int GS_KANTO_GRASS = (unsigned int)0x2B7C0;
const unsigned int GS_JP_KANTO_GRASS = (unsigned int)0x2B8A6;
const unsigned int C_KANTO_GRASS = (unsigned int)0x2B274;
const unsigned int C_JP_KANTO_GRASS = (unsigned int)0x2B297;

const unsigned int GS_JOHTO_SURF = (unsigned int)0x2B669;
const unsigned int GS_JP_JOHTO_SURF = (unsigned int)0x2B74F;
const unsigned int C_JOHTO_SURF = (unsigned int)0x2B11D;
const unsigned int C_JP_JOHTO_SURF = (unsigned int)0x2B140;

const unsigned int GS_KANTO_SURF = (unsigned int)0x2BD43;
const unsigned int GS_JP_KANTO_SURF = (unsigned int)0x2BE29;
const unsigned int C_KANTO_SURF = (unsigned int)0x2B7F7;
const unsigned int C_JP_KANTO_SURF = (unsigned int)0x2B81A;

const unsigned int GS_SWARM_GRASS = (unsigned int)0x2BE1C;
const unsigned int GS_JP_SWARM_GRASS = (unsigned int)0x2BF02;
const unsigned int C_SWARM_GRASS = (unsigned int)0x2B8D0;
const unsigned int C_JP_SWARM_GRASS = (unsigned int)0x2B8F3;

const unsigned int GS_SWARM_SURF = (unsigned int)0x2BED9;
const unsigned int GS_JP_SWARM_SURF = (unsigned int)0x2BFBF;
const unsigned int C_SWARM_SURF = (unsigned int)0x2B92F;
const unsigned int C_JP_SWARM_SURF = (unsigned int)0x2B952;

const unsigned int GS_POKEMON_COLORS = 0xAD45;
const unsigned int GS_JP_POKEMON_COLORS = 0xACCB;
const unsigned int C_POKEMON_COLORS = 0xA8D6;
const unsigned int C_JP_POKEMON_COLORS = 0xA893;

unsigned int address_level_table = GS_LEVEL_TABLE;
unsigned int address_egg_table = GS_EGG_TABLE;
unsigned int address_base_stats = GS_BASE_STATS;
unsigned int address_trainer_table = GS_TRAINER_TABLE;
unsigned int address_trainer_classes = GS_TRAINER_TYPES;
unsigned int address_map_header_table = GS_MAP_TABLE;
unsigned int address_map_name_table = GS_LOCATION_NAME_TABLE;
unsigned int address_johto_grass = GS_JOHTO_GRASS;
unsigned int address_kanto_grass = GS_KANTO_GRASS;
unsigned int address_johto_surf = GS_JOHTO_SURF;
unsigned int address_kanto_surf = GS_KANTO_SURF;
unsigned int address_swarm_grass = GS_SWARM_GRASS;
unsigned int address_swarm_surf = GS_SWARM_SURF;
unsigned int address_pokemon_colors = GS_POKEMON_COLORS;

unsigned int GetAddress(int type) {

	switch (type) {
	case ADD_LEVEL_TABLE:
		return address_level_table;

	case ADD_EGG_TABLE:
		return address_egg_table;

	case ADD_BASE_STATS:
		return address_base_stats;

	case ADD_TRAINER_TABLE:
		return address_trainer_table;

	case ADD_TRAINER_CLASSES:
		return address_trainer_classes;

	case ADD_MAP_HEADER_TABLE:
		return address_map_header_table;

	case ADD_MAP_NAME_TABLE:
		return address_map_name_table;

	case ADD_JOHTO_GRASS:
		return address_johto_grass;

	case ADD_KANTO_GRASS:
		return address_kanto_grass;

	case ADD_JOHTO_SURF:
		return address_johto_surf;

	case ADD_KANTO_SURF:
		return address_kanto_surf;

	case ADD_SWARM_GRASS:
		return address_swarm_grass;

	case ADD_SWARM_SURF:
		return address_swarm_surf;

	case ADD_POKEMON_COLORS:
		return address_pokemon_colors;
	}

	return 0;
}

void SetAddress(int type, unsigned int address) {

	switch (type) {
	case ADD_LEVEL_TABLE:
		address_level_table = address;
		break;

	case ADD_EGG_TABLE:
		address_egg_table = address;
		break;

	case ADD_BASE_STATS:
		address_base_stats = address;
		break;

	case ADD_TRAINER_TABLE:
		address_trainer_table = address;
		break;

	case ADD_TRAINER_CLASSES:
		address_trainer_classes = address;
		break;

	case ADD_MAP_HEADER_TABLE:
		address_map_header_table = address;
		break;

	case ADD_MAP_NAME_TABLE:
		address_map_name_table = address;
		break;

	case ADD_JOHTO_GRASS:
		address_johto_grass = address;
		break;

	case ADD_KANTO_GRASS:
		address_kanto_grass = address;
		break;

	case ADD_JOHTO_SURF:
		address_johto_surf = address;
		break;

	case ADD_KANTO_SURF:
		address_kanto_surf = address;
		break;

	case ADD_SWARM_GRASS:
		address_swarm_grass = address;
		break;

	case ADD_SWARM_SURF:
		address_swarm_surf = address;
		break;

	case ADD_POKEMON_COLORS:
		address_pokemon_colors = address;
		break;
	}

}