#include "trainertools.h"

#include "address.h"
#include "guicodes.h"
#include "pointertools.h"
#include "interpreter.h"
#include "main.h"

void FillTrainerTree(std::vector<byte>& data, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_TRAINERS);
	byte* pointer = new byte[3];
	unsigned int train_add = GetAddress(ADD_TRAINER_TABLE);
	unsigned int cur_address = 0;
	unsigned int end_address = 0;
	game_string name;
	name.characters = 0;
	int trainer_code = 0;
	int type_quantity = GetNumberOfTableElements(train_add, data);
	
	pointer[2] = FindBank(train_add);
	pointer[0] = data[train_add];
	pointer[1] = data[train_add + 1];

	cur_address = PointerToAddress(pointer);

	GetTrainerTypes(data, hWndtv);
	HTREEITEM hti = TreeView_GetFirstVisible(hWndtv);
	HTREEITEM htr = TreeView_GetFirstVisible(hWndtv);



	for (int i = 1; i < type_quantity + 1; i++) {
		pointer[2] = FindBank(train_add);
		pointer[0] = data[train_add + (2 * (i-1))];
		pointer[1] = data[train_add + (2 * (i-1)) + 1];
		cur_address = PointerToAddress(pointer);
		//Find the end of the last trainers data, by going to end of ROM bank and iterating backwards to the end
		if (i == type_quantity) {
			
			pointer[2] = pointer[2] + 1;
			pointer[0] = 0x00;
			pointer[1] = 0x40;

			end_address = PointerToAddress(pointer) - 1;

			while (data[end_address] != (byte)0xFF) {
				end_address--;
			}
		}//Find the end of data for current trainer type by finding start of next trainer type data
		else {
			pointer[2] = FindBank(train_add);
			pointer[0] = data[train_add + (2*i)];
			pointer[1] = data[train_add + (2*i) + 1];
			end_address = PointerToAddress(pointer);
		}
		//Handle duplicates in trainer types (eg. Elite 4 Will is the same data for Pokemon Prof.)
		if (cur_address == end_address) {
			pointer[2] = FindBank(train_add);
			pointer[0] = data[train_add + (2 * (i+1))];
			pointer[1] = data[train_add + (2 * (i+1)) + 1];
			end_address = PointerToAddress(pointer);
		}
		

		while (cur_address < end_address) {
			trainer_code++;

			name = GetGameString(data, cur_address, 0x50);
			hti = InsertTreeItem(hWndtv, (LPWSTR)name.wstring.c_str(), 2, hti, htr, NULL, (LPARAM) trainer_code);
			cur_address += name.characters;
			
			while (data[cur_address] != (byte)0xFF) {
				cur_address++;
			}
			
			cur_address++;
		
		}

		trainer_code = 0;
		if(i != type_quantity) htr = TreeView_GetNextItem(hWndtv, hti, TVGN_NEXTVISIBLE);
	}

	delete pointer;
}

void GetTrainerTypes(std::vector<byte>& data, HWND hWndtv) {
	game_string name;
	unsigned int add = GetAddress(ADD_TRNR_STR_PNTR);
	HTREEITEM hti = TVI_FIRST;
	int type_quantity = GetNumberOfTableElements(GetAddress(ADD_TRAINER_TABLE), data);
	
	byte* pointer = new byte[3];

	pointer[2] = data[add - 1];
	pointer[1] = data[add + 1];
	pointer[0] = data[add];

	add = PointerToAddress(pointer);

	TreeView_DeleteAllItems(hWndtv);

	for (int i = 0; i < type_quantity; i++) {
		name = GetGameString(data, add, 0x50);
		hti = InsertTreeItem(hWndtv, (LPWSTR)name.wstring.c_str(), 1, hti, NULL, NULL, (LPARAM)i + 1);
		add += name.characters + 1;
	}
	delete pointer;
}

void GetTrainerData(std::vector<byte>& data, HTREEITEM item, HWND hWnd) {
	HWND hWndtv = GetDlgItem(hWnd, TV_TRAINERS);
	HTREEITEM hti = item;
	byte* pointer = new byte[3];
	unsigned int address = GetAddress(ADD_TRAINER_TABLE);
	int cur_address = 0;
	game_string name;
	trainer_pokemon poke = { 0 };
	name.characters = 0;
	int exp = 0;
	int exp_total = 0;
	byte trainer = 0;
	byte type = 0;
	byte control = 0;

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(hWndtv, &it);
	trainer = (byte)it.lParam;

	hti = TreeView_GetParent(hWndtv, hti);
	it.hItem = hti;
	TreeView_GetItem(hWndtv, &it);
	type = (byte)it.lParam;

	pointer[2] = FindBank(address);
	pointer[0] = data[address + (2 * (type -1))];
	pointer[1] = data[address + (2 * (type - 1)) + 1];

	cur_address = PointerToAddress(pointer);

	for (int i = 1; i < trainer; i++) {
		while (data[cur_address] != (byte)0xFF) {
			cur_address++;
		}
		cur_address++;
	}

	name = GetGameString(data, cur_address, 0x50);
	cur_address += name.characters + 1;

	control = data[cur_address];

	SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_SETCURSEL, (WPARAM)control, 0);

	cur_address++;

	for (int i = 0; i < 6; i++) {//Reset the EXP Labels
		SetDlgItemText(hWnd, STC_POKE_EXP1 + i, L"");
	}

	for (int i = 0; i < 6; i++) {

		if (data[cur_address] == 0xFF) {
			SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_SETCURSEL, (WPARAM)0, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_SETCURSEL, (WPARAM)0, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1 + (i * 5)), CB_SETCURSEL, (WPARAM)0, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2 + (i * 5)), CB_SETCURSEL, (WPARAM)0, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3 + (i * 5)), CB_SETCURSEL, (WPARAM)0, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4 + (i * 5)), CB_SETCURSEL, (WPARAM)0, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1 + (i * 5)), CB_SETCURSEL, (WPARAM)0, 0);
		}

		if (data[cur_address] != 0xFF) {
			poke = GetTrainerPokemon(data, cur_address, control);
			SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_SETCURSEL, (WPARAM)poke.level, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_SETCURSEL, (WPARAM)poke.pokemon, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1 + (i * 5)), CB_SETCURSEL, (WPARAM)poke.move1, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2 + (i * 5)), CB_SETCURSEL, (WPARAM)poke.move2, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3 + (i * 5)), CB_SETCURSEL, (WPARAM)poke.move3, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4 + (i * 5)), CB_SETCURSEL, (WPARAM)poke.move4, 0);
			SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1 + (i * 5)), CB_SETCURSEL, (WPARAM)poke.item, 0);

			exp = GetBaseExp(data, poke.pokemon) * (int)poke.level * 1.5 / 7;
			SetDlgItemText(hWnd, STC_POKE_EXP1 + i, (std::to_wstring(exp) + L"  XP").c_str());
			exp_total += exp;
		}

	}

	SetDlgItemText(hWnd, STC_EXP_TOTAL, (std::to_wstring(exp_total) + L"  XP").c_str());

	DisableTrainerControls(hWnd, control);

	SetDlgItemText(hWnd, EB_TRAINER_NAME, (LPWSTR)name.wstring.c_str());
	SetDlgItemText(hWnd, STC_TRAINER_CODE, (LPWSTR)IntToHexString(trainer).c_str());
	SetDlgItemText(hWnd, STC_TRAINER_TYPE, (LPWSTR)IntToHexString(type).c_str());
}

trainer_pokemon GetTrainerPokemon(std::vector<byte>& data, int& address, byte control) {
	trainer_pokemon poke = { 0 };

	switch (control) {
	case 0x00:
		poke.level = data[address++];
		poke.pokemon = data[address++];
		break;
	case 0x01:
		poke.level = data[address++];
		poke.pokemon = data[address++];
		poke.move1 = data[address++];
		poke.move2 = data[address++];
		poke.move3 = data[address++];
		poke.move4 = data[address++];
		break;
	case 0x02:
		poke.level = data[address++];
		poke.pokemon = data[address++];
		poke.item = data[address++];

		break;
	case 0x03:
		poke.level = data[address++];
		poke.pokemon = data[address++];
		poke.item = data[address++];
		poke.move1 = data[address++];
		poke.move2 = data[address++];
		poke.move3 = data[address++];
		poke.move4 = data[address++];
		break;
	}

	return poke;

}

void ChangeTrainerData(std::vector<byte>& data, HTREEITEM hti, HWND hWnd) {
	std::vector<byte> copy;
	trainer_pokemon poke = { 0 };
	unsigned int address = GetAddress(ADD_TRAINER_TABLE);

	wchar_t name[10] = { L'\0' };
	GetWindowText(GetDlgItem(hWnd, EB_TRAINER_NAME), name, 10);
	int type_quantity = GetNumberOfTableElements(address, data);

	int cur_address = address;
	int copy_point = 0;
	int end_address = address;
	byte* pointer = new byte[3];
	
	int new_size = 0;
	int old_size = 0;

	byte trainer = 0;
	byte type = 0;
	byte control = (byte)SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_GETCURSEL, 0, 0);

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;

	TreeView_GetItem(GetDlgItem(hWnd, TV_TRAINERS), &it);
	trainer = (byte)it.lParam;

	hti = TreeView_GetParent(GetDlgItem(hWnd, TV_TRAINERS), hti);
	it.hItem = hti;
	TreeView_GetItem(GetDlgItem(hWnd, TV_TRAINERS), &it);
	type = (byte)it.lParam;

	
	//Find start of Trainer's Class Table
	pointer[2] = FindBank(address);
	pointer[0] = data[address + ((type - 1)* 2)];
	pointer[1] = data[address + ((type - 1) * 2) + 1];

	cur_address = PointerToAddress(pointer);
	copy_point = cur_address;

	//Iterate through Class data to get to requested Trainer
	for (int i = 0; i < trainer; i++) {
		cur_address = copy_point;
		while (data[copy_point] != 0xFF) copy_point++;
		copy_point++;
	}
	copy_point--;

	old_size = copy_point - cur_address;

	pointer[2] = pointer[2] + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;

	end_address = PointerToAddress(pointer) - 1;

	copy = CopyData(data, copy_point, end_address);

	//Insert Trainer Name
	for (wchar_t c : name) {
		if (c != L'\0') {
			data[cur_address] = TextToHex(c);
			cur_address++;
			new_size++;
		}
	}

	//End Marker for Name Text
	data[cur_address] = 0x50;
	cur_address++;
	new_size++;
	//Control Byte
	data[cur_address] = control;
	cur_address++;
	new_size++;

	if (control == 0x03) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				new_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				new_size++;
			}
			//Item
			poke.item = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.item;
				cur_address++;
				new_size++;
			}
			//Move 1
			poke.move1 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move1;
				cur_address++;
				new_size++;
			}
			//Move 2
			poke.move2 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move2;
				cur_address++;
				new_size++;
			}
			//Move 3
			poke.move3 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move3;
				cur_address++;
				new_size++;
			}
			//Move 4
			poke.move4 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move4;
				cur_address++;
				new_size++;
			}

		}
	}

	if (control == 0x02) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				new_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				new_size++;
			}
			//Item
			poke.item = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.item;
				cur_address++;
				new_size++;
			}
		}
	}

	if (control == 0x01) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				new_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				new_size++;
			}
			//Move 1
			poke.move1 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move1;
				cur_address++;
				new_size++;
			}
			//Move 2
			poke.move2 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move2;
				cur_address++;
				new_size++;
			}
			//Move 3
			poke.move3 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move3;
				cur_address++;
				new_size++;
			}
			//Move 4
			poke.move4 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move4;
				cur_address++;
				new_size++;
			}
		}
	}

	if (control == 0x00) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				new_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				new_size++;
			}
		}
	}

	copy = CopyData(copy, 0, copy.size() - new_size);

	PasteData(data, cur_address, copy);

	copy = CopyData(data, address + (type * 2), address + (type_quantity * 2));
	copy = UpdatePointerTable(copy, (unsigned short)(new_size - old_size));

	PasteData(data, address + (type * 2), copy);

}

void AddTrainerData(std::vector<byte>& data, HTREEITEM hti, HWND hWnd) {
	std::vector<byte> copy;
	trainer_pokemon poke = { 0 };

	wchar_t name[10] = { L'\0' };
	GetWindowText(GetDlgItem(hWnd, EB_TRAINER_NAME), name, 10);

	unsigned int address = GetAddress(ADD_TRAINER_TABLE);
	int cur_address = address;
	int end_address = address;
	byte* pointer = new byte[3];

	int data_size = 0;
	int type_quantity = GetNumberOfTableElements(address, data);

	//byte trainer = 0;
	byte type = 0;
	byte control = (byte)SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_GETCURSEL, 0, 0);

	TVITEM it;
	it.mask = TVIF_PARAM;
	it.hItem = hti;
	it.lParam = NULL;
	//Get Current Selected Tree Item
	TreeView_GetItem(GetDlgItem(hWnd, TV_TRAINERS), &it);
	//Find the Parent
	hti = TreeView_GetParent(GetDlgItem(hWnd, TV_TRAINERS), hti);
	it.hItem = hti;
	TreeView_GetItem(GetDlgItem(hWnd, TV_TRAINERS), &it);
	type = (byte)it.lParam;
	type++;

	if (type < type_quantity + 1) {
		pointer[2] = FindBank(address);
		pointer[0] = data[address + ((type - 1) * 2)];
		pointer[1] = data[address + ((type - 1) * 2) + 1];
		cur_address = PointerToAddress(pointer);
	}
	else {
		pointer[2] = FindBank(address) + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;
		cur_address = PointerToAddress(pointer) - 1;
		while (data[cur_address] != 0xFF) cur_address--;
		cur_address += 1;
	}

	pointer[2] = FindBank(address) + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;
	end_address = PointerToAddress(pointer) - 1;

	copy = CopyData(data, cur_address, end_address);

	//Insert Trainer Name
	for (wchar_t c : name) {
		if (c != L'\0') {
			data[cur_address] = TextToHex(c);
			cur_address++;
			data_size++;
		}
	}

	//End Marker for Name Text
	data[cur_address] = 0x50;
	cur_address++;
	data_size++;
	//Control Byte
	data[cur_address] = control;
	cur_address++;
	data_size++;

	if (control == 0x03) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				data_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				data_size++;
			}
			//Item
			poke.item = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.item;
				cur_address++;
				data_size++;
			}
			//Move 1
			poke.move1 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move1;
				cur_address++;
				data_size++;
			}
			//Move 2
			poke.move2 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move2;
				cur_address++;
				data_size++;
			}
			//Move 3
			poke.move3 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move3;
				cur_address++;
				data_size++;
			}
			//Move 4
			poke.move4 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move4;
				cur_address++;
				data_size++;
			}

		}
	}

	if (control == 0x02) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				data_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				data_size++;
			}
			//Item
			poke.item = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.item;
				cur_address++;
				data_size++;
			}
		}
	}

	if (control == 0x01) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				data_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				data_size++;
			}
			//Move 1
			poke.move1 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move1;
				cur_address++;
				data_size++;
			}
			//Move 2
			poke.move2 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move2;
				cur_address++;
				data_size++;
			}
			//Move 3
			poke.move3 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move3;
				cur_address++;
				data_size++;
			}
			//Move 4
			poke.move4 = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4 + (i * 5)), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.move4;
				cur_address++;
				data_size++;
			}
		}
	}

	if (control == 0x00) {
		//Pokemon Data
		for (int i = 0; i < 6; i++) {
			//Level
			poke.level = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_LVL_1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.level;
				cur_address++;
				data_size++;
			}
			//Pokemon
			poke.pokemon = (byte)SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1 + i), CB_GETCURSEL, 0, 0);
			if (poke.level != 0x00) {
				data[cur_address] = poke.pokemon;
				cur_address++;
				data_size++;
			}
		}
	}

	data[cur_address] = 0xFF;
	data_size++;
	cur_address++;

	copy = CopyData(copy, 0, copy.size() - data_size - 1);

	PasteData(data, cur_address, copy);

	copy = CopyData(data, address + ((type-1) * 2), address + (type_quantity * 2));
	copy = UpdatePointerTable(copy, (unsigned short)data_size);

	PasteData(data, address + ((type-1) * 2), copy);

}

void DisableTrainerControls(HWND hWnd, int control) {

	switch (control) {
	case 0:
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_5), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_6), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_4), false);
		break;
	case 1:
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_5), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_6), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_4), true);
		break;
	case 2:
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_5), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_6), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_4), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_1), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_2), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_3), false);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_4), false);
		break;
	case 3:
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_5), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_ITEM_6), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_4), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_1), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_2), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_3), true);
		EnableWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_4), true);
		break;
	}
}

int GetBaseExp(std::vector<byte>& data,byte pokemon) {
	int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32);
	cur_address += 10;

	return (int) data[cur_address];
}