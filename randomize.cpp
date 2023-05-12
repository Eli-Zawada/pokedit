#include "randomencounters.h"

#include "address.h"
#include "pointertools.h"
#include "profile.h"
#include "main.h"
#include "guicodes.h"

std::vector<random_pokemon> LoadPokemonProfile() {
	return std::vector<random_pokemon> {
		bulbasaur, ivysaur, venusaur, charmander, charmeleon, charizard, squirtle, wartortle, blastoise,
		caterpie, metapod, butterfree, weedle, kakuna, beedrill, pidgey, pidgeotto, pidgeot, rattata,
		ratticate, spearow, fearow, ekans, arbok, pikachu, raichu, sandshrew, sandslash, nidoranf,
		nidorina, nidoqueen, nidoranm, nidorino, nidoking, clefairy, clefable, vulpix, ninetails,
		jigglypuff, wigglytuff, zubat, golbat, oddish, gloom, vileplume, paras, parasect, venonat,
		venomoth, diglett, dugtrio, meowth, persian, psyduck, golduck, mankey, primeape, growlithe,
		arcanine, poliwag, poliwhirl, poliwrath, abra, kadabra, alakazam, machop, machoke, machamp,
		bellsprout, weepinbell, victreebel, tentacool, tentacruel, geodude, graveler, golem, ponyta,
		rapidash, slowpoke, slowbro, magnemite, magneton, farfetchd, doduo, dodrio, seel, dewgong,
		grimer, muk, shellder, cloyster, gastly, haunter, gengar, onix, drowzee, hypno, krabby, kingler, 
		voltorb, electrode, exeggcute, exeggutor, cubone, marowak, hitmonlee, hitmonchan, lickitung,
		koffing, weezing, rhyhorn, rhydon, chansey, tangela, kangaskhan, horsea, seadra, goldeen, seaking,
		staryu, starmie, mrmime, scyther, jynx, electabuzz, magmar, pinsir, tauros, magikarp, gyarados,
		lapras, ditto, eevee, vaporeon, jolteon, flareon, porygon, omanyte, omastar, kabuto, kabutops,
		aerodactyl, snorlax, articuno, zapdos, moltres, dratini, dragonair, dragonite, mewtwo, mew,
		chikorita, bayleef, meganium, cyndaquil, quilava, typhlosion, totodile, croconaw, feraligatr,
		sentret, furret, hoothoot, noctowl, ledyba, ledian, spinarak, ariados, crobat, chinchou, lanturn,
		pichu, cleffa, igglybuff, togepi, togetic, natu, xatu, mareep, flaaffy, ampharos, bellossom,
		marill, azumarill, sudowoodo, politoed, hoppip, skiploom, jumpluff, aipom, sunkern, sunflora,
		yanma, wooper, quagsire, espeon, umbreon, murkrow, slowking, misdreavus, unown, wobbuffet,
		girafarig, pineco, forretress, dunsparce, gligar, steelix, snubbull, granbull, qwilfish, scizor,
		shuckle, heracross, sneasel, teddiursa, ursaring, slugma, magcargo, swinub, piloswine, corsola,
		remoraid, octillery, delibird, mantine, skarmory, houndour, houndoom, kingdra, phanpy, donphan,
		porygon2, stantler, smeargle, tyrogue, hitmontop, smoochum, elekid, magby, miltank, blissey,
		raikou, entei, suicune, larvitar, pupitar, tyranitar, lugia, hooh, celebi
	};
}

std::vector<random_encounter> LoadMapProfile() {
	return std::vector<random_encounter> {
		g1mC,	g1mD,	g1mE,	g2m5,	g2m6,	g3m2,	g3m3,	g3m5,	g3m6,	g3m7,
		g3m8,	g3m9,	g3mA,	g3mB,	g3mC,	g3mD,	g3mE,	g3mF,	g3m16,	g3m1B,
		g3m1D,	g3m1E,	g3m1F,	g3m20,	g3m21,	g3m2C,	g3m31,	g3m32,	g3m33,	g3m34, 
		g3m35,	g3m36,	g3m37,	g3m38,	g3m39,	g3m3A,	g3m3B,	g3m3C,	g3m3D,	g3m3E,
		g3m3F,	g3m40,	g3m41,	g3m42,	g3m43,	g3m44,	g3m45,	g3m46,	g3m47,	g3m49,
		g3m4A,	g3m4B,	g3m4C,	g3m4E,	g3m4F,	g3m52,	g4m9,	g5m8,	g5m9,	g5mA,
		g6m5,	g6m6,	g6m7,	g6m8,	g7mC,	g7mD,	g7mE,	g7mF,	g7m10,	g7m11,
		g8m6,	g9m5,	g9m6,	gAm1,	gAm2,	gAm3,	gAm4,	gAm5,	gBm1,	gCm1,
		gCm2,	gCm3,	gDm1,	gDm2,	gEm1,	gFm1,	gFm2,	g11m1,	g11m2,	g11m3,
		g11m4,	g11m5,	g12m1,	g12m2,	g13m1,	g13m2,	g15m1,	g15m2,	g15m3,	g15m4,
		g16m1,	g16m2,	g16m3,	g17m1,	g17m2,	g17m3,	g18m1,	g18m2,	g18m3,	g18m4,
		g19m1,	g1Am1,	g1Am2, g1Am3
	};
}

void DisplayRandomPokemon(HWND hWnd, byte id) {
	random_pokemon selected = { 0 };
	std::vector<random_pokemon> pokemon = LoadPokemonProfile();
	std::vector<std::wstring> names = GetTagNames();
	
	for (random_pokemon p : pokemon) {
		if (p.pokemon == id) {
			selected = p;
			break;
		}
	}

	if (selected.pokemon != 0) {
		SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_SETCURSEL, selected.level_min - 1, NULL);
		SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_SETCURSEL, selected.level_max - 1, NULL);
		
		if (selected.morning == 1) {
			SendMessage(GetDlgItem(hWnd, CHB_MOR), BM_SETCHECK, BST_CHECKED, NULL);
		}
		else {
			SendMessage(GetDlgItem(hWnd, CHB_MOR), BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		if (selected.day == 1) {
			SendMessage(GetDlgItem(hWnd, CHB_DAY), BM_SETCHECK, BST_CHECKED, NULL);
		}
		else {
			SendMessage(GetDlgItem(hWnd, CHB_DAY), BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		if (selected.night == 1) {
			SendMessage(GetDlgItem(hWnd, CHB_NGT), BM_SETCHECK, BST_CHECKED, NULL);
		}
		else {
			SendMessage(GetDlgItem(hWnd, CHB_NGT), BM_SETCHECK, BST_UNCHECKED, NULL);
		}

		for (int i = 0; i < selected.tags.size(); i++) {
			if (selected.tags[i] == 1) {
				SendMessage(GetDlgItem(hWnd, LB_TAGS), LB_ADDSTRING, 0, (LPARAM)(names[i].c_str()));
			}
		}
	}
	else {
		SendMessage(GetDlgItem(hWnd, CHB_MOR), BM_SETCHECK, BST_UNCHECKED, NULL);
		SendMessage(GetDlgItem(hWnd, CHB_DAY), BM_SETCHECK, BST_UNCHECKED, NULL);
		SendMessage(GetDlgItem(hWnd, CHB_NGT), BM_SETCHECK, BST_UNCHECKED, NULL);
	}

}

void DisplayRandomMap(HWND hWnd, HTREEITEM hti) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	random_encounter selected = { 0 };
	std::vector<random_encounter> map = LoadMapProfile();
	std::vector<std::wstring> names = GetTagNames();
	byte group = 0;
	byte id = 0;

	SendMessage(GetDlgItem(hWnd, LB_TAGS), LB_RESETCONTENT, NULL, NULL);

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	id = (byte)it.lParam;

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	group = (byte)it.lParam;

	for (random_encounter m : map) {
		if (m.map_group == group && m.map_id == id) {
			selected = m;
			break;
		}
	}

	SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_SETCURSEL, selected.level_min - 1, NULL);
	SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_SETCURSEL, selected.level_max - 1, NULL);

	for (int i = 0; i < selected.tags.size(); i++) {
		if (CheckBit(selected.tags[i], 7) == 1 && selected.tags[i]%128 > 0) {
			SendMessage(GetDlgItem(hWnd, LB_EXCLUSIVES), LB_ADDSTRING, 0, (LPARAM)(names[i].c_str()));
		}
		if (CheckBit(selected.tags[i], 7) == 0 && selected.tags[i] > 0) {
			SendMessage(GetDlgItem(hWnd, LB_TAGS), LB_ADDSTRING, 0, (LPARAM)(names[i].c_str()));
		}
	}
}

std::vector<random_pokemon> GeneratePokemonList(HWND hWnd) {
	std::vector<random_pokemon> profile = LoadPokemonProfile();
	std::vector<random_pokemon> list;
	bool added = false;
	bool b = false;

	for (random_pokemon p : profile) {

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_MOR), BM_GETCHECK, NULL, NULL));
		if (p.morning == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_DAY), BM_GETCHECK, NULL, NULL));
		if (p.day == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_NGT), BM_GETCHECK, NULL, NULL));
		if (p.night == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_GRASSLANDS), BM_GETCHECK, NULL, NULL));
		if (p.tags[10] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_FOREST), BM_GETCHECK, NULL, NULL));
		if (p.tags[11] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_FIELD), BM_GETCHECK, NULL, NULL));
		if (p.tags[9] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_SHORE), BM_GETCHECK, NULL, NULL));
		if (p.tags[2] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_SALT), BM_GETCHECK, NULL, NULL));
		if (p.tags[3] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_FRESH), BM_GETCHECK, NULL, NULL));
		if (p.tags[4] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_RARE), BM_GETCHECK, NULL, NULL));
		if (p.tags[0] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_LEGEND), BM_GETCHECK, NULL, NULL));
		if (p.tags[1] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_CAVE), BM_GETCHECK, NULL, NULL));
		if (p.tags[5] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_MOUNTAIN), BM_GETCHECK, NULL, NULL));
		if (p.tags[6] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_URBAN), BM_GETCHECK, NULL, NULL));
		if (p.tags[7] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_RUINS), BM_GETCHECK, NULL, NULL));
		if (p.tags[8] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_HOT), BM_GETCHECK, NULL, NULL));
		if (p.tags[12] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_COLD), BM_GETCHECK, NULL, NULL));
		if (p.tags[13] == true && b == true) {
			added = true;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_ELECTRIC), BM_GETCHECK, NULL, NULL));
		if (p.tags[14] == true && b == true) {
			added = true;
		}

		if (p.level_min < SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_GETCURSEL, NULL, NULL) + 1 &&
			p.level_max < SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_GETCURSEL, NULL, NULL) + 1) {
			added = false;
		}

		if (p.level_min > SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_GETCURSEL, NULL, NULL) + 1 &&
			p.level_max > SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_GETCURSEL, NULL, NULL) + 1) {
			added = false;
		}

		b = (BST_CHECKED == SendMessage(GetDlgItem(hWnd, CHB_LEGEND), BM_GETCHECK, NULL, NULL));
		if (p.tags[1] == true && b == false) {
			added = false;
		}

		if (added == true) {
			list.push_back(p);
		}
		added = false;
	}

	return list;
}

std::vector<random_pokemon> GGeneratePokemonList(random_encounter enc, byte bit) {
	std::vector<random_pokemon> profile = LoadPokemonProfile();
	std::vector<random_pokemon> list;
	bool added = false;
	bool b = false;

	for (random_pokemon p : profile) {

		b = (p.tags[10] == CheckBit(enc.tags[10], bit));
		if (p.tags[10] == true && b == true) {
			added = true;
		}

		b = (p.tags[11] == CheckBit(enc.tags[11], bit));
		if (p.tags[11] == true && b == true) {
			added = true;
		}

		b = (p.tags[9] == CheckBit(enc.tags[9], bit));
		if (p.tags[9] == true && b == true) {
			added = true;
		}

		b = (p.tags[2] == CheckBit(enc.tags[2], bit));
		if (p.tags[2] == true && b == true) {
			added = true;
		}

		b = (p.tags[3] == CheckBit(enc.tags[3], bit));
		if (p.tags[3] == true && b == true) {
			added = true;
		}

		b = (p.tags[4] == CheckBit(enc.tags[4], bit));
		if (p.tags[4] == true && b == true) {
			added = true;
		}

		b = (p.tags[0] == enc.tags[0]);
		if (p.tags[0] == true && b == true) {
			added = true;
		}

		b = (p.tags[5] == CheckBit(enc.tags[5], bit));
		if (p.tags[5] == true && b == true) {
			added = true;
		}

		b = (p.tags[6] == CheckBit(enc.tags[6], bit));
		if (p.tags[6] == true && b == true) {
			added = true;
		}

		b = (p.tags[7] == CheckBit(enc.tags[7], bit));
		if (p.tags[7] == true && b == true) {
			added = true;
		}

		b = (p.tags[8] == CheckBit(enc.tags[8], bit));
		if (p.tags[8] == true && b == true) {
			added = true;
		}

		b = (p.tags[12] == CheckBit(enc.tags[12], bit));
		if (p.tags[12] == true && b == true) {
			added = true;
		}

		b = (p.tags[13] == CheckBit(enc.tags[13], bit));
		if (p.tags[13] == true && b == true) {
			added = true;
		}

		b = (p.tags[14] == CheckBit(enc.tags[14], bit));
		if (p.tags[14] == true && b == true) {
			added = true;
		}

		if (p.level_min < enc.level_min && p.level_max < enc.level_max) {
			added = false;
		}

		if (p.level_min > enc.level_min && p.level_max > enc.level_max) {
			added = false;
		}

		b = (p.tags[1] == enc.tags[1]);
		if (p.tags[1] == true && b == false) {
			added = false;
		}

		if (added == true) {
			list.push_back(p);
		}
		added = false;
	}

	return list;
}

std::vector<random_pokemon> GeneratePokemonList(random_encounter enc, byte bit) {
	std::vector<random_pokemon> profile = LoadPokemonProfile();
	std::vector<random_pokemon> list;
	bool added = false;
	bool b = false;
	unsigned int size = tag_names.size();

	for (random_pokemon p : profile) {

		for (unsigned int i = 0; i < size; i++) {
			bool exclusive = CheckBit(enc.tags[i], 7);
			if (exclusive == 1) {//Check to see if tag is exclusive
				if (p.tags[i] == 1 && CheckBit(enc.tags[i], bit) == 0) {
					added = false;
					break;
				}
			}
			else {//Check for Non-exclusive tags
				if (p.tags[i] == 1 && CheckBit(enc.tags[i], bit) == 1) {
					added = true;
				}
			}
		}

		if (p.level_min < enc.level_min && p.level_max < enc.level_max) {
			added = false;
		}

		if (p.level_min > enc.level_min && p.level_max > enc.level_max) {
			added = false;
		}

		if (added == true) {
			list.push_back(p);
		}
		added = false;
	}

	return list;
}

void RandomizeEncounters(HWND hWnd) {
	std::vector<random_pokemon> pokemon = GeneratePokemonList(hWnd);
	int size = pokemon.size();
	int min = SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_GETCURSEL, NULL, NULL) + 1;
	int max = SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_GETCURSEL, NULL, NULL) + 1;
	int temp_min = 0;
	int temp_max = 0;
	random_pokemon p;

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution<int> dist_p(0, size - 1);
	std::uniform_int_distribution<int> dist_l(1, 100);


	for (int i = 0; i < 7; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		while (p.morning == false) {
			p = pokemon[dist_p(gen)];
		}

		if (p.level_min > min) temp_min = p.level_min; 
		if (p.level_max < max) temp_max = p.level_max;
		if (min > max) temp_min = temp_max;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });

		SendMessage(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), CB_SETCURSEL, (WPARAM)p.pokemon - 1, 0);
		SendMessage(GetDlgItem(hWnd, CB_MOR_LVL_1 + i), CB_SETCURSEL, (WPARAM)dist_l(gen) - 1, 0);
	}

	for (int i = 0; i < 7; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		while (p.day == false) {
			p = pokemon[dist_p(gen)];
		}

		if (p.level_min > min) temp_min = p.level_min;
		if (p.level_max < max) temp_max = p.level_max;
		if (min > max) temp_min = temp_max;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });

		SendMessage(GetDlgItem(hWnd, CB_DAY_POKE_1 + i), CB_SETCURSEL, (WPARAM)p.pokemon - 1, 0);
		SendMessage(GetDlgItem(hWnd, CB_DAY_LVL_1 + i), CB_SETCURSEL, (WPARAM)dist_l(gen) - 1, 0);
	}

	for (int i = 0; i < 7; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		while (p.night == false) {
			p = pokemon[dist_p(gen)];
		}

		if (p.level_min > min) temp_min = p.level_min;
		if (p.level_max < max) temp_max = p.level_max;
		if (min > max) temp_min = temp_max;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });

		SendMessage(GetDlgItem(hWnd, CB_NGT_POKE_1 + i), CB_SETCURSEL, (WPARAM)p.pokemon - 1, 0);
		SendMessage(GetDlgItem(hWnd, CB_NGT_LVL_1 + i), CB_SETCURSEL, (WPARAM)dist_l(gen) - 1, 0);
	}

}

int RandomizeGrassEntry(std::vector<byte>& data, random_encounter enc) {
	unsigned int johto_grass = GetAddress(ADD_JOHTO_GRASS);
	unsigned int kanto_grass = GetAddress(ADD_KANTO_GRASS);
	unsigned int cur = johto_grass;
	std::vector<random_pokemon> pokemon = GeneratePokemonList(enc, 0);
	random_pokemon p;
	int size_p = pokemon.size();
	int min = (int)enc.level_min;
	int max = (int)enc.level_max;

	if (size_p < 1) return -2;//If No valid Entries for Map Return out

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution<int> dist_p(0, size_p - 1);
	std::uniform_int_distribution<int> dist_l(1, 100);

	while (data[cur] != enc.map_group || data[cur + 1] != enc.map_id) {
		if (data[cur] == 0xFF) {
			cur = kanto_grass;
			break;
		}
		
		cur += 47;
	}

	while (data[cur] != enc.map_group || data[cur + 1] != enc.map_id) {
		if (data[cur] == 0xFF) return -1;//If Map not Found in Encounter Table
		cur += 47;
	}
	
	cur += 5;

	for (int i = 0; i < 7; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		while (p.morning == false) {
			p = pokemon[dist_p(gen)];
		}

		if (p.level_min > min) temp_min = p.level_min;
		if (p.level_max < max) temp_max = p.level_max;
		if (temp_min > temp_max) temp_min = temp_max - 1;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });
		
		data[cur++] = (byte)dist_l(gen);
		data[cur++] = (byte)p.pokemon;
	}

	for (int i = 0; i < 7; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		while (p.day == false) {
			p = pokemon[dist_p(gen)];
		}

		if (p.level_min > min) temp_min = p.level_min;
		if (p.level_max < max) temp_max = p.level_max;
		if (temp_min > temp_max) temp_min = temp_max - 1;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });
		
		data[cur++] = (byte)dist_l(gen);
		data[cur++] = (byte)p.pokemon;
	}

	for (int i = 0; i < 7; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		while (p.night == false) {
			p = pokemon[dist_p(gen)];
		}

		if (p.level_min > min) temp_min = p.level_min;
		if (p.level_max < max) temp_max = p.level_max;
		if (temp_min > temp_max) temp_min = temp_max - 1;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });
		
		data[cur++] = (byte)dist_l(gen);
		data[cur++] = (byte)p.pokemon;
	}

	return 0;
}

int RandomizeSurfEntry(std::vector<byte>& data, random_encounter enc) {
	unsigned int johto_surf = GetAddress(ADD_JOHTO_SURF);
	unsigned int kanto_surf = GetAddress(ADD_KANTO_SURF);
	unsigned int cur = johto_surf;
	std::vector<random_pokemon> pokemon = GeneratePokemonList(enc, 1);
	random_pokemon p;
	int size_p = pokemon.size();
	int min = (int)enc.level_min;
	int max = (int)enc.level_max;

	if (size_p < 1) return -2;//If No valid Entries for Map Return out

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution<int> dist_p(0, size_p - 1);
	std::uniform_int_distribution<int> dist_l(1, 100);

	while (data[cur] != enc.map_group || data[cur + 1] != enc.map_id) {
		if (data[cur] == 0xFF) {
			cur = kanto_surf;
			break;
		}

		cur += 9;
	}

	while (data[cur] != enc.map_group || data[cur + 1] != enc.map_id) {
		if (data[cur] == 0xFF) return -1;//If Map not Found in Encounter Table
		cur += 9;
	}

	cur += 3;

	for (int i = 0; i < 3; i++) {
		int temp_min = min;
		int temp_max = max;
		p = pokemon[dist_p(gen)];

		if (p.level_min > min) temp_min = p.level_min;
		if (p.level_max < max) temp_max = p.level_max;
		if (min > max) temp_min = temp_max - 1;
		dist_l.param(std::uniform_int_distribution<int>::param_type{ temp_min, temp_max });

		data[cur++] = (byte)dist_l(gen);
		data[cur++] = (byte)p.pokemon;
	}

	return 0;
}

int RandomizeTables(std::vector<byte>& data) {
	std::vector<random_encounter> maps = LoadMapProfile();
	int size_m = maps.size();

	for (int i = 0; i < size_m; i++) {
		RandomizeGrassEntry(data, maps[i]);
		RandomizeSurfEntry(data, maps[i]);
	}

	return 0;
}

std::vector<std::wstring> GetTagNames() {
	return tag_names;
}