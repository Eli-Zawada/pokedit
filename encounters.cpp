#include "encounters.h"

#include "address.h"
#include "guicodes.h"
#include "main.h"
#include "pointertools.h"

void FillEncountersTree(std::vector<byte>& data, HWND hWndtv) {
	byte* pointer = new byte[3];
	unsigned int map_add = GetAddress(ADD_MAP_HEADER_TABLE);
	unsigned int name_add = GetAddress(ADD_MAP_NAME_TABLE);
	unsigned int cur_address = 0;
	unsigned int next_group = 0;
	unsigned int end_address = 0;
	game_string name;
	name.characters = 0;
	int map_id = 0;
	int group_quantity = GetNumberOfTableElements(map_add, data);

	pointer[2] = FindBank(map_add);
	pointer[0] = data[map_add];
	pointer[1] = data[map_add + 1];

	cur_address = PointerToAddress(pointer);
	/////
	pointer[0] = data[map_add + 2];
	pointer[1] = data[map_add + 3];

	next_group = PointerToAddress(pointer);
	//////
	pointer[2] = data[cur_address];//Bank of Secondary Header
	pointer[0] = data[cur_address + 3];//Pointer to Secondary Header
	pointer[1] = data[cur_address + 4];//

	end_address = PointerToAddress(pointer);//**NOTE** The first Primary header's Secondary Header is NOT the first Secondary Header

	HTREEITEM hti = TVI_FIRST;

	TreeView_DeleteAllItems(hWndtv);

	for (int i = 0; i < group_quantity; i++) {
		hti = InsertTreeItem(hWndtv, (LPWSTR)(L"Map Group " + std::to_wstring(i+1)).c_str(), 1, hti, NULL, NULL, (LPARAM)i + 1);
	}

	hti = TreeView_GetFirstVisible(hWndtv);
	HTREEITEM htr = TreeView_GetFirstVisible(hWndtv);

	for (int i = 0; i < group_quantity + 1; i++) {
		int j = 1;
		while (cur_address < next_group && cur_address < end_address) {
			int temp = 0;//Placeholder for Secondary Header addresses

			pointer[2] = data[cur_address];//Bank of Secondary Header
			cur_address += 3;
			pointer[0] = data[cur_address];//Pointer to Secondary Header
			cur_address++;
			pointer[1] = data[cur_address];//

			temp = PointerToAddress(pointer);

			if (temp < end_address) end_address = temp;//Set the first Secondary Header as the end of Primary Headers

			cur_address++;

			name = GetMapName(data, name_add, data[cur_address]);

			hti = InsertTreeItem(hWndtv, (LPWSTR)name.wstring.c_str(), 2, hti, htr, NULL, (LPARAM)j);

			if (GrassSwarmCheck(data, i + 1, j) == true || SurfSwarmCheck(data, i + 1, j) == true) {
				hti = InsertTreeItem(hWndtv, (LPWSTR)(name.wstring + L" (Swarm)").c_str(), 2, hti, htr, NULL, (LPARAM)0);
			}

			j++;

			cur_address += 4;
		}

		if (i < group_quantity + 1 && cur_address < end_address) {
			pointer[0] = data[((i + 1) * 2) + map_add + 2];
			pointer[1] = data[((i + 1) * 2) + map_add + 3];

			next_group = PointerToAddress(pointer);

			htr = TreeView_GetNextItem(hWndtv, hti, TVGN_NEXTVISIBLE);
		}
	}
}

bool GrassSwarmCheck(std::vector<byte>& data, byte group, byte id) {
	unsigned int cur = GetAddress(ADD_SWARM_GRASS);
	bool match = false;
	while (data[cur] != 0xFF) {
		if (data[cur] == group && data[cur + 1] == id) {
			match = true;
			break;
		}
		cur += 47;//Encounter Table is a struct of 47 bytes
	}
	return match;
}

bool SurfSwarmCheck(std::vector<byte>& data, byte group, byte id) {
	unsigned int cur = GetAddress(ADD_SWARM_SURF);
	bool match = false;
	while (data[cur] != 0xFF) {
		if (data[cur] == group && data[cur + 1] == id) {
			match = true;
			break;
		}
		cur += 9;//Encounter Table is a struct of 9 bytes
	}
	return match;
}

void GetGrassEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	unsigned int j_address = GetAddress(ADD_JOHTO_GRASS);
	unsigned int k_address = GetAddress(ADD_KANTO_GRASS);
	int cur_address = j_address;
	byte map_group = 0;
	byte map_id = 0;
	bool found = false;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	map_id = (byte)it.lParam;

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	map_group = (byte)it.lParam;

	SetDlgItemText(hWnd, STC_ENCOUNTER_MAP, (LPWSTR)IntToHexString(map_group).c_str());
	SetDlgItemText(hWnd, STC_ENCOUNTER_INDEX, (LPWSTR)IntToHexString(map_id).c_str());

	while (found == false && data[cur_address] != 0xFF) {//Johto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 47;//Encounter Table is a struct of 47 bytes
		}
	}
	if (found == false) cur_address = k_address;
	while (found == false && data[cur_address] != 0xFF) {//Kanto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 47;//Encounter Table is a struct of 47 bytes
		}
	}

	if (found == true) {
		cur_address += 2;

		for (int i = 0; i < 3; i++) {//Morning
			SendMessage(GetDlgItem(hWnd, CB_MOR_RATE + i), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
			cur_address++;
		}


		for (int i = 0; i < 7; i++) {//Morning
			SendMessage(GetDlgItem(hWnd, CB_MOR_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
		for (int i = 0; i < 7; i++) {//Day
			SendMessage(GetDlgItem(hWnd, CB_DAY_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_DAY_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
		for (int i = 0; i < 7; i++) {//Night
			SendMessage(GetDlgItem(hWnd, CB_NGT_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_NGT_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
	}
	else {
		for (int i = 0; i < 45; i++) {
			SendMessage(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), CB_SETCURSEL, (WPARAM)-1, 0);
		}
	}

}

void GetGrassSwarmData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	int cur_address = GetAddress(ADD_SWARM_GRASS);
	byte map_group = 0;
	byte map_id = 0;
	bool found = false;
	bool swarm = false;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	map_id = (byte)it.lParam;

	if (map_id == 0x00) {
		hti = TreeView_GetPrevSibling(hWndtv, hti);
		it.hItem = hti;
		TreeView_GetItem(hWndtv, &it);
		map_id = (byte)it.lParam;
		swarm = true;
	}

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	map_group = (byte)it.lParam;

	SetDlgItemText(hWnd, STC_ENCOUNTER_MAP, (LPWSTR)IntToHexString(map_group).c_str());
	SetDlgItemText(hWnd, STC_ENCOUNTER_INDEX, (LPWSTR)IntToHexString(map_id).c_str());

	while (found == false && data[cur_address] != 0xFF) {//Swarm Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 47;//Encounter Table is a struct of 47 bytes
		}
	}

	if (found == true && swarm == true) {
		cur_address += 2;

		for (int i = 0; i < 3; i++) {//Morning
			SendMessage(GetDlgItem(hWnd, CB_MOR_RATE + i), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
			cur_address++;
		}


		for (int i = 0; i < 7; i++) {//Morning
			SendMessage(GetDlgItem(hWnd, CB_MOR_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
		for (int i = 0; i < 7; i++) {//Day
			SendMessage(GetDlgItem(hWnd, CB_DAY_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_DAY_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
		for (int i = 0; i < 7; i++) {//Night
			SendMessage(GetDlgItem(hWnd, CB_NGT_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_NGT_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
	}

}

void GetSurfEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	unsigned int j_address = GetAddress(ADD_JOHTO_SURF);
	unsigned int k_address = GetAddress(ADD_KANTO_SURF);
	int cur_address = j_address;
	byte map_group = 0;
	byte map_id = 0;
	bool found = false;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	map_id = (byte)it.lParam;

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	map_group = (byte)it.lParam;

	while (found == false && data[cur_address] != 0xFF) {//Johto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 9;//Encounter Table is a struct of 9 bytes
		}
	}
	if (found == false) cur_address = k_address;
	while (found == false && data[cur_address] != 0xFF) {//Kanto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 9;
		}
	}

	if (found == true) {
		cur_address += 2;

		SendMessage(GetDlgItem(hWnd, CB_SURF_RATE), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
		cur_address++;
		

		for (int i = 0; i < 3; i++) {
			SendMessage(GetDlgItem(hWnd, CB_SURF_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_SURF_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
	}
	else {
		for (int i = 0; i < 7; i++) {
			SendMessage(GetDlgItem(hWnd, CB_SURF_RATE + i), CB_SETCURSEL, (WPARAM)-1, 0);
		}
	}

}

void GetSurfSwarmData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	int cur_address = GetAddress(ADD_SWARM_SURF);
	byte map_group = 0;
	byte map_id = 0;
	bool found = false;
	bool swarm = false;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	map_id = (byte)it.lParam;

	if (map_id == 0x00) {
		hti = TreeView_GetPrevSibling(hWndtv, hti);
		it.hItem = hti;
		TreeView_GetItem(hWndtv, &it);
		map_id = (byte)it.lParam;
		swarm = true;
	}

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	map_group = (byte)it.lParam;

	while (found == false && data[cur_address] != 0xFF) {//Johto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 9;//Encounter Table is a struct of 9 bytes
		}
	}

	if (found == true && swarm == true) {
		cur_address += 2;

		SendMessage(GetDlgItem(hWnd, CB_SURF_RATE), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
		cur_address++;


		for (int i = 0; i < 3; i++) {
			SendMessage(GetDlgItem(hWnd, CB_SURF_LVL_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
			SendMessage(GetDlgItem(hWnd, CB_SURF_POKE_1 + i), CB_SETCURSEL, (WPARAM)data[cur_address] - 1, 0);
			cur_address++;
		}
	}
}

game_string GetMapName(std::vector<byte>& data, int name_add, int element) {
	byte* pointer = new byte[3];
	unsigned int cur_address = 0;
	
	pointer[2] = FindBank(name_add);
	pointer[0] = data[name_add + (4 * element) + 2];
	pointer[1] = data[name_add + (4 * element) + 3];

	cur_address = PointerToAddress(pointer);

	return GetGameString(data, cur_address, 0x50);
}

void ChangeGrassEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	unsigned int j_address = GetAddress(ADD_JOHTO_GRASS);
	unsigned int k_address = GetAddress(ADD_KANTO_GRASS);
	int cur_address = j_address;
	byte map_group = 0;
	byte map_id = 0;
	bool found = false;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	map_id = (byte)it.lParam;

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	map_group = (byte)it.lParam;

	while (found == false && data[cur_address] != 0xFF) {//Johto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 47;//Encounter Table is a struct of 47 bytes
		}
	}
	if (found == false) cur_address = k_address;
	while (found == false && data[cur_address] != 0xFF) {//Kanto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 47;//Encounter Table is a struct of 47 bytes
		}
	}

	if (found == true) {
		cur_address += 2;

		for (int i = 0; i < 3; i++) {//Encounter Rates
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_MOR_RATE + i), CB_GETCURSEL, 0, 0);
			cur_address++;
		}

		for (int i = 0; i < 7; i++) {//Morning
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_MOR_LVL_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
		}
		for (int i = 0; i < 7; i++) {//Day
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_DAY_LVL_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_DAY_POKE_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
		}
		for (int i = 0; i < 7; i++) {//Night
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_NGT_LVL_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_NGT_POKE_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
		}
	}
}

void ChangeSurfEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_ENCOUNTERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	unsigned int j_address = GetAddress(ADD_JOHTO_GRASS);
	unsigned int k_address = GetAddress(ADD_KANTO_GRASS);
	int cur_address = j_address;
	byte map_group = 0;
	byte map_id = 0;
	bool found = false;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	map_id = (byte)it.lParam;

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	map_group = (byte)it.lParam;

	while (found == false && data[cur_address] != 0xFF) {//Johto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 9;
		}
	}
	if (found == false) cur_address = k_address;
	while (found == false && data[cur_address] != 0xFF) {//Kanto Table
		if (data[cur_address] == map_group && data[cur_address + 1] == map_id) {
			found = true;
		}
		else {
			cur_address += 9;
		}
	}

	if (found == true) {
		cur_address += 2;

		data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_SURF_RATE), CB_GETCURSEL, 0, 0);
		cur_address++;

		for (int i = 0; i < 3; i++) {
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_SURF_LVL_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
			data[cur_address] = SendMessage(GetDlgItem(hWnd, CB_SURF_POKE_1 + i), CB_GETCURSEL, 0, 0) + 1;
			cur_address++;
		}
	}
}