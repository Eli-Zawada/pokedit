#include "randomencounters.h"

#include "address.h"
#include "pointertools.h"
#include "profile.h"
#include "main.h"
#include "guicodes.h"

void DisplayRandomPokemon(HWND hWnd, byte id) {
	random_pokemon selected = { 0 };
	std::vector<random_pokemon> pokemon = GetPokemonProfile();
	std::vector<std::wstring> names = GetTagNames();

	SendMessage(GetDlgItem(hWnd, LB_TAGS), LB_RESETCONTENT, 0, 0);
	
	for (random_pokemon& p : pokemon) {
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
	std::vector<random_encounter> map = GetMapProfile();
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
	std::vector<random_pokemon> profile = GetPokemonProfile();
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

		if (p.level_min < SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_GETCURSEL, NULL, NULL) + 1 &&
			p.level_max < SendMessage(GetDlgItem(hWnd, CB_MIN_LVL), CB_GETCURSEL, NULL, NULL) + 1) {
			added = false;
		}

		if (p.level_min > SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_GETCURSEL, NULL, NULL) + 1 &&
			p.level_max > SendMessage(GetDlgItem(hWnd, CB_MAX_LVL), CB_GETCURSEL, NULL, NULL) + 1) {
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
	std::vector<random_pokemon> profile = GetPokemonProfile();
	std::vector<random_pokemon> list;
	bool added = false;
	bool b = false;
	unsigned int size = GetTagNames().size();

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
	std::vector<random_encounter> maps = GetMapProfile();
	int size_m = maps.size();

	for (int i = 0; i < size_m; i++) {
		RandomizeGrassEntry(data, maps[i]);
		RandomizeSurfEntry(data, maps[i]);
	}

	return 0;
}